
needle_center_x = -0.01
needle_center_y = -0.01
needle_center_z = 0
needle_axis_theta = 0
needle_axis_phi = 0

for i in range(32):
  print """[./HeatSource""" + str(i+1) + """]
  type = DwarfElephantRBRFHeatsourceKernel
  ID_Fq = """ + str(i+1) + """
  block = """ + str(i+1) + """
  simulation_type = transient
  needle_center_x = """ + str(needle_center_x) + """
  needle_center_y = """ + str(needle_center_y) + """
  needle_center_z = """ + str(needle_center_z) + """
  needle_axis_phi = """ + str(needle_axis_phi) + """
  needle_axis_theta = """ + str(needle_axis_theta) + """
  r0 = 0.004 
  l0 = 0.06
  r = 0.003
  l = 0.04
[../]
"""
