 //---------------------------------INCLUDES-------------------------------
#include "Assembly.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEMaxwellEFieldForcingTerm.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEMaxwellEFieldForcingTerm);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEMaxwellEFieldForcingTerm>()
{
  InputParameters params = validParams<VectorKernel>();
  params.addRequiredParam<Real>("angular_frequency",
                                "Defines the value of the angular frequency.");
  params.addRequiredParam<Real>("electrical_conductivity",
                                "Defines the value of the electrical conductivity.");
  params.addParam<bool>("imaginary_part",false,
                        "If set to true this means that we are currently solving for the imaginary part.");
  params.addRequiredCoupledVar("E_field", "The coupled part of the E-Field which provides the force");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEMaxwellEFieldForcingTerm::DwarfElephantFEMaxwellEFieldForcingTerm(const InputParameters & parameters) :
  VectorKernel(parameters),
  _E_var(coupled("E_field")),
  _E(coupledVectorValue("E_field")),
  _angular_freq(getParam<Real>("angular_frequency")),
  _elec_cond(getParam<Real>("electrical_conductivity")),
  _imaginary_part(getParam<bool>("imaginary_part"))
{
  _pre_factor=1.0;
  if(_imaginary_part)
    _pre_factor*=-1;
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFEMaxwellEFieldForcingTerm::computeQpResidual()
{
  return _pre_factor*(_angular_freq*_elec_cond) * _E[_qp] * _test[_i][_qp];
}

Real
DwarfElephantFEMaxwellEFieldForcingTerm::computeQpJacobian()
{
  return 0;
}

Real
DwarfElephantFEMaxwellEFieldForcingTerm::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _E_var)
    return _pre_factor*(_angular_freq*_elec_cond) * _phi[_j][_qp] * _test[_i][_qp];
  return 0.0;
}
