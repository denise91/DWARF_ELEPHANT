function [ output_args ] = write_ThetaObj_txt( tetrahedronNames, diffusion_theta_objects, determinants )

  syms zero L h k k_t k_b r r_0 l l_0 d one perf_theta rho_C_t rho_C_b;
  perf_theta = 1e3*r_0*r_0*l_0/(r*r*l);
  zero = 0;
  one = r/r;
  % Write diffusion thetas first
  index = ["X","Y","Z"];
  theta_dir = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/theta_functions/";
  matlabFunction(L,'File',strcat(theta_dir,'test'));
  q_a = 0;
  for tet_num = 1:30 % diffusion thetas for all tetrahedral subdomains in the mesh
      RBThetaMatrix_str = "";
      %fileID = fopen(tetrahedronNames(tet_num)+"_RBAThetas_Diffusion.txt",'w');
      %fileID_M = fopen(tetrahedronNames(tet_num)+"_RBMThetas.txt",'w');
      for iii = 1:3
          for jjj = 1:3
              if (diffusion_theta_objects(iii,jjj,tet_num) == zero)
                  RBThetaMatrix_str = strcat('   t0 = 0;\n');
              else
                  RBThetaMatrix_str = strcat(ccode(diffusion_theta_objects(iii,jjj,tet_num)),'\n');
                  matlabFunction(diffusion_theta_objects(iii,jjj,tet_num)*k_t/k + (L + r + r_0 + l + l_0 + h + d + k)*0,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
                  q_a = q_a + 1;
              end
              %fprintf(fileID,RBThetaMatrix_str);
          end
      end
      matlabFunction(determinants(tet_num)*rho_C_t,'File',strcat(theta_dir,'RBMTheta_',int2str(tet_num-1)));
      %fprintf(fileID_M,ccode(determinants(tet_num)));
      %fclose(fileID_M);
      %fclose(fileID);
  end
  
  RBThetaMatrix_str = ""; % Diffusion thetas For the vessel cylinder
  %fileID = fopen("VesselCyl_RBAThetas_Diffusion.txt",'w');
  %fileID_M = fopen("VesselCyl_RBMThetas.txt","w");
  for iii = 1:3
      for jjj = 1:3
          if (diffusion_theta_objects(iii,jjj,31) == zero)
              RBThetaMatrix_str = strcat('   t0 = 0;\n');
          else
              RBThetaMatrix_str = strcat(ccode(diffusion_theta_objects(iii,jjj,31)),'\n');
              matlabFunction(diffusion_theta_objects(iii,jjj,31)*k_b/k,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
              q_a = q_a + 1;
          end
          %fprintf(fileID,RBThetaMatrix_str);
      end
  end
  matlabFunction(determinants(31)*rho_C_b,'File',strcat(theta_dir,'RBMTheta_30'));
  %fprintf(fileID_M,ccode(determinants(31)));
  %fclose(fileID_M);
  %fclose(fileID);
  
  
  RBThetaMatrix_str = ""; % Diffusion thetas For the bounding box
  %fileID = fopen("BoundingBox_RBAThetas_Diffusion.txt",'w');
  %fileID_M = fopen("BoundingBox_RBMThetas.txt","w");
  for iii = 1:3
      for jjj = 1:3
          if (diffusion_theta_objects(iii,jjj,32) == zero)
              RBThetaMatrix_str = strcat('   t0 = 0;\n');
          else
              RBThetaMatrix_str = strcat(ccode(diffusion_theta_objects(iii,jjj,32)),'\n');
              matlabFunction(diffusion_theta_objects(iii,jjj,32)*k_t/k,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
              q_a = q_a + 1;
          end
          %fprintf(fileID,RBThetaMatrix_str);
      end
  end
  matlabFunction(determinants(32)*rho_C_t,'File',strcat(theta_dir,'RBMTheta_31'));
  %fprintf(fileID_M,ccode(determinants(32)));
  %fclose(filID_M);
  %fclose(fileID);
  
    % Perfusion theta objects
  %fileID = fopen("VesselCyl_RBAThetas_Perf.txt",'w');
  RBThetaMatrix_str = "";
  RBThetaMatrix_str = strcat(ccode(determinants(31)),'\n');
  %fprintf(fileID,RBThetaMatrix_str);
  %fclose(fileID);
  matlabFunction(perf_theta,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
  q_a = q_a + 1;
  
  matlabFunction(one,'File',strcat(theta_dir,'RBTheta_',int2str(q_a))); % RBTheta for the convection BC A matrix
  q_a = q_a + 1;
end

