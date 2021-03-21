clear all

num_params = 3;
num_meshes = 5;


addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis');

%for param_num = 1:num_params
    %for mesh_num = 3:num_meshes-1
      perform_FE_solve(3,1, false ); %third function argument true for testcase and false for real case
      %test_mesh_deform(3,0,false);
    %end
%end
