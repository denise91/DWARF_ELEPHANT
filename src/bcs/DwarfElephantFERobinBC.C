#include "DwarfElephantFERobinBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFERobinBC);

template <>
InputParameters
validParams<DwarfElephantFERobinBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("alpha", "Factor that determines the ratio between Dirichlet and Neumann BC.");
  params.addParam<Real>("value", 0.0, "Boundary value of the variable");
  params.declareControllable("value");

  return params;
}

DwarfElephantFERobinBC::DwarfElephantFERobinBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
  _alpha(getParam<Real>("alpha")),
  _value(getParam<Real>("value"))
{
}

Real
DwarfElephantFERobinBC::computeQpResidual()
{
  return _test[_i][_qp] * (_alpha*_u[_qp]-_value);
}

Real
DwarfElephantFERobinBC::computeQpJacobian()
{
  return _alpha * _phi[_j][_qp] * _test[_i][_qp];
}
