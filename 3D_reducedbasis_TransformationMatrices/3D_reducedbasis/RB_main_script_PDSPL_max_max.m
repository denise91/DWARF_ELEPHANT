addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/theta_functions');% location of .m files
format long
[RB_Con,RB_Eval,EIM_data] = set_input_params_PDSPL_max_max(); % to be modified for PDSPL: done


if (RB_Eval.offline_stage)
  [RB_Con, RB_Eval, Mesh_data, EIM_data] = load_FE_data_PDSPL_max_max(RB_Con, RB_Eval, EIM_data); % to be modified for PDSPL: done
  [RB_Con, RB_Eval] = perform_RB_offline_stage(RB_Con,RB_Eval,EIM_data,Mesh_data); % no modification for PDSPL
  save("RB_data_PDSPL_max_max.mat",'RB_Eval'); % to be modified for PDSPL: done
  save("Mesh_data_PDSPL_max_max.mat",'Mesh_data'); % to be modified for PDSPL: done
end
if (RB_Eval.online_stage)
 load("Mesh_data_PDSPL_max_max.mat"); % to be modified for PDSPL: done
 load("RB_data_PDSPL_max_max.mat"); % to be modified for PDSPL: done
 EIM_data = load_EIM_data_PDSPL_max_max(EIM_data); % to be modified for PDSPL: done
 online_mu_cell_arr = get_online_mu_list('online_mu_list.txt'); % change online mu list file name: done
 compute_thermal_lesion(online_mu_cell_arr,RB_Eval,EIM_data,Mesh_data); % needs to be modified to choose the appropriate model for parameter values in question
end
