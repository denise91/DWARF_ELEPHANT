///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTGEOM2DRBTHETA_H
#define DWARFELEPHANTGEOM2DRBTHETA_H

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
    double r = 1;
  double  l = 2;
  double L = 4;
   double k = 1;
   double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");
 
    return fabs(L-l_new)/fabs(L-l)+(fabs(L-l_new)*1.0/pow(L-l_new,2.0)*pow(r-r_new,2.0)*4.0)/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionXY_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 1;
  double  l = 2;
  double L = 4;
   double k = 1;
   double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");

    return (fabs(L-l_new)*(L-l)*1.0/pow(L-l_new,2.0)*(r-r_new)*-2.0)/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionYX_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 1;
  double  l = 2;
  double L = 4;
   double k = 1;
   double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");

    return (fabs(L-l_new)*(L-l)*1.0/pow(L-l_new,2.0)*(r-r_new)*-2.0)/fabs(L-l);
  }
};
struct Geom2DRB_ATheta_DiffusionYY_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  double  l = 2;
  double L = 4;
   double k = 1;
   double r = 1;
   double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");

     return (fabs(L-l_new)*pow(L-l,2.0)*1.0/pow(L-l_new,2.0))/fabs(L-l);
  }
};
/*
struct Geom2DRB_FTheta_HeatSource_maxZ1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
  double  l = 2;
  double L = 4;
    return fabs(L-2*_mu.get_value("mu_0"))/fabs(L-l);
  }
};
*/
struct Geom2DRB_ATheta_DiffusionXX_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 1;
  double  l = 2;
  double L = 4;
   double k = 1;
   double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");

    return ((r*r)*1.0/(r_new*r_new)*fabs(r_new*(L-l_new)))/(fabs(r)*fabs(L-l))+(1.0/(r_new*r_new)*fabs(r_new*(L-l_new))*1.0/pow(L-l_new,2.0)*pow(L*r-L*r_new,2.0))/(fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionXY_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 1;
  double  l = 2;
  double L = 4;
   double k = 1;
  double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");

    return (fabs(r_new*(L-l_new))*(L-l)*1.0/pow(L-l_new,2.0)*(L*r-L*r_new))/(r_new*fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionYX_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 1;
  double  l = 2;
  double L = 4;
   double k = 1;
  double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");

   return (fabs(r_new*(L-l_new))*(L-l)*1.0/pow(L-l_new,2.0)*(L*r-L*r_new))/(r_new*fabs(r)*fabs(L-l));
  }
};
struct Geom2DRB_ATheta_DiffusionYY_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 1;
  double  l = 2;
  double L = 4;
   double k = 1;
   double l_new = _mu.get_value("mu_1");
   double r_new = _mu.get_value("mu_0");

    return (fabs(r_new*(L-l_new))*pow(L-l,2.0)*1.0/pow(L-l_new,2.0))/(fabs(r)*fabs(L-l));
  }
};


struct Geom2DRB_FTheta_HeatSource_maxZ2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    double r = 1;
  double  l = 2;
  double L = 4;
  double r_new = _mu.get_value("mu_0");
    return sqrt(1.0/(r*r)*(r_new*r_new));
  }
};

#endif //DWARFELEPHANTGEOM2DRBTHETA_H
