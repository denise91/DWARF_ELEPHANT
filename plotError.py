#grep "Average error bound" Obtain_EIM_data_PDSPL_max_max_furthersplit_2.out | cut -c 23- > avg_error_EIM_max_max_furtherspl_2.txt
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import rc
import sys
#rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
## for Palatino and other serif fonts use:
#rc('font',**{'family':'serif','serif':['Palatino']})
#rc('text', usetex=True)

fig, ax = plt.subplots()
ax.xaxis.set_major_locator(plt.MultipleLocator(50.0))#furtherspl_7b and final
ax.xaxis.set_minor_locator(plt.MultipleLocator(25.0))


def PlotRBError(N_array, Error, xlabel, ylabel, labelfontsize, tickfontsize, param_str, linestyle_str):
  plt.semilogy(N_array, Error, color='k', linestyle=linestyle_str, label=param_str)
  plt.xlabel(xlabel, fontsize=labelfontsize)
  plt.ylabel(ylabel, fontsize=labelfontsize)
  plt.xticks(fontsize=tickfontsize)
  plt.yticks(fontsize=tickfontsize)
  plt.ylim([1e-16,20])

  #ax.semilogy(N_array, Error, label=param_str)
  #ax.set_xlabel(xlabel, fontsize=labelfontsize)
  #ax.set_ylabel(ylabel, fontsize=labelfontsize)
  #ax.set_xticks(fontsize=tickfontsize)
  #ax.set_yticks(fontsize=tickfontsize)
  #ax.set_ylim([1e-16,20])
  
  


  #plt.show()

suffix = sys.argv[1]
color_list = ["b","r","g"]
linestyle_list = ['--', ':', '-']
max_Error = np.genfromtxt('max_error_EIM_'+suffix+'.txt',comments="#",delimiter=",")
min_Error = np.genfromtxt('min_error_EIM_'+suffix+'.txt',comments="#",delimiter=",")
avg_Error = np.genfromtxt('avg_error_EIM_'+suffix+'.txt',comments="#",delimiter=",")
#Error_min_min = np.genfromtxt('EIM_fine_min_min_error_bounds.txt',comments="#",delimiter=",")
#Error_max_min = np.genfromtxt('EIM_fine_max_min_error_bounds.txt',comments="#",delimiter=",")
#Error_max_max = np.genfromtxt('EIM_fine_max_max_error_bounds.txt',comments="#",delimiter=",")
#Error_min_max = np.genfromtxt('EIM_fine_min_max_error_bounds.txt',comments="#",delimiter=",")
#print Error.shape
N_max = np.arange(1,max_Error.shape[0]+1)
N_min = np.arange(1,min_Error.shape[0]+1)
N_avg = np.arange(1,avg_Error.shape[0]+1)
#N_max_max = np.arange(1,Error_max_max.shape[0]+1)
#N_min_max = np.arange(1,Error_min_max.shape[0]+1)
#N_min_min = np.arange(1,Error_min_min.shape[0]+1)
#N_max_min = np.arange(1,Error_max_min.shape[0]+1)

PlotRBError(N_max,max_Error,r"$N_g$",r"$op_{\mu \in \Xi^g_{train}}\varepsilon^{rel}_{N_g}(\mu)$",24,16,r"op$\equiv$max",linestyle_list[0])#18,14#for furtherspl_7b and final
PlotRBError(N_min,min_Error,r"$N_g$",r"$op_{\mu \in \Xi^g_{train}}\varepsilon^{rel}_{N_g}(\mu)$",24,16,r"op$\equiv$min",linestyle_list[1])#24,16#for max_max/max_min/min_max/min_min
PlotRBError(N_avg,avg_Error,r"$N_g$",r"$op_{\mu \in \Xi^g_{train}}\varepsilon^{rel}_{N_g}(\mu)$",24,16,r"op$\equiv$avg",linestyle_list[2])
plt.tight_layout()
#PlotRBError(N_max_max,Error_max_max,"N","EIM error bound",18,14,"max_max")
#PlotRBError(N_min_max,Error_min_max,"N","EIM error bound",18,14,"min_max")
#PlotRBError(N_min_min,Error_min_min,"N","EIM error bound",18,14,"min_min")
#PlotRBError(N_max_min,Error_max_min,"N","EIM error bound",18,14,"max_min")
plt.legend(fontsize='18')
#plt.plot(N,Error[:,2])
#plt.xlabel("M", fontsize=18)
#plt.ylabel("$max_{\mu \in \Xi}|g(\cdot;\mu) - g^*_M(\cdot;\mu)|_{L_\infty}$", fontsize=18)
#plt.xticks(fontsize=14)
#plt.yticks(fontsize=14)
plt.grid(True)
plt.savefig('EIM_error_max_avg_min_'+suffix+'.png', dpi=600, format='png')
#plt.show()
