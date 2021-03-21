function [] = perform_FE_solve_PDSplit(param_subd,param_num,mesh_num,test_case)
%Performs full FE solve for given parameter value and mesh number
% Input:
% param_subd: parameter space subdomain "min_min"/"min_max"/"max_max"/"max_min"
% param_num : 1=param_min/2=param_ref/3=param_max
% mesh_num : number of mesh refinement (0,1..4)
% Action:
% Writes the temperature solution to vtu files
% Compute mesh convergence metric and writes to file
[mem,vmem] = get_memory_usage()
mem_init = 0;%mem
vmem_init = 0;%vmem
fprintf(1,"Starting FE solve; Memory consumption: rss=%e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
get_memory_usage_from_qstat();

if (~strcmp(param_subd,'max_max') && ~strcmp(param_subd,'min_max') && ~strcmp(param_subd,'max_min') && ~strcmp(param_subd,'min_min'))
    error("Invalid value provided for param_subd")
end

if (param_num ~= 1) && (param_num ~= 2) && (param_num ~=3)
    error("Invalid value provided for param_num");
end

if (mesh_num < 0) || (mesh_num > 4) || (mod(mesh_num,1) ~= 0)
    error("Invalid value provided for mesh_num");
end

param_subd
param_num
mesh_num

r_arr = [4e-4 7.521e-4 1.414e-3 2.659e-3 5e-3];
l_arr = [5e-3 9.672e-3 1.871e-2 3.619e-2 7e-2];

keySet = {'max_min','max_max','min_max','min_min'};
valueSet = {[r_arr(4) l_arr(2)], [r_arr(4) l_arr(4)], [r_arr(2) l_arr(4)], [r_arr(2) l_arr(2)]};
r_l_ref = containers.Map(keySet, valueSet);
r_l_new = containers.Map(keySet,{[[r_arr(3) l_arr(1)]; [r_arr(4) l_arr(2)]; [r_arr(5) l_arr(3)]], [[r_arr(3) l_arr(3)]; [r_arr(4) l_arr(4)]; [r_arr(5) l_arr(5)]], [[r_arr(1) l_arr(3)]; [r_arr(2) l_arr(4)]; [r_arr(3) l_arr(5)]], [[r_arr(1) l_arr(1)]; [r_arr(2) l_arr(2)]; [r_arr(3) l_arr(3)]]});




param_label_S = ["min","ref","max"];
param_label_L = ["Min","Ref","Max"];

% make sure the correct directories are added to the search path before
% calling this function



if (test_case)
    test_suffix = "_test";
    test_mat_folder = "";
else
    test_suffix = "";
    test_mat_folder = "";
end
output_file_name = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/PDSplit",test_suffix,"/",param_subd,"/param",param_label_L(param_num),"/mesh",int2str(mesh_num),"/");
%node_coords_file_base = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/mesh_",int2str(mesh_num),"/mesh_node_coords");% old text
%node_connect_file_base = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/mesh_",int2str(mesh_num),"/mesh_node_connectivity");% old text
node_coords_file_base = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/PDSplit/",param_subd,"/mesh_",int2str(mesh_num),"/mesh_node_coords");
node_connect_file_base = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/PDSplit/",param_subd,"/mesh_",int2str(mesh_num),"/mesh_node_connectivity");
%node_subd_file_path = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/mesh_",int2str(mesh_num),"/");
%node_subdomain = readmatrix(strcat(node_subd_file_path,'node_subdomain.txt'));

mesh_dim = 3;
nodes_per_elem = 4;

% Read libmesh mesh data
load_mesh_start = tic;
[node_x, element_node, subdomain_ids, node_num, element_num, ~] = read_libmesh_mesh_data(node_coords_file_base,node_connect_file_base);
load_mesh_time = toc(load_mesh_start);
fprintf(1,"\nTime to load mesh: %f min\n",load_mesh_time/60.0);
[mem,vmem] = get_memory_usage();
fprintf(1,"Mesh loaded: Memory consumption: rss=%e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
get_memory_usage_from_qstat();

node_num = length(node_x(1,:));
element_num = length(element_node(1,:));

 N_FE = node_num;
 L = 0.1;
 r_l_ref_temp = r_l_ref(param_subd);
 r = r_l_ref_temp(1)%0.001414
 l = r_l_ref_temp(2)%0.01871
 d = (8.0/3.0)*r;
 h = (4.0/3.0)*l;
 
 r_l_new_temp = r_l_new(param_subd);
 r_0 = r_l_new_temp(param_num,1)
 l_0 = r_l_new_temp(param_num,2)
 
 rho_C_t = 3.82e6;
 rho_C_b = 3.798e6;
 k_t = 0.8;
 k_b = 0.52;
 
 dt = 0.5/(sqrt(2.0)^mesh_num);
 time_end = 540.;%540.;
 num_time_steps = ceil(time_end/dt);
 x = zeros(N_FE,1); % Current Solution vector
 x_old = zeros(N_FE,1); % Old solution vector
 
 inner_prod_mat = sparse(N_FE,N_FE);
 inner_prod_mat_L2 = sparse(N_FE,N_FE);
 A_mu = sparse(N_FE,N_FE);
 M_mu = sparse(N_FE,N_FE);
 F_mu = zeros(N_FE,1);

 Arrh_integral = zeros(N_FE,1);
 integrand = zeros(N_FE,1);
 
 
 Qm = 31;
 Qa = 253;
 Qf = 32; 
load_system_mats_start = tic;
 %addpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices',test_mat_folder,'/mesh',int2str(mesh_num)));
 addpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/PDSplit',test_suffix,'/',param_subd,'/mesh',int2str(mesh_num)));
 disp("Reading Matrices")
 % load Mq matrices
 Mq_mat_cell = cell(Qm+1,1);
 base_name = 'Mq_';
 Mq_mat_size = cell(Qm+1);
 for q_m = 0:Qm %For loop cannot be parallelized
    mat_filename = strcat(base_name,int2str(q_m),'.txt');
    Mq_nz_i = readmatrix(mat_filename);
    Mq_mat_cell{q_m+1} = spconvert(Mq_nz_i);
    Mq_mat_size{q_m+1} = size(Mq_mat_cell{q_m+1});
 end

 % load Aq matrices
 Aq_mat_cell = cell(Qa+1,1);
 base_name = 'Aq_';
 Aq_mat_size = cell(Qa+1,1);
 for q_a = 0:Qa %For loop cannot be parallelized
     mat_filename = strcat(base_name,int2str(q_a),'.txt');
     Aq_nz_i = readmatrix(mat_filename);
     Aq_mat_cell{q_a+1} = spconvert(Aq_nz_i);
     Aq_mat_size{q_a+1} = size(Aq_mat_cell{q_a+1});
 end
 %rmpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices',test_mat_folder,'/mesh',int2str(mesh_num)));
 rmpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/PDSplit',test_suffix,'/',param_subd,'/mesh',int2str(mesh_num)));
 
 % load Fq vectors
 %addpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices',test_mat_folder,'/F_vectors/param_',param_label_S(param_num),'/mesh',int2str(mesh_num)));
 addpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/PDSplit',test_suffix,'/',param_subd,'/F_vectors/param_',param_label_S(param_num),'/mesh',int2str(mesh_num)));
 Fq_vec_cell = cell(Qf+1,1);
 base_name = 'Fq_';
 Fq_vec_size = zeros(Qf+1,1);
 for q_f = 0:Qf %For loop cannot be parallelized
    vec_filename = strcat(base_name,int2str(q_f),'.txt');
    Fq_vec_cell{q_f+1} = readmatrix(vec_filename);
    Fq_vec_size(q_f+1) = length(Fq_vec_cell{q_f+1});
 end
 %rmpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices',test_mat_folder,'/F_vectors/param_',param_label_S(param_num),'/mesh',int2str(mesh_num)));
 rmpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/PDSplit',test_suffix,'/',param_subd,'/F_vectors/param_',param_label_S(param_num),'/mesh',int2str(mesh_num)));
 load_system_mats_time = toc(load_system_mats_start);
 fprintf(1,"\nTime to load matrices and vectors: %f min\n",load_system_mats_time/60.0);
[mem,vmem] = get_memory_usage();
 fprintf(1,"Matrices and vecs loaded; Memory consumption: rss=%e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
get_memory_usage_from_qstat();

 disp("Assembling Stiffness Matrix and Load Vector")
  assemble_mat_vec_start = tic;
 % Assemble M matrix
  for q_m = 0:Qm %For loop can be parallelized
      RBMTheta_handle = str2func(strcat('RBMTheta_',int2str(q_m)));
      if (q_m == 30)
        M_mu = M_mu + RBMTheta_handle(L,r,r_0,l,l_0,h,d,rho_C_b)* Mq_mat_cell{q_m+1};
      else
        M_mu = M_mu + RBMTheta_handle(L,r,r_0,l,l_0,h,d,rho_C_t) * Mq_mat_cell{q_m+1};
      end
      inner_prod_mat_L2 = inner_prod_mat_L2 + RBMTheta_handle(L,r,r_0,l,l_0,h,d,1.0)*Mq_mat_cell{q_m+1};
  end
  fprintf(1,'\n');
 
 % Assemble A matrix
  for q_a = 0:Qa %For loop can be parallelized
      RBATheta_handle = str2func(strcat('RBTheta_',int2str(q_a)));
      if (q_a >= 246) && (q_a <= 248)
        A_mu = A_mu + RBATheta_handle(L,r,r_0,l,l_0,h,d,k_b) * Aq_mat_cell{q_a+1};
      else
        A_mu = A_mu + RBATheta_handle(L,r,r_0,l,l_0,h,d,k_t) * Aq_mat_cell{q_a+1};
      end
  end
  fprintf(1,'\n');
 % Assemble inner product matrix
  for q_a = 0:Qa %For loop can be parallelized
      RBTheta_handle = str2func(strcat('RBTheta_',int2str(q_a)));
      if (q_a >= 246) && (q_a <= 248)
          inner_prod_mat = inner_prod_mat + RBATheta_handle(L,r,r,l,l,h,d,k_b) * Aq_mat_cell{q_a+1};
      else
          inner_prod_mat = inner_prod_mat + RBATheta_handle(L,r,r,l,l,h,d,k_t) * Aq_mat_cell{q_a+1};
      end
  end
  fprintf(1,'\n');

 % Assemble F vector
  for q_f = 0:Qf %For loop can be parallelized
      F_mu = F_mu + Fq_vec_cell{q_f+1};
  end
  assemble_mat_vec_time = toc(assemble_mat_vec_start);
  fprintf(1,"\nTime to assemble system matrices and vectors: %f min\n",assemble_mat_vec_time/60.0);
  [mem,vmem] = get_memory_usage();
  fprintf(1,"Matrices and vecs assembled; Memory consumption: rss=%e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
  get_memory_usage_from_qstat();


 solve_and_postproc_start = tic;
 disp("Solving FE Problem")

  A = 3.1e98;
  E_a = 6.28e5;
  k = 8.3145;
  mesh_conv_metric = 0;
  x_mesh_conv = zeros(N_FE,1);

  start_mesh_deform = tic;
  %node_x_new = deform_mesh_fast(node_x, node_subdomain, element_node, r_0, l_0);
  node_x_new = deform_mesh_fast(node_x, subdomain_ids, element_node, r, l, r_0, l_0);
  mesh_deform_time = toc(start_mesh_deform);
  fprintf(1,"\nTime for mesh deformation: %f min\n",mesh_deform_time/60.0);
  [mem,vmem] = get_memory_usage();
  fprintf(1,"Mesh deformed: Memory consumption: rss = %e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
  
  start_mesh_conv = tic;
  [mesh_conv_node_ids, mesh_conv_vol] = get_mesh_conv_node_ids(node_x_new);
  mesh_conv_vol
  [mem,vmem] = get_memory_usage();
  fprintf(1,"\nMesh conv node ids obtained: Memory consumption: rss = %e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);

% Solve transient problem (backward Euler)
  icholesky_start = tic;
  R_i = ichol(M_mu/dt + A_mu);
  
  for time_step = 2:num_time_steps+1
      x = pcg(A_mu + M_mu/dt,F_mu + M_mu*x_old(:)/dt,1e-6,1000,R_i,R_i');
      integrand = -A.*exp(-E_a./(k.*(x + 310.15)));
      Arrh_integral = Arrh_integral + integrand*dt;
      x_mesh_conv = 0*x_mesh_conv;
      x_mesh_conv(mesh_conv_node_ids) = x(mesh_conv_node_ids) + 310.15;
      T_norm_t = sqrt((x_mesh_conv'*inner_prod_mat_L2*x_mesh_conv)/mesh_conv_vol);
      mesh_conv_metric = mesh_conv_metric + T_norm_t*dt;
      x_old = x;
  end
  icholesky_time = toc(icholesky_start);
  fprintf(1,"\nTime for full precond. CG solve: %f min\n",icholesky_time/60.0);
  mesh_conv_metric = mesh_conv_metric / time_end;
  Arrh_tissue_damage = 1 - heaviside(-exp(-1) + exp(Arrh_integral));
  solve_time = toc(solve_and_postproc_start);
  fprintf(1,"\nTime for FE solve, Arrhenius, mesh conv: %f min\n",solve_time/60.0);
  
  [mem,vmem] = get_memory_usage();
  fprintf(1,"Temperature computed: Memory consumption: rss = %e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
  
  x = x + 310.15;
  solve_and_postproc_time = toc(solve_and_postproc_start);
  fprintf(1,"\nTime to solve and postprocess: %f min\n",solve_and_postproc_time/60.0);
[mem,vmem] = get_memory_usage();
  fprintf(1,"Solution and postproc complete; Memory consumption: rss=%e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
  get_memory_usage_from_qstat();

  write_output_start = tic;
  disp("Writing results to file")
  % Deform mesh
%  % Write results to .vtu file (ParaView)
%   
     output_unit = fopen(output_file_name + "temperature_" + int2str(num_time_steps+1-2) + ".vtu","w");
     write_vtu ( output_unit, node_num, element_num, nodes_per_elem, node_x_new, element_node, subdomain_ids, x, "temperature" );
     fclose(output_unit); 

 output_unit = fopen(output_file_name+"Arrh_tissue_damage.vtu","w");
 write_vtu(output_unit, node_num, element_num, nodes_per_elem, node_x_new, element_node, subdomain_ids, Arrh_tissue_damage,"arrhenius_tissue_damage");
 fclose(output_unit);
 output_unit = fopen(output_file_name+"mesh_conv_metric.txt","w");
 fprintf(output_unit,num2str(mesh_conv_metric));
 fclose(output_unit);
 write_output_time = toc(write_output_start);
 fprintf(1,"\nTime to write output: %f min\n",write_output_time/60.0);
[mem,vmem] = get_memory_usage();
 fprintf(1,'Output written; Memory consumption: rss=%e Mb; vmem=%e Mb;\n',mem - mem_init,vmem - vmem_init);
end

