import matplotlib.pyplot as plt

def PlotRBError(N_array, Error, xlabel, ylabel, labelfontsize, tickfontsize)
  plt.semilogy(N_array, Error)
  plt.xlabel(xlabel, labelfontsize)
  plt.ylabel(ylabel, labelfontsize)
  plt.xticks(tickfontsize)
  plt.yticks(tickfontsize)
  plt.show()
