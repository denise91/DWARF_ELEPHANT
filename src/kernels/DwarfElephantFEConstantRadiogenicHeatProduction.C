/**
 * This Kernel is implements a constant radiogenic heat production using the full
 * Finite Element solution. It is included in this package for validation
 * purposes.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEConstantRadiogenicHeatProduction.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEConstantRadiogenicHeatProduction);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEConstantRadiogenicHeatProduction>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("The class implements a constant radiogenic heat"
                              "production.");
  params.addRequiredParam<Real>("radiogenic_heat_production", "Defines the value"
                                "of the radiogenic heat production");
  params.addParam<Real>("norm_value_radiogenic_heat_production", 1.0, "Defines the normalization value.");
  params.addParam<Real>("density", 1.0, "Defines the bulk density.");
  params.addParam<Real>("specific_heat", 1.0, "Defines the bulk specific heat.");
  params.addParam<Real>("norm_value_density", 1.0, "Defines the normalization value.");
  params.addParam<Real>("norm_value_specific_heat", 1.0, "Defines the normalization value.");
  params.addParam<bool>("transient", false, "Determines whether the problem is transient or steady state.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEConstantRadiogenicHeatProduction::DwarfElephantFEConstantRadiogenicHeatProduction(const InputParameters & parameters) :
  Kernel(parameters),
  _radiogenic_heat_production(getParam<Real>("radiogenic_heat_production")),
  _norm_value_radiogenic_heat_production(getParam<Real>("norm_value_radiogenic_heat_production")),
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
DwarfElephantFEConstantRadiogenicHeatProduction::computeQpResidual()
{
  if(!_transient)
    return -(_radiogenic_heat_production/_norm_value_radiogenic_heat_production) * _test[_i][_qp];
  else
    return -(_radiogenic_heat_production/_norm_value_radiogenic_heat_production) *
           ((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat)) *
           _test[_i][_qp];
}

Real
DwarfElephantFEConstantRadiogenicHeatProduction::computeQpJacobian()
{
  return 0;
}
