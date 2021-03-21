param_num_list = [1,2,3]
mesh_num_list = [2]

str_pattern = """clear all

addpath('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis');

      perform_FE_solve(%d,%d, true );
"""

for p_num in param_num_list:
  for m_num in mesh_num_list:
    mesh_conv_str = str_pattern % (p_num,m_num)
    #with open("perform_mesh_conv_p%d_m%d.m" % (p_num,m_num),"w") as mesh_conv_file:
    with open("solve_FE_p%d_m%d.m" % (p_num,m_num),"w") as mesh_conv_file:
      mesh_conv_file.write(mesh_conv_str)
