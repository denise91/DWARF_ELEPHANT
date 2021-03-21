///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTGEOM3DRBTHETA_RFA_H
#define DWARFELEPHANTGEOM3DRBTHETA_RFA_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

// Forward Declarations
namespace libMesh
{
  class RBParameters;
  class RBTheta;
}
struct MTheta_subdomain_1: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * fabs(L*l-h*_mu.get_value("mu_1"))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_2: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * fabs(L*l-h*_mu.get_value("mu_1"))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_3: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * (fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_4: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * (fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_5: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct MTheta_subdomain_6: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_7: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_8: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_9: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_10: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    Real h = 1.5*l;
    return rho_C * (fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_11: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_12: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_13: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_14: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_15: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    Real h = 1.5*l;
    return rho_C * (fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_16: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_17: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_18: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_19: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_20: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    Real h = 1.5*l;
    return rho_C * (fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_21: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_22: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * fabs(L*r-d*_mu.get_value("mu_0"))/(fabs(L-d)*fabs(r));
  }
};
struct MTheta_subdomain_23: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_24: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    return rho_C * (fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_25: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real d = 3*r;
    Real h = 1.5*l;
    return rho_C * (fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct MTheta_subdomain_26: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * fabs(L*l-h*_mu.get_value("mu_1"))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_27: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * fabs(L*l-h*_mu.get_value("mu_1"))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_28: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * (fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_29: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * (fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct MTheta_subdomain_30: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real rho_C = _mu.get_value("mu_12");
    Real h = 1.5*l;
    return rho_C * fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct MTheta_subdomain_31: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real rho_C = _mu.get_value("mu_12");
    return rho_C * (fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct MTheta_subdomain_32: RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real rho_C = _mu.get_value("mu_12");
    return rho_C * (fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return ((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return ((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return ((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return ((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r*r+_mu.get_value("mu_0")*_mu.get_value("mu_0"))*(1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r+_mu.get_value("mu_0"))*(r-_mu.get_value("mu_0"))*(-1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r+_mu.get_value("mu_0"))*(r-_mu.get_value("mu_0"))*(-1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r*r+_mu.get_value("mu_0")*_mu.get_value("mu_0"))*(1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*(r*r)*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*l+h*_mu.get_value("mu_1"),2.0)+(d*d)*(l*l)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*_mu.get_value("mu_0")+h*r,2.0)+(h*h)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*l+h*_mu.get_value("mu_1"),2.0)+(d*d)*(l*l)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*(r*r)*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*_mu.get_value("mu_0")+h*r,2.0)+(h*h)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxX3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return ((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxX4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_maxX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*(r*r)*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_maxX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*l+h*_mu.get_value("mu_1"),2.0)+(d*d)*(l*l)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_maxX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_maxX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_maxX5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*_mu.get_value("mu_0")+h*r,2.0)+(h*h)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minY1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((d*d)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(d*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*h*k*r*fabs(L*r-d*_mu.get_value("mu_0"))*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(h*k*(r*r)*fabs(L*r-d*_mu.get_value("mu_0"))*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(l*fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minY2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*r-d*_mu.get_value("mu_0"))*((h*h)*1.0/(l*l)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)+1.0))/(fabs(L-d)*fabs(r));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minY3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -(L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return -((L*L)*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(l-_mu.get_value("mu_1"))*(r-_mu.get_value("mu_0"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*_mu.get_value("mu_0")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (L*k*(r*r)*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(L-d)*(l-_mu.get_value("mu_1"))*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minY4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    return (k*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0)))/(fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((r*r)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*l+h*_mu.get_value("mu_1"),2.0)+(d*d)*(l*l)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*(r*r)*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*pow(L-d,2.0)*1.0/pow(L*r-d*_mu.get_value("mu_0"),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*(d*(l*l)*(r-_mu.get_value("mu_0"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*_mu.get_value("mu_0")+h*r)+h*(r*r)*(l-_mu.get_value("mu_1"))*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*(d*l+h*_mu.get_value("mu_1"))))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minY5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs((d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r)*(L*r-d*_mu.get_value("mu_0")))*1.0/pow(fabs(r),2.0)*((l*l)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)*pow(d*_mu.get_value("mu_0")+h*r,2.0)+(h*h)*(r*r)*pow(l-_mu.get_value("mu_1"),2.0)*1.0/pow(d*l*_mu.get_value("mu_0")+h*_mu.get_value("mu_1")*r,2.0)))/(fabs(d+h)*fabs(l)*fabs(L-d));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return ((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return ((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return -(d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return ((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return ((d*d)*k*(l*l)*1.0/(r*r)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*((d*d)*(l*l)*1.0/(r*r)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)+1.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real d = 3*r;
    Real h = 1.5*l;
    return (d*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(r*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minZ3 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXZ_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -((L*L)*k*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*((r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*(l*l)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*pow(r-_mu.get_value("mu_0"),2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYZ_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZX_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZY_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return -(L*k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*(L-h)*(r-_mu.get_value("mu_0"))*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(_mu.get_value("mu_0")*fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minZ4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(L*l-h*_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0)*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_minZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r*r+_mu.get_value("mu_0")*_mu.get_value("mu_0"))*(1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXY_minZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r+_mu.get_value("mu_0"))*(r-_mu.get_value("mu_0"))*(1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYX_minZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r+_mu.get_value("mu_0"))*(r-_mu.get_value("mu_0"))*(1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionYY_minZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*(r*r+_mu.get_value("mu_0")*_mu.get_value("mu_0"))*(1.0/2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_minZ5 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
  Real L = 0.1;
   Real k = _mu.get_value("mu_11");
    Real h = 1.5*l;
    return (k*(l*l)*fabs(_mu.get_value("mu_0")*(L*l-h*_mu.get_value("mu_1")))*pow(L-h,2.0)*1.0/pow(L*l-h*_mu.get_value("mu_1"),2.0))/(fabs(l)*fabs(r)*fabs(L-h));
  }
};
struct Geom3DRB_ATheta_DiffusionXX_VesselCyl : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real k = _mu.get_value("mu_13");
    return (k*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct Geom3DRB_ATheta_DiffusionYY_VesselCyl : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real k = _mu.get_value("mu_13");
    return (k*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_VesselCyl : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real k = _mu.get_value("mu_13");
    return (k*(l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct Geom3DRB_ATheta_DiffusionXX_BoundingBox : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real k = _mu.get_value("mu_11");
    return (k*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct Geom3DRB_ATheta_DiffusionYY_BoundingBox : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real k = _mu.get_value("mu_11");
    return (k*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct Geom3DRB_ATheta_DiffusionZZ_BoundingBox : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real k = _mu.get_value("mu_11");
    return (k*(l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*fabs(_mu.get_value("mu_1"))*1.0/pow(fabs(r),2.0)*pow(fabs(_mu.get_value("mu_0")),2.0))/fabs(l);
  }
};
struct Geom3DRB_ATheta_Perfusion_VesselCyl : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    Real r = _mu.get_value("mu_9");
  Real  l = _mu.get_value("mu_10");
   Real omega = _mu.get_value("mu_8");
    return omega * pow(_mu.get_value("mu_0"),2)*_mu.get_value("mu_1")/(pow(r,2)*l);
  }
};
#endif //DWARFELEPHANTGEOM3DRBTHETA_RFA_H
