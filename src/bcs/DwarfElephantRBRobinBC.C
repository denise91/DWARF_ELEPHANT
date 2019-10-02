#include "DwarfElephantRBRobinBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBRobinBC);

template <>
InputParameters
validParams<DwarfElephantRBRobinBC>()
{
  InputParameters params = validParams<DwarfElephantRBIntegratedBC>();
  params.addRequiredParam<Real>("penalty", "Penalty scalar");
  params.addParam<Real>("value", 0.0, "Boundary value of the variable");
  params.declareControllable("value");
  params.addClassDescription("Enforces a Dirichlet boundary condition "
                             "in a weak sense by penalizing differences between the current "
                             "solution and the Dirichlet data.");
  return params;
}

DwarfElephantRBRobinBC::DwarfElephantRBRobinBC(const InputParameters & parameters)
  : DwarfElephantRBIntegratedBC(parameters),
  _p(getParam<Real>("penalty")),
  _v(getParam<Real>("value"))
{
}

Real
DwarfElephantRBRobinBC::computeQpResidual()
{
  return -_test[_i][_qp] * ((_p*_u[_qp])-_v);
}

Real
DwarfElephantRBRobinBC::computeQpJacobian()
{
  return _p * _phi[_j][_qp] * _test[_i][_qp];
}
