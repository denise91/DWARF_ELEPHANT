#include "DwarfElephantRBRobinNeumannBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBRobinNeumannBC);

template <>
InputParameters
validParams<DwarfElephantRBRobinNeumannBC>()
{
  InputParameters params = validParams<DwarfElephantRBIntegratedBC>();
  params.addParam<Real>("value", 0.0, "Boundary value of the variable");
  params.declareControllable("value");
  return params;
}

DwarfElephantRBRobinNeumannBC::DwarfElephantRBRobinNeumannBC(const InputParameters & parameters)
  : DwarfElephantRBIntegratedBC(parameters),
  _value(getParam<Real>("value"))
{
}

Real
DwarfElephantRBRobinNeumannBC::computeQpResidual()
{
  return _test[_i][_qp] * (-_value);
}

Real
DwarfElephantRBRobinNeumannBC::computeQpJacobian()
{
  return 0;
}
