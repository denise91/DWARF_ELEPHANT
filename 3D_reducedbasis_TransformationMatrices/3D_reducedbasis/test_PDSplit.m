clear all
param_subd_arr = ["min_min","min_max","max_min","max_max"];
num_params = 3;
num_meshes = 5;
testing = false;


addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis');

for param_subd = param_subd_arr
   for param = 1:num_params
       perform_FE_solve_PDSplit(param_subd, param, 2, testing); %third function argument true for testcase and false for real case
   end
end
