function compute_thermal_lesion(mu_list,RB_Eval,EIM_data,mesh_data)
  rss_init = 0;
  vmem_init = 0;
  A = RB_Eval.A_Arrh;
  k_bolt = RB_Eval.k_Arrh;
  E_a = RB_Eval.E_a_Arrh;
  dt = RB_Eval.dt;
  K = RB_Eval.n_time_steps;
  i_mu = 1;
  for mu = mu_list
    time_begin = tic;
    [RB_Eval] = compute_EIM_theta_objects(mu{1},RB_Eval,EIM_data);
    [TN,~] = solveRB_timedep(mu{1}, RB_Eval);
    T_Arrh_int = RB_Eval.Z(:,1)*0;
    for k = 1:K
      T_Arrh_int = T_Arrh_int - A.*exp(-E_a./(k_bolt.*(RB_Eval.Z*TN(:,k) + 310.15)))*dt;
    end
    survival_fraction = exp(T_Arrh_int);
    tissue_damage = 1 - heaviside(- exp(-1) + survival_fraction);
    [mesh_node_coords_new,tissue_damage] = deform_mesh_RB(mesh_data.node_x, mesh_data.subdomain_ids, mesh_data.element_node, mu{1}, tissue_damage);
    %output_unit = fopen(strcat('lesion_data_r_0_',num2str(mu{1}('r_0')),'_l_0_',num2str(mu{1}('l_0')),'_x_',num2str(mu{1}('needle_x')),'_y_',num2str(mu{1}('needle_y')),'_z_',num2str(mu{1}('needle_z')),'_theta_',num2str(mu{1}('needle_theta')),'_phi_',num2str(mu{1}('needle_phi')),'_P_n_',num2str(mu{1}('needle_power')),'.vtu'),'w');
    output_unit = fopen(strcat('thermal_lesion_RB_',num2str(i_mu),'.vtu'),'w');
    write_vtu(output_unit, mesh_data.node_num, mesh_data.element_num, max(size(mesh_data.element_node(:,1))), mesh_node_coords_new, mesh_data.element_node, mesh_data.subdomain_ids, tissue_damage, "Tissue_Damage");
    fclose(output_unit);
    output_unit = fopen(strcat('final_temp_RB_',num2str(i_mu),'.vtu'),'w');
    write_vtu(output_unit, mesh_data.node_num, mesh_data.element_num, max(size(mesh_data.element_node(:,1))), mesh_node_coords_new, mesh_data.element_node, mesh_data.subdomain_ids, RB_Eval.Z*TN(:,K) + 310.15, "Temperature");
    fclose(output_unit);
    [rss,vmem] = get_memory_usage();
    time_online_solve = toc(time_begin);
    fprintf(1,'RB soln computed at:\n r_0 = %e\n l_0 = %e\n needle_x = %e\n needle_y = %e\n needle_z = %e\n needle_theta = %e\n needle_phi = %e\n needle_power = %e\n',mu{1}('r_0'),mu{1}('l_0'),mu{1}('needle_x'),mu{1}('needle_y'),mu{1}('needle_z'),mu{1}('needle_phi'),mu{1}('needle_theta'),mu{1}('needle_power'));
    fprintf(1,'Memory consumption for online solve: rss = %e Mb; vmem = %e Mb\n',rss-rss_init,vmem - vmem_init);
    fprintf(1,'Time required for online solve: %f minutes\n',time_online_solve/60.0);
    i_mu = i_mu + 1;
  end
end
