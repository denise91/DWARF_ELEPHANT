function [RB_Con,RB_Eval,EIM_data] = set_input_params()
  % Specify data file paths
  RB_Eval.offline_stage = true;
  RB_Eval.online_stage = false;
  mesh_num = 2;
  RB_Con.mesh_data_path = strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data/final/mesh_',num2str(mesh_num),'/');
  RB_Con.RB_matrix_path = strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/final/mesh',num2str(mesh_num),'/');
  RB_Con.RB_F_vec_path = strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/final/F_vectors/mesh',num2str(mesh_num),'/');
  RB_Eval.RB_theta_path = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/theta_functions/';
  EIM_data.use_EIM = 1;
  EIM_data.EIM_data_path = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/';

  % Transient Simulation params
  RB_Con.dt = 0.5/(sqrt(2.0)^mesh_num);
  RB_Eval.dt = RB_Con.dt;
  RB_Con.time_end = 540.;%10.0*RB_Con.dt;%
  RB_Eval.time_end = RB_Con.time_end;
  RB_Con.n_time_steps = ceil(RB_Con.time_end/RB_Con.dt);
  RB_Eval.n_time_steps = RB_Con.n_time_steps;
  
  % FE and RB solver params
  RB_Con.l_rel_tol = 1e-6;
  RB_Con.l_max_its = 50;
  RB_Eval.e_tol_min = 1e-2;
  RB_Eval.n_training_samples = 100;
  RB_Eval.n_RB_max = 30;
  
  % Parameter values for inner product computation
  RB_Eval.mu_bar = containers.Map('KeyType','char','ValueType','any');
  RB_Eval.mu_bar('L') = 0.1;
  RB_Eval.mu_bar('r') = 0.00306;
  RB_Eval.mu_bar('l') = 0.02602;
  RB_Eval.mu_bar('d') = (8.0/3.0)*RB_Eval.mu_bar('r');
  RB_Eval.mu_bar('h') = (4.0/3.0)*RB_Eval.mu_bar('l');
  RB_Eval.mu_bar('rho_C_t') = 3.82e6;
  RB_Eval.mu_bar('rho_C_b') = 3.798e6;
  RB_Eval.mu_bar('k_t') = 0.83;
  RB_Eval.mu_bar('k_b') = 0.52;
  RB_Eval.mu_bar('r_0') = 0.00306;
  RB_Eval.mu_bar('l_0') = 0.02602; 
  RB_Eval.mu_bar('needle_x') = 0.0032;
  RB_Eval.mu_bar('needle_y') = 0.0;
  RB_Eval.mu_bar('needle_z') = -0.0007;
  RB_Eval.mu_bar('needle_phi') = 0.0; 
  RB_Eval.mu_bar('needle_theta')  = 0.0;
  %RB_Eval.mu_bar('omega_p') = 1.9e5;
  RB_Eval.mu_bar('needle_power') = 0.447;
  
  % Min/Max values for RB variable params
  RB_Eval.mu_min = containers.Map('KeyType','char','ValueType','any');
  RB_Eval.mu_min('L') = 0.1;
  RB_Eval.mu_min('r') = 0.00306;
  RB_Eval.mu_min('l') = 0.02602;
  RB_Eval.mu_min('d') = (8.0/3.0)*RB_Eval.mu_min('r');
  RB_Eval.mu_min('h') = (4.0/3.0)*RB_Eval.mu_min('l');
  RB_Eval.mu_min('rho_C_t') = 3.82e6;
  RB_Eval.mu_min('rho_C_b') = 3.798e6;
  RB_Eval.mu_min('k_t') = 0.83;
  RB_Eval.mu_min('k_b') = 0.52;
  RB_Eval.mu_min('r_0') = 0.003044;
  RB_Eval.mu_min('l_0') = 0.02589;
  RB_Eval.mu_min('needle_x') = 3.06e-3;
  RB_Eval.mu_min('needle_y') = 0.0;
  RB_Eval.mu_min('needle_z') = -1.406e-3;
  RB_Eval.mu_min('needle_phi') = 0; 
  RB_Eval.mu_min('needle_theta') = 0;
  %RB_Eval.mu_min('omega_p') = 1.9e5;
  RB_Eval.mu_min('needle_power') = 0.1;
  
  RB_Eval.mu_max = containers.Map('KeyType','char','ValueType','any');
  RB_Eval.mu_max('L') = 0.1;
  RB_Eval.mu_max('r') = 0.00306;
  RB_Eval.mu_max('l') = 0.02602;
  RB_Eval.mu_max('d') = (8.0/3.0)*RB_Eval.mu_max('r');
  RB_Eval.mu_max('h') = (4.0/3.0)*RB_Eval.mu_max('l');
  RB_Eval.mu_max('rho_C_t') = 3.82e6;
  RB_Eval.mu_max('rho_C_b') = 3.798e6;
  RB_Eval.mu_max('k_t') = 0.83;
  RB_Eval.mu_max('k_b') = 0.52;
  RB_Eval.mu_max('r_0') = 0.003074;%
  RB_Eval.mu_max('l_0') = 0.02615; % 
  RB_Eval.mu_max('needle_x') = 0.003412;
  RB_Eval.mu_max('needle_y') = 0.0;
  RB_Eval.mu_max('needle_z') = 0.0;
  RB_Eval.mu_max('needle_phi') = 9.817e-2; 
  RB_Eval.mu_max('needle_theta') = 4.659e-2;
  %RB_Eval.mu_max('omega_p') = 1.9e5;
  RB_Eval.mu_max('needle_power') = 2.0;

  assert(strcmp(cell2mat(keys(RB_Eval.mu_bar)),cell2mat(keys(RB_Eval.mu_max))),'Dimensions of mu_bar and mu_max do not match!');
  assert(strcmp(cell2mat(keys(RB_Eval.mu_min)),cell2mat(keys(RB_Eval.mu_max))),'Dimensions of mu_min and mu_max do not match!');  

  EIM_data.use_EIM = 1;

  RB_Eval.A_Arrh = 3.1e98;
  RB_Eval.k_Arrh = 8.3145;
  RB_Eval.E_a_Arrh = 6.28e5;
end
