
clear all
%mesh_file_name = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/RBGeom_Test.msh";
output_file_name = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/paramRef/mesh0_paramRef";

node_coords_file_base = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data_test/mesh_node_coords";
node_connect_file_base = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data_test/mesh_node_connectivity";

mesh_dim = 3;
nodes_per_elem = 4;

disp("Read gmsh file")
% Read gmsh file
cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis';

%[ node_x, element_node ] = read_gmsh_file(mesh_file_name,mesh_dim,nodes_per_elem);
[node_x, element_node, node_num, element_num, Permute_nodes] = read_libmesh_mesh_data(node_coords_file_base,node_connect_file_base);
%node_num = length(node_x(1,:));
%element_num = length(element_node(1,:));

 N_FE = node_num;
 L = 0.1;
 r = 0.003;
 l = 0.04;
  
 r_0 = r;
 l_0 = l;
 
 rho_C_t = 3.82e6;
 rho_C_b = 3.798e6;
 k_t = 0.8;
 k_b = 0.52;
 
 %dt = 0.707106781187;
 %time_end = 540.0;
 %num_time_steps = ceil(time_end/dt);
 %x = zeros(N_FE,num_time_steps+1); % Solution vector
 x = zeros(N_FE,1);
 
 A_mu = sparse(N_FE,N_FE);
 %A_mu
 M_mu = sparse(N_FE,N_FE);
 F_mu = zeros(N_FE,1);
 
 Qa = 3;%253;
 Qf = 32;
 
cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/steadytestcase/';
 
 disp("Reading Matrices")
% load Mq matrices
%Mq_mat_cell = cell(1,1);
%for q_m = 0:31
%    eval([strcat('Mq_',int2str(q_m))]);
%    Mq_mat_cell{q_m+1} = eval([strcat('Mq_',int2str(q_m),'_sp')]);
%end

% load Aq matrices
Aq_mat_cell = cell(1,1);
for q_a = 0:Qa%0:3
    eval([strcat('Aq_',int2str(q_a))]);
    Aq_mat_cell{q_a+1} = eval([strcat('Aq_',int2str(q_a),'_sp')]);
end

cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/steadytestcase/F_vectors';


% load Fq vectors
Fq_vec_cell = cell(1,1);
for q_f = 0:32
    eval([strcat('Fq_',int2str(q_f))]);
    Fq_vec_cell{q_f+1} = eval([strcat('Fq_',int2str(q_f),'_vec')]);
end

cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/'

disp("Assembling Stiffness Matrix and Load Vector")
% Assemble M matrix
%for q_m = 0:31
%    if (q_m == 30)
%        M_mu = M_mu + feval(strcat('RBMTheta_',int2str(q_m)),L,r,r_0,l,l_0,3*r,1.5*l,rho_C_b) * Mq_mat_cell{q_m+1};
%    else
%        M_mu = M_mu + feval(strcat('RBMTheta_',int2str(q_m)),L,r,r_0,l,l_0,3*r,1.5*l,rho_C_t) * Mq_mat_cell{q_m+1};
%    end
%end

% Assemble A matrix
%A_mu = Aq_mat_cell{1}*k_t + Aq_mat_cell{3}*k_b + Aq_mat_cell{4} + Aq_mat_cell{2}*1.9e5;% 
for q_a = 0:Qa
    if (q_a >= 246) && (q_a <= 248)
        A_mu = A_mu + feval(strcat('RBTheta_',int2str(q_a)),L,r,r_0,l,l_0,3*r,1.5*l,k_b) * Aq_mat_cell{q_a+1};
    else
        A_mu = A_mu + feval(strcat('RBTheta_',int2str(q_a)),L,r,r_0,l,l_0,3*r,1.5*l,k_t) * Aq_mat_cell{q_a+1};
    end
end

%A_mu = A_mu(Permute_nodes,:);
%A_mu = A_mu(:,Permute_nodes);
condest(A_mu)
% Assemble F vector
for q_f = 0:32
    F_mu = F_mu + Fq_vec_cell{q_f + 1};
end
%F_mu = F_mu(Permute_nodes);    

disp("Solving FE Problem")
% Solve transient problem
x = A_mu \ F_mu;

x = x(Permute_nodes);
disp("Writing results to file")
% Write results to .vtu file (ParaView)
output_unit = fopen(output_file_name + "_steady.vtu","w");
write_vtu ( output_unit, node_num, element_num, nodes_per_elem, node_x, element_node, x, "temperature" );
    
