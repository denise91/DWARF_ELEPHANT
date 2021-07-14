function [RB_Con, RB_Eval, Mesh_data, EIM_data] = load_FE_data_PDSPL_max_max(RB_Con,RB_Eval,EIM_data)
  time_load_data_begin = tic;
  rss_init = 0;
  vmem_init = 0;
  
  
  node_coords_file_base = strcat(RB_Con.mesh_data_path,'mesh_node_coords');
  node_connect_file_base = strcat(RB_Con.mesh_data_path,'mesh_node_connectivity');
  
  Mesh_data.mesh_dim = 3;
  Mesh_data.nodes_per_elem = 4;

  % Read libmesh mesh data
  [Mesh_data.node_x, Mesh_data.element_node, Mesh_data.subdomain_ids, Mesh_data.node_num, Mesh_data.element_num, ~] = read_libmesh_mesh_data(node_coords_file_base,node_connect_file_base);

  get_memory_usage_from_qstat();
  
  node_num = length(Mesh_data.node_x(1,:));
  RB_Con.element_num = length(Mesh_data.element_node(1,:));
  
  RB_Con.N_FE = node_num;
  RB_Con.u_init = zeros(RB_Con.N_FE,1);  

  [rss,vmem] = get_memory_usage();
  time_load_mesh = toc(time_load_data_begin);
  fprintf(1,'Memory consumption to load mesh data: rss = %e Mb; vmem = %e Mb\n',rss-rss_init,vmem - vmem_init);
  fprintf(1,'Time requried to load mesh data: %f minutes\n',time_load_mesh/60.0);
  
  time_create_mats_begin = tic;
  RB_Con.inner_prod_mat = sparse(node_num,node_num);
  RB_Con.inner_prod_mat_L2 = sparse(node_num,node_num);
  RB_Con.A_mu = sparse(node_num,node_num);
  RB_Con.M_mu = sparse(node_num,node_num);
 
  disp('Reading Mq Matrices\n')
  Mq_dirname = RB_Con.RB_matrix_path;
  Mq_file_base = 'Mq_*.txt';
  Mq_mat_files = dir(strcat(Mq_dirname,Mq_file_base));
  MTheta_dirname = RB_Eval.RB_theta_path;
  MTheta_file_base = 'RBMTheta*.m';
  MTheta_files = dir(strcat(MTheta_dirname,MTheta_file_base));
  if (max(size(MTheta_files)) == max(size(Mq_mat_files)))
    RB_Con.Qm = max(size(Mq_mat_files));
    RB_Eval.Qm = RB_Con.Qm;
  else
    error('Error!!! The number of Mq matrices and MTheta objects does not match.')
  end
 
  RB_Con.Mq_mat_map = containers.Map('KeyType','int32','ValueType','any');
  RB_Eval.RB_M_Theta_map = containers.Map('KeyType','int32','ValueType','any');
  
  for q_m = 1:RB_Con.Qm
    Mq_nz_i = readmatrix(strcat(Mq_dirname,'/',Mq_mat_files(q_m).name));
    Mq_index = round(str2double(regexp(Mq_mat_files(q_m).name,'\d+','match')));
    RB_Con.Mq_mat_map(Mq_index) = spconvert(Mq_nz_i);
    MTheta_index = round(str2double(regexp(MTheta_files(q_m).name,'\d+','match')));
    MTheta_func_name = erase(MTheta_files(q_m).name,'.m');
    RB_Eval.RB_M_Theta_map(MTheta_index) = str2func(MTheta_func_name);
  end
  fprintf(1,'Read %d Mq matrices\n',RB_Con.Qm);
  
  disp('Reading Aq Matrices\n')
  Aq_dirname = RB_Con.RB_matrix_path;
  Aq_file_base = 'Aq_*.txt';
  ATheta_dirname = RB_Eval.RB_theta_path;
  ATheta_file_base = 'RBTheta*.m';
  Aq_mat_files = dir(strcat(Aq_dirname,Aq_file_base));
  ATheta_files = dir(strcat(ATheta_dirname,ATheta_file_base));
  if (max(size(ATheta_files)) == max(size(Aq_mat_files)))
    RB_Con.Qa = max(size(Aq_mat_files));
    RB_Eval.Qa = RB_Con.Qa;
  else
    error('Error!!! The number of Aq matrices and ATheta objects does not match.')
  end
 
  RB_Con.Aq_mat_map = containers.Map('KeyType','int32','ValueType','any');
  RB_Eval.RB_A_Theta_map = containers.Map('KeyType','int32','ValueType','any');
  
  for q_a = 1:RB_Con.Qa	
	Aq_nz_i = readmatrix(strcat(Aq_dirname,'/',Aq_mat_files(q_a).name));
	Aq_index = round(str2double(regexp(Aq_mat_files(q_a).name,'\d+','match')));
    RB_Con.Aq_mat_map(Aq_index) = spconvert(Aq_nz_i);
	ATheta_index = round(str2double(regexp(ATheta_files(q_a).name,'\d+','match')));
	ATheta_func_name = erase(ATheta_files(q_a).name,'.m');
    RB_Eval.RB_A_Theta_map(ATheta_index) = str2func(ATheta_func_name);
  end
  fprintf(1,'Read %d Aq matrices\n',RB_Con.Qa);
  
  disp('Reading Fq Vectors\n');
  if (EIM_data.use_EIM == 1)
    tempvar = 1;
    EIM_data = load_EIM_data_PDSPL_max_max(EIM_data);
    tempvar = 2;
  else
    error('Invalid value provided for use_EIM! It must be 1.');
  end
  Fq_dirname = RB_Con.RB_F_vec_path;
  Fq_file_base = 'Fq_*.txt';
  FTheta_dirname = RB_Eval.RB_theta_path;
  FTheta_file_base = 'RBFTheta*.m';
  Fq_mat_files = dir(strcat(Fq_dirname,Fq_file_base));
  FTheta_files = dir(strcat(FTheta_dirname,FTheta_file_base));
  if ((max(size(FTheta_files)) + EIM_data.use_EIM*EIM_data.M*EIM_data.num_subdomains) == max(size(Fq_mat_files)))
    RB_Con.Qf = max(size(Fq_mat_files));
    RB_Eval.Qf = RB_Con.Qf;
  else
    error('Error!!! The number of Fq vectors and FTheta objects does not match.')
  end
 
  RB_Con.Fq_vec_map = containers.Map('KeyType','int32','ValueType','any');
  RB_Eval.RB_F_Theta_map = containers.Map('KeyType','int32','ValueType','any');
  
  for q_f = 1:RB_Con.Qf
	Fq_index = round(str2double(regexp(Fq_mat_files(q_f).name,'\d+','match')));
    RB_Con.Fq_vec_map(Fq_index) = readmatrix(strcat(Fq_dirname,'/',Fq_mat_files(q_f).name));
	if (q_f <= max(size(FTheta_files)))
          FTheta_index = round(str2double(regexp(FTheta_files(q_f).name,'\d+','match')));
          FTheta_func_name = erase(FTheta_files(q_f).name,'.m');
          RB_Eval.RB_F_Theta_map(FTheta_index) = str2func(FTheta_func_name);
	end
  end
  fprintf(1,'Read %d Fq matrices\n',RB_Con.Qf);

  RB_Eval.EIM_qf_begin = max(size(FTheta_files));
  [rss,vmem] = get_memory_usage();
  time_create_mats_begin = toc(time_load_data_begin);
  fprintf(1,'Memory consumption to create matrices: rss = %e Mb; vmem = %e Mb\n',rss-rss_init,vmem - vmem_init);
  fprintf(1,'Time requried to create matrices: %f minutes\n',time_create_mats_begin/60.0);
end
