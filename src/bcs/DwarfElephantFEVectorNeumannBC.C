#include "DwarfElephantFEVectorNeumannBC.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEVectorNeumannBC);

template <>
InputParameters
validParams<DwarfElephantFEVectorNeumannBC>()
{
  InputParameters params = validParams<VectorIntegratedBC>();
  params.addRequiredParam<RealVectorValue>(
      "vector_value", "vector this BC should act in");
  return params;
}

DwarfElephantFEVectorNeumannBC::DwarfElephantFEVectorNeumannBC(const InputParameters & parameters)
  : VectorIntegratedBC(parameters),
  _value(getParam<RealVectorValue>("vector_value"))
{
}

Real
DwarfElephantFEVectorNeumannBC::computeQpResidual()
{
  return -_test[_i][_qp] * _value;
}
