/** 
* This Kernel splits the diffusion operator into a sum of products of partial dervatives 
* This is for use with geometrical parametrizations 
*/ 
 
 ///---------------------------------INCLUDES-------------------------------- 
//MOOSE includes (DwarfElephant package) 
#include "DwarfElephantRBDiffusionZY.h" 

///----------------------------INPUT PARAMETERS----------------------------- 
template<> 
InputParameters validParams<DwarfElephantRBDiffusionZY>() 
{
  InputParameters params = validParams<DwarfElephantRBKernel>(); 
  params.addClassDescription("Implements a Diffusion problem using \ 
                             the RBKernel.");
  return params;
}

///-------------------------------CONSTRUCTOR------------------------------- 
DwarfElephantRBDiffusionZY::DwarfElephantRBDiffusionZY(const InputParameters & parameters) : 
  DwarfElephantRBKernel(parameters) 
{
}

///----------------------------------PDEs----------------------------------- 
Real
DwarfElephantRBDiffusionZY::computeQpResidual() 
{
  return _grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusionZY::computeQpJacobian()
{
  return _grad_phi[_j][_qp](2) * _grad_test[_i][_qp](1);
}

Real
DwarfElephantRBDiffusionZY::computeQpOutput()
{
  return 1;
}
