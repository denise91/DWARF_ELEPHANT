with open("get_EIM_data_PDSPL_base.sh","r") as base_script_file:
    base_script_text = base_script_file.readlines()

with open("Obtain_EIM_data_PDSPL_base.i","r") as base_input_file:
    base_input_text = base_input_file.readlines()
mesh_file_name = "RBGeom_r{r_ref:.3e}mm_l{l_ref:.3e}mm_d_8by3r_h_4by3l_mesh2_RBPDSPL.msh"
script_file_name = "get_EIM_data_PDSPL_{param_str}.sh"

param_str_arr = ["max_max", "min_max", "max_min", "min_min"]
r_arr = [4e-4, 7.521e-4, 1.414e-3, 2.659e-3, 5e-3]
l_arr = [5e-3, 9.672e-3, 1.871e-2, 3.619e-2, 7e-2]
r_ref_arr = [r_arr[3],r_arr[1],r_arr[3],r_arr[1]]
l_ref_arr = [l_arr[3],l_arr[3],l_arr[1],l_arr[1]]

r_0_max_arr = [r_arr[4],r_arr[2],r_arr[4],r_arr[2]]
l_0_max_arr = [l_arr[4],l_arr[4],l_arr[2],l_arr[2]]
r_0_min_arr = [r_arr[2],r_arr[0],r_arr[2],r_arr[0]]
l_0_min_arr = [l_arr[2],l_arr[2],l_arr[0],l_arr[0]]

N_max_EIM=200
n_training_samples_EIM=1000
rel_train_tol_EIM=1e-2
# check limits
n_x_min_arr = [0.0, 0.0, 0.0, 0.0]
n_y_min_arr = [0.0, 0.0, 0.0, 0.0]
n_z_min_arr = [-0.045, -0.045, -l_0_max_arr[2]*0.5 + 1.75e-2, -l_0_max_arr[2]*0.5 +1.75e-2]
# check limits
n_x_max_arr = [r_0_max_arr[0]+1.75e-2, r_0_max_arr[1]+1.75e-2, r_0_max_arr[2]+1.75e-2, r_0_max_arr[3]+1.75e-2]
n_y_max_arr = [0.0, 0.0, 0.0, 0.0]
n_z_max_arr = [0.045, 0.045, l_0_max_arr[2]*0.5 + 1.75e-2, l_0_max_arr[3]*0.5 +1.75e-2]
# check limits
n_power_min_arr = [0.1, 0.1, 0.1, 0.1]
n_power_max_arr = [2.0, 2.0, 2.0, 2.0]

n_theta_min_arr = [0.0, 0.0, 0.0, 0.0]
n_theta_max_arr = [3.14159, 3.14159, 3.14159, 3.14159]

n_phi_min_arr = [0.0, 0.0, 0.0, 0.0]
n_phi_max_arr = [6.28319, 6.28319, 6.28319, 6.28319]
input_file_name = "Obtain_EIM_data_PDSPL_{param_str}.i"
for i, param_str in enumerate(param_str_arr):
    print("param_str = ",param_str)
    r_ref = r_ref_arr[i]
    l_ref = l_ref_arr[i]
    print("r_ref = ", r_ref)
    print("l_ref = ", l_ref)

    r_0_min = r_0_min_arr[i]
    l_0_min = l_0_min_arr[i]

    r_0_max = r_0_max_arr[i]
    l_0_max = l_0_max_arr[i]
    
    n_x_min = n_x_min_arr[i]
    n_y_min = n_y_min_arr[i]
    n_z_min = n_z_min_arr[i]

    n_x_max = n_x_max_arr[i]
    n_y_max = n_y_max_arr[i]
    n_z_max = n_z_max_arr[i]

    n_theta_min = n_theta_min_arr[i]
    n_theta_max = n_theta_max_arr[i]
    
    n_phi_min = n_phi_min_arr[i]
    n_phi_max = n_phi_max_arr[i]

    n_power_min = n_power_min_arr[i]
    n_power_max = n_power_max_arr[i]

    new_input_file_lines = []
    for line in base_input_text:
        new_input_file_lines.append(line.format(\
                mesh_file_name = mesh_file_name.format(r_ref=r_ref,l_ref=l_ref),\
                r_ref=r_ref,\
                l_ref=l_ref,\
                r_0_min=r_0_min,\
                r_0_max=r_0_max,\
                l_0_min=l_0_min,\
                l_0_max=l_0_max,\
                n_x_min=n_x_min,\
                n_y_min=n_y_min,\
                n_z_min=n_z_min,\
                n_x_max=n_x_max,\
                n_y_max=n_y_max,\
                n_z_max=n_z_max,\
                n_theta_min=n_theta_min,\
                n_theta_max=n_theta_max,\
                n_phi_min=n_phi_min,\
                n_phi_max=n_phi_max,\
                n_power_min=n_power_min,\
                n_power_max=n_power_max,\
                param_str=param_str,\
                N_max_EIM=N_max_EIM,\
                n_training_samples_EIM=n_training_samples_EIM,\
                rel_train_tol_EIM=rel_train_tol_EIM))
        
        new_script_file_lines = []
        for line in base_script_text:
            new_script_file_lines.append(line.format(param_str=param_str))
    
    with open(input_file_name.format(param_str=param_str),"w") as new_input_file:
        new_input_file.writelines(new_input_file_lines)
    with open(script_file_name.format(param_str=param_str),"w") as new_script_file:
        new_script_file.writelines(new_script_file_lines)
