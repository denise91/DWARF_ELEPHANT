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
  params.addParam<Real>("perfusion_coeff",1.0,"Perfusion coefficient");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBPennesPerfusion::DwarfElephantRBPennesPerfusion(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters), _perfusion_coeff(getParam<Real>("perfusion_coeff"))
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
  return _perfusion_coeff * _phi[_j][_qp] * _test[_i][_qp];
}
