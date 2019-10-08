/**
 * This Kernel is implements a thermal conduction problem using the full
 * Finite Element solution. It is included in this package for validation
 * purposes.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEThermalConduction.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEThermalConduction);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEThermalConduction>()
{
  InputParameters params = validParams<Diffusion>();
  params.addClassDescription("The class implements a thermal conduction \
                              problem.");
  params.addRequiredParam<Real>("thermal_conductivity", "Defines the value of the thermal conductivity");
  params.addParam<Real>("density", 1.0, "Defines the bulk density.");
  params.addParam<Real>("specific_heat", 1.0, "Defines the bulk specific heat.");
  params.addParam<Real>("norm_value_thermal_conductivity", 1.0, "Defines the normalization value.");
  params.addParam<Real>("norm_value_density", 1.0, "Defines the normalization value.");
  params.addParam<Real>("norm_value_specific_heat", 1.0, "Defines the normalization value.");
  params.addParam<bool>("transient", false, "Determines whether the problem is transient or steady state.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEThermalConduction::DwarfElephantFEThermalConduction(const InputParameters & parameters) :
  Diffusion(parameters),
  // gets the thermal conductivity directly from the corresponding material file for future use in case of varying parameters
//  _lambda(getMaterialProperty<Real>("thermal_conductivity"))
  _thermal_conductivity(getParam<Real>("thermal_conductivity")),
  _norm_value_thermal_conductivity(getParam<Real>("norm_value_thermal_conductivity")),
  _transient(getParam<bool>("transient")),
  _density(getParam<Real>("density")),
  _specific_heat(getParam<Real>("specific_heat")),
  _norm_value_density(getParam<Real>("norm_value_density")),
  _norm_value_specific_heat(getParam<Real>("norm_value_specific_heat"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFEThermalConduction::computeQpResidual()
{
//  return _lambda[_qp] * Diffusion::computeQpResidual(); // in case of getting lambda from the material property class
  if(!_transient)
    return (_thermal_conductivity/_norm_value_thermal_conductivity) * Diffusion::computeQpResidual();
  else
    return (_thermal_conductivity/_norm_value_thermal_conductivity) *
           ((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat)) *
           Diffusion::computeQpResidual();
}

Real
DwarfElephantFEThermalConduction::computeQpJacobian()
{
//  return _lambda[_qp] * Diffusion::computeQpJacobian(); // in case of getting lambda from the material property class
  if(!_transient)
    return (_thermal_conductivity/_norm_value_thermal_conductivity) * Diffusion::computeQpJacobian();
  else
    return (_thermal_conductivity/_norm_value_thermal_conductivity) *
           ((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat)) *
           Diffusion::computeQpJacobian();
}
