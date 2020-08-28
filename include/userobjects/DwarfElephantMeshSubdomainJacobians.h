#ifndef DWARFELEPHANTMESHSUBDOMAINJACOBIANS_H
#define DWARFELEPHANTMESHSUBDOMAINJACOBIANS_H
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"
// Forward Declarations 
namespace libMesh 
{ 
  class RBParameters; 
  class RBTheta; 
} 


struct jacobian_subdomain_1 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_2 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_3 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_4 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_5 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*l*r_0-h*l_0*r_0)/(fabs(l)*fabs(r)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_6 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_7 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_8 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_9 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_10 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_11 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_12 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_13 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_14 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_15 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_16 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_17 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_18 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_19 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_20 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_21 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_22 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_23 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_24 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_25 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_26 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_27 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_28 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_29 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_30 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = fabs(L*l*r_0-h*l_0*r_0)/(fabs(l)*fabs(r)*fabs(L-h));
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_31 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/fabs(l);
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};


struct jacobian_subdomain_32 : public RBTheta
{
  virtual Number evaluate(const RBParameters & mu)
  {


    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real L = 0.1, r = mu.get_value("mu_9"), l = mu.get_value("mu_10"), h = 1.5*l, d = 3.*r, t0;
  t0 = (fabs(l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/fabs(l);
    return t0 + 0*(r_0+l_0+r+l+L+d+h);
}
};
#endif //DWARFELEPHANTMESHSUBDOMAINJACOBIANS_H
