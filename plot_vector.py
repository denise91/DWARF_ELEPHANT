import numpy as np
import matplotlib.pyplot as plt

rhs_serial = np.genfromtxt("rhs_serial_node_id.txt",delimiter=" ")

rhs_parallel_1 = np.genfromtxt("rhs_parallel_node_id_0.txt",delimiter=" ")
rhs_parallel_2 = np.genfromtxt("rhs_parallel_node_id_1.txt",delimiter=" ")
rhs_parallel_3 = np.genfromtxt("rhs_parallel_node_id_2.txt",delimiter=" ")
rhs_parallel_4 = np.genfromtxt("rhs_parallel_node_id_3.txt",delimiter=" ")

temp_array = np.append(rhs_parallel_1, rhs_parallel_2, axis=0)
temp_array_2 = np.append(temp_array, rhs_parallel_3,axis=0)
rhs_parallel = np.append(temp_array_2, rhs_parallel_4,axis=0)

plt.plot(rhs_serial[:,1],"r")
plt.plot(rhs_parallel[:,1],"b")
plt.show()
