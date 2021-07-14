import numpy as np
import matplotlib.pyplot as plt

param_suffix_list = ["Min", "Ref", "Max"]
plot_color = ["b","r","k"]
mesh_num_tuple = range(5)
num_mesh_nodes = np.array([72099, 183268, 488105, 1328320, 3519770])
mesh_conv_metric = [[],[],[]]

for i_suff, suffix in enumerate(param_suffix_list):
  print("param = ",suffix)
  for mesh_num in mesh_num_tuple:
    mesh_conv_metric[i_suff].append(np.genfromtxt("./param"+suffix+"/mesh"+str(mesh_num)+"/mesh_conv_metric.txt"))
  mesh_conv_metric[i_suff] = np.array(mesh_conv_metric[i_suff])
  plt.plot(num_mesh_nodes,100*np.absolute(mesh_conv_metric[i_suff]-mesh_conv_metric[i_suff][-1])/mesh_conv_metric[i_suff][-1],color=plot_color[i_suff],label="param "+suffix,marker="x")
  print("mesh nodes = ", num_mesh_nodes, " relative error = ",100*np.absolute(mesh_conv_metric[i_suff]-mesh_conv_metric[i_suff][-1])/mesh_conv_metric[i_suff][-1])

#plt.ylim([1e2,1e3])
plt.xlabel("Number of Nodes",fontsize='x-large')
plt.ylabel(r"$\frac{1}{t_e}\int_0^{t_e}\frac{||T||_{L_2(\Omega_m)}}{|\Omega_m|} dt$ (relative error %)",fontsize=20)
plt.tick_params(labelsize='large')
plt.ticklabel_format(axis='x',style='scientific',scilimits=(0,0))
plt.legend()
plt.show()


