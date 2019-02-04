from subprocess import call
import os

def replace_line(file_name, line_num, text):
    lines = open(file_name, 'r').readlines()
    lines[line_num - 1] = text + '\n'
    out = open(file_name, 'w')
    out.writelines(lines)
    out.close()

#-----------------------User Defined Variables-------------------------------#
InputFileName = "GeometricalParameters_RBNICS.i"
OnlineN_LineNumber = 282
#---------------------------End User Defined Variables---------------------#


for N in range(1,21):
 replace_line(InputFileName,OnlineN_LineNumber,"  online_N = " + str(N)) # input modification command here
 print "N = ", N
 call("./DwarfElephant-opt -i " + InputFileName, shell=True) # simulation running command here
 os.rename("./out_0.vtu", "./out_N{0:02d}.vtu".format(N))
