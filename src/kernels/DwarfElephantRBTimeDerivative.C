#include "DwarfElephantRBTimeDerivative.h"

// MOOSE includes
#include "Assembly.h"
#include "MooseVariable.h"

// libMesh includes
#include "libmesh/quadrature.h"

template <>
InputParameters
validParams<DwarfElephantRBTimeDerivative>()
{
  InputParameters params = validParams<DwarfElephantRBTimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  params.addParam<Real>("heat_capacity",1.0,"Heat capacity");
  return params;
}

DwarfElephantRBTimeDerivative::DwarfElephantRBTimeDerivative(const InputParameters & parameters)
  : DwarfElephantRBTimeKernel(parameters), _lumping(getParam<bool>("lumping")), _heat_capacity(getParam<Real>("heat_capacity"))
{
}

Real
DwarfElephantRBTimeDerivative::computeQpResidual()
{
  return 0;
}

Real
DwarfElephantRBTimeDerivative::computeQpJacobian()
{
  return _heat_capacity * _test[_i][_qp] * _phi[_j][_qp];
}

void
DwarfElephantRBTimeDerivative::computeJacobian()
{
  if (_lumping)
  {
    DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());

    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < _phi.size(); _j++)
        for (_qp = 0; _qp < _qrule->n_points(); _qp++)
          ke(_i, _i) += _JxW[_qp] * _coord[_qp] * computeQpJacobian();
  }
  else
    DwarfElephantRBTimeKernel::computeJacobian();
}
