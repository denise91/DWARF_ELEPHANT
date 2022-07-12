/**
 * This Kernel is implements the source term for the calculation of the
 * gravitation field using the full
 * Finite Element solution. It is included in this package for validation
 * purposes.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEGravityFieldSourceTerm.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEGravityFieldSourceTerm);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEGravityFieldSourceTerm>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("The class implements the source term for the"
                              "calculation of the gravity field.");
  params.addRequiredParam<Real>("density", "Defines the bulk density.");
  params.addParam<Real>("gravitational_constant", 6.67408e-11, "Defines the gravitational constant.");
  params.addParam<Real>("norm_value_density", 1.0, "Defines the normalization value.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEGravityFieldSourceTerm::DwarfElephantFEGravityFieldSourceTerm(const InputParameters & parameters) :
  Kernel(parameters),
  _density(getParam<Real>("density")),
  _gravitational_constant(getParam<Real>("gravitational_constant")),
  _norm_value_density(getParam<Real>("norm_value_density"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFEGravityFieldSourceTerm::computeQpResidual()
{
  return -(_density/_norm_value_density)* 4 * libMesh::pi * _gravitational_constant *
          _test[_i][_qp];
}

Real
DwarfElephantFEGravityFieldSourceTerm::computeQpJacobian()
{
  return 0;
}
