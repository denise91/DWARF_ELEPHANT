/** 
* This Kernel splits the diffusion operator into a sum of products of partial dervatives 
* This is for use with geometrical parametrizations 
*/ 
 
 ///---------------------------------INCLUDES-------------------------------- 
//MOOSE includes (DwarfElephant package) 
#include "DwarfElephantRBDiffusionYX.h" 

///----------------------------INPUT PARAMETERS----------------------------- 
template<> 
InputParameters validParams<DwarfElephantRBDiffusionYX>() 
{
  InputParameters params = validParams<DwarfElephantRBKernel>(); 
  params.addClassDescription("Implements a Diffusion problem using the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR------------------------------- 
DwarfElephantRBDiffusionYX::DwarfElephantRBDiffusionYX(const InputParameters & parameters) : 
  DwarfElephantRBKernel(parameters) 
{
}

///----------------------------------PDEs----------------------------------- 
Real
DwarfElephantRBDiffusionYX::computeQpResidual() 
{
  return 0;
}

Real
DwarfElephantRBDiffusionYX::computeQpJacobian()
{
  return _grad_phi[_j][_qp](1) * _grad_test[_i][_qp](0);
}

Real
DwarfElephantRBDiffusionYX::computeQpOutput()
{
  return 1;
}
