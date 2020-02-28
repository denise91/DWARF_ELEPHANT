/**
 * This Kernel is implements a constant radiogenic heat production using the
 * Reduced Basis solution.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBConstantRadiogenicHeatProduction.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBConstantRadiogenicHeatProduction);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBConstantRadiogenicHeatProduction>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
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
DwarfElephantRBConstantRadiogenicHeatProduction::DwarfElephantRBConstantRadiogenicHeatProduction(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
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
DwarfElephantRBConstantRadiogenicHeatProduction::computeQpResidual()
{
  if(!_transient)
    return (_radiogenic_heat_production/_norm_value_radiogenic_heat_production) * _test[_i][_qp];
  else
    return ((_radiogenic_heat_production*_norm_value_density*_norm_value_specific_heat)/
           (_norm_value_radiogenic_heat_production*_density*_specific_heat)) *
           _test[_i][_qp];
}

Real
DwarfElephantRBConstantRadiogenicHeatProduction::computeQpJacobian()
{
  return 0;
}
