from subprocess import call
import os

def replace_line(file_name, line_num, text):
    lines = open(file_name, 'r').readlines()
    tempString = lines[line_num - 1].strip()
    if tempString[0:8] != "online_N":
      print " Re check like number in input file"
      quit()

    lines[line_num - 1] = text + '\n'
    out = open(file_name, 'w')
    out.writelines(lines)
    out.close()

#-----------------------User Defined Variables-------------------------------#
InputFileName = "RBRFAModel3D_Transient.i"
OnlineN_LineNumber = 2300
#---------------------------End User Defined Variables---------------------#


for N in range(1,10):
 replace_line(InputFileName,OnlineN_LineNumber,"  online_N = " + str(N)) # input modification command here
 print "N = ", N
 call("./DwarfElephant-opt -i " + InputFileName, shell=True) # simulation running command here
 for timestep in range(0,11):
  #print "./RBRFAModel3D_Transient_out_0{0:02d}_0.vtu".format(timestep), "./RBRFAModel3D_Transient_out_0{0:02d}_0_{1:1d}.vtu".format(timestep,N)
  #print "./RBRFAModel3D_Transient_out_0{0:02d}.vtk".format(timestep), "./RBRFAModel3D_Transient_out_0{0:02d}_{1:1d}.vtk".format(timestep,N)
  os.rename("./RBRFAModel3D_Transient_out_0{0:02d}_0.vtu".format(timestep), "./RBRFAModel3D_Transient_out_0{0:02d}_0_N{1:1d}.vtu".format(timestep,N))
  os.rename("./RBRFAModel3D_Transient_out_0{0:02d}.vtk".format(timestep), "./RBRFAModel3D_Transient_out_0{0:02d}_N{1:1d}.vtk".format(timestep,N))
  #os.rename("./out_0.vtu", "./out_N{0:02d}.vtu".format(N))
