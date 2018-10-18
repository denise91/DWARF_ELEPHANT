/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
 * This is for use with geometrical parametrizations
 */

///---------------------------------INCLUDES--------------------------------
//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBDiffusionYZ.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionYZ>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a Diffusion problem using \
                             the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBDiffusionYZ::DwarfElephantRBDiffusionYZ(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters)
{
}

///----------------------------------PDEs-----------------------------------
Real
DwarfElephantRBDiffusionYZ::computeQpResidual()
{
  return _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusionYZ::computeQpJacobian()
{
  return _grad_phi[_j][_qp](1) * _grad_test[_i][_qp](2);
}

Real
DwarfElephantRBDiffusionYZ::computeQpOutput()
{
  return 1;
}
