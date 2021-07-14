import numpy as np
from sys import argv

if (len(argv) != 2):
    print("Error! 1 command line argument required!")
    exit()
else:
    online_mu_num = int(argv[1])

#read online_param_list.txt
#choose a single parameter value
with open('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/online_mu_list.txt','r') as online_mu_file:
    online_mu_file_lines = online_mu_file.readlines()

online_mu_line = online_mu_file_lines[online_mu_num]
online_mu_line = online_mu_line.split()

#read Obtain_EIM_data_final.out
#iterate over each greedy iteration text block
#    determine relative errors between online mu components and truth solve param components
#    Key:
#    online_mu                   greedy_mu               definition
#    1                           mu_0                    r0
#    2                           mu_1                    l0
#    3                           mu_2                    needle_x
#    4                           mu_3                    needle_y
#    5                           mu_4                    needle_z
#    6                           mu_5                    needle_theta
#    7                           mu_6                    needle_phi
#    print relative errors
with open('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/Obtain_EIM_data_final.out','r') as EIM_greedy_file:
    EIM_greedy_lines = EIM_greedy_file.readlines()

min_rel_error_overall = 1e10
M_min_error_overall = 0
M = -1
for i, line in enumerate(EIM_greedy_lines):
    max_rel_error_M = 0
    if (line.find('Performing truth solve at parameter:') != -1):
        M = M + 1
        r0_greedy = EIM_greedy_lines[i+1].split()
        r0_greedy = float(r0_greedy[1])
        r0_rel_error = np.abs(float(online_mu_line[0]) - r0_greedy)/r0_greedy
        max_rel_error_M = np.maximum(max_rel_error_M,r0_rel_error)
        print("r0_rel_error = ",r0_rel_error)

        l0_greedy = EIM_greedy_lines[i+2].split()
        l0_greedy = float(l0_greedy[1])
        l0_rel_error = np.abs(float(online_mu_line[1]) - l0_greedy)/l0_greedy
        max_rel_error_M = np.maximum(max_rel_error_M,l0_rel_error)
        print("l0_rel_error = ",l0_rel_error)

        needle_x_greedy = EIM_greedy_lines[i+6].split()
        needle_x_greedy = float(needle_x_greedy[1])
        needle_x_rel_error = np.abs(float(online_mu_line[2]) - needle_x_greedy)/needle_x_greedy
        max_rel_error_M = np.maximum(max_rel_error_M,needle_x_rel_error)
        print("needle_x_rel_error = ",needle_x_rel_error)

        needle_z_greedy = EIM_greedy_lines[i+8].split()
        needle_z_greedy = float(needle_z_greedy[1])
        needle_z_rel_error = np.abs(float(online_mu_line[4]) - needle_z_greedy)/np.abs(needle_z_greedy)
        max_rel_error_M = np.maximum(max_rel_error_M,needle_z_rel_error)
        print("needle_z_rel_error = ",needle_z_rel_error)
        
        needle_theta_greedy = EIM_greedy_lines[i+9].split()
        needle_theta_greedy = float(needle_theta_greedy[1])
        needle_theta_rel_error = np.abs(float(online_mu_line[5]) - needle_theta_greedy)/needle_theta_greedy
        max_rel_error_M = np.maximum(max_rel_error_M,needle_theta_rel_error)
        print("needle_theta_rel_error = ",needle_theta_rel_error)

        needle_phi_greedy = EIM_greedy_lines[i+10].split()
        needle_phi_greedy = float(needle_phi_greedy[1])
        needle_phi_rel_error = np.abs(float(online_mu_line[6]) - needle_phi_greedy)/needle_phi_greedy
        max_rel_error_M = np.maximum(max_rel_error_M,needle_phi_rel_error)
        print("needle_phi_rel_error = ", needle_phi_rel_error)
        
        min_rel_error_overall = np.minimum(max_rel_error_M,min_rel_error_overall)
        if (min_rel_error_overall == max_rel_error_M):
            M_min_error_overall = M
        print("M = ",M)
        print("max_rel_error_M = ",max_rel_error_M)
        print()
        #break

print("min_error_overall = ", min_rel_error_overall)
print("M_min_error_overall = ", M_min_error_overall)


