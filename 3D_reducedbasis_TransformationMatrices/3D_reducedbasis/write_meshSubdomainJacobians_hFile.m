function [ output_args ] = write_meshSubdomainJacobians_hFile( allTransformationMatrices )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
  syms zero;
  zero = 0;
  fileID = fopen("DwarfElephantMeshSubdomainJacobians.h","w");
  fprintf(fileID,'#ifndef DWARFELEPHANTMESHSUBDOMAINJACOBIANS_H\n');
  fprintf(fileID,'#define DWARFELEPHANTMESHSUBDOMAINJACOBIANS_H\n');

  fprintf(fileID,'#include "libmesh/rb_theta.h"\n');
  fprintf(fileID,'#include "libmesh/rb_assembly_expansion.h"\n');

  fprintf(fileID,'// Forward Declarations \n');
  fprintf(fileID,'namespace libMesh \n');
  fprintf(fileID,'{ \n');
  fprintf(fileID,'  class RBParameters; \n');
  fprintf(fileID,'  class RBTheta; \n');
  fprintf(fileID,'} \n');
  
  for subdomain = 1:32    
    fprintf(fileID,strcat('\n\nstruct subdomain_',int2str(subdomain),' : public RBTheta\n'));
    fprintf(fileID,'{\n');
    fprintf(fileID,'  virtual Number evaluate(const RBParameters & mu)\n');
    fprintf(fileID,'  {\n');
    
    fprintf(fileID,'\n\n    Real r_0 = mu.get_value("mu_0");\n');
    fprintf(fileID,'    Real l_0 = mu.get_value("mu_1");\n');
    fprintf(fileID,'    Real L = 0.1, r = 0.003, l = 0.05, h = 1.5*l, d = 3.*r, t0;');
  
    matrix = [allTransformationMatrices(4,subdomain) allTransformationMatrices(5,subdomain) allTransformationMatrices(6,subdomain); allTransformationMatrices(7,subdomain) allTransformationMatrices(8,subdomain) allTransformationMatrices(9,subdomain); allTransformationMatrices(10,subdomain) allTransformationMatrices(11,subdomain) allTransformationMatrices(12,subdomain)];

    fprintf(fileID,strcat('\n',ccode(abs(det(matrix)))));
    fprintf(fileID,'\n    return t0;');
    fprintf(fileID,'\n}\n');
    fprintf(fileID,'};\n');
  end
  
 
  fprintf(fileID,'#endif //DWARFELEPHANTMESHSUBDOMAINJACOBIANS_H');
  fclose(fileID);
end