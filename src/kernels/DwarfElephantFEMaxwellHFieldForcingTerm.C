 //---------------------------------INCLUDES-------------------------------
#include "Assembly.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEMaxwellHFieldForcingTerm.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEMaxwellHFieldForcingTerm);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEMaxwellHFieldForcingTerm>()
{
  InputParameters params = validParams<VectorKernel>();
  params.addRequiredParam<Real>("angular_frequency",
                                "Defines the value of the angular frequency.");
  params.addParam<Real>("magnetic_permeability", 1.2566370614359173e-06,
                        "Defines the value of the magnetic permeability.");
  params.addParam<bool>("imaginary_part",false,
                        "If set to true this means that we are currently solving for the imaginary part.");
  params.addRequiredCoupledVar("E_field", "The coupled part of the E-Field which provides the force");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEMaxwellHFieldForcingTerm::DwarfElephantFEMaxwellHFieldForcingTerm(const InputParameters & parameters) :
  VectorKernel(parameters),
  _H_var(coupled("E_field")),
  _H(coupledVectorValue("E_field")),
  _angular_freq(getParam<Real>("angular_frequency")),
  _mag_perm(getParam<Real>("magnetic_permeability")),
  _imaginary_part(getParam<bool>("imaginary_part"))
{
  _pre_factor=1.0;
  if(_imaginary_part)
    _pre_factor*=-1;
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFEMaxwellHFieldForcingTerm::computeQpResidual()
{
  return _pre_factor*(_angular_freq*_mag_perm) * _H[_qp] * _test[_i][_qp];
}

Real
DwarfElephantFEMaxwellHFieldForcingTerm::computeQpJacobian()
{
  return 0;
}

Real
DwarfElephantFEMaxwellHFieldForcingTerm::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _H_var)
    return _pre_factor*(_angular_freq*_mag_perm) * _phi[_j][_qp] * _test[_i][_qp];
  return 0.0;
}
