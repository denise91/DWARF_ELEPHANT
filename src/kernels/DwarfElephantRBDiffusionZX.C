/** 
* This Kernel splits the diffusion operator into a sum of products of partial dervatives 
* This is for use with geometrical parametrizations 
*/ 
 
 ///---------------------------------INCLUDES-------------------------------- 
//MOOSE includes (DwarfElephant package) 
#include "DwarfElephantRBDiffusionZX.h" 

///----------------------------INPUT PARAMETERS----------------------------- 
template<> 
InputParameters validParams<DwarfElephantRBDiffusionZX>() 
{
  InputParameters params = validParams<DwarfElephantRBKernel>(); 
  params.addClassDescription("Implements a Diffusion problem using the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR------------------------------- 
DwarfElephantRBDiffusionZX::DwarfElephantRBDiffusionZX(const InputParameters & parameters) : 
  DwarfElephantRBKernel(parameters) 
{
}

///----------------------------------PDEs----------------------------------- 
Real
DwarfElephantRBDiffusionZX::computeQpResidual() 
{
  return 0;
}

Real
DwarfElephantRBDiffusionZX::computeQpJacobian()
{
  return _grad_phi[_j][_qp](2) * _grad_test[_i][_qp](0);
}

Real
DwarfElephantRBDiffusionZX::computeQpOutput()
{
  return 1;
}
