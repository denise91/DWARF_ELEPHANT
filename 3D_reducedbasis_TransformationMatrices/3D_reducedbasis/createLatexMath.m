function [output_args] = createLatexMath(allTransformationMatrices,diffusion_theta_objects, determinants)
syms zero L h k k_t k_b r r_0 l l_0 d one rho_t C_t rho_b C_b;
syms d_0 h_0 r_ref l_ref;
syms x_n y_n z_n theta_n phi_n eta_P a_q b_q h_q c_q kappa_q;
syms x_1 x_2 x_3;
assume(L>0 & h>0 & r >0 & r_0 > 0 & l > 0 & l_0 > 0 & d > 0);
assumeAlso(x_1,'real');
assumeAlso(x_2,'real');
assumeAlso(x_3,'real');
assumeAlso(x_n,'real');
assumeAlso(y_n,'real');
assumeAlso(z_n,'real');
assumeAlso(theta_n>0 & phi_n>0);
assumeAlso(a_q >0 & b_q>0 & c_q>0 & eta_P >0 & kappa_q > 0);
zero = 0;
one = 1;
latex_file = fopen("RBModelEqns.tex","w");
heat_source_file = fopen("RFHeatSource.tex","w");
fprintf(latex_file,'%s','\section{Geometrical Transformations and Jacobians}\label{sec:geom_trafo_and_jac}');
fprintf(latex_file,'\n');
fprintf(heat_source_file,'%s','\section{RF Heat Source Defined on Reference Domain}\label{sec:rf_heat_source_trafo}');
fprintf(heat_source_file,'\n');
for tet_num = 1:32
  matrix = [allTransformationMatrices(4,tet_num) allTransformationMatrices(5,tet_num) allTransformationMatrices(6,tet_num); allTransformationMatrices(7,tet_num) allTransformationMatrices(8,tet_num) allTransformationMatrices(9,tet_num); allTransformationMatrices(10,tet_num) allTransformationMatrices(11,tet_num) allTransformationMatrices(12,tet_num)];
  jacobian = det(matrix);
  matrix_latex_str = latex(subs(matrix,{r,l,d,h},{r_ref,l_ref,d_0,h_0}));
  fprintf(latex_file,'%s','\begin{equation}');
  fprintf(latex_file,'\n');
  fprintf(latex_file,'%s',"\mathbf{G}^{"+num2str(tet_num)+"}(\mu)=");
  fprintf(latex_file,'%s',matrix_latex_str+",\quad");
  fprintf(latex_file,"\n");
  vec = [allTransformationMatrices(1,tet_num); allTransformationMatrices(2,tet_num); allTransformationMatrices(3,tet_num)];
  x_ref = [x_1; x_2; x_3];
  n_hat = [sin(theta_n)*cos(phi_n); sin(theta_n)*sin(phi_n); cos(theta_n)];
  O_vec = [x_n; y_n; z_n];
  x_0 = matrix*x_ref + vec;
  r_q = norm((x_0 - O_vec) - n_hat * dot((x_0 - O_vec),n_hat));
  z_q = dot((x_0 - O_vec),n_hat);
  gamma_rq = exp(-r_q^2/(2*c_q^2));
  S_m = (1 + exp(-b_q*(z_q-h_q)))^-1;
  S_p = (1 + exp(-b_q*(z_q+h_q)))^-1;
  P_zq = eta_P*(a_q*z_q^4+kappa_q)*S_m*(1-S_p);
  q_dot = simplify(gamma_rq*P_zq);
  q_dot_latex = latex(subs(q_dot,{r,l,d,h},{r_ref,l_ref,d_0,h_0}));
  vec_latex_str = latex(subs(vec,{r,l,d,h},{r_ref,l_ref,d_0,h_0}));
  fprintf(latex_file,'%s',"c^{"+num2str(tet_num)+"}(\mu)=");
  fprintf(latex_file,'%s',vec_latex_str);
  fprintf(latex_file,"\n");
  fprintf(latex_file,'%s','\end{equation}');
  fprintf(latex_file,'\n');
  fprintf(latex_file,'%s','\begin{equation}');
  fprintf(latex_file,'\n');
  fprintf(latex_file,'%s',"J^{"+num2str(tet_num)+"}(\mu)=");
  fprintf(latex_file,'%s',latex(subs(jacobian,{r,l,d,h},{r_ref,l_ref,d_0,h_0})));
  fprintf(latex_file,'\n')
  fprintf(latex_file,'%s','\end{equation}');
  fprintf(heat_source_file,'%s','\begin{equation}');
  fprintf(heat_source_file,'\n');
  fprintf(heat_source_file,'%s',"\dot{q}(\mathfrak{T}^{"+num2str(tet_num)+"}(\vec{x};\mu);\mu)=");
  fprintf(heat_source_file,'%s',q_dot_latex+"\quad\text{for }\vec{x}\in\Omega^l");
  fprintf(heat_source_file,'\n');
  fprintf(heat_source_file,'%s','\end{equation}');
  fprintf(heat_source_file,'\n');
end
fclose(heat_source_file);
fprintf(latex_file,'%s','\section{$\Theta_a^q(\mu)$ Objects}');
fprintf(latex_file,'\n');

latex_table_file = fopen("RBModelTable.tex","w");
fprintf(latex_table_file,'%s',"\begin{table}");
fprintf(latex_table_file,'\n');
fprintf(latex_table_file,'%s','\centering');
fprintf(latex_table_file,'\n');
fprintf(latex_table_file,'%s',"\begin{tabular}{c c c c | c c c c | c c c c | c c c c}");
fprintf(latex_table_file,'\n');
fprintf(latex_table_file,'%s',"$q$ & $i(q)$ & $j(q)$ & $k(q)$ & $q$ & $i(q)$ & $j(q)$ & $k(q)$ & $q$ & $i(q)$ & $j(q)$ & $k(q)$ & $q$ & $i(q)$ & $j(q)$ & $k(q)$\\ \hline");
fprintf(latex_table_file,'\n');
perf_theta = "\omega(r_0)r_0^2l_0/(r_\text{ref}^2l_\text{ref})";
q_a = 0;
  for tet_num = 1:30 % diffusion thetas for all tetrahedral subdomains in the mesh
      RBThetaMatrix_str = "";
      for iii = 1:3
          for jjj = 1:3
              if (diffusion_theta_objects(iii,jjj,tet_num) ~= zero)
                  RBThetaMatrix_str = strcat(ccode(diffusion_theta_objects(iii,jjj,tet_num)),'\n');
                  RBATheta_latex = latex(subs(diffusion_theta_objects(iii,jjj,tet_num)*k_t/k,{r,l,d,h},{r_ref,l_ref,d_0,h_0}));
                  fprintf(latex_file,'%s','\begin{equation}');
                  fprintf(latex_file,'\n');
                  fprintf(latex_file,'%s',"\Theta_a^{"+num2str(q_a+1)+"}(\mu)=");
                  fprintf(latex_file,'%s',RBATheta_latex);
                  fprintf(latex_file,'%s','\end{equation}');
                  fprintf(latex_file,'\n');
                  %matlabFunction(diffusion_theta_objects(iii,jjj,tet_num)*k_t/k + (L + r + r_0 + l + l_0 + h + d + k)*0,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
                  fprintf(latex_table_file,'%s',num2str(q_a+1)+" &"+num2str(tet_num)+" &"+num2str(iii)+" &"+num2str(jjj));
                  if (mod(q_a+1,4) == 0)
                      fprintf(latex_table_file,'%s',"\\");
                      fprintf(latex_table_file,'\n');
                  else
                      fprintf(latex_table_file,'%s'," & ");
                  end
                  q_a = q_a + 1;
              end
          end
      end
%      matlabFunction(determinants(tet_num)*rho_C_t,'File',strcat(theta_dir,'RBMTheta_',int2str(tet_num-1)));
  end
  
  RBThetaMatrix_str = ""; % Diffusion thetas For the vessel cylinder
  for iii = 1:3
      for jjj = 1:3
          if (diffusion_theta_objects(iii,jjj,31) ~= zero)
              RBThetaMatrix_str = strcat(ccode(diffusion_theta_objects(iii,jjj,31)),'\n');
              RBATheta_latex = latex(subs(diffusion_theta_objects(iii,jjj,31)*k_b/k,{r,l,d,h},{r_ref,l_ref,d_0,h_0}));
              fprintf(latex_file,'%s','\begin{equation}');
              fprintf(latex_file,'\n');
              fprintf(latex_file,'%s',"\Theta_a^{"+num2str(q_a+1)+"}(\mu)=");
              fprintf(latex_file,'%s',RBATheta_latex);
              fprintf(latex_file,'%s','\end{equation}');
              fprintf(latex_file,'\n');
              %matlabFunction(diffusion_theta_objects(iii,jjj,31)*k_b/k,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
              fprintf(latex_table_file,'%s',num2str(q_a+1)+" &"+num2str(31)+" &"+num2str(iii)+" &"+num2str(jjj));
              if (mod(q_a+1,4) == 0)
                  fprintf(latex_table_file,'%s',"\\");
                  fprintf(latex_table_file,'\n');
              else
                  fprintf(latex_table_file,'%s'," & ");
              end
              q_a = q_a + 1;
          end
          %fprintf(fileID,RBThetaMatrix_str);
      end
  end
  %matlabFunction(determinants(31)*rho_C_b,'File',strcat(theta_dir,'RBMTheta_30'));
  
  
  RBThetaMatrix_str = ""; % Diffusion thetas For the bounding box
  for iii = 1:3
      for jjj = 1:3
          if (diffusion_theta_objects(iii,jjj,32) ~= zero)
              RBThetaMatrix_str = strcat(ccode(diffusion_theta_objects(iii,jjj,32)),'\n');
              RBATheta_latex = latex(subs(diffusion_theta_objects(iii,jjj,32)*k_t/k,{r,l,d,h},{r_ref,l_ref,d_0,h_0}));
              fprintf(latex_file,'%s','\begin{equation}');
              fprintf(latex_file,'\n');
              fprintf(latex_file,'%s',"\Theta_a^{"+num2str(q_a+1)+"}(\mu)=");
              fprintf(latex_file,'%s',RBATheta_latex);
              fprintf(latex_file,'%s','\end{equation}');
              fprintf(latex_file,'\n');
              %matlabFunction(diffusion_theta_objects(iii,jjj,32)*k_t/k,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
              fprintf(latex_table_file,'%s',num2str(q_a+1)+" &"+num2str(32)+" &"+num2str(iii)+" &"+num2str(jjj));
              if (mod(q_a+1,4) == 0)
                  fprintf(latex_table_file,'%s',"\\");
                  fprintf(latex_table_file,'\n');
              else
                  fprintf(latex_table_file,'%s'," & ");
              end
              q_a = q_a + 1;
          end
          %fprintf(fileID,RBThetaMatrix_str);
      end
  end
%  matlabFunction(determinants(32)*rho_C_t,'File',strcat(theta_dir,'RBMTheta_31')); 
  fprintf(latex_table_file,'\n');
  fprintf(latex_table_file,'%s',"\end{tabular}\caption{Table showing the numbering of $\Theta_a^q(\mu)$ objects for $1\leq q\leq Q_a$.}\label{tab:theta_a_q_num}");
  fprintf(latex_table_file,'\n');
  fprintf(latex_table_file,'%s','\end{table}');
  fclose(latex_table_file);
    % Perfusion theta objects
  RBThetaMatrix_str = "";
  RBThetaMatrix_str = strcat(ccode(determinants(31)),'\n');
%  matlabFunction(perf_theta,'File',strcat(theta_dir,'RBTheta_',int2str(q_a)));
  fprintf(latex_file,'%s','\begin{equation}');
  fprintf(latex_file,'\n');
  fprintf(latex_file,'%s',"\Theta_a^{"+num2str(q_a+1)+"}(\mu)=");
  fprintf(latex_file,'%s',perf_theta);
  fprintf(latex_file,'%s','\end{equation}');
  fprintf(latex_file,'\n');
  q_a = q_a + 1;
  
%  matlabFunction(one,'File',strcat(theta_dir,'RBTheta_',int2str(q_a))); % RBTheta for the convection BC A matrix
  fprintf(latex_file,'%s','\begin{equation}');
  fprintf(latex_file,'\n');
  fprintf(latex_file,'%s',"\Theta_a^{"+num2str(q_a+1)+"}(\mu)=");
  fprintf(latex_file,'%s','1');
  fprintf(latex_file,'%s','\end{equation}');
  fprintf(latex_file,'\n');
  q_a = q_a + 1;

  
  % Write RBMThetas
  fprintf(latex_file,'%s','\section{$\Theta_m^q(\mu)$ Objects}');
  fprintf(latex_file,'\n');
  q_m = 0;
  for tet_num = 1:30 % diffusion thetas for all tetrahedral subdomains in the mesh
%      matlabFunction(determinants(tet_num)*rho_t * C_t,'File',strcat(theta_dir,'RBMTheta_',int2str(tet_num-1)));
      fprintf(latex_file,'%s','\begin{equation}');
      fprintf(latex_file,'\n');
      fprintf(latex_file,'%s',"\Theta_m^{"+num2str(q_m+1)+"}(\mu)=");
      fprintf(latex_file,'%s',latex(subs(determinants(tet_num)*rho_t * C_t,{r,l,h,d},{r_ref,l_ref,h_0,d_0})));
      fprintf(latex_file,'%s','\end{equation}');
      fprintf(latex_file,'\n');
      q_m = q_m + 1;
  end
  
  %matlabFunction(determinants(31)*rho_b * C_b,'File',strcat(theta_dir,'RBMTheta_30'));
  fprintf(latex_file,'%s','\begin{equation}');
  fprintf(latex_file,'\n');
  fprintf(latex_file,'%s',"\Theta_m^{"+num2str(q_m+1)+"}(\mu)=");
  fprintf(latex_file,'%s',latex(subs(determinants(31)*rho_b * C_b,{r,l,h,d},{r_ref,l_ref,h_0,d_0})));
  fprintf(latex_file,'%s','\end{equation}');
  fprintf(latex_file,'\n');
  q_m = q_m + 1;
  %matlabFunction(determinants(32)*rho_t * C_t,'File',strcat(theta_dir,'RBMTheta_31'));
  fprintf(latex_file,'%s','\begin{equation}');
  fprintf(latex_file,'\n');
  fprintf(latex_file,'%s',"\Theta_m^{"+num2str(q_m+1)+"}(\mu)=");
  fprintf(latex_file,'%s',latex(subs(determinants(32)*rho_t * C_t,{r,l,h,d},{r_ref,l_ref,h_0,d_0})));
  fprintf(latex_file,'%s','\end{equation}');
  fprintf(latex_file,'\n');
  q_m = q_m + 1;

fclose(latex_file);
end
