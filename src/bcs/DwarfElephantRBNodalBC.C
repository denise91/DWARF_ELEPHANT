/**
 * This BC is required to use the RB method as it is provided by the
 * RB libMesh package. The RBNodalBC inherits from the NodalBC class. It
 * overwrites the function computeJacobian because for the RB method the
 * stiffness matrix is needed separated in its subdomain contributions. In
 * addition it overwrites the function computeResidual.
 */

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantRBNodalBC.h"
#include "MooseVariable.h"
#include "Assembly.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBNodalBC>()
{
  InputParameters params = validParams<NodalBC>();

  params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system.");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addParam<std::vector<unsigned int>>("ID_Fq",std::vector<unsigned int> {0},"ID of the load vector.");
  params.addParam<std::vector<unsigned int>>("ID_Aq",std::vector<unsigned int> {0}, "ID of the stiffness matrix.");
  params.addParam<unsigned int>("ID_Mq", 0 , "ID 0f the mass matrix.");
  params.addParam<bool>("compute_output",false,"Determines whether an output function is used or not");
  params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addParam<bool>("matrix_seperation_according_to_subdomains", true, "Tells whether the stiffness matrix is separated according to the subdomain_ids");


  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBNodalBC::DwarfElephantRBNodalBC(const InputParameters & parameters) :
    NodalBC(parameters),
    _matrix_seperation_according_to_subdomains(getParam<bool>("matrix_seperation_according_to_subdomains")),
    _compute_output(getParam<bool>("compute_output")),
    _simulation_type(getParam<std::string>("simulation_type")),
    _ID_Fq(getParam<std::vector<unsigned int>>("ID_Fq")),
    _ID_Aq(getParam<std::vector<unsigned int>>("ID_Aq")),
    _ID_Mq(getParam<unsigned int>("ID_Mq"))
{
    _rb_problem = cast_ptr<DwarfElephantRBProblem *>(&_fe_problem);
}

///-------------------------------------------------------------------------

void
DwarfElephantRBNodalBC::initialSetup()
{
  if(_simulation_type == "steady")  // SteadyState
    _initialize_rb_system = &getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
  else
    _initialize_rb_system_transient = &getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

  if(_compute_output)
    mooseError("You are trying to retrieve data on a nodal boundary. This feature is not supported.");
}

void
DwarfElephantRBNodalBC::computeResidual() // DwarfElephantRBNodalBC::computeResidual(NumericVector<Number> & residual)
{
  if (_var.isNodalDefined())
  {
    const dof_id_type & dof_idx = _var.nodalDofIndex();
    // _qp = 0;
    Real res = computeQpResidual();
    // residual.set(dof_idx, res);


    if (_simulation_type == "steady")  // Steady State
    {
      for(unsigned int i = 0; i < _ID_Fq.size(); i++){
        if (_ID_Fq[i] >= _initialize_rb_system->getQf())
          mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

          if(_initialize_rb_system->getOfflineStage())
          {
            if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
            {
              _rb_problem->rbAssembly().cacheResidual(dof_idx, -res,_ID_Fq[i]);
              // _initialize_rb_system->_residuals[_ID_Fq]->set(dof_idx, -res);
            }
          }
        }
    }

    else if (_simulation_type == "transient")
    {
      for(unsigned int i = 0; i < _ID_Fq.size(); i++){
        if (_ID_Fq[i] >= _initialize_rb_system_transient->getQf())
          mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

        if(_initialize_rb_system_transient->getOfflineStage())
          if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
            _rb_problem->rbAssembly().cacheResidual(dof_idx, -res, _ID_Fq[i]);
      }
    }

    if (_has_save_in)
    {
      Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
      for (unsigned int i=0; i<_save_in.size(); i++)
        _save_in[i]->sys().solution().set(_save_in[i]->nodalDofIndex(), res);
    }
  }
}

void
DwarfElephantRBNodalBC::computeJacobian()
{
  // We call the user's computeQpJacobian() function and store the
  // results in the _assembly object. We can't store them directly in
  // the element stiffness matrix, as they will only be inserted after
  // all the assembly is done.
  if (_var.isNodalDefined())
  {
    // _qp = 0;
    Real cached_val = computeQpJacobian();
    dof_id_type cached_row = _var.nodalDofIndex();

    // Cache the user's computeQpJacobian() value for later use.
    // for(unsigned int i = 0; i < _ID_Aq.size(); i++)
    //   _rb_problem->rbAssembly(0).cacheJacobianContribution(cached_row, cached_row, cached_val,_ID_Aq[i]);

    if (_simulation_type == "steady")
    {
      if(_initialize_rb_system->getOfflineStage())
      {
        if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0 )
        {
          if (_matrix_seperation_according_to_subdomains)
          {
            unsigned int _ID_first_block = *_fe_problem.mesh().meshSubdomains().begin();
            const std::set< SubdomainID > & _node_boundary_list = _mesh.getNodeBlockIds(*_var.node());

            cached_val = cached_val/_node_boundary_list.size();
            for (std::set<SubdomainID>::const_iterator it = _node_boundary_list.begin();
              it != _node_boundary_list.end(); it++)
            {
              if (*it-_ID_first_block >= _initialize_rb_system->getQa())
               mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");

              _rb_problem->rbAssembly().cacheJacobianContribution(cached_row, cached_row, cached_val,*it-_ID_first_block);
            }
           }
           else{
             for(unsigned int i = 0; i < _ID_Aq.size(); i++){
               if (_ID_Aq[i] >= _initialize_rb_system->getQa())
                mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");
	               _rb_problem->rbAssembly().cacheJacobianContribution(cached_row, cached_row, cached_val,_ID_Aq[i]);
            }
          }
        }
      }
    }

    else if (_simulation_type == "transient")
    {
      if(_initialize_rb_system_transient->getOfflineStage())
        if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
        {
          if (_matrix_seperation_according_to_subdomains)
          {
            unsigned int _ID_first_block = *_fe_problem.mesh().meshSubdomains().begin();
            const std::set< SubdomainID > & _node_boundary_list = _mesh.getNodeBlockIds(*_var.node());

            cached_val = cached_val/_node_boundary_list.size();
            for (std::set<SubdomainID>::const_iterator it = _node_boundary_list.begin();
               it != _node_boundary_list.end(); it++)
            {
              if (*it-_ID_first_block >= _initialize_rb_system_transient->getQa())
                mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");

              _rb_problem->rbAssembly().cacheJacobianContribution(cached_row, cached_row, cached_val,*it-_ID_first_block);
            }
          }
          else
          {
            for(unsigned int i = 0; i < _ID_Aq.size(); i++){
              if (_ID_Aq[i] >= _initialize_rb_system_transient->getQa())
                mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");

              _rb_problem->rbAssembly().cacheJacobianContribution(cached_row, cached_row, cached_val,_ID_Aq[i]);
            }
          }
          if (_ID_Mq >= _initialize_rb_system_transient->getQm())
           mooseError("The number of mass matrices you defined here is not matching the number of mass matrices you specified in the RBClasses Class.");

          _rb_problem->rbAssembly().cacheMassMatrixContribution(cached_row, cached_row, cached_val,_ID_Mq);
       }
    }


    if (_has_diag_save_in)
    {
      Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
      for (unsigned int i=0; i<_diag_save_in.size(); i++)
        _diag_save_in[i]->sys().solution().set(_diag_save_in[i]->nodalDofIndex(), cached_val);
    }
  }
}

Real
DwarfElephantRBNodalBC::computeQpJacobian()
{
  return 1.;
}

Real
DwarfElephantRBNodalBC::computeQpResidual()
{
  return 0.;
}
