/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
 * This is for use with geometrical parametrizations
 */

///---------------------------------INCLUDES--------------------------------
//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBDiffusionXZ.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionXZ>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a Diffusion problem using \
                             the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBDiffusionXZ::DwarfElephantRBDiffusionXZ(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters)
{
}

///----------------------------------PDEs-----------------------------------
Real
DwarfElephantRBDiffusionXZ::computeQpResidual()
{
  return _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusionXZ::computeQpJacobian()
{
  return _grad_phi[_j][_qp](0) * _grad_test[_i][_qp](2);
}

Real
DwarfElephantRBDiffusionXZ::computeQpOutput()
{
  return 1;
}
