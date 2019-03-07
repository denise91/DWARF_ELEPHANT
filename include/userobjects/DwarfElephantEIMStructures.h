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

/*
struct ShiftedGaussian : public RBParametrizedFunction
{
  virtual Number evaluate(const RBParameters & mu,
                          const Point & p,
                          const Elem & elem)
  {
    
    Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real x_prime = mu.get_value("mu_2");
    Real y_prime = mu.get_value("mu_3");
    Number result;
    Number x_new, y_new, Jacobian;
    double trafo_mat[2][2]={0}, trafo_vec[2][1]={0}, L = 4.0, r = 1.0, l = 2.0;

    if (elem.subdomain_id() == 1)// Point p is in subdomain 1
    {  
       trafo_mat[0][0] = 1.0;
       trafo_mat[0][1] = (r*2.0-r_0*2.0)/(L-l);
       trafo_mat[1][1] = (L-l_0)/(L-l);  
       trafo_vec[0][0] = -(L*(r-r_0))/(L-l);
       trafo_vec[1][0] = (L*(l-l_0)*(-1.0/2.0))/(L-l);
       x_new = trafo_mat[0][0]*p(0) + trafo_mat[0][1]*p(1) + trafo_vec[0][0];
       y_new = trafo_mat[1][0]*p(0) + trafo_mat[1][1]*p(1) + trafo_vec[1][0];
       Jacobian = (L-l_0)/(L - l);
    }
    else
    {
       trafo_mat[0][0] = r_0/r;
       trafo_mat[0][1] = -(L*r-L*r_0)/(L*r-l*r);
       trafo_mat[1][1] = (L-l_0)/(L-l);  
       trafo_vec[0][0] = (L*(l*r-l*r_0)*(1.0/2.0))/(L*r-l*r);
       trafo_vec[1][0] = (L*(l-l_0)*(-1.0/2.0))/(L-l);
       x_new = trafo_mat[0][0]*p(0) + trafo_mat[0][1]*p(1) + trafo_vec[0][0];
       y_new = trafo_mat[1][0]*p(0) + trafo_mat[1][1]*p(1) + trafo_vec[1][0];
       Jacobian = r_0 * (L - l_0)/(r * (L - l));
    }
     
    //Real center_x = mu.get_value("mu_0");
    //Real center_y = mu.get_value("mu_1");

    //return exp(-(pow(center_x-p(0),2.) + pow(center_y-p(1),2.))); //Forcing function from libMesh rb example 4
    return exp(-(pow(x_prime - x_new,2) + pow(y_prime - y_new,2))) * Jacobian; // Forcing function for geometrical parametrization example
  }
};*/

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

