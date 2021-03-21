function [mesh_conv_node_ids, cyl_vol] = get_mesh_conv_node_ids(node_x)
%Returns ids of nodes to be considered in mesh convergence analysis
%The node ids contained within a cylinder around RF needle returned
%RF needle center at (-0.012,0,0)
%radius of cylinder : 1.5 cm
%length of cylinder : 4 cm
%Input:
%  node_x : array containing node coordinates; array index is node id
%Output:
%  mesh_conv_node_ids : array of node ids to be considered for mesh conv
needle_center = [-0.012; 0; 0];
cylinder_radius = 0.015;
cylinder_length = 0.04;
cylinder_axis = [-1; 0; 0];
node_num = max(size(node_x));
mesh_conv_node_ids = [];
%distance_to_center_array = node_x - needle_center;
%radial_distance_array = dot(
for i = 1:node_num
    distance_to_center = node_x(:,i)-needle_center;
    axial_distance_signed = dot(cylinder_axis,distance_to_center);
    radial_distance = norm(distance_to_center - axial_distance_signed.*cylinder_axis);
    axial_distance_abs = abs(axial_distance_signed);
    if (axial_distance_abs <= cylinder_length*0.5) && (radial_distance <= cylinder_radius)
        mesh_conv_node_ids = [mesh_conv_node_ids i];
    end
end
cyl_vol = pi*cylinder_radius^2*cylinder_length;
end

