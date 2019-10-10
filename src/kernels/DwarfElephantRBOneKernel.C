 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBOneKernel.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBOneKernel);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBOneKernel>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addParam<Real>("density", 1.0, "Defines the bulk density.");
  params.addParam<Real>("specific_heat", 1.0, "Defines the bulk specific heat.");
  params.addParam<Real>("norm_value_density", 1.0, "Defines the normalization value.");
  params.addParam<Real>("norm_value_specific_heat", 1.0, "Defines the normalization value.");
  params.addParam<bool>("transient", false, "Determines whether the problem is transient or steady state.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBOneKernel::DwarfElephantRBOneKernel(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
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
DwarfElephantRBOneKernel::computeQpResidual()
{
  if(!_transient)
    return _test[_i][_qp];
    else
      return  ((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat)) * _test[_i][_qp];
}

Real
DwarfElephantRBOneKernel::computeQpJacobian()
{
  return 0;
}
