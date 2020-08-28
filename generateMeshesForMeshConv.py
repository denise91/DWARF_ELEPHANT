from subprocess import call
import os
import re

def replace_line(file_name, pattern, newtext):
    """
    Replace line <pattern> in file <file_name> with <text>
    """
    lines = open(file_name, 'r').readlines()
    for i in range(len(lines)):
      newline = re.sub(pattern,newtext,lines[i])
      lines[i] = newline

    out = open(file_name, 'w')
    out.writelines(lines)
    out.close()

GeoFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/ReducedBasisGeom3D_7_fullylabeled.geo"
r_pattern = re.compile('r = DefineNumber[ .* , Name "Parameters/r" ];')
l_pattern = re.compile('l = DefineNumber[ .* , Name "Parameters/l" ];')
d_pattern = re.compile('d = DefineNumber[ .* , Name "Parameters/d" ];')
h_pattern = re.compile('h = DefineNumber[ .* , Name "Parameters/h" ];')

bounding_box_mesh_size_pattern = re.compile('bounding_box_mesh_size = DefineNumber[ .* , Name "Parameters/bounding_box_mesh_size" ];')
cylinder_mesh_size_pattern = re.compile('cylinder_mesh_size = DefineNumber[ .* , Name "Parameters/cylinder_mesh_size" ];')
cube_mesh_size_pattern = re.compile('cube_meshsize = DefineNumber[ .* , Name "Parameters/cube_meshsize" ];')

r = 0.003
l = 0.04
d = 2*r*3.0/2.0
h = l*3.0/2.0

cylinder_mesh_size_0 = 4e-4
bounding_box_mesh_size_0 = 4e-4
cube_mesh_size_0 = 8.5e-3

number_of_meshes = 5
mesh_size_ratio = 2.0**(-0.5)
for mesh_num in range(number_of_meshes):
    replace_line(GeoFileName,r_pattern,'r = DefineNumber[ ' + str(r) + ' , Name "Parameters/r" ];')
    replace_line(GeoFileName,l_pattern,'l = DefineNumber[ ' + str(l) + ' , Name "Parameters/l" ];')
    replace_line(GeoFileName,d_pattern,'d = DefineNumber[ ' + str(d) + ' , Name "Parameters/d" ];')
    replace_line(GeoFileName,h_pattern,'h = DefineNumber[ ' + str(h) + ' , Name "Parameters/h" ];')
    replace_line(GeoFileName,cube_mesh_size_pattern,'cube_meshsize = DefineNumber[ ' + str(cube_mesh_size_0*mesh_size_ratio**mesh_num) + ' , Name "Parameters/cube_meshsize" ];')
    replace_line(GeoFileName,bounding_box_mesh_size_pattern,'bounding_box_mesh_size = DefineNumber[ ' + str(bounding_box_mesh_size_0*mesh_size_ratio**mesh_num) + ' , Name "Parameters/bounding_box_mesh_size" ];')
    replace_line(GeoFileName,cylinder_mesh_size_pattern,'cylinder_mesh_size = DefineNumber[ ' + str(cylinder_mesh_size_0*mesh_size_ratio**mesh_num) + ' , Name "Parameters/cylinder_mesh_size" ];')
    call("gmsh "+GeoFileName+" -3 -o RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh"+str(mesh_num)+".msh",shell=True)
