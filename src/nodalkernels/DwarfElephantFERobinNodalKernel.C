#include "DwarfElephantFERobinNodalKernel.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFERobinNodalKernel);

defineLegacyParams(DwarfElephantFERobinNodalKernel);

InputParameters
DwarfElephantFERobinNodalKernel::validParams()
{
  InputParameters params = NodalKernel::validParams();
  params.addClassDescription("Enforces a Dirichlet boundary condition "
                             "in a weak sense by penalizing differences between the current "
                             "solution and the Dirichlet value on nodesets.");

  params.addRequiredParam<Real>("alpha", "Penalty scalar");

  return params;
}

DwarfElephantFERobinNodalKernel::DwarfElephantFERobinNodalKernel(const InputParameters & parameters)
  : NodalKernel(parameters),
  _alpha(getParam<Real>("alpha"))
{
}

Real
DwarfElephantFERobinNodalKernel::computeQpResidual()
{
  return _alpha * (_u[_qp]);
}

Real
DwarfElephantFERobinNodalKernel::computeQpJacobian()
{
  return 0;
}
