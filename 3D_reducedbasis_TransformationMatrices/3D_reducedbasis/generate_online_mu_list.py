import numpy as np

r0_min = 0.00306
r0_max = 0.003074
l0_min = 0.02602
l0_max = 0.02615
nx_min = 3.06e-3
nx_max = 3.412e-3
nz_min = -1.406e-3
nz_max =  0.0
nphi_min = 0
nphi_max = 9.817e-2
ntheta_min = 0
ntheta_max = 4.659e-2

with open("online_mu_list.txt","w") as mu_file:
    mu_file.write("r_0 l_0 needle_x needle_y needle_z needle_theta needle_phi needle_power r l k_t k_b rho_C_t rho_C_b\n") 
    for i in range(1,11):
        mu_file.write(str(r0_min+np.random.rand()*(r0_max-r0_min))+" "+str(l0_min+np.random.rand()*(l0_max-l0_min))+" "+str(nx_min+np.random.rand()*(nx_max-nx_min))+" "+str(0.0)+" "+str(nz_min+np.random.rand()*(nz_max-nz_min))+" "+str(ntheta_min+np.random.rand()*(ntheta_max-ntheta_min))+" "+str(nphi_min+np.random.rand()*(nphi_max-nphi_min))+" 1.0 0.00306 0.02602 0.83 0.52 3.82e6 3.798e6\n")

