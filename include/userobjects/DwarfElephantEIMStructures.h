#ifndef DWARFELEPHANTEIMSTRUCTURES_H
#define DWARFELEPHANTEIMSTRUCTURES_H

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
// Just the bits we're using, since this is a header.
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


struct ShiftedGaussianTest : public RBParametrizedFunction
{
  virtual Number evaluate(const RBParameters & mu,
                          const Point & p,
                          const Elem & /*elem*/)
  {
    
    Real _needle_center_x = mu.get_value("mu_0");
    //Real _variance = mu.get_value("mu_1");
    
    
    Real _needle_center_y = mu.get_value("mu_1");
    //Real _needle_center_z = 0.;
    Real _needle_axis_theta = pi/2.0;
    Real _needle_axis_phi = mu.get_value("mu_2");
    
    Real _needle_power = 1e-15;

  VectorValue<Real> _A_bar(p(0),p(1),0.);

  VectorValue<Real> _Z_cap(std::sin(_needle_axis_theta)*std::cos(_needle_axis_phi),std::sin(_needle_axis_theta)*std::sin(_needle_axis_phi),std::cos(_needle_axis_theta));

  VectorValue<Real> _O_cap(_needle_center_x, _needle_center_y, 0);

  VectorValue<Real> _temp_vec = _A_bar - _O_cap;
  VectorValue<Real> _r_A_bar = _temp_vec - _Z_cap * (_temp_vec * _Z_cap);

  Real _r_needle = _r_A_bar.norm();
  Real _z_needle = _temp_vec * _Z_cap; 

  Real Q_G = exp(-pow(_r_needle,2)/(2. * pow(2.201e-3,2))); // ORIGINAL
  // Real Q_G = exp(-pow(_r_needle,2)/(2. * pow(2.201e-0,2))); // MODIFIED FOR QUICK CONVERGENCE OF EIM
  Real _sigmoid_plus = 1./(1. + exp(-1.303e4*(_z_needle - 1.052e-2))); // ORIGINAL
  //Real _sigmoid_plus = 1./(1. + exp(-1.303e0*(_z_needle - 1.052e-2))); // MODIFIED FOR QUICK CONVERGENCE OF EIM
  Real _sigmoid_minus = 1./(1. + exp(-1.303e4*(_z_needle + 1.052e-2))); // ORIGINAL
  //Real _sigmoid_minus = 1./(1. + exp(-1.303e0*(_z_needle + 1.052e-2))); // MODIFIED FOR QUICK CONVERGENCE OF EIM
  Real P = _needle_power * 1.383e15 * (pow(_z_needle,4) + 2.624e6)*(_sigmoid_minus *(1. - _sigmoid_plus)); // ORIGINAL
  //Real P = _needle_power * 1.383e15 * (pow(_z_needle,2) + 2.624e6)*(_sigmoid_minus *(1. - _sigmoid_plus));  // MODIFIED FOR QUICK CONVERGENCE OF EIM
  return P*Q_G;
    //return exp(-pow(_needle_center_x - p(0),2)/_variance); //5e-4);
  }
};

struct InverseSquaredRFHeatSource : public RBParametrizedFunction
{
     virtual Number evaluate(const RBParameters & mu,
                          const Point & p,
                          const Elem & /*elem*/)
  {
    Real _needle_center_x = mu.get_value("mu_0");
    //Real _variance = mu.get_value("mu_1");
    
    
    Real _needle_center_y = mu.get_value("mu_1");
    Real _needle_center_z = 0.;
    Real _needle_axis_theta = pi/2.0;
    Real _needle_axis_phi = mu.get_value("mu_2");
    
    Real _needle_power = 1.0;
Real l = 0.01;
    VectorValue<Real> _O_cap(_needle_center_x, _needle_center_y, _needle_center_z);
    VectorValue<Real> _n_cap(std::sin(_needle_axis_theta) * std::cos(_needle_axis_phi), std::sin(_needle_axis_theta) * std::sin(_needle_axis_phi), std::cos(_needle_axis_theta));
    VectorValue<Real> _A_bar(_needle_center_x + l/2. * std::sin(_needle_axis_theta) * std::cos(_needle_axis_phi), _needle_center_y +l/2. * std::sin(_needle_axis_theta) * std::sin(_needle_axis_phi), _needle_center_z + l/2. * std::cos(_needle_axis_theta));
    VectorValue<Real> _B_bar(_needle_center_x - l/2. * std::sin(_needle_axis_theta) * std::cos(_needle_axis_phi), _needle_center_y - l/2. * std::sin(_needle_axis_theta) * std::sin(_needle_axis_phi), _needle_center_z - l/2. * std::cos(_needle_axis_theta));
    
    VectorValue<Real> _normal_planeA(std::sin(_needle_axis_theta) * std::cos(_needle_axis_phi), std::sin(_needle_axis_theta) * std::sin(_needle_axis_phi), std::cos(_needle_axis_theta));
    VectorValue<Real> _normal_planeB(-std::sin(_needle_axis_theta) * std::cos(_needle_axis_phi), -std::sin(_needle_axis_theta) * std::sin(_needle_axis_phi), -std::cos(_needle_axis_theta));
    
    VectorValue<Real> _minus_A_bar = -_A_bar;
    VectorValue<Real> _minus_B_bar = -_B_bar;
    VectorValue<Real> distA = p + _minus_A_bar;
    VectorValue<Real> distB = p + _minus_B_bar;
    Real _eval_PlaneA = _normal_planeA*distA;
    Real _eval_PlaneB = _normal_planeB*distB;
    Real _result = 0.0;
    //Real p_along_nA = distA*_normal_planeA;
    Real p_along_nB = distB*_normal_planeB;
    if (_eval_PlaneA >= 0)
    {
      _result = std::min(_needle_power / pow(0.00075,2),_needle_power / distA.norm_sq());
    }
    if (_eval_PlaneB >= 0)
    {
      _result = std::min(_needle_power / pow(0.00075,2),_needle_power / distB.norm_sq());
    }
    if ((_eval_PlaneA < 0) && (_eval_PlaneB < 0))
    {
      VectorValue<Real> r = distB - p_along_nB * _normal_planeB;
      _result = std::min(_needle_power / pow(0.00075,2),_needle_power /r.norm_sq());
    }

   return _result; //1/(pow(p(0) - _needle_center_x,2.0) + pow(p(1) - _needle_center_y,2.0) +0.1); //
  }
};

struct AffineFunction : RBParametrizedFunction
{
    virtual Number evaluate(const RBParameters & mu,
                            const Point & /*p*/,
                            const Elem & elem)
    {
        Real val_subdomain_0 = mu.get_value("mu_0");
        Real val_subdomain_1 = mu.get_value("mu_1");
        Real val_subdomain_2 = mu.get_value("mu_2");
        Real val_subdomain_3 = mu.get_value("mu_3");
        Real _result;
        
        if (elem.subdomain_id() == 1)
            _result = val_subdomain_0;
        else if (elem.subdomain_id() == 2)
            _result = val_subdomain_1;
        else if (elem.subdomain_id() == 3)
            _result = val_subdomain_2;
        else
            _result = val_subdomain_3;
        
        return _result;
    }
};
// Expansion of the PDE operator
//struct DwarfElephantEIMThetaA0 : RBTheta { virtual Number evaluate(const RBParameters &) { return 0.05;  } }; //theta_A0 for libMesh rb example 4
struct DwarfElephantEIMThetaA0 : RBTheta { virtual Number evaluate(const RBParameters &) { return 0.05;  } }; //theta_A0 for libmesh EIM example

// Define an RBThetaExpansion class for this PDE
struct DwarfElephantEIMTestRBThetaExpansion : RBThetaExpansion
{
  /**
   * Constructor.
   */
  DwarfElephantEIMTestRBThetaExpansion()
  {
    attach_A_theta(&theta_a_0);
    attach_A_theta(&_rb_theta);
  }

  // The RBTheta member variables
  DwarfElephantEIMThetaA0 theta_a_0;
  RBTheta _rb_theta;
};

struct DwarfElephantEIMFAssembly : RBEIMAssembly
{
  DwarfElephantEIMFAssembly(RBEIMConstruction & rb_eim_con_in, unsigned int basis_function_index_in) : 
    RBEIMAssembly(rb_eim_con_in, basis_function_index_in)
  {
  }

  void get_eim_basis_function_values(const Elem * _elem, const QBase * _qrule,std::vector<Number>  & eim_values)
  {
    evaluate_basis_function(0,*_elem, _qrule->get_points(),eim_values);
  }  

  virtual void interior_assembly(FEMContext & /*c*/)
  {
  }
};

#endif //DWARFELEPHANTEIMSTRUCTURES_H

