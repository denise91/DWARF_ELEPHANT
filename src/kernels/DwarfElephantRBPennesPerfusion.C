/**
 * This Kernel is implements a Pennes Perfusion term using the
 * reduced basis method.
 */

 ///---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBPennesPerfusion.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBPennesPerfusion>()
{
  InputParameters params = validParams<DwarfElephantRBDiffusion>();
  params.addClassDescription("The class implements a Pennes perfusion term.");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBPennesPerfusion::DwarfElephantRBPennesPerfusion(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters)
{
}

///----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantRBPennesPerfusion::computeQpResidual()
{
  return 0;
}

Real
DwarfElephantRBPennesPerfusion::computeQpJacobian()
{
  return 35.0 * 3617.0 * _phi[_j][_qp] * _test[_i][_qp];
}
