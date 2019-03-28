// For RBnics Geometry
#ifndef DWARFELEPHANTNONAFFINEFUNCTION_H
#define DWARFELEPHANTNONAFFINEFUNCTION_H

 
// libMesh includes
#include "libmesh/libmesh.h"
#include "libmesh/mesh.h"
#include "libmesh/equation_systems.h"
#include "libmesh/fe.h"
#include "libmesh/quadrature.h"
#include "libmesh/dof_map.h"
#include "libmesh/dense_matrix.h"
#include "libmesh/dense_vector.h"
#include "libmesh/fe_interface.h"
#include "libmesh/elem.h"
#include "libmesh/vector_value.h"


// rbOOmit includes
#include "libmesh/rb_assembly_expansion.h"
#include "libmesh/rb_eim_theta.h"
#include "libmesh/rb_parametrized_function.h"


// MOOSE includes
#include "Function.h"

// Bring in bits from the libMesh namespace.
// Just the bits we are using, since this is a header.
using libMesh::ElemAssembly;
using libMesh::FEMContext;
using libMesh::Number;
using libMesh::RBAssemblyExpansion;
using libMesh::RBEIMAssembly;
using libMesh::RBEIMConstruction;
using libMesh::RBParametrizedFunction;
using libMesh::RBParameters;
using libMesh::RBTheta;
using libMesh::RBThetaExpansion;
using libMesh::Real;
using libMesh::RealGradient;
using libMesh::Elem;
using libMesh::FEBase;
using libMesh::VectorValue;
using libMesh::pi;


struct ShiftedGaussian : public RBParametrizedFunction
{
  virtual Number evaluate(const RBParameters & mu,
                          const Point & p,
                          const Elem & elem)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    //Real x_prime = mu.get_value("mu_2");
    //Real y_prime = mu.get_value("mu_3");
    Real _needle_center_x = mu.get_value("mu_2");
    Real _needle_center_y = -0.04;//mu.get_value("mu_3");
    Real _needle_axis_theta = pi/2.0;
    Real _needle_axis_phi = pi;//mu.get_value("mu_3");
    
    Real _needle_power = 1.0;

    Number result;
    Number x_new, y_new, t0;
    double matrix[2][2]={0}, vec[2][1]={0}, L = 0.1, r = 0.03, l = 0.06;
if (elem.subdomain_id() == 2)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-l));
  matrix[1][1] = (L-l_0)/(L-l);  vec[0][0] = (L*l*(r-r_0)*(1.0/2.0))/(r*(L-l));
  vec[1][0] = (L*(l-l_0)*(-1.0/2.0))/(L-l);
  t0 = fabs(r_0*(L-l_0))/(fabs(r)*fabs(L-l));
}
if (elem.subdomain_id() == 1)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = (r*2.0-r_0*2.0)/(L-l);
  matrix[1][1] = (L-l_0)/(L-l);  vec[0][0] = -(L*(r-r_0))/(L-l);
  vec[1][0] = (L*(l-l_0)*(-1.0/2.0))/(L-l);
  t0 = fabs(L-l_0)/fabs(L-l);
}
if (elem.subdomain_id() == 3)
 {
  matrix[0][0] = (L-r_0*2.0)/(L-r*2.0);
  matrix[1][0] = -(l-l_0)/(L-r*2.0);
  matrix[1][1] = 1.0;  vec[0][0] = -(L*(r-r_0))/(L-r*2.0);
  vec[1][0] = (L*(l-l_0))/(L*2.0-r*4.0);
  t0 = fabs(L-r_0*2.0)/fabs(L-r*2.0);
}
if (elem.subdomain_id() == 4)
 {
  matrix[0][0] = (L-r_0*2.0)/(L-r*2.0);
  matrix[1][0] = (L*(l-l_0))/(l*(L-r*2.0));
  matrix[1][1] = l_0/l;  vec[0][0] = -(L*(r-r_0))/(L-r*2.0);
  vec[1][0] = -(L*r*(l-l_0))/(l*(L-r*2.0));
  t0 = fabs(l_0*(L-r_0*2.0))/(fabs(l)*fabs(L-r*2.0));
}
if (elem.subdomain_id() == 5)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = (r*2.0-r_0*2.0)/(L-l);
  matrix[1][1] = (L-l_0)/(L-l);  vec[0][0] = (L*(r-r_0))/(L-l);
  vec[1][0] = (L*(l-l_0)*(1.0/2.0))/(L-l);
  t0 = fabs(L-l_0)/fabs(L-l);
}
if (elem.subdomain_id() == 6)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-l));
  matrix[1][1] = (L-l_0)/(L-l);  vec[0][0] = (L*l*(r-r_0)*(-1.0/2.0))/(r*(L-l));
  vec[1][0] = (L*(l-l_0)*(1.0/2.0))/(L-l);
  t0 = fabs(r_0*(L-l_0))/(fabs(r)*fabs(L-l));
}
if (elem.subdomain_id() == 7)
 {
  matrix[0][0] = (L-r_0*2.0)/(L-r*2.0);
  matrix[1][0] = -(l-l_0)/(L-r*2.0);
  matrix[1][1] = 1.0;  vec[0][0] = (L*(r-r_0))/(L-r*2.0);
  vec[1][0] = -(L*(l-l_0))/(L*2.0-r*4.0);
  t0 = fabs(L-r_0*2.0)/fabs(L-r*2.0);
}
if (elem.subdomain_id() == 8)
 {
  matrix[0][0] = (L-r_0*2.0)/(L-r*2.0);
  matrix[1][0] = (L*(l-l_0))/(l*(L-r*2.0));
  matrix[1][1] = l_0/l;  vec[0][0] = (L*(r-r_0))/(L-r*2.0);
  vec[1][0] = (L*r*(l-l_0))/(l*(L-r*2.0));
  t0 = fabs(l_0*(L-r_0*2.0))/(fabs(l)*fabs(L-r*2.0));
}
if (elem.subdomain_id() == 9)
 {
  matrix[0][0] = r_0/r;
  matrix[1][1] = l_0/l;  vec[0][0] = 0;  vec[1][0] = 0;
  t0 = fabs(l_0*r_0)/(fabs(l)*fabs(r));
}
x_new = matrix[0][0]*p(0) + matrix[0][1]*p(1) + vec[0][0];
y_new = matrix[1][0]*p(0) + matrix[1][1]*p(1) + vec[1][0];
//return exp(-(pow(x_prime - x_new,2) + pow(y_prime - y_new,2))) * t0; // Forcing function for geometrical parametrization example

  //VectorValue<Real> _X_bar(_needle_active_region_p1_x, _needle_active_region_p1_y, 0.);
  //VectorValue<Real> _Y_bar(_needle_active_region_p2_x, _needle_active_region_p2_y, 0.);
  VectorValue<Real> _A_bar(x_new,y_new,0.);

  //VectorValue<Real> _temp_vec = _X_bar - _Y_bar;
  //VectorValue<Real> _Z_cap = _temp_vec / _temp_vec.norm(); // Unit vector along needle
  VectorValue<Real> _Z_cap(std::sin(_needle_axis_theta)*std::cos(_needle_axis_phi),std::sin(_needle_axis_theta)*std::sin(_needle_axis_phi),std::cos(_needle_axis_theta));

  //_temp_vec = _X_bar + _Y_bar;
  //VectorValue<Real> _O_cap = _temp_vec * 0.5; // position vector of needle center
  VectorValue<Real> _O_cap(_needle_center_x, _needle_center_y, 0);

  VectorValue<Real> _temp_vec = _A_bar - _O_cap;
  VectorValue<Real> _r_A_bar = _temp_vec - _Z_cap * (_temp_vec * _Z_cap);

  Real _r_needle = _r_A_bar.norm();
  Real _z_needle = _temp_vec * _Z_cap; 

  Real Q_G = exp(-pow(_r_needle,2)/(2. * pow(2.201e-3,2)));
  Real _sigmoid_plus = 1./(1. + exp(-1.303e4*(_z_needle - 1.052e-2)));
  Real _sigmoid_minus = 1./(1. + exp(-1.303e4*(_z_needle + 1.052e-2)));
  Real P = (_needle_power * 1.383e15 * pow(_z_needle,4) + 2.624e6)*(_sigmoid_minus *(1. - _sigmoid_plus));
  return P*Q_G*t0;
 } 
}; 
#endif //DWARFELEPHANTNONAFFINEFUNCTION_H
