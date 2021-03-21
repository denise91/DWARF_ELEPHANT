addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/theta_functions');% location of .m files
format long
[RB_Con,RB_Eval,EIM_data] = set_input_params();


if (RB_Eval.offline_stage)
  [RB_Con, RB_Eval, Mesh_data, EIM_data] = load_FE_data(RB_Con, RB_Eval, EIM_data);
  [RB_Con, RB_Eval] = perform_RB_offline_stage(RB_Con,RB_Eval,EIM_data,Mesh_data);
  save("RB_data.mat",'RB_Eval');
  save("Mesh_data.mat",'Mesh_data');
end
%Resume debugging here
if (RB_Eval.online_stage)
 load("Mesh_data.mat");
 load("RB_data.mat");
 EIM_data = load_EIM_data(EIM_data);
 online_mu_cell_arr = get_online_mu_list('online_mu_list.txt');%to be defined;
 compute_thermal_lesion(online_mu_cell_arr,RB_Eval,EIM_data,Mesh_data);
end
