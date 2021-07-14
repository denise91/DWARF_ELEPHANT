/**
 * This Kernel implements the Diffusion problem by using the RB method.
 * It is important to note that every PDE that will be used within the RB
 * method has to inherit from RBKernel and not from Kernel.
 * Furthermore, one should recall that the stiffness matrix and the load
 * vector are constructed out of the parameter independent part of the
 * PDE. Therefore, the functions computeQpResidual() and computeQpJacobian()
 * should only contain this parameter independent part. Consequently, the
 * RBDiffusion Kernel is used for a Conduction problem.
 */

///---------------------------------INCLUDES--------------------------------
//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBDiffusion.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusion>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a Diffusion problem using \
                             the RBKernel.");
  params.addParam<Real>("thermal_conductivity",1.0,"Thermal conductivity");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBDiffusion::DwarfElephantRBDiffusion(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters), _thermal_conductivity(getParam<Real>("thermal_conductivity"))
{
}

///----------------------------------PDEs-----------------------------------
Real
DwarfElephantRBDiffusion::computeQpResidual()
{
  return 0;
}

Real
DwarfElephantRBDiffusion::computeQpJacobian()
{
  return _thermal_conductivity * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusion::computeQpOutput()
{
  return 1;
}
