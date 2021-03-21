param_subd_list = ['"min_min"','"min_max"','"max_min"','"max_max"']
param_num_list = [1,2,3]
mesh_num_list = [2]
testing = "true"

str_pattern = """clear all

addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis');

      perform_FE_solve_PDSplit(%s,%d,%d,%s);
"""
for param_subd in param_subd_list:
  for p_num in param_num_list:
    for m_num in mesh_num_list:
      mesh_conv_str = str_pattern % (param_subd,p_num,m_num,testing)
      #with open("perform_mesh_conv_p%d_m%d.m" % (p_num,m_num),"w") as mesh_conv_file:
      with open("solve_FE_PDSplit_%s_p%d_m%d.m" % (param_subd[1:-1],p_num,m_num),"w") as mesh_conv_file:
        mesh_conv_file.write(mesh_conv_str)
