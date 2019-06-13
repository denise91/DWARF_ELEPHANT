/**
 * This Kernel is required to use the RB method as it is provided by the
 * RB libMesh package. The RBKernel inherits from the Kernel class. It
 * overwrites the function computeJacobian because for the RB method the
 * stiffness matrix is needed separated in its subdomain contributions. In
 * addition it overwrites the function computeResidual.
 */

///---------------------------------INCLUDES--------------------------------
// libMesh includes
#include "libmesh/threads.h"
#include "libmesh/quadrature.h"

//MOOSE includes
#include "Assembly.h"
#include "MooseVariable.h"
#include "MooseVariableScalar.h"
#include "Problem.h"
#include "SubProblem.h"
#include "SystemBase.h"

//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBKernel>()
{
  InputParameters params = validParams<Kernel>();

  params.addClassDescription("Overwrites the function computeJacobian. This is required because for the RB method the stiffness matrix needs to be saved in its subdomain contributions.");
  params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addParam<unsigned int>("ID_Aq", 0, "ID of the current stiffness matrix");
  params.addParam<unsigned int>("ID_Mq", 0, "ID of the current mass matrix");
  params.addParam<unsigned int>("ID_Fq", 0, "ID of the current load vector");
  params.addParam<unsigned int>("ID_Oq", 0, "ID of the current output vector");
  params.addParam<bool>("matrix_seperation_according_to_subdomains", false, "Tells whether the stiffness matrix is separated according to the subdomain_ids");
  params.addParam<bool>("time_matrix_seperation_according_to_subdomains", true, "Tells whether the mass matrix is separated according to the subdomain_ids");
  params.addParam<bool>("vector_seperation_according_to_subdomains", false, "Tells whether the load vector is separated according to the subdomain_ids");
  params.addParam<bool>("compute_output",false,"Determines whether an output function is used or not");

  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBKernel::DwarfElephantRBKernel(const InputParameters & parameters) :
    Kernel(parameters),
    _use_displaced(getParam<bool>("use_displaced")),
    _matrix_seperation_according_to_subdomains(getParam<bool>("matrix_seperation_according_to_subdomains")),
    _time_matrix_seperation_according_to_subdomains(getParam<bool>("time_matrix_seperation_according_to_subdomains")),
    _vector_seperation_according_to_subdomains(getParam<bool>("vector_seperation_according_to_subdomains")),
    _compute_output(getParam<bool>("compute_output")),
    _simulation_type(getParam<std::string>("simulation_type")),
    _ID_first_block(*_fe_problem.mesh().meshSubdomains().begin()),
    _ID_Aq(getParam<unsigned int>("ID_Aq")),
    _ID_Mq(getParam<unsigned int>("ID_Mq")),
    _ID_Fq(getParam<unsigned int>("ID_Fq")),
    _ID_Oq(getParam<unsigned int>("ID_Oq")),
    _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es())

{

}

///-------------------------------------------------------------------------
void
DwarfElephantRBKernel::initialSetup()
{
  // mooseInfo("For performing the reduced basis method a seperation of the stiffness matrix and the load vector according to "
  //           "the theta values is necessary. Therefore, the algorithm needs an ID for the matrices and vectors. The default "
  //           "setting seperates the matrices into the subdomain contributions. By performing the "
  //           "Kernels block wise and specify the ID in the inputfile any other seperation is also possible. Due to the seperation the occurence of segmentation faults is likely. If "
  //           "a segementation fault occurs right after 'quiet mode?' check whether you: used the correct RBStructures header file in the RBClasses class.");
}

void
DwarfElephantRBKernel::computeResidual()
{
  if(_vector_seperation_according_to_subdomains)
    _ID_Fq = _current_elem->subdomain_id() - _ID_first_block;

  DenseVector<Number> & re = _assembly.residualBlock(_var.number());
  _local_re.resize(re.size());
  _local_re.zero();

  precalculateResidual();
  for (_i = 0; _i < _test.size(); _i++)
    for (_qp = 0; _qp < _qrule->n_points(); _qp++)
      {
      _local_re(_i) += _JxW[_qp] * _coord[_qp] * computeQpResidual();
      }

  re += _local_re;

  if(_simulation_type == "steady")  // SteadyState
  {
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");

    if(_initialize_rb_system._exec_flags[0] != EXEC_INITIAL)
    mooseError("The UserObject 'DwarfElephantInitializeRBSystemSteadyState' has to be executed on 'initial'. "
               "You defined a wrong state in your 'execute_on' line in the input file. "
               "Please, correct your settings.");

    if(_initialize_rb_system._offline_stage) // order of offline_stage and _ID_Fq if statements changed to make code compatible with EIM.
    {
      if (_ID_Fq >= _initialize_rb_system._qf)
        mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");

    
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
        _initialize_rb_system._residuals[_ID_Fq] -> add_vector(_local_re, _var.dofIndices());
    }
  }
  else if (_simulation_type == "transient") // Transient
  {
    const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

    if(_initialize_rb_system._exec_flags[0] != EXEC_INITIAL)
    mooseError("The UserObject 'DwarfElephantInitializeRBSystemTransient' has to be executed on 'initial'. "
               "You defined a wrong state in your 'execute_on' line in the input file. "
               "Please, correct your settings.");

    if (_ID_Fq >= _initialize_rb_system._qf)
      mooseError("The number of load vectors you defined here is not matching the number of load vectors you specified in the RBClasses Class.");


    if(_initialize_rb_system._offline_stage)
      // Add the calculated vectors to the vectors from the RB system.
      if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
        _initialize_rb_system._residuals[_ID_Fq] -> add_vector(_local_re, _var.dofIndices());
  }

  if (_has_save_in)
  {
    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (const auto & var : _save_in)
      var->sys().solution().add_vector(_local_re, var->dofIndices());
  }

 if(_compute_output)
  computeOutput();
}

void
DwarfElephantRBKernel::computeOutput()
{
 if(_vector_seperation_according_to_subdomains)
    _ID_Oq = _current_elem->subdomain_id() - _ID_first_block;

  DenseVector<Number> & out = _assembly.residualBlock(_var.number());
  _local_out.resize(out.size());
  _local_out.zero();

  precalculateResidual();
  for (_i = 0; _i < _test.size(); _i++)
    for (_qp = 0; _qp < _qrule->n_points(); _qp++)
      _local_out(_i) += _JxW[_qp] * _coord[_qp] * computeQpOutput();

  out += _local_out;


  if(_simulation_type == "steady")  // SteadyState
  {
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");

    if(_initialize_rb_system._offline_stage)
      // Add the calculated vectors to the vectors from the RB system.
        _initialize_rb_system._outputs[0][_ID_Oq] -> add_vector(_local_out, _var.dofIndices());
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
DwarfElephantRBKernel::computeJacobian()
{
  if(_matrix_seperation_according_to_subdomains)
    _ID_Aq = _current_elem->subdomain_id() - _ID_first_block;

  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());
  _local_ke.resize(ke.m(), ke.n());
  _local_ke.zero();

  precalculateJacobian();
  for (_i = 0; _i < _test.size(); _i++)
    for (_j = 0; _j < _phi.size(); _j++)
      for (_qp = 0; _qp < _qrule->n_points(); _qp++)
        _local_ke(_i, _j) += _JxW[_qp] * _coord[_qp] * computeQpJacobian();

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

    if(_initialize_rb_system._offline_stage)
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
    {
        _initialize_rb_system._jacobian_subdomain[_ID_Aq] -> add_matrix(_local_ke, _var.dofIndices());
    }
  }

 if (_has_diag_save_in)
  {
    unsigned int rows = ke.m();
    DenseVector<Number> diag(rows);
    for (unsigned int i=0; i<rows; i++)
      diag(i) = _local_ke(i,i);

    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (const auto & var : _diag_save_in)
      var->sys().solution().add_vector(diag, var->dofIndices());
  }
}
///----------------------------------PDEs-----------------------------------
// For the PDEs zero is implemented, since this Kernel shall be used for any
// RB problem. The problem specific PDEs are implemented in separate Kernels.

Real
DwarfElephantRBKernel::computeQpJacobian()
{
  return 0;
}

Real
DwarfElephantRBKernel::computeQpResidual()
{
  return 0;
}

Real
DwarfElephantRBKernel::computeQpOutput()
{
  return 0;
}
