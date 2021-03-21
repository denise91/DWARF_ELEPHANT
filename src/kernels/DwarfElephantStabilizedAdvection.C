//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DwarfElephantStabilizedAdvection.h"
#include "Function.h"

template <>
InputParameters
validParams<DwarfElephantStabilizedAdvection>()
{
  InputParameters params = validParams<INSBase>();

  params.addClassDescription("This class solves the scalar advection equation, "
                             "$\\vec{a}\\cdot\\nabla u = f$ with SUPG stabilization.");
  params.addParam<FunctionName>("forcing_func", 0, "The forcing function, typically used for MMS.");
  MooseEnum tau_type("opt mod");
  params.addRequiredParam<MooseEnum>(
      "tau_type", tau_type, "The type of stabilization parameter to use.");
  params.addRequiredParam<FunctionName>("Xvelocity_function", "Function that returns the x component of the vector velocity");
  params.addRequiredParam<FunctionName>("Yvelocity_function", "Function that returns the y component of the vector velocity");
  params.addRequiredParam<FunctionName>("Zvelocity_function", "Function that returns the z component of the vector velocity");
  params.addParam<bool>("stabilized",true,"Flag to apply supg stabilization to kernel");
  return params;
}

DwarfElephantStabilizedAdvection::DwarfElephantStabilizedAdvection(const InputParameters & parameters)
  : INSBase(parameters),
    _ffn(getFunction("forcing_func")),
    _tau_type(getParam<MooseEnum>("tau_type")),
    _Xvelocity(getFunction("Xvelocity_function")),
    _Yvelocity(getFunction("Yvelocity_function")),
    _Zvelocity(getFunction("Zvelocity_function")),
    _second_u(second()),
    _rhoC(getMaterialProperty<Real>("specific_heat")),
    _kappa(getMaterialProperty<Real>("thermal_conductivity")),
    _stabilized(getParam<bool>("stabilized"))
{
}

Real
DwarfElephantStabilizedAdvection::computeQpResidual()
{
  Real tau_val = (_tau_type == "opt" ? tauNodal() : tau());
  //RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);
  RealVectorValue U(_Xvelocity.value(_t, _q_point[_qp]),_Yvelocity.value(_t, _q_point[_qp]),_Zvelocity.value(_t, _q_point[_qp]));
  return _rhoC[_qp] * (_test[_i][_qp] * U * _grad_u[_qp] 
                       + tau_val * (U *_grad_test[_i][_qp]) * (U *_grad_u[_qp] - _kappa[_qp]/_rhoC[_qp]*_second_u[_qp].tr() - _ffn.value(_t, _q_point[_qp])/_rhoC[_qp]));
}

Real
DwarfElephantStabilizedAdvection::computeQpJacobian()
{
  Real tau_val = (_tau_type == "opt" ? tauNodal() : tau());
  RealVectorValue U(_Xvelocity.value(_t, _q_point[_qp]),_Yvelocity.value(_t, _q_point[_qp]),_Zvelocity.value(_t, _q_point[_qp]));
  return _rhoC[_qp] * (_test[_i][_qp] * (U * _grad_phi[_j][_qp]) + tau_val * (U * _grad_test[_i][_qp]) * (U * _grad_phi[_j][_qp] - _kappa[_qp]/_rhoC[_qp]*_second_phi[_j][_qp].tr()));
}

Real DwarfElephantStabilizedAdvection::tau()
{
  Real nu = _kappa[_qp] / _rhoC[_qp];
  RealVectorValue U(_Xvelocity.value(_t, _q_point[_qp]),_Yvelocity.value(_t, _q_point[_qp]),_Zvelocity.value(_t, _q_point[_qp]));
  Real h = _current_elem->hmax();
  Real transient_part = _transient_term ? 4. / (_dt * _dt) : 0.;
  return (_stabilized) ? _alpha / std::sqrt(transient_part + (2. * U.norm() / h) * (2. * U.norm() / h) + 9. * (4. * nu / (h * h)) * (4. * nu / (h * h))) : 0;
}
