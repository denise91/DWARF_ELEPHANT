/**
 * This Kernel is implements a electrical conduction problem using the
 * reduced basis solution. It is included in this package for validation
 * purposes.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBElectricalConduction.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBElectricalConduction);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBElectricalConduction>()
{
  InputParameters params = validParams<DwarfElephantRBDiffusion>();
  params.addClassDescription("The class implements a electrical conduction \
                              problem.");
  params.addRequiredParam<Real>("resisitivty", "Defines the value of the resisitivty");
  params.addParam<Real>("norm_value", 1.0, "Defines the normalization value.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBElectricalConduction::DwarfElephantRBElectricalConduction(const InputParameters & parameters) :
  DwarfElephantRBDiffusion(parameters),
  _resistivity(getParam<Real>("resisitivty")),
  _norm_value(getParam<Real>("norm_value"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantRBElectricalConduction::computeQpResidual()
{
  return -(_norm_value/_resistivity) * DwarfElephantRBDiffusion::computeQpResidual();
}

Real
DwarfElephantRBElectricalConduction::computeQpJacobian()
{
  return (_norm_value/_resistivity) * DwarfElephantRBDiffusion::computeQpJacobian();
}
