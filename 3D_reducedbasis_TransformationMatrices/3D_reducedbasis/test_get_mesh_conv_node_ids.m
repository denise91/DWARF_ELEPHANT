clear all

output_file_name = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/paramRef/mesh0_paramRef";

[ node_x, element_node ] = read_gmsh_file("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh1.msh",3,4);
%[ node_x, element_node ] = read_gmsh_file("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/RBGeom_Test.msh",3,4);
[mesh_conv_node_ids] = get_mesh_conv_node_ids(node_x);

node_num = length(node_x(1,:));
element_num = length(element_node(1,:));

cylinder_level_set = zeros(1,node_num);
cylinder_level_set(mesh_conv_node_ids) = 1;

output_unit = fopen(output_file_name+"_cyl_level_set.vtu","w");
%element_node should start node ids from 0 and not 1
write_vtu(output_unit, node_num, element_num, 4, node_x, element_node-1, cylinder_level_set,"cylinder_around_needle");