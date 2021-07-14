#grep "Average error bound" Obtain_EIM_data_PDSPL_max_max_furthersplit_2.out | cut -c 23- > avg_error_EIM_max_max_furtherspl_2.txt
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import rc
import sys
#rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
## for Palatino and other serif fonts use:
#rc('font',**{'family':'serif','serif':['Palatino']})
#rc('text', usetex=True)
def PlotRBError(N_array, Error, xlabel, ylabel, labelfontsize, tickfontsize, param_str):
  plt.semilogy(N_array, Error, color='k', label=param_str)
  plt.xlabel(xlabel, fontsize=labelfontsize)
  plt.ylabel(ylabel, fontsize=labelfontsize)
  plt.xticks(fontsize=tickfontsize)
  plt.yticks(fontsize=tickfontsize)
  plt.ylim([1e-4,20])

  #plt.show()

#suffix = sys.argv[1]
color_list = ["k","k","k"]
Error = np.genfromtxt('RB_greedy_error_v_N.csv',comments="#",delimiter=",")
N = np.arange(1,Error.shape[0]+1)
PlotRBError(N,Error,"N",r"$max_{\mu\in\Xi_{train}}\Delta^K_N(\mu)$",18,14,"")
plt.tight_layout()
#plt.legend(fontsize='18')
#plt.plot(N,Error[:,2])
#plt.xlabel("M", fontsize=18)
#plt.ylabel("$max_{\mu \in \Xi}|g(\cdot;\mu) - g^*_M(\cdot;\mu)|_{L_\infty}$", fontsize=18)
#plt.xticks(fontsize=14)
#plt.yticks(fontsize=14)
plt.grid(True)
plt.savefig('RB_error_bound.png', dpi=600, format='png')
#plt.show()
