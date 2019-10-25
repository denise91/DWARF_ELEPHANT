#include "DwarfElephantRBRobinBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBRobinBC);

template <>
InputParameters
validParams<DwarfElephantRBRobinBC>()
{
  InputParameters params = validParams<DwarfElephantRBIntegratedBC>();
  params.addRequiredParam<Real>("alpha", "Factor that determines the ratio between Dirichlet and Neumann BC.");
  params.addParam<Real>("value", 0.0, "Boundary value of the variable");
  params.declareControllable("value");
  return params;
}

DwarfElephantRBRobinBC::DwarfElephantRBRobinBC(const InputParameters & parameters)
  : DwarfElephantRBIntegratedBC(parameters),
  _alpha(getParam<Real>("alpha")),
  _value(getParam<Real>("value"))
{
}

Real
DwarfElephantRBRobinBC::computeQpResidual()
{
  return _test[_i][_qp] * ((_alpha*_u[_qp])+_value);
}

Real
DwarfElephantRBRobinBC::computeQpJacobian()
{
  return -_alpha * _phi[_j][_qp] * _test[_i][_qp];
}
