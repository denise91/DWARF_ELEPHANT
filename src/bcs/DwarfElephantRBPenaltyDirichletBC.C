#include "DwarfElephantRBPenaltyDirichletBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBPenaltyDirichletBC);

template <>
InputParameters
validParams<DwarfElephantRBPenaltyDirichletBC>()
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

DwarfElephantRBPenaltyDirichletBC::DwarfElephantRBPenaltyDirichletBC(const InputParameters & parameters)
  : DwarfElephantRBIntegratedBC(parameters), _p(getParam<Real>("penalty")), _v(getParam<Real>("value"))
{
}

Real
DwarfElephantRBPenaltyDirichletBC::computeQpResidual()
{
  return _p * -_test[_i][_qp] * (-_v + _u[_qp]);
}

Real
DwarfElephantRBPenaltyDirichletBC::computeQpJacobian()
{
  return _p * _phi[_j][_qp] * _test[_i][_qp];
}
