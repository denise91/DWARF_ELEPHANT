
clear all

%mesh_file_name = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/RBGeom_Test.msh";
output_file_name = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/paramMin/mesh0_paramMin";

node_coords_file_base = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data_test/mesh_node_coords";
node_connect_file_base = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data_test/mesh_node_connectivity";

mesh_dim = 3;
nodes_per_elem = 4;

disp("Read gmsh file")
% Read gmsh file
cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis';

%[ node_x, element_node ] = read_gmsh_file(mesh_file_name,mesh_dim,nodes_per_elem);
[node_x, element_node, subdomain_ids, ~, ~, Permute_nodes] = read_libmesh_mesh_data(node_coords_file_base,node_connect_file_base);
node_num = length(node_x(1,:));
element_num = length(element_node(1,:));

 N_FE = node_num;
 L = 0.1;
 r = 0.003;
 l = 0.04;
  
 r_0 = 4e-4;%4e-4;
 l_0 = 5e-3;%5e-4;
 
 rho_C_t = 3.82e6;
 rho_C_b = 3.798e6;
 k_t = 0.8;
 k_b = 0.52;
 
 dt = 0.707106781187;
 time_end = 540.;%20*dt;%
 num_time_steps = ceil(time_end/dt);
 x = zeros(N_FE,num_time_steps+1); % Solution vector
 
 A_mu = sparse(N_FE,N_FE);
 M_mu = sparse(N_FE,N_FE);
 F_mu = zeros(N_FE,1);
 
 Qm = 31;
 Qa = 253;
 Qf = 32;
 matlab_thetas = [];
 cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/transienttestcase';
 
 disp("Reading Matrices")
 % load Mq matrices
 Mq_mat_cell = cell(1,1);
for q_m = 0:Qm %For loop can be parallelized
    eval([strcat('Mq_',int2str(q_m))]);
    Mq_mat_cell{q_m+1} = eval([strcat('Mq_',int2str(q_m),'_sp')]);
end

% load Aq matrices
Aq_mat_cell = cell(1,1);
for q_a = 0:Qa %For loop can be parallelized
    eval([strcat('Aq_',int2str(q_a))]);
    Aq_mat_cell{q_a+1} = eval([strcat('Aq_',int2str(q_a),'_sp')]);
end

 cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/transienttestcase/F_vectors/param_min';
% load Fq vectors
Fq_vec_cell = cell(1,1);
for q_f = 0:Qf %For loop can be parallelized
    eval([strcat('Fq_',int2str(q_f))]);
    Fq_vec_cell{q_f+1} = eval([strcat('Fq_',int2str(q_f),'_vec')]);
end

cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/'

disp("Assembling Stiffness Matrix and Load Vector")
% Assemble M matrix
for q_m = 0:Qm %For loop can be parallelized
    if (q_m == 30)
        M_mu = M_mu + feval(strcat('RBMTheta_',int2str(q_m)),L,r,r_0,l,l_0,1.5*l,3*r,rho_C_b) * Mq_mat_cell{q_m+1};
        matlab_thetas = [matlab_thetas; feval(strcat('RBMTheta_',int2str(q_m)),L,r,r_0,l,l_0,1.5*l,3*r,rho_C_b)];
    else
        M_mu = M_mu + feval(strcat('RBMTheta_',int2str(q_m)),L,r,r_0,l,l_0,1.5*l,3*r,rho_C_t) * Mq_mat_cell{q_m+1};
        matlab_thetas = [matlab_thetas; feval(strcat('RBMTheta_',int2str(q_m)),L,r,r_0,l,l_0,1.5*l,3*r,rho_C_t)];
    end
end
% M_mu = Mq_mat_cell{1}*rho_C_t + Mq_mat_cell{2}*rho_C_b;
% M_mu = M_mu(Permute_nodes,:);
% M_mu = M_mu(:,Permute_nodes);
% 
% Assemble A matrix
for q_a = 0:Qa %For loop can be parallelized
    if (q_a >= 246) && (q_a <= 248)
        A_mu = A_mu + feval(strcat('RBTheta_',int2str(q_a)),L,r,r_0,l,l_0,1.5*l,3*r,k_b) * Aq_mat_cell{q_a+1};
        matlab_thetas = [matlab_thetas; feval(strcat('RBTheta_',int2str(q_a)),L,r,r_0,l,l_0,1.5*l,3*r,k_b)];
    else
        A_mu = A_mu + feval(strcat('RBTheta_',int2str(q_a)),L,r,r_0,l,l_0,1.5*l,3*r,k_t) * Aq_mat_cell{q_a+1};
        matlab_thetas = [matlab_thetas; feval(strcat('RBTheta_',int2str(q_a)),L,r,r_0,l,l_0,1.5*l,3*r,k_t)];
    end
end

% Assemble inner product matrix
% A_mu = Aq_mat_cell{1}*k_t + Aq_mat_cell{2}*1.9e5 + Aq_mat_cell{3}*k_b + Aq_mat_cell{4}*1.0;
% A_mu = A_mu(Permute_nodes,:);
% A_mu = A_mu(:,Permute_nodes);
% Assemble F vector
F_mu = F_mu + Fq_vec_cell{1};
for q_f = 1:Qf %For loop can be parallelized
    F_mu = F_mu + Fq_vec_cell{q_f+1}; %%% CHECK SCALING OF FORCING FUNCION
end

%F_mu = F_mu(Permute_nodes);
disp("Solving FE Problem")
% Initialize solution vector
% Solve transient problem (backward Euler)
for time_step = 2:num_time_steps+1
    x(:,time_step) = (M_mu/dt + A_mu)\(F_mu + M_mu*x(:,time_step-1)/dt);
end


A = 3.1e98;
E_a = 6.28e5;
k = 8.3145;

cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/'
[Arrh_tissue_damage, survival_fraction] = compute_Arrhenius_tissue_damage(x,dt,A,E_a,k);
[mesh_conv_node_ids] = get_mesh_conv_node_ids(node_x);
[mesh_conv_metric] = compute_mesh_conv_metric(x,mesh_conv_node_ids,A_mu,dt);

%mesh_conv_metric

disp("Writing results to file")
% Write results to .vtu file (ParaView)

% deform mesh
node_x_new = deform_mesh(node_x, subdomain_ids, element_node, r_0, l_0);
x = x + 310.15;
for time_step = 2:num_time_steps+1
    time_step
    output_unit = fopen(output_file_name + "_" + int2str(time_step-1) + ".vtu","w");
    %x(:,time_step) = x(:,time_step) + 100;
    write_vtu ( output_unit, node_num, element_num, nodes_per_elem, node_x_new, element_node, subdomain_ids, x(:,time_step), "temperature" );    
    fclose(output_unit);
end



% write vtu
output_unit = fopen(output_file_name+"_Arrh_tissue_damage.vtu","w");
write_vtu(output_unit, node_num, element_num, nodes_per_elem, node_x_new, element_node, subdomain_ids, Arrh_tissue_damage,"arrhenius_tissue_damage");