/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
 * This is for use with geometrical parametrizations
 */

///---------------------------------INCLUDES--------------------------------
//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBDiffusionZZ.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionZZ>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a Diffusion problem using \
                             the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBDiffusionZZ::DwarfElephantRBDiffusionZZ(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters)
{
}

///----------------------------------PDEs-----------------------------------
Real
DwarfElephantRBDiffusionZZ::computeQpResidual()
{
  return _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusionZZ::computeQpJacobian()
{
  return _grad_phi[_j][_qp](2) * _grad_test[_i][_qp](2);
}

Real
DwarfElephantRBDiffusionZZ::computeQpOutput()
{
  return 1;
}
