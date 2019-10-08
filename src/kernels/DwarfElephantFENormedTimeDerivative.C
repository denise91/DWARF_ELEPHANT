//---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFENormedTimeDerivative.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFENormedTimeDerivative);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFENormedTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addClassDescription("The class implements a constant radiogenic heat"
                              "production.");
  params.addRequiredParam<Real>("norm_value", "Defines the normalization value.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFENormedTimeDerivative::DwarfElephantFENormedTimeDerivative(const InputParameters & parameters) :
  TimeDerivative(parameters),
  _norm_value(getParam<Real>("norm_value"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation
Real
DwarfElephantFENormedTimeDerivative::computeQpResidual()
{
  return _norm_value * _u_dot[_qp] * _test[_i][_qp];
}

Real
DwarfElephantFENormedTimeDerivative::computeQpJacobian()
{
  return _norm_value * _du_dot_du[_qp] * _phi[_j][_qp] * _test[_i][_qp];
}
