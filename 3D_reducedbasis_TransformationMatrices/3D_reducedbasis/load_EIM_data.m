function [EIM_data] = load_EIM_data(EIM_data)
  file_path = EIM_data.EIM_data_path;
  B_matrix_filename = file_path + "EIM_interpolation_matrix.txt";
  EIM_data.B_matrix = readmatrix(B_matrix_filename);
  mat_size = size(EIM_data.B_matrix);
  EIM_data.B_matrix = EIM_data.B_matrix(:,1:min(mat_size));
  int_points_filename = file_path + "EIM_interpolation_points.txt";
  EIM_data.interpolation_points = readmatrix(int_points_filename); % interpolation_points size: (num_points,3)
  interp_points_size = size(EIM_data.interpolation_points);
  int_points_subd_filename = file_path + "EIM_interpolation_points_subdomain.txt";
  EIM_data.interpolation_points_subdomains = readmatrix(int_points_subd_filename);
  EIM_data.M = interp_points_size(1);% max(size(EIM_data.B_matrix));
  EIM_data.B_matrix = EIM_data.B_matrix(1:EIM_data.M,1:EIM_data.M);
  EIM_data.num_subdomains = max(readmatrix(strcat(file_path,"EIM_num_subdomains.txt")));%length(unique(EIM_data.interpolation_points_subdomains));
end
