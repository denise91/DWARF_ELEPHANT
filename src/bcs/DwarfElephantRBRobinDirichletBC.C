#include "DwarfElephantRBRobinDirichletBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBRobinDirichletBC);

template <>
InputParameters
validParams<DwarfElephantRBRobinDirichletBC>()
{
  InputParameters params = validParams<DwarfElephantRBIntegratedBC>();
  params.addRequiredParam<Real>("alpha", "Factor that determines the ratio between Dirichlet and Dirichlet BC.");
  return params;
}

DwarfElephantRBRobinDirichletBC::DwarfElephantRBRobinDirichletBC(const InputParameters & parameters)
  : DwarfElephantRBIntegratedBC(parameters),
  _alpha(getParam<Real>("alpha"))
{
}

Real
DwarfElephantRBRobinDirichletBC::computeQpResidual()
{
  return _test[_i][_qp] * (_alpha*_u[_qp]);
}

Real
DwarfElephantRBRobinDirichletBC::computeQpJacobian()
{
  return _alpha * _phi[_j][_qp] * _test[_i][_qp];
}
