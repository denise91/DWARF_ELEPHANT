function [ output_args ] = write_nonAffineFunc_hFile( allTransformationMatrices )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
  syms zero;
  zero = 0;
  fileID_NAF = fopen("DwarfElephantNonAffineFunction.h","w");
  fprintf(fileID_NAF,'// For RBnics Geometry\n');
  fprintf(fileID_NAF,'#ifndef DWARFELEPHANTNONAFFINEFUNCTION_H\n');
  fprintf(fileID_NAF,'#define DWARFELEPHANTNONAFFINEFUNCTION_H\n');

  fprintf(fileID_NAF,'\n \n// libMesh includes\n');
  fprintf(fileID_NAF,'#include "libmesh/libmesh.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/mesh.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/equation_systems.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/fe.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/quadrature.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/dof_map.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/dense_matrix.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/dense_vector.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/fe_interface.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/elem.h"\n');

  fprintf(fileID_NAF,'\n\n// rbOOmit includes\n');
  fprintf(fileID_NAF,'#include "libmesh/rb_assembly_expansion.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/rb_eim_theta.h"\n');
  fprintf(fileID_NAF,'#include "libmesh/rb_parametrized_function.h"\n');


  fprintf(fileID_NAF,'\n\n// MOOSE includes\n');
  fprintf(fileID_NAF,'#include "Function.h"\n');

  fprintf(fileID_NAF,'\n// Bring in bits from the libMesh namespace.\n');
  fprintf(fileID_NAF,'// Just the bits we are using, since this is a header.\n');
  fprintf(fileID_NAF,'using libMesh::ElemAssembly;\n');
  fprintf(fileID_NAF,'using libMesh::FEMContext;\n');
  fprintf(fileID_NAF,'using libMesh::Number;\n');
  fprintf(fileID_NAF,'using libMesh::RBAssemblyExpansion;\n');
  fprintf(fileID_NAF,'using libMesh::RBEIMAssembly;\n');
  fprintf(fileID_NAF,'using libMesh::RBEIMConstruction;\n');
  fprintf(fileID_NAF,'using libMesh::RBParametrizedFunction;\n');
  fprintf(fileID_NAF,'using libMesh::RBParameters;\n');
  fprintf(fileID_NAF,'using libMesh::RBTheta;\n');
  fprintf(fileID_NAF,'using libMesh::RBThetaExpansion;\n');
  fprintf(fileID_NAF,'using libMesh::Real;\n');
  fprintf(fileID_NAF,'using libMesh::RealGradient;\n');
  fprintf(fileID_NAF,'using libMesh::Elem;\n');
  fprintf(fileID_NAF,'using libMesh::FEBase;\n');

  fprintf(fileID_NAF,'\n\nstruct ShiftedGaussian : public RBParametrizedFunction\n');
  fprintf(fileID_NAF,'{\n');
  fprintf(fileID_NAF,'  virtual Number evaluate(const RBParameters & mu,\n');
  fprintf(fileID_NAF,'                          const Point & p,\n');
  fprintf(fileID_NAF,'                          const Elem & elem)\n');
  fprintf(fileID_NAF,'  {\n');
    
  fprintf(fileID_NAF,'\n\n    Real r_0 = mu.get_value("mu_0");\n');
  fprintf(fileID_NAF,'    Real l_0 = mu.get_value("mu_1");\n');
  fprintf(fileID_NAF,'Real x_prime = mu.get_value("mu_2");\n');
  fprintf(fileID_NAF,'    Real y_prime = mu.get_value("mu_3");\n');
  fprintf(fileID_NAF,'Real z_prime = mu.get_value("mu_4");\n');
  fprintf(fileID_NAF,'    Number result;\n');
  fprintf(fileID_NAF,'    Number x_new, y_new, z_new, t0;\n');
  fprintf(fileID_NAF,'    double matrix[3][3]={0}, vec[3][1]={0}, L = 4.0, r = 1.0, l = 2.0;\n');
  fprintf(fileID_NAF,'    double d = 3*r, h = 1.5*l;\n');
  for tet_num = 1:32
      matrix = [allTransformationMatrices(4,tet_num) allTransformationMatrices(5,tet_num) allTransformationMatrices(6,tet_num); allTransformationMatrices(7,tet_num) allTransformationMatrices(8,tet_num) allTransformationMatrices(9,tet_num); allTransformationMatrices(10,tet_num) allTransformationMatrices(11,tet_num) allTransformationMatrices(12,tet_num)];
      if (allTransformationMatrices(1,tet_num) ~= zero)
          temp_str = ccode(allTransformationMatrices(1,tet_num));
          ccode_vector = " vec[0][0]" + replace(temp_str,"t0 ","");
      else
          ccode_vector = "  vec[0][0] = 0;";
      end
      if (allTransformationMatrices(2,tet_num) ~= zero)
          temp_str = ccode(allTransformationMatrices(2,tet_num));
          ccode_vector = ccode_vector + " vec[1][0]" + replace(temp_str,"t0 ","");
      else
          ccode_vector = ccode_vector + " vec[1][0] = 0;";
      end
      if (allTransformationMatrices(3,tet_num) ~= zero)
          temp_str = ccode(allTransformationMatrices(3,tet_num));
          ccode_vector = ccode_vector + " vec[2][0]" + replace(temp_str,"t0 ","");
      else
          ccode_vector = ccode_vector + " vec[2][0] = 0;";
      end
      fprintf(fileID_NAF,"if (elem.subdomain_id() == "+int2str(tet_num)+")\n {\n");
      fprintf(fileID_NAF,ccode(matrix));
      fprintf(fileID_NAF,ccode_vector);

      fprintf(fileID_NAF,strcat('\n',ccode(abs(det(matrix)))));
      fprintf(fileID_NAF,'\n}\n');
  end
  fprintf(fileID_NAF,'x_new = matrix[0][0]*p(0) + matrix[0][1]*p(1) + matrix[0][2]*p(2) + vec[0][0];\n');
  fprintf(fileID_NAF,'y_new = matrix[1][0]*p(0) + matrix[1][1]*p(1) + matrix[1][2]*p(2) + vec[1][0];\n'); 
  fprintf(fileID_NAF,'z_new = matrix[2][0]*p(0) + matrix[2][1]*p(1) + matrix[2][2]*p(2) + vec[2][0];\n');
  fprintf(fileID_NAF,'return exp(-(pow(x_prime - x_new,2) + pow(y_prime - y_new,2) + pow(z_prime - z_new,2))) * t0; // Forcing function for geometrical parametrization example\n } \n }; \n');
  fprintf(fileID_NAF,'#endif //DWARFELEPHANTNONAFFINEFUNCTION_H');
  fclose(fileID_NAF);
end
