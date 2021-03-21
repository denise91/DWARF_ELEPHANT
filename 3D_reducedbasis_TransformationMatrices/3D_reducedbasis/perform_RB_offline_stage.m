function [RB_Con, RB_Eval] = perform_RB_offline_stage(RB_Con, RB_Eval, EIM_data, mesh_data)
  % Initialize logging data 
  time_preproc_begin = tic;
  %[rss_init, vmem_init] = get_memory_usage();
  rss_init = 0;
  vmem_init = 0;
 
  % Set FE solver constants 
  dt = RB_Con.dt; 
  K = RB_Con.n_time_steps; 
  RB_Con.g_FE = ones(RB_Con.n_time_steps,1);% Forcing input for the full FE solutions (RB basis vectors)(impulse input)
  RB_Eval.g_FE = RB_Con.g_FE;
 
  % Compute inner product matrix 
  mu_bar = RB_Eval.mu_bar;
  RB_Con.X_curN = sparse(RB_Con.N_FE,RB_Con.N_FE); 
  mat_qa_min = min(cell2mat(keys(RB_Con.Aq_mat_map)));
  theta_qa_min = min(cell2mat(keys(RB_Eval.RB_A_Theta_map))); 
  for q = 1:RB_Con.Qa
    RBATheta_handle = RB_Eval.RB_A_Theta_map(theta_qa_min - 1 + q);
    RB_Con.X_curN = RB_Con.X_curN + RBATheta_handle(mu_bar) * RB_Con.Aq_mat_map(mat_qa_min - 1 + q);
  end


  % Compute approximate coercivity constant
  [alpha_min] = get_alpha_min_est(RB_Con,RB_Eval);

  % Create training parameter set  
  xi_train = containers.Map('KeyType','char','ValueType','any');
  mu_min_keys_arr = keys(RB_Eval.mu_min);
  for i_key = 1:length(mu_min_keys_arr)
    mu_min_keys_cell = mu_min_keys_arr(i_key);
    key = mu_min_keys_cell{1};
    xi_train(key) = RB_Eval.mu_min(key) + (RB_Eval.mu_max(key) - RB_Eval.mu_min(key))*rand(RB_Eval.n_training_samples,1);
  end
 
  % Create parameter object compute RB basis function 
  mu_0star = containers.Map('KeyType','char','ValueType','any');
  for i_key = 1:length(mu_min_keys_arr)
    mu_min_keys_cell = mu_min_keys_arr(i_key);
    key = mu_min_keys_cell{1};
    train_param_array = xi_train(key);
    mu_0star(key) = train_param_array(1);
  end
  [rss,vmem] = get_memory_usage();
  time_preproc = toc(time_preproc_begin);
  fprintf(1,'Memory consumption for RB offline pre-processing: rss = %e Mb; vmem = %e Mb\n',rss-rss_init,vmem - vmem_init);
  fprintf(1,'Time requried for RB offline pre-processing: %f minutes\n',time_preproc/60.0);

  time_offline_begin = tic;
  N = 1; 
 
  % Create residual dual-norm and RB error bound arrays 
  ResNorm_OnOff = zeros(RB_Eval.n_time_steps,1); 
  delta_kN_sq_onoff = zeros(RB_Eval.n_time_steps,1); 
  
  mu_0star('r_0') = mu_0star('r');% temporary code
  mu_0star('l_0') = mu_0star('l');% temporary code
  mu_0star('needle_x') = 0.01;% temporary code 
  mu_0star('needle_y') = 0.01;% temporary code
  mu_0star('needle_z') = 0.01;% temporary code
  mu_0star('needle_phi') = 0;%3.691039e-02;% temporary code
  mu_0star('needle_theta') = 0;%9.389991e-02;% temporary code
  fprintf('Perfusion coefficient = %e\n',mu_0star('omega_p'));% temporary code

  % Compute needle_tfirst basis function 
  [RB_Eval] = compute_EIM_theta_objects(mu_0star,RB_Eval,EIM_data);% change mu var
  [u_fem, ~] = solve_FEM_timedep(mu_0star, RB_Con, RB_Eval);% change mu var
  
  [mesh_node_coords_new] = deform_mesh_RB(mesh_data.node_x, mesh_data.subdomain_ids, mesh_data.element_node, mu_0star);% temporary code
  output_unit = fopen(strcat('temperature_test.vtu'),'w');
  write_vtu(output_unit, mesh_data.node_num, mesh_data.element_num, max(size(mesh_data.element_node(:,1))), mesh_node_coords_new, mesh_data.element_node, mesh_data.subdomain_ids, u_fem(:,K), "Temperature");
  error('Ended execution!'); % temporary code
  
  Z_new = POD_X(u_fem, 1, RB_Con.X_curN, RB_Con.n_time_steps); 
  Z = Z_new/sqrt(Z_new'*RB_Con.X_curN*Z_new); 
  RB_Eval = createRBStruct_timedep(Z, RB_Con, RB_Eval); 
 
  % Perform offline computation for Riesz representor inner products 
  [RB_Con, RB_Eval] = Initialize_Riesz_representors(RB_Con, RB_Eval);
  [RB_Con, RB_Eval] = ResNormPara_Offline( RB_Con, RB_Eval ); 
  
  
  maxbound = 1e100;
  maxbound_init = 1;
  [rss,vmem] = get_memory_usage();
  time_offline_iter_0 = toc(time_offline_begin);
  fprintf(1,'Memory consumption for RB offline iter 0: rss = %e Mb; vmem = %e Mb\n',rss-rss_init,vmem - vmem_init);
  fprintf(1,'Time requried for RB offline iter 0: %f minutes\n',time_offline_iter_0/60.0);

  mu = containers.Map('KeyType','char','ValueType','any');
  
 while (maxbound/maxbound_init > RB_Eval.e_tol_min)
      time_offline_iter_begin = tic;
      
      maxbound = 0;
      for i = 1:RB_Eval.n_training_samples
        time_get_param_value_begin = tic; 
        for i_key = 1:length(mu_min_keys_arr)
            mu_min_keys_cell = mu_min_keys_arr(i_key);
            key = mu_min_keys_cell{1};
            train_param_array = xi_train(key);
            mu(key) = train_param_array(i);
        end
        time_get_param_value_end = toc(time_get_param_value_begin);
	fprintf(1,'Time required to get param value: %f minutes\n',time_get_param_value_end/60.0);
        [RB_Eval] = compute_EIM_theta_objects(mu,RB_Eval,EIM_data);	
        [uN, ~] = solveRB_timedep(mu, RB_Eval);		
        [CmuT_X_Cmu, CmuT_X_Amu, CmuT_X_Mmu, MmuT_X_Mmu, MmuT_X_Amu, MmuT_X_Cmu, AmuT_X_Amu, AmuT_X_Mmu, AmuT_X_Cmu] = ResNormPara_Online_TimeIndepTerms(mu, RB_Eval);
	
	time_error_bound_begin = tic;
        ResNorm_OnOff(1) = ResNormPara_Online_Result(CmuT_X_Cmu, CmuT_X_Amu, CmuT_X_Mmu, MmuT_X_Mmu, MmuT_X_Amu, MmuT_X_Cmu, AmuT_X_Amu, AmuT_X_Mmu, AmuT_X_Cmu, uN(:,1), RB_Eval.uN_init, RB_Eval.g_FE(1), dt);
        delta_kN_sq_onoff(1) = dt*ResNorm_OnOff(1);
        for j = 2:K
          ResNorm_OnOff(j) = ResNormPara_Online_Result(CmuT_X_Cmu, CmuT_X_Amu, CmuT_X_Mmu, MmuT_X_Mmu, MmuT_X_Amu, MmuT_X_Cmu, AmuT_X_Amu, AmuT_X_Mmu, AmuT_X_Cmu, uN(:,j), uN(:,j-1), RB_Eval.g_FE(j), dt);
          delta_kN_sq_onoff(j) = delta_kN_sq_onoff(j-1) + dt*ResNorm_OnOff(j);
        end
        delta_kN_onoff = sqrt(delta_kN_sq_onoff(K)/alpha_min);
        time_error_bound = toc(time_error_bound_begin);
        fprintf(1,'Time to compute error bound: %f minutes\n',time_error_bound/60.0);
        
	time_maxbound_begin = tic;
        if (delta_kN_onoff > maxbound)
          mu_0star = mu;
          maxbound = delta_kN_onoff;
        end
		if (N == 1)
			maxbound_init = maxbound;
		end
	time_maxbound = toc(time_maxbound_begin);
	fprintf(1,'Time to compute maxbound iteration: %f minutes\n',time_maxbound/60.0);
      end
      fprintf(1,'RB dimension N = %d. Basis function to be computed at:\n r_0 = %e\n l_0 = %e\n needle_x = %e\n needle_y = %e\n needle_z = %e\n needle_theta = %e\n needle_phi = %e\n',N,mu_0star('r_0'),mu_0star('l_0'),mu_0star('needle_x'),mu_0star('needle_y'),mu_0star('needle_z'),mu_0star('needle_phi'),mu_0star('needle_theta'));
      fprintf(1,'Maximum error bound (relative to 1st iteration) is: %e\n',maxbound/maxbound_init);
      
      N = N + 1;
      [RB_Eval] = compute_EIM_theta_objects(mu_0star,RB_Eval,EIM_data);
      [u_fem, ~] = solve_FEM_timedep(mu_0star, RB_Con, RB_Eval);
      e_Nproj = u_fem - RB_Eval.Z*(RB_Eval.Z'*RB_Con.X_curN*u_fem); 
      Z_new = POD_X(e_Nproj, 1, RB_Con.X_curN, RB_Con.n_time_steps);
      Z(:,N) = Z_new/sqrt(Z_new'*RB_Con.X_curN*Z_new);
      RB_Eval = createRBStruct_timedep(Z(:,1:N), RB_Con, RB_Eval);
      [RB_Con, RB_Eval] = ResNormPara_Offline( RB_Con, RB_Eval);
    
      [rss,vmem] = get_memory_usage();
      time_offline_next_iter = toc(time_offline_iter_begin);
      fprintf(1,'Memory consumption for RB offline next iter: rss = %e Mb; vmem = %e Mb\n',rss-rss_init,vmem - vmem_init);
      fprintf(1,'Time requried for RB offline next iter: %f minutes\n',time_offline_next_iter/60.0);
 end
end
