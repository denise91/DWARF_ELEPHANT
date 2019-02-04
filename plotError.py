import matplotlib.pyplot as plt
import numpy as np

def PlotRBError(N_array, Error, xlabel, ylabel, labelfontsize, tickfontsize):
  plt.semilogy(N_array, Error)
  plt.xlabel(xlabel, fontsize=labelfontsize)
  plt.ylabel(ylabel, fontsize=labelfontsize)
  plt.xticks(fontsize=tickfontsize)
  plt.yticks(fontsize=tickfontsize)
  plt.show()

Error = np.genfromtxt('ModifiedPennesGreedyErrorBounds.csv',comments="#",delimiter=",")
#print Error.shape
N = np.arange(1,Error.shape[0]+1)

PlotRBError(N,Error[:,1],"N","$max_{\mu \in \Xi}\Delta^N(\mu)$",18,14)
#plt.plot(N,Error[:,2])
#plt.xlabel("M", fontsize=18)
#plt.ylabel("$max_{\mu \in \Xi}|g(\cdot;\mu) - g^*_M(\cdot;\mu)|_{L_\infty}$", fontsize=18)
#plt.xticks(fontsize=14)
#plt.yticks(fontsize=14)
#plt.show()
