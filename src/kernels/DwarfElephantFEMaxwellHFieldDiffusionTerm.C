 //---------------------------------INCLUDES-------------------------------
#include "Assembly.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEMaxwellHFieldDiffusionTerm.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEMaxwellHFieldDiffusionTerm);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEMaxwellHFieldDiffusionTerm>()
{
  InputParameters params = validParams<VectorKernel>();
  params.addRequiredParam<Real>("electrical_conductivity",
                        "Defines the value of the electrical conductivity.");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEMaxwellHFieldDiffusionTerm::DwarfElephantFEMaxwellHFieldDiffusionTerm(const InputParameters & parameters) :
  VectorKernel(parameters),
  _elec_cond(getParam<Real>("electrical_conductivity"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFEMaxwellHFieldDiffusionTerm::computeQpResidual()
{
  return (1/_elec_cond)*_grad_u[_qp].contract(_grad_test[_i][_qp]);
}

Real
DwarfElephantFEMaxwellHFieldDiffusionTerm::computeQpJacobian()
{
  return (1/_elec_cond)*_grad_phi[_j][_qp].contract(_grad_test[_i][_qp]);
}
