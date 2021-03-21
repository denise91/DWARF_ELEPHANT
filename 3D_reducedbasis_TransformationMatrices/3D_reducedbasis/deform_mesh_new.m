function [mesh_node_coords_new] = deform_mesh_new(mesh_node_coords_old, subdomain_ids, element_node, r_new, l_new)
% returns deformed mesh node coordinates
% Input:
% mesh_node_coords_old: old mesh node coordinates (3,num_nodes)
% subdomain_ids: array containing subdomains ids for the elements (num_elements)
% element_node: array containing nodes which are part of each element (nodes_per_elem,num_elems)


%load('allTransformationMatrices.mat');
num_nodes = length(mesh_node_coords_old(1,:));
num_elems = length(element_node(1,:));

mesh_node_coords_new = zeros(3,num_nodes);

trafo_mat_cell = cell(32,1);
trafo_vec_cell = cell(32,1);

L = 0.1;
r = 3e-3;
l = 4e-2;
r_0 = r_new;
l_0 = l_new;
d = (8.0/3.0)*r;
h = (4.0/3.0)*l;

%if (subdomain_id==1)
    trafo_mat_cell{1} = [1 0 -(d*(r - r_0))/(r*(L - h)); 0 1 (d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{1} = [(L*d*(r - r_0))/(2*r*(L - h)); -(L*d*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==2)
    trafo_mat_cell{2} = [1 0 (d*(r - r_0))/(r*(L - h)); 0 1 -(d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{2} = [-(L*d*(r - r_0))/(2*r*(L - h)); (L*d*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==3)
    trafo_mat_cell{3} = [r_0/r 0 (L*(r - r_0))/(r*(L - h)); 0 r_0/r (L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{3} = [-(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==4)
    trafo_mat_cell{4} = [r_0/r 0 -(L*(r - r_0))/(r*(L - h)); 0 r_0/r -(L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{4} = [(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==5)
    trafo_mat_cell{5} = [(r + r_0)/(2*r) (r - r_0)/(2*r) 0; (r - r_0)/(2*r) (r + r_0)/(2*r) 0; 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{5} = [0; 0; -(L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==6)
    trafo_mat_cell{6} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(d*(r - r_0))/(r*(L - d)) 1 0; -(h*(l - l_0))/(l*(L - d)) 0 1];
    trafo_vec_cell{6} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==7)
    trafo_mat_cell{7} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (d*(r - r_0))/(r*(L - d)) 1 0; (h*(l - l_0))/(l*(L - d)) 0 1];
    trafo_vec_cell{7} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==8)
    trafo_mat_cell{8} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (L*(r - r_0))/(r*(L - d)) r_0/r 0; -(L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    trafo_vec_cell{8} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==9)
    trafo_mat_cell{9} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(L*(r - r_0))/(r*(L - d)) r_0/r 0; (L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    trafo_vec_cell{9} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==10)
    trafo_mat_cell{10} = [(L*r - d*r_0)/(r*(L - d)) 0 0; 0 (d*r_0 + h*r)/(r*(d + h)) -(d*(r - r_0))/(r*(d + h)); 0 -(h*(l - l_0))/(l*(d + h)) (d*l + h*l_0)/(l*(d + h))];
    trafo_vec_cell{10} = [(L*d*(r - r_0))/(2*r*(L - d)); 0; 0];
%end 

%if (subdomain_id==11)
    trafo_mat_cell{11} = [1 -(d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (h*(l - l_0))/(l*(L - d)) 1];
    trafo_vec_cell{11} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==12)
    trafo_mat_cell{12} = [1 (d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(h*(l - l_0))/(l*(L - d)) 1];
    trafo_vec_cell{12} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==13)
    trafo_mat_cell{13} = [r_0/r (L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (L*(l - l_0))/(l*(L - d)) l_0/l];
    trafo_vec_cell{13} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==14)
    trafo_mat_cell{14} = [r_0/r -(L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(L*(l - l_0))/(l*(L - d)) l_0/l];
    trafo_vec_cell{14} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==15)
    trafo_mat_cell{15} = [(d*r_0 + h*r)/(r*(d + h)) 0 (d*(r - r_0))/(r*(d + h)); 0 (L*r - d*r_0)/(r*(L - d)) 0; (h*(l - l_0))/(l*(d + h)) 0 (d*l + h*l_0)/(l*(d + h))];
    trafo_vec_cell{15} = [0; -(L*d*(r - r_0))/(2*r*(L - d)); 0];
%end 

%if (subdomain_id==16)
    trafo_mat_cell{16} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(d*(r - r_0))/(r*(L - d)) 1 0; (h*(l - l_0))/(l*(L - d)) 0 1];
    trafo_vec_cell{16} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==17)
    trafo_mat_cell{17} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (d*(r - r_0))/(r*(L - d)) 1 0; -(h*(l - l_0))/(l*(L - d)) 0 1];
    trafo_vec_cell{17} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==18)
    trafo_mat_cell{18} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (L*(r - r_0))/(r*(L - d)) r_0/r 0; (L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    trafo_vec_cell{18} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==19)
    trafo_mat_cell{19} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(L*(r - r_0))/(r*(L - d)) r_0/r 0; -(L*(l - l_0))/(l*(L - d)) 0 l_0/l];
    trafo_vec_cell{19} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==20)
    trafo_mat_cell{20} = [(L*r - d*r_0)/(r*(L - d)) 0 0; 0 (d*r_0 + h*r)/(r*(d + h)) (d*(r - r_0))/(r*(d + h)); 0 (h*(l - l_0))/(l*(d + h)) (d*l + h*l_0)/(l*(d + h))];
    trafo_vec_cell{20} = [-(L*d*(r - r_0))/(2*r*(L - d)); 0; 0];
%end 

%if (subdomain_id==21)
    trafo_mat_cell{21} = [1 -(d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(h*(l - l_0))/(l*(L - d)) 1];
    trafo_vec_cell{21} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==22)
    trafo_mat_cell{22} = [1 (d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (h*(l - l_0))/(l*(L - d)) 1];
    trafo_vec_cell{22} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==23)
    trafo_mat_cell{23} = [r_0/r -(L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (L*(l - l_0))/(l*(L - d)) l_0/l];
    trafo_vec_cell{23} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==24)
    trafo_mat_cell{24} = [r_0/r (L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(L*(l - l_0))/(l*(L - d)) l_0/l];
    trafo_vec_cell{24} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
%end 

%if (subdomain_id==25)
    trafo_mat_cell{25} = [(d*r_0 + h*r)/(r*(d + h)) 0 -(d*(r - r_0))/(r*(d + h)); 0 (L*r - d*r_0)/(r*(L - d)) 0; -(h*(l - l_0))/(l*(d + h)) 0 (d*l + h*l_0)/(l*(d + h))];
    trafo_vec_cell{25} = [0; (L*d*(r - r_0))/(2*r*(L - d)); 0];
%end 

%if (subdomain_id==26)
    trafo_mat_cell{26} = [1 0 (d*(r - r_0))/(r*(L - h)); 0 1 (d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{26} = [(L*d*(r - r_0))/(2*r*(L - h)); (L*d*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==27)
    trafo_mat_cell{27} = [1 0 -(d*(r - r_0))/(r*(L - h)); 0 1 -(d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{27} = [-(L*d*(r - r_0))/(2*r*(L - h)); -(L*d*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==28)
    trafo_mat_cell{28} = [r_0/r 0 (L*(r - r_0))/(r*(L - h)); 0 r_0/r -(L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{28} = [(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==29)
    trafo_mat_cell{29} = [r_0/r 0 -(L*(r - r_0))/(r*(L - h)); 0 r_0/r (L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{29} = [-(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==30)
    trafo_mat_cell{30} = [(r + r_0)/(2*r) -(r - r_0)/(2*r) 0; -(r - r_0)/(2*r) (r + r_0)/(2*r) 0; 0 0 (L*l - h*l_0)/(l*(L - h))];
    trafo_vec_cell{30} = [0; 0; (L*h*(l - l_0))/(2*l*(L - h))];
%end 

%if (subdomain_id==31)
    trafo_mat_cell{31} = [r_0/r 0 0; 0 r_0/r 0; 0 0 l_0/l];
    trafo_vec_cell{31} = [0; 0; 0];
%end 

%if (subdomain_id==32)
    trafo_mat_cell{32} = [r_0/r 0 0; 0 r_0/r 0; 0 0 l_0/l];
    trafo_vec_cell{32} = [0; 0; 0];
%end 

for node = 1:num_nodes
  [~, temp2] = find(element_node == node-1);
  x_old = mesh_node_coords_old(:,node);
  elem_id = temp2(1);
  mesh_node_coords_new(:,node) = trafo_mat_cell{subdomain_ids(elem_id)}*x_old + trafo_vec_cell{subdomain_ids(elem_id)};
end

end
