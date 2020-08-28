# make sure needle center coordinates are correct

from subprocess import call
import re

file_in = "RBRFAModel3D_TransientMeshConv.i"
needle_center_x = -0.012 # single value
needle_center_y = 0 # single value
needle_center_z = 0.0 # single value
needle_axis_theta = 1.57 # single value
needle_axis_phi = 0.0 # single value
r_0_list =  [4e-4, 3e-3, 5e-3] # three levels
l_0_list =  [5e-3, 4e-2, 7e-2] # three levels

mesh_file_list = ["RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh0.msh", "RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh1.msh", "RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh2.msh","RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh3.msh", "RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh4.msh"]

time_step_ratio = 2**0.5
coarsest_time_step = 0.5*time_step_ratio
total_time = 540.0

mesh_pattern = re.compile(".*file.*")
needle_x_pattern = re.compile("  needle_center_x = .*")
needle_y_pattern = re.compile("  needle_center_y = .*")
needle_z_pattern = re.compile("  needle_center_z = .*")
needle_axis_theta_pattern = re.compile("  needle_axis_theta = .*")
needle_axis_phi_pattern = re.compile("  needle_axis_phi = .*")
r0_heatsource_pattern = re.compile("  r0 = .*")
l0_heatsource_pattern = re.compile("  l0 = .*")
param_min_values_pattern = re.compile("  parameter_min_values_RB =.*")
param_max_values_pattern = re.compile("  parameter_max_values_RB =.*")
mesh_index_pattern = re.compile("  mesh_index = .*")
online_mu_pattern = re.compile("  online_mu = .*")
mu_ref_pattern = re.compile("  mu_ref = .*")
time_step_pattern = re.compile("  delta_t_RB = .*")
n_time_steps_pattern = re.compile("  n_time_steps_RB = .*")


for mesh in mesh_file_list:
    for geom_param_index in range(len(r_0_list)):
          with open(file_in, 'r') as base_file:
            lines = base_file.readlines()

          for line_num in range(len(lines)):
            newline = re.sub(mesh_pattern,"  file = " + mesh,lines[line_num])
            lines[line_num] = newline

            newline = re.sub(needle_x_pattern,"  needle_center_x = " + str(needle_center_x),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(needle_y_pattern,"  needle_center_y = " + str(needle_center_y),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(needle_z_pattern,"  needle_center_z = " + str(needle_center_z),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(needle_axis_theta_pattern,"  needle_axis_theta = " + str(needle_axis_theta),lines[line_num])   
            lines[line_num] = newline

            newline = re.sub(needle_axis_phi_pattern,"  needle_axis_phi = " + str(needle_axis_phi),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(r0_heatsource_pattern,"  r0 = " + str(r_0_list[geom_param_index]),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(l0_heatsource_pattern,"  l0 = " + str(l_0_list[geom_param_index]),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(param_min_values_pattern,"""  parameter_min_values_RB = '""" + str(r_0_list[geom_param_index]) + " " + str(l_0_list[geom_param_index]) + " 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'""",lines[line_num])
            lines[line_num] = newline

            newline = re.sub(param_max_values_pattern,"""  parameter_max_values_RB = '""" + str(r_0_list[geom_param_index]) + " " + str(l_0_list[geom_param_index]) + " 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'""", lines[line_num])
            lines[line_num] = newline

            newline = re.sub(mesh_index_pattern,"  mesh_index = " + str(mesh_file_list.index(mesh)),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(online_mu_pattern,"""  online_mu = '""" + str(r_0_list[geom_param_index]) + " " + str(l_0_list[geom_param_index]) + " 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'""",lines[line_num])
            lines[line_num] = newline

            newline = re.sub(mu_ref_pattern,"""  mu_ref = '""" + str(r_0_list[geom_param_index]) + " " + str(l_0_list[geom_param_index]) + " 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'""",lines[line_num])
            lines[line_num] = newline

            newline = re.sub(time_step_pattern,"  delta_t_RB = " + str(coarsest_time_step/time_step_ratio**(mesh_file_list.index(mesh))),lines[line_num])
            lines[line_num] = newline

            newline = re.sub(n_time_steps_pattern,"  n_time_steps_RB = 2",lines[line_num])#"  n_time_steps_RB = " + str(int(total_time / (coarsest_time_step/time_step_ratio**(mesh_file_list.index(mesh))))),lines[line_num]) # EDITED FOR TESTING
            lines[line_num] = newline

          with open("RBRFA3DMeshConv_needle_theta"+str(needle_axis_theta)+"_phi"+str(needle_axis_phi)+"_r0"+str(r_0_list[geom_param_index])+"_l0"+str(l_0_list[geom_param_index])+"_mesh_"+str(mesh_file_list.index(mesh))+".i", 'w') as file_out:
            file_out.writelines(lines)
            file_out.close()
