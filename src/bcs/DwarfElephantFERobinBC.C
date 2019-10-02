#include "DwarfElephantFERobinBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFERobinBC);

template <>
InputParameters
validParams<DwarfElephantFERobinBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<Real>("penalty", "Penalty scalar");
  params.addParam<Real>("value", 0.0, "Boundary value of the variable");
  params.declareControllable("value");

  return params;
}

DwarfElephantFERobinBC::DwarfElephantFERobinBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
  _p(getParam<Real>("penalty")),
  _v(getParam<Real>("value"))
{
}

Real
DwarfElephantFERobinBC::computeQpResidual()
{
  return _test[_i][_qp] * ((_p*_u[_qp])-_v);
}

Real
DwarfElephantFERobinBC::computeQpJacobian()
{
  return _p * _phi[_j][_qp] * _test[_i][_qp];
}
