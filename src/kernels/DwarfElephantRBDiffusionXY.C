/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
 * This is for use with geometrical parametrizations
 */

///---------------------------------INCLUDES--------------------------------
//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBDiffusionXY.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionXY>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a Diffusion problem using \
                             the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBDiffusionXY::DwarfElephantRBDiffusionXY(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters)
{
}

///----------------------------------PDEs-----------------------------------
Real
DwarfElephantRBDiffusionXY::computeQpResidual()
{
  return _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusionXY::computeQpJacobian()
{
  return _grad_phi[_j][_qp](0) * _grad_test[_i][_qp](1);
}

Real
DwarfElephantRBDiffusionXY::computeQpOutput()
{
  return 1;
}
