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


struct ShiftedGaussian_3DRFA : public RBParametrizedFunction
{
  virtual Number evaluate(const RBParameters & mu,
                          const Point & p,
                          const Elem & elem)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real x_prime = mu.get_value("mu_2");
    Real y_prime = mu.get_value("mu_3");
    Real z_prime = mu.get_value("mu_4");
    Number result;
    Number x_new, y_new, z_new, t0;
    double matrix[3][3]={0}, vec[3][1]={0}, L = 0.1, r = 3e-3, l = 5e-2;
    double d = 3*r, h = 1.5*l;
if (elem.subdomain_id() == 1)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = (d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 2)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = (d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 3)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = (L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = (L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 4)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 5)
 {
  matrix[0][0] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[0][1] = (r*(1.0/2.0)-r_0*(1.0/2.0))/r;
  matrix[1][0] = (r*(1.0/2.0)-r_0*(1.0/2.0))/r;
  matrix[1][1] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));  vec[0][0] = 0; vec[1][0] = 0; vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l*r_0-h*l_0*r_0)/(fabs(l)*fabs(r)*fabs(L-h));
}
if (elem.subdomain_id() == 6)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 7)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 8)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 9)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 10)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][1] = (d*r_0+h*r)/(r*(d+h));
  matrix[1][2] = -(d*(r-r_0))/(r*(d+h));
  matrix[2][1] = -(h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h)); vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 11)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 12)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 13)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 14)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 15)
 {
  matrix[0][0] = (d*r_0+h*r)/(r*(d+h));
  matrix[0][2] = (d*(r-r_0))/(r*(d+h));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][0] = (h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));  vec[0][0] = 0; vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 16)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 17)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 18)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 19)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 20)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][1] = (d*r_0+h*r)/(r*(d+h));
  matrix[1][2] = (d*(r-r_0))/(r*(d+h));
  matrix[2][1] = (h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h)); vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 21)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 22)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (elem.subdomain_id() == 23)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 24)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 25)
 {
  matrix[0][0] = (d*r_0+h*r)/(r*(d+h));
  matrix[0][2] = -(d*(r-r_0))/(r*(d+h));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][0] = -(h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));  vec[0][0] = 0; vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (elem.subdomain_id() == 26)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = (d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = (d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 27)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 28)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = (L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 29)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = (L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (elem.subdomain_id() == 30)
 {
  matrix[0][0] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[0][1] = (r*(-1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[1][0] = (r*(-1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[1][1] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));  vec[0][0] = 0; vec[1][0] = 0; vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l*r_0-h*l_0*r_0)/(fabs(l)*fabs(r)*fabs(L-h));
}
if (elem.subdomain_id() == 31)
 {
  matrix[0][0] = r_0/r;
  matrix[1][1] = r_0/r;
  matrix[2][2] = l_0/l;  vec[0][0] = 0; vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs(l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/fabs(l);
}
if (elem.subdomain_id() == 32)
 {
  matrix[0][0] = r_0/r;
  matrix[1][1] = r_0/r;
  matrix[2][2] = l_0/l;  vec[0][0] = 0; vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs(l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/fabs(l);
}
x_new = matrix[0][0]*p(0) + matrix[0][1]*p(1) + matrix[0][2]*p(2) + vec[0][0];
y_new = matrix[1][0]*p(0) + matrix[1][1]*p(1) + matrix[1][2]*p(2) + vec[1][0];
z_new = matrix[2][0]*p(0) + matrix[2][1]*p(1) + matrix[2][2]*p(2) + vec[2][0];
return 10*exp(-(pow(x_prime - x_new,2) + pow(y_prime - y_new,2) + pow(z_prime - z_new,2)));//exp(-(pow(x_prime - x_new,2) + pow(y_prime - y_new,2) + pow(z_prime - z_new,2))) * t0; // Forcing function for geometrical parametrization example
 } 
 }; 
#endif //DWARFELEPHANTNONAFFINEFUNCTION_H
