 //---------------------------------INCLUDES-------------------------------
#include "Assembly.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEMaxwellEFieldDiffusionTerm2D.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEMaxwellEFieldDiffusionTerm2D);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEMaxwellEFieldDiffusionTerm2D>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("magnetic_permeability", 1.2566370614359173e-06,
                        "Defines the value of the magnetic permeability.");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEMaxwellEFieldDiffusionTerm2D::DwarfElephantFEMaxwellEFieldDiffusionTerm2D(const InputParameters & parameters) :
  Kernel(parameters),
  _mag_perm(getParam<Real>("magnetic_permeability"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFEMaxwellEFieldDiffusionTerm2D::computeQpResidual()
{
  return (1/_mag_perm)*_grad_u[_qp]*_grad_test[_i][_qp];
}

Real
DwarfElephantFEMaxwellEFieldDiffusionTerm2D::computeQpJacobian()
{
  return (1/_mag_perm)*_grad_phi[_j][_qp]*_grad_test[_i][_qp];
}
