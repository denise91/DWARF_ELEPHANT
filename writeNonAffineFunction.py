def write_newCoords_and_Jacobian(dim, trafoFile):
  

with open(Kernel_h_Filename+Suffix_List[index]+".h","w") as h_file:
  h_file.write("/**\n")
  h_file.write(" * This file defines a non-affine function in a parameterized geometry.\n ")
  h_file.write(" */\n")
  h_file.write("\n")
  h_file.write("///-------------------------------------------------------------------------\n")
  h_file.write("#ifndef DWARFELEPHANTNONAFFINEFUNCTION_H\n")
  h_file.write("#define DWARFELEPHANTNONAFFINEFUNCTION_H\n")
  h_file.write("\n")
  h_file.write("// libMesh includes \n")
  h_file.write("""#include "libmesh/libmesh.h"
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
using libMesh::FEBase;\n""")




  h_file.write("""struct ShiftedGaussian : public RBParametrizedFunction
{
  virtual Number evaluate(const RBParameters & mu,
                          const Point & p,
                          const Elem & elem)
  {""")
  h_file.write("""Real r_0 = mu.get_value("mu_0");
    Real l_0 = mu.get_value("mu_1");
    Real x_prime = mu.get_value("mu_2");
    Real y_prime = mu.get_value("mu_3");
    Number result;
    Number x_new, y_new, Jacobian;""")

  h_file.write("double trafo_mat[2][2]={0}, trafo_vec[2][1]={0}, L = 4.0, r = 1.0, l = 2.0;\n\n")
  
  h_file.write("""if (elem.subdomain_id() == 1)// Point p is in subdomain 1
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
     
    return exp(-(pow(x_prime - x_new,2) + pow(y_prime - y_new,2))) * Jacobian; // Forcing function for geometrical parametrization example
  }
};
  h_file.write("#endif // DWARFELEPHANTNONAFFINEFUNCTION_H");
