///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTGEOM2DRBTHETA_RFA_H
#define DWARFELEPHANTGEOM2DRBTHETA_RFA_H

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
struct Geom2DRB_ATheta_DiffusionXX_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(L-_mu.get_value("mu_1"))*(k+k*1.0/pow(L-_mu.get_value("mu_1"),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*4.0))/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionXY_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_1"))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0"))*-2.0)/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionYX_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_1"))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0"))*-2.0)/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionYY_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_1"))*pow(L-l,2.0)*1.0/pow(L-_mu.get_value("mu_1"),2.0))/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionXX_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*(k*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*1.0/pow(L-_mu.get_value("mu_1"),2.0)*pow(r-_mu.get_value("mu_0"),2.0)))/(fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionXY_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (L*k*fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0")))/(_mu.get_value("mu_0")*fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionYX_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (L*k*fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0")))/(_mu.get_value("mu_0")*fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionYY_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*pow(L-l,2.0)*1.0/pow(L-_mu.get_value("mu_1"),2.0))/(fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionXX_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_0")*2.0)*pow(L-r*2.0,2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionXY_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_0")*2.0)*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionYX_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_0")*2.0)*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionYY_maxX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(L-_mu.get_value("mu_0")*2.0)*(k+k*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*pow(l-_mu.get_value("mu_1"),2.0)))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionXX_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*pow(L-r*2.0,2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0))/(fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionXY_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return -(L*k*fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionYX_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return -(L*k*fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionYY_maxX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*(k*(l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*k*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*pow(l-_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionXX_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(L-_mu.get_value("mu_1"))*(k+k*1.0/pow(L-_mu.get_value("mu_1"),2.0)*pow(r-_mu.get_value("mu_0"),2.0)*4.0))/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionXY_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_1"))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0"))*-2.0)/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionYX_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_1"))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0"))*-2.0)/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionYY_minZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_1"))*pow(L-l,2.0)*1.0/pow(L-_mu.get_value("mu_1"),2.0))/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionXX_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*(k*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))+(L*L)*k*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*1.0/pow(L-_mu.get_value("mu_1"),2.0)*pow(r-_mu.get_value("mu_0"),2.0)))/(fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionXY_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (L*k*fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0")))/(_mu.get_value("mu_0")*fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionYX_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (L*k*fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*(L-l)*1.0/pow(L-_mu.get_value("mu_1"),2.0)*(r-_mu.get_value("mu_0")))/(_mu.get_value("mu_0")*fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionYY_minZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(_mu.get_value("mu_0")*(L-_mu.get_value("mu_1")))*pow(L-l,2.0)*1.0/pow(L-_mu.get_value("mu_1"),2.0))/(fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionXX_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_0")*2.0)*pow(L-r*2.0,2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionXY_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_0")*2.0)*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionYX_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(L-_mu.get_value("mu_0")*2.0)*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionYY_minX1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(L-_mu.get_value("mu_0")*2.0)*(k+k*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*pow(l-_mu.get_value("mu_1"),2.0)))/fabs(L-r*2.0);
  }
};
struct Geom2DRB_ATheta_DiffusionXX_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (k*fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*pow(L-r*2.0,2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0))/(fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionXY_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return -(L*k*fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionYX_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return -(L*k*fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*(L-r*2.0)*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*(l-_mu.get_value("mu_1")))/(_mu.get_value("mu_1")*fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionYY_minX2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
  double L = 1;
   double k = 1;
    return (fabs(_mu.get_value("mu_1")*(L-_mu.get_value("mu_0")*2.0))*(k*(l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))+(L*L)*k*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*1.0/pow(L-_mu.get_value("mu_0")*2.0,2.0)*pow(l-_mu.get_value("mu_1"),2.0)))/(fabs(l)*fabs(L-r*2.0));
  }
};
struct Geom2DRB_ATheta_DiffusionXX_BoundingBox : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
   double k = 1;
    return (k*(r*r)*1.0/(_mu.get_value("mu_0")*_mu.get_value("mu_0"))*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")))/(fabs(l)*fabs(r));
  }
};
struct Geom2DRB_ATheta_DiffusionYY_BoundingBox : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
   double k = 1;
    return (k*(l*l)*1.0/(_mu.get_value("mu_1")*_mu.get_value("mu_1"))*fabs(_mu.get_value("mu_1")*_mu.get_value("mu_0")))/(fabs(l)*fabs(r));
  }
};
struct Geom2DRB_ATheta_Perfusion_BoundingBox : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 0.3;
  double  l = 0.6;
    return _mu.get_value("mu_0")*_mu.get_value("mu_1")/(r*l);
  }
};
#endif //DWARFELEPHANTGEOM2DRBTHETA_RFA_H