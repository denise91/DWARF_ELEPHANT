#include "DwarfElephantRBDiracKernel.h"

template <>
InputParameters
validParams<DwarfElephantRBDiracKernel>()
{
  InputParameters params = validParams<DiracKernel>();
  params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system");
  params.addParam<unsigned int>("ID_Aq", 0, "ID of the current stiffness matrix");
  params.addParam<unsigned int>("ID_Fq", 0, "ID of the current load vector");
  params.addParam<bool>("matrix_seperation_according_to_subdomains", true, "Tells whether the stiffness matrix is separated according to the subdomain_ids");
  params.addParam<bool>("vector_seperation_according_to_subdomains", false, "Tells whether the load vector is separated according to the subdomain_ids");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");

  return params;
}

DwarfElephantRBDiracKernel::DwarfElephantRBDiracKernel(const InputParameters & parameters)
  : DiracKernel(parameters),

  _matrix_seperation_according_to_subdomains(getParam<bool>("matrix_seperation_according_to_subdomains")),
  _vector_seperation_according_to_subdomains(getParam<bool>("vector_seperation_according_to_subdomains")),
  _simulation_type(getParam<std::string>("simulation_type")),
  _ID_first_block(*_c_fe_problem.mesh().meshSubdomains().begin()),
  _ID_Aq(getParam<unsigned int>("ID_Aq")),
  _ID_Fq(getParam<unsigned int>("ID_Fq"))
{
}


void
DwarfElephantRBDiracKernel::computeResidual()
{
  if(_vector_seperation_according_to_subdomains)
    _ID_Fq = _current_elem->subdomain_id() - _ID_first_block;

  DenseVector<Number> & re = _assembly.residualBlock(_var.number());

  const std::vector<unsigned int> * multiplicities =
      _drop_duplicate_points ? NULL : &_local_dirac_kernel_info.getPoints()[_current_elem].second;
  unsigned int local_qp = 0;
  Real multiplicity = 1.0;

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
  {
    _current_point = _physical_point[_qp];
    if (isActiveAtPoint(_current_elem, _current_point))
    {
      if (!_drop_duplicate_points)
        multiplicity = (*multiplicities)[local_qp++];

      for (_i = 0; _i < _test.size(); _i++)
        re(_i) += multiplicity * computeQpResidual();
    }
  }

  if(_simulation_type == "steady")  // SteadyState
  {
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
    if(_initialize_rb_system.getOfflineStage())
      // Add the calculated vectors to the vectors from the RB system.
      if (_c_fe_problem.getNonlinearSystemBase().computingInitialResidual())
        _initialize_rb_system.getResiduals()[_ID_Fq] -> add_vector(re, _var.dofIndices());
  }
  else if (_simulation_type == "transient") // Transient
  {
    const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

    if(_initialize_rb_system.getOfflineStage())
      // Add the calculated vectors to the vectors from the RB system.
      if (_c_fe_problem.getNonlinearSystemBase().computingInitialResidual())
        _initialize_rb_system.getResiduals()[_ID_Fq] -> add_vector(re, _var.dofIndices());
  }
}

void
DwarfElephantRBDiracKernel::computeJacobian()
{
  if(_matrix_seperation_according_to_subdomains)
    _ID_Aq = _current_elem->subdomain_id() - _ID_first_block;

  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());

  const std::vector<unsigned int> * multiplicities =
      _drop_duplicate_points ? NULL : &_local_dirac_kernel_info.getPoints()[_current_elem].second;
  unsigned int local_qp = 0;
  Real multiplicity = 1.0;

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
  {
    _current_point = _physical_point[_qp];
    if (isActiveAtPoint(_current_elem, _current_point))
    {
      if (!_drop_duplicate_points)
        multiplicity = (*multiplicities)[local_qp++];

      for (_i = 0; _i < _test.size(); _i++)
        for (_j = 0; _j < _phi.size(); _j++)
          ke(_i, _j) += multiplicity * computeQpJacobian();
    }
  }

  if(_simulation_type == "steady")  // Steady State
  {
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
    if(_initialize_rb_system.getOfflineStage())
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_c_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
        _initialize_rb_system.getJacobianSubdomain()[_ID_Aq] -> add_matrix(ke, _var.dofIndices());
   }

  else if(_simulation_type == "transient") // Transient
  {
    const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");
    if(_initialize_rb_system.getOfflineStage())
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_c_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
    {
        _initialize_rb_system.getJacobianSubdomain()[_ID_Aq] -> add_matrix(ke, _var.dofIndices());
    }
  }
}


Real
DwarfElephantRBDiracKernel::computeQpResidual()
{
  return 0;
}
