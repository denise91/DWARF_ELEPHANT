#include "DwarfElephantRBFunctionPenaltyDirichletBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBFunctionPenaltyDirichletBC);

template <>
InputParameters
validParams<DwarfElephantRBFunctionPenaltyDirichletBC>()
{
  InputParameters params = validParams<DwarfElephantRBIntegratedBC>();
  params.addRequiredParam<Real>("penalty", "Penalty scalar");
  params.addRequiredParam<FunctionName>("function", "Forcing function");

  return params;
}

DwarfElephantRBFunctionPenaltyDirichletBC::DwarfElephantRBFunctionPenaltyDirichletBC(const InputParameters & parameters)
  : DwarfElephantRBIntegratedBC(parameters), _func(getFunction("function")), _p(getParam<Real>("penalty"))
{
}

Real
DwarfElephantRBFunctionPenaltyDirichletBC::computeQpResidual()
{
  return _p * -_test[_i][_qp] * (-_func.value(_t, _q_point[_qp]) + _u[_qp]);
}

Real
DwarfElephantRBFunctionPenaltyDirichletBC::computeQpJacobian()
{
  return _p * _phi[_j][_qp] * _test[_i][_qp];
}
