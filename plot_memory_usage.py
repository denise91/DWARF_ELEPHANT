import numpy as np
import matplotlib.pyplot as plt

data_new = np.genfromtxt("Memory_usage_trace_ignore_zero_entries.csv",delimiter=",")
data_old = np.genfromtxt("Memory_usage_trace_save_zero_entries.csv",delimiter=",")
num_lines_new = 3
num_lines_old = 8
num_datasets_new = len(data_new)/num_lines_new
num_datasets_old = len(data_old)/num_lines_old

memory_req_v_mesh_size_old = []
memory_req_v_mesh_size_new = []

#averaged_data = np.zeros((8,2))
#std_dev_data = np.zeros((8,2))
#sample_point = np.zeros(8)

#for i in range(num_datasets*8):
#  averaged_data[i%8,:] += data[i,:]
#  sample_point[i%8] = i%8
#averaged_data = averaged_data/float(num_datasets)

#for i in range(num_datasets*8):
#  std_dev_data[i%8,:] += np.multiply(data[i,:] - averaged_data[i%8,:],data[i,:] - averaged_data[i%8,:])

#std_dev_data = std_dev_data/float(num_datasets)
#std_dev_data = np.sqrt(std_dev_data)

#print std_dev_data

for i in range(num_datasets_old):
  memory_req_v_mesh_size_old.append(data_old[i*num_lines_old+num_lines_old-1,0] - data_old[i*num_lines_old,0])
  memory_req_v_mesh_size_new.append(data_new[i*num_lines_new+num_lines_new-1,0] - data_new[i*num_lines_new,0])

  #plt.plot(data_old[i*num_lines_old:i*num_lines_old+num_lines_old,0]*1e-6,color="r",label="Virtual Memory (saving zeros)")
  #plt.plot(data_new[i*num_lines_new:i*num_lines_new+num_lines_new,0]*1e-6,color="b",label="Virtual Memory (ignoring zeros)")
memory_req_v_mesh_old = np.array(memory_req_v_mesh_size_old)
memory_req_v_mesh_new = np.array(memory_req_v_mesh_size_new)

plt.plot(memory_req_v_mesh_old*1e-6,color="r",label="Virtual Memory (saving zeros)")
plt.plot(memory_req_v_mesh_new*1e-6,color="b",label="Virtual Memory (ignoring zeros)")
plt.legend()
plt.savefig("memory_usage_comparison.png")
