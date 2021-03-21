function [xyz, elem_nodes, subdomain_ids, num_nodes, num_elems, Permute_nodes] = read_libmesh_mesh_data(node_coords_file_base, node_connect_file_base)
    % Input Parameters
    % node_coords_file : file containing list of node coords
    % node_connect_file : file containing list of node comprising each element
    % Output Parameters
    % xyz : array containing x, y, and z coordinates of nodes xyz(3, num_nodes)
    % elem_nodes : array listing nodes constituting elements
    % elem_nodes(nodes_per_elem, num_elems) : Nodes per elem is currently 4
    % subdomain_ids : array containing subdomain ids of all elements (num_elems)
    err_msg = '';
    index = 0;
    num_nodes = 0;
    xyz = [];
    [fileID, err_msg] = fopen(strcat(node_coords_file_base,int2str(index),".txt"));
    while strcmp(err_msg,'') 
        xyz_temp = fscanf(fileID,"%f",[4,Inf]);   
        temp = size(xyz_temp(1,:));
        num_nodes = num_nodes + temp(2);
        xyz = [xyz xyz_temp];
        index = index + 1;
        [fileID, err_msg] = fopen(strcat(node_coords_file_base,int2str(index),".txt"));
    end
    [B,I] = sort(xyz,2);
    Permute_nodes = I(1,:);
    xyz = xyz(:,I(1,:)); % sort node coords according to node ids
    xyz = xyz(2:4,:);
    err_msg = '';
    index = 0;
    num_elems = 0;
    elem_nodes = [];
    [fileID, err_msg] = fopen(strcat(node_connect_file_base,int2str(index),".txt"));
    while strcmp(err_msg,'') 
        elem_nodes_temp = fscanf(fileID,"%f",[6,Inf]);
        temp = size(elem_nodes_temp(1,:));
        num_elems = num_elems + temp(2);
        elem_nodes = [elem_nodes elem_nodes_temp];
        index = index + 1;
        [fileID, err_msg] = fopen(strcat(node_connect_file_base,int2str(index),".txt"));
    end
    [B, I] = sort(elem_nodes,2);
    elem_nodes = elem_nodes(:,I(1,:));
    subdomain_ids = elem_nodes(6,:);
    elem_nodes = elem_nodes(2:5,:);
end