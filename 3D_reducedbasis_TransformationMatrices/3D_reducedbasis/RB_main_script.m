addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/theta_functions');% location of .m files
format long
[RB_Con,RB_Eval,EIM_data] = set_input_params();


if (RB_Eval.offline_stage)
  [RB_Con, RB_Eval, Mesh_data, EIM_data] = load_FE_data(RB_Con, RB_Eval, EIM_data);
  [RB_Con, RB_Eval] = perform_RB_offline_stage(RB_Con,RB_Eval,EIM_data,Mesh_data);
%   save("RB_data.mat",'RB_Eval','-v7.3');
%   save("Mesh_data.mat",'Mesh_data','-v7.3');
end
%Resume debugging here
if (RB_Eval.online_stage)
 time_main_script_begin = tic;
 time_read_basis_begin = tic;
 load("Mesh_data.mat");
 load("RB_data.mat");
 time_read_basis = toc(time_read_basis_begin);
 fprintf(1,'Time to read basis data = %f minutes\n',time_read_basis/60.0);
 EIM_data = load_EIM_data(EIM_data);
 online_mu_cell_arr = get_online_mu_list('online_mu_list.txt');
 compute_thermal_lesion(online_mu_cell_arr,RB_Eval,EIM_data,Mesh_data);
 time_main_script = toc(time_main_script_begin);
 fprintf(1,'Time for RB main script = %f minutes\n',time_main_script/60.0);
end
