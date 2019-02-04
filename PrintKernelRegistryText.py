kernel_name = "DwarfElephantRBDiffusion"
suffix_list = ["YX","ZX","ZY"]

for suffix in suffix_list:
  print '#include "'+kernel_name+suffix+'.h"'

for suffix in suffix_list:
  print 'registerKernel('+kernel_name+suffix+');'

