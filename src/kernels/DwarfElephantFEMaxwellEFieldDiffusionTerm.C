 //---------------------------------INCLUDES-------------------------------
#include "Assembly.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEMaxwellEFieldDiffusionTerm.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEMaxwellEFieldDiffusionTerm);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEMaxwellEFieldDiffusionTerm>()
{
  InputParameters params = validParams<VectorKernel>();
  params.addParam<Real>("magnetic_permeability", 1.2566370614359173e-06,
                        "Defines the value of the magnetic permeability.");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEMaxwellEFieldDiffusionTerm::DwarfElephantFEMaxwellEFieldDiffusionTerm(const InputParameters & parameters) :
  VectorKernel(parameters),
  _mag_perm(getParam<Real>("magnetic_permeability"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFEMaxwellEFieldDiffusionTerm::computeQpResidual()
{
  return (1/_mag_perm)*_grad_u[_qp].contract(_grad_test[_i][_qp]);
}

Real
DwarfElephantFEMaxwellEFieldDiffusionTerm::computeQpJacobian()
{
  return (1/_mag_perm)*_grad_phi[_j][_qp].contract(_grad_test[_i][_qp]);
}
