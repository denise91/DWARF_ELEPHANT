#include "DwarfElephantFEVectorPenaltyDirichletBC.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEVectorPenaltyDirichletBC);

template <>
InputParameters
validParams<DwarfElephantFEVectorPenaltyDirichletBC>()
{
  InputParameters params = validParams<VectorIntegratedBC>();
  params.addRequiredParam<RealVectorValue>(
      "value", "Value of the BC");
  params.addRequiredParam<Real>("penalty", "Penalty scalar");
  return params;
}

DwarfElephantFEVectorPenaltyDirichletBC::DwarfElephantFEVectorPenaltyDirichletBC(const InputParameters & parameters)
  : VectorIntegratedBC(parameters),
  _value(getParam<RealVectorValue>("value")),
  _penalty(getParam<Real>("penalty"))
{
}

Real
DwarfElephantFEVectorPenaltyDirichletBC::computeQpResidual()
{
  return _penalty*_test[_i][_qp]*(_u[_qp]-_value);
}

Real
DwarfElephantFEVectorPenaltyDirichletBC::computeQpJacobian()
{
  return _penalty * _phi[_j][_qp] * _test[_i][_qp];
}
