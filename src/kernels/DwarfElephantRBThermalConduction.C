/**
 * This Kernel is implements a thermal conduction problem using the
 * reduced basis solution. It is included in this package for validation
 * purposes.
 */

 ///---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBThermalConduction.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBThermalConduction>()
{
  InputParameters params = validParams<DwarfElephantRBDiffusion>();
  params.addClassDescription("The class implements a thermal conduction \
                              problem.");
  params.addRequiredParam<Real>("thermal_conductivity", "Defines the value of the thermal conductivity");
  params.addParam<Real>("norm_value", 1.0, "Defines the normalization value.");
  return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBThermalConduction::DwarfElephantRBThermalConduction(const InputParameters & parameters) :
  DwarfElephantRBDiffusion(parameters),
  _lambda(getParam<Real>("thermal_conductivity")),
  _norm_value(getParam<Real>("norm_value"))
{
}

///----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantRBThermalConduction::computeQpResidual()
{
  return -(_lambda/_norm_value) * DwarfElephantRBDiffusion::computeQpResidual()*0;
}

Real
DwarfElephantRBThermalConduction::computeQpJacobian()
{
  return (_lambda/_norm_value) * DwarfElephantRBDiffusion::computeQpJacobian();
}
