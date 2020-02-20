#include "DwarfElephantRBIntegratedBC.h"
#include "SubProblem.h"
#include "SystemBase.h"
#include "MooseVariable.h"
#include "Assembly.h"

// libMesh includes
#include "libmesh/quadrature.h"

template<>
InputParameters validParams<DwarfElephantRBIntegratedBC>()
{
  InputParameters params = validParams<IntegratedBC>();

  params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addParam<unsigned int>("ID_Aq", 0, "ID of the current stiffness matrix.");
  params.addParam<unsigned int>("ID_Aq_split", 0, "ID of the current stiffness matrix.");
  params.addParam<std::vector<unsigned int>>("subdomain_split", "ID of the current stiffness matrix.");
  params.addParam<unsigned int>("ID_Mq", 0, "ID of the current mass matrix.");
  params.addParam<unsigned int>("ID_Mq_split", 0, "Defines the number that has to be added to the subdomain ID to get the correct mass matrix ID. This is only required when the boundary is splitted into the subdomains.");
  params.addParam<unsigned int>("ID_Fq", 0, "ID of the current load vector.");
  params.addParam<unsigned int>("ID_Fq_split", 0, "Defines the number that has to be added to the subdomain ID to get the correct load vector ID. This is only required when the boundary is splitted into the subdomains.");
  params.addParam<unsigned int>("ID_Oq", 0, "ID of the current output vector.");
  params.addParam<bool>("matrix_seperation_according_to_subdomains", false, "Tells whether the stiffness matrix is separated according to the subdomain_ids");
  params.addParam<bool>("compute_output",false,"Determines whether an output function is used or not");
  params.addParam<bool>("split_boundary_according_to_subdomains", false, "Determines whether boundary will be splitted or not.");
  params.addParam<bool>("compliant", false, "Specifies if you have a compliant or non-compliant case.");

  return params;
}

DwarfElephantRBIntegratedBC::DwarfElephantRBIntegratedBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _use_displaced(getParam<bool>("use_displaced")),
    _matrix_seperation_according_to_subdomains(getParam<bool>("matrix_seperation_according_to_subdomains")),
    _compute_output(getParam<bool>("compute_output")),
    _compliant(getParam<bool>("compliant")),
    _split_boundary_according_to_subdomains(getParam<bool>("split_boundary_according_to_subdomains")),
    _simulation_type(getParam<std::string>("simulation_type")),
    _ID_first_block(*_fe_problem.mesh().meshSubdomains().begin()),
    _ID_Aq(getParam<unsigned int>("ID_Aq")),
    _ID_Aq_split(getParam<unsigned int>("ID_Aq_split")),
    _subdomain_split(getParam<std::vector<unsigned int>>("subdomain_split")),
    _ID_Mq(getParam<unsigned int>("ID_Mq")),
    _ID_Mq_split(getParam<unsigned int>("ID_Mq_split")),
    _ID_Fq(getParam<unsigned int>("ID_Fq")),
    _ID_Fq_split(getParam<unsigned int>("ID_Fq_split")),
    _ID_Oq(getParam<unsigned int>("ID_Oq")),
    _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es())
{
}

DwarfElephantRBIntegratedBC::~DwarfElephantRBIntegratedBC()
{
}

void
DwarfElephantRBIntegratedBC::initialSetup()
{
  if(_compute_output)
    mooseWarning("You are retrieving boundary values for your output of interest.");
}

void
DwarfElephantRBIntegratedBC::computeResidual()
{
  if(_split_boundary_according_to_subdomains)
  {
    unsigned int _ID_inter = _current_elem->subdomain_id();
    if (_ID_inter >= _subdomain_split[0] && _ID_inter <= _subdomain_split[_subdomain_split.size()-1])
      _ID_Aq_split = _ID_inter - _ID_first_block;
  }

  DenseVector<Number> & re = _assembly.residualBlock(_var.number());
  _local_re.resize(re.size());
  _local_re.zero();

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    for (_i = 0; _i < _test.size(); _i++)
      _local_re(_i) += _JxW[_qp]*_coord[_qp]*computeQpResidual();

  re += _local_re;

  if(_simulation_type == "steady")  // SteadyState
  {
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");

    if(_initialize_rb_system._offline_stage)
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
      {
        if (!_split_boundary_according_to_subdomains)
        {
          if (_ID_Fq >= _initialize_rb_system._qf)
            mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

          _initialize_rb_system._residuals[_ID_Fq] -> add_vector(_local_re, _var.dofIndices());

          if (_compliant)
            _initialize_rb_system._outputs[_ID_Fq][0] -> add_vector(_local_re, _var.dofIndices());
        } else {

          if (_ID_Aq_split + _ID_Fq_split >= _initialize_rb_system._qf)
            mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

            _initialize_rb_system._residuals[_ID_Aq_split + _ID_Fq_split] -> add_vector(_local_re, _var.dofIndices());

            if(_compliant)
              _initialize_rb_system._outputs[_ID_Aq_split + _ID_Fq_split][0] -> add_vector(_local_re, _var.dofIndices());
        }
      }
  }

  else if (_simulation_type == "transient") // Transient
  {
    const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");
    if(_initialize_rb_system._offline_stage)
      // Add the calculated vectors to the vectors from the RB system.
    if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
    {
      if (!_split_boundary_according_to_subdomains)
      {
        if (_ID_Fq >= _initialize_rb_system._qf)
          mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

        _initialize_rb_system._residuals[_ID_Fq] -> add_vector(_local_re, _var.dofIndices());

        if (_compliant)
          _initialize_rb_system._outputs[_ID_Fq][0] -> add_vector(_local_re, _var.dofIndices());
        } else {
          if (_ID_Aq_split + _ID_Fq_split >= _initialize_rb_system._qf)
            mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

          _initialize_rb_system._residuals[_ID_Aq_split + _ID_Fq_split] -> add_vector(_local_re, _var.dofIndices());

          if(_compliant)
            _initialize_rb_system._outputs[_ID_Aq_split + _ID_Fq_split][0] -> add_vector(_local_re, _var.dofIndices());
        }
      }
    }


  if (_has_save_in)
  {
    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (unsigned int i=0; i<_save_in.size(); i++)
      _save_in[i]->sys().solution().add_vector(_local_re, _save_in[i]->dofIndices());
  }

 if(_compute_output)
   computeOutput();
}

void
DwarfElephantRBIntegratedBC::computeOutput()
{
  DenseVector<Number> & out = _assembly.residualBlock(_var.number());
  _local_out.resize(out.size());
  _local_out.zero();

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    for (_i = 0; _i < _test.size(); _i++)
      _local_out(_i) += _JxW[_qp]*_coord[_qp]*computeQpOutput();

  out += _local_out;

  if(_simulation_type == "steady")  // SteadyState
  {
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
    if(_initialize_rb_system._offline_stage)
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
      {
        _initialize_rb_system._outputs[_ID_Oq][0] -> add_vector(_local_out, _var.dofIndices());
     }
  }

  else if (_simulation_type == "transient") // Transient
  {
    const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");
    if(_initialize_rb_system._offline_stage)
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
         _initialize_rb_system._outputs[0][_ID_Oq] -> add_vector(_local_out, _var.dofIndices());
  }
}

void
DwarfElephantRBIntegratedBC::computeJacobian()
{
  if(_matrix_seperation_according_to_subdomains)
  {
    _ID_Aq = _current_elem->subdomain_id() - _ID_first_block;

//    unsigned int _ID_inter = _current_elem->subdomain_id();
//    if (_ID_inter >= _subdomain_split[0] && _ID_inter <= _subdomain_split[_subdomain_split.size()-1])
//      _ID_Aq_split = _ID_inter - _ID_first_block;
  }

  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());
  _local_ke.resize(ke.m(), ke.n());
  _local_ke.zero();

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < _phi.size(); _j++)
        _local_ke(_i, _j) += _JxW[_qp]*_coord[_qp]*computeQpJacobian();

  ke += _local_ke;

  if(_simulation_type == "steady")  // Steady State
  {
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");

    if (_ID_Aq >= _initialize_rb_system._qa)
      mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");

    if(_initialize_rb_system._offline_stage || _initialize_rb_system._hp_EIM_testing)
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
        _initialize_rb_system._jacobian_subdomain[_ID_Aq] -> add_matrix(_local_ke, _var.dofIndices());
   }

  else if(_simulation_type == "transient") // Transient
  {
    const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

    if (_ID_Aq >= _initialize_rb_system._qa)
      mooseError("The number of stiffness matrices you defined here is not matching the number of stiffness matrices you specified in the RBClasses Class.");

    if (_ID_Mq >= _initialize_rb_system._qm)
      mooseError("The number of mass matrices you defined here is not matching the number of mass matrices you specified in the RBClasses Class.");

    if(_initialize_rb_system._offline_stage)
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
    {
      _initialize_rb_system._jacobian_subdomain[_ID_Aq] -> add_matrix(_local_ke, _var.dofIndices());
      //_initialize_rb_system._mass_matrix_subdomain[_ID_Mq] -> add_matrix(_local_ke, _var.dofIndices());
    }
  }

  if (_has_diag_save_in)
  {
    unsigned int rows = ke.m();
    DenseVector<Number> diag(rows);
    for (unsigned int i=0; i<rows; i++)
      diag(i) = _local_ke(i,i);

    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (unsigned int i=0; i<_diag_save_in.size(); i++)
      _diag_save_in[i]->sys().solution().add_vector(diag, _diag_save_in[i]->dofIndices());
  }
}

void
DwarfElephantRBIntegratedBC::computeJacobianBlock(unsigned int jvar)
{
  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), jvar);

  for (_qp=0; _qp<_qrule->n_points(); _qp++)
    for (_i=0; _i<_test.size(); _i++)
      for (_j=0; _j<_phi.size(); _j++)
      {
        if (_var.number() == jvar)
          ke(_i,_j) += _JxW[_qp]*_coord[_qp]*computeQpJacobian();
        else
          ke(_i,_j) += _JxW[_qp]*_coord[_qp]*computeQpOffDiagJacobian(jvar);
      }
}

void
DwarfElephantRBIntegratedBC::computeJacobianBlockScalar(unsigned int jvar)
{
  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), jvar);

  MooseVariableScalar & jv = _sys.getScalarVariable(_tid, jvar);
  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < jv.order(); _j++)
        ke(_i, _j) += _JxW[_qp] * _coord[_qp] * computeQpOffDiagJacobian(jvar);
}

Real
DwarfElephantRBIntegratedBC::computeQpResidual()
{
  return 0;
}

Real
DwarfElephantRBIntegratedBC::computeQpOutput()
{
  return 0;
}

Real
DwarfElephantRBIntegratedBC::computeQpJacobian()
{
  return 0;
}

Real
DwarfElephantRBIntegratedBC::computeQpOffDiagJacobian(unsigned int /*jvar*/)
{
  return 0;
}
