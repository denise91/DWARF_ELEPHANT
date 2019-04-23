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
                          const Elem & elem)
  {
    
    Real _needle_center_x = mu.get_value("mu_0");
    /*
    Real _needle_center_y = mu.get_value("mu_1");
    Real _needle_axis_theta = pi/2.0;
    Real _needle_axis_phi = mu.get_value("mu_2");
    
    Real _needle_power = 1.0;

 //VectorValue<Real> _X_bar(_needle_active_region_p1_x, _needle_active_region_p1_y, 0.);
  //VectorValue<Real> _Y_bar(_needle_active_region_p2_x, _needle_active_region_p2_y, 0.);
  VectorValue<Real> _A_bar(p(0),p(1),0.);

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
  return P*Q_G;*/
    return exp(-pow(_needle_center_x - p(0),2)/5e-4);
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
    evaluate_basis_function(0,*_elem, *_qrule,eim_values);
  }  

  virtual void interior_assembly(FEMContext & c)
  {
  }
};

#endif //DWARFELEPHANTEIMSTRUCTURES_H

