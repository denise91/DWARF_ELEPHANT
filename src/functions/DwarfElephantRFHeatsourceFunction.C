#include "DwarfElephantRFHeatsourceFunction.h"

template<>
InputParameters
validParams<DwarfElephantRFHeatsourceFunction>()
{
  InputParameters params = validParams<Function>();
  params.addRequiredParam<std::vector<Real>>("needle_active_region_p1","Coordinates of the upper point of the needle active region.");
  params.addRequiredParam<std::vector<Real>>("needle_active_region_p2","Coordinates of the lower point of the needle active region.");
  params.addRequiredParam<Real>("needle_power","The input power of the RF needle.");

  return params;
}

DwarfElephantRFHeatsourceFunction::DwarfElephantRFHeatsourceFunction(const InputParameters & parameters) :
  Function(parameters),
  _needle_active_region_p1(getParam<std::vector<Real>>("needle_active_region_p1")),
  _needle_active_region_p2(getParam<std::vector<Real>>("needle_active_region_p2")),
  _needle_power(getParam<Real>("needle_power"))
{

}

Real DwarfElephantRFHeatsourceFunction::value(Real /*t*/, const Point & p) const
{
  RealVectorValue _X_bar(_needle_active_region_p1[0], _needle_active_region_p1[1], _needle_active_region_p1[2]);
  RealVectorValue _Y_bar(_needle_active_region_p2[0], _needle_active_region_p2[1], _needle_active_region_p2[2]);
  RealVectorValue _A_bar(p(0),p(1),p(2));

  RealVectorValue _temp_vec = _X_bar - _Y_bar;
  RealVectorValue _Z_cap = _temp_vec / _temp_vec.norm();
  _temp_vec = _X_bar + _Y_bar;
  RealVectorValue _O_cap = _temp_vec * 0.5;

  _temp_vec = _A_bar - _O_cap;
  RealVectorValue _r_A_bar = _temp_vec - _Z_cap * (_temp_vec * _Z_cap);

  Real _r_needle = _r_A_bar.norm();
  Real _z_needle = _temp_vec * _Z_cap; 

  Real Q_G = exp(-pow(_r_needle,2)/(2. * pow(2.201e-3,2)));
  Real _sigmoid_plus = 1./(1. + exp(-1.303e4*(_z_needle - 1.052e-2)));
  Real _sigmoid_minus = 1./(1. + exp(-1.303e4*(_z_needle + 1.052e-2)));
  Real P = (_needle_power * 1.383e15 * pow(_z_needle,4) + 2.624e6)*(_sigmoid_minus *(1. - _sigmoid_plus));
  return P*Q_G;
}
