/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
 * This is for use with geometrical parametrizations
 */

///---------------------------------INCLUDES--------------------------------
//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBDiffusionXX.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionXX>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a Diffusion problem using \
                             the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBDiffusionXX::DwarfElephantRBDiffusionXX(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters)
{
}

///----------------------------------PDEs-----------------------------------
Real
DwarfElephantRBDiffusionXX::computeQpResidual()
{
  return _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusionXX::computeQpJacobian()
{
  return _grad_phi[_j][_qp](0) * _grad_test[_i][_qp](0);
}

Real
DwarfElephantRBDiffusionXX::computeQpOutput()
{
  return 1;
}
