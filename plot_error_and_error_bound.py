# Call this script from the folder containing the text files which have the error and error bound data
import os
import numpy as np
import matplotlib.pyplot as plt



directory = os.listdir('.')
os.chdir('.')
pattern = "mu_"


number_of_param_values = 20
subplot_rows = 2
subplot_cols = 2
lines_per_plot = (number_of_param_values/(subplot_rows*subplot_cols))
plot_markers = ["X","s","D","1","o"]
plot_linestyles = ["-","--","-.",":","-"]
fig, ax = plt.subplots(2,2)
line_num = 0


for filename in directory:
	if pattern in filename:
		temp_list = filename.split(".txt")
		data = np.genfromtxt(filename,delimiter=",")
		N_array = data[:,0]
		error_array = data[:,1]
		error_bound_array = data[:,2]
		subplot_num = int(line_num/lines_per_plot)
		subplot_x = int(subplot_num/subplot_cols)
		subplot_y = subplot_num%subplot_cols
		curr_ax = ax[subplot_x][subplot_y]
		
		curr_ax.semilogy(N_array,error_bound_array,color="r",marker=plot_markers[int(line_num%lines_per_plot)],ls=plot_linestyles[int(line_num%lines_per_plot)])
		curr_ax.semilogy(N_array,error_array,color="k",marker=plot_markers[int(line_num%lines_per_plot)],ls=plot_linestyles[int(line_num%lines_per_plot)])
		if (int(line_num%lines_per_plot) == 0):
			curr_ax.set_xlabel("Reduced Basis Dimension N")
			#curr_ax.legend()
		line_num = line_num + 1
plt.show()
