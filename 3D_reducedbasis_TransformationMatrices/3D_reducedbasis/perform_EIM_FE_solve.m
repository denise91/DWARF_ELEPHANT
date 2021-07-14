addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/theta_functions');% location of .m files
format long
[RB_Con,RB_Eval,EIM_data] = set_input_params();
[RB_Con, RB_Eval, mesh_data, EIM_data] = load_FE_data(RB_Con, RB_Eval, EIM_data);
RB_Con.g_FE = ones(RB_Con.n_time_steps,1);% Forcing input for the full FE solutions (RB basis vectors)(impulse input)
RB_Eval.g_FE = RB_Con.g_FE;
K = RB_Con.n_time_steps;

online_mu_cell_arr = get_online_mu_list('online_mu_list.txt');
i_mu = 0;
for mu_cell = online_mu_cell_arr
  i_mu = i_mu + 1;
  fprintf(1,'Performing FE_EIM solve for param %d\n',i_mu);
  mu = mu_cell{1};
  [RB_Eval] = compute_EIM_theta_objects(mu,RB_Eval,EIM_data);
  [u_fem, ~] = solve_FEM_timedep(mu, RB_Con, RB_Eval);
  [tissue_damage,~] = compute_Arrhenius_tissue_damage(u_fem,RB_Con.dt,3.1e98,6.28e5,8.314);     
  [mesh_node_coords_new,tissue_damage] = deform_mesh_RB(mesh_data.node_x, mesh_data.subdomain_ids, mesh_data.element_node, mu,tissue_damage);% temporary code
  output_unit = fopen(strcat("temperature_EIM_FE_"+num2str(i_mu)+".vtu"),'w');
  write_vtu(output_unit, mesh_data.node_num, mesh_data.element_num, max(size(mesh_data.element_node(:,1))), mesh_node_coords_new, mesh_data.element_node, mesh_data.subdomain_ids, u_fem(:,K), "Temperature");
  fclose(output_unit);
  output_unit = fopen(strcat("thermal_lesion_EIM_FE_"+num2str(i_mu)+".vtu"),'w');
  write_vtu(output_unit, mesh_data.node_num, mesh_data.element_num, max(size(mesh_data.element_node(:,1))), mesh_node_coords_new, mesh_data.element_node, mesh_data.subdomain_ids, tissue_damage, "ThermalDamage");
  fclose(output_unit);
end
