#include "DwarfElephantFEVectorRobinBC.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEVectorRobinBC);

template <>
InputParameters
validParams<DwarfElephantFEVectorRobinBC>()
{
  InputParameters params = validParams<VectorIntegratedBC>();
  params.addRequiredParam<RealVectorValue>(
      "value", "Value of the BC");
  params.addRequiredParam<Real>("penalty", "Penalty scalar");
  return params;
}

DwarfElephantFEVectorRobinBC::DwarfElephantFEVectorRobinBC(const InputParameters & parameters)
  : VectorIntegratedBC(parameters),
  _value(getParam<RealVectorValue>("value")),
  _penalty(getParam<Real>("penalty"))
{
}

Real
DwarfElephantFEVectorRobinBC::computeQpResidual()
{
  return _test[_i][_qp]*((_penalty*_u[_qp])-_value);
}

Real
DwarfElephantFEVectorRobinBC::computeQpJacobian()
{
  return _penalty * _phi[_j][_qp] * _test[_i][_qp];
}
