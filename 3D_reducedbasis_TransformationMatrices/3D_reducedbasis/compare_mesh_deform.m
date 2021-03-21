function [] = compare_mesh_deform(param_num,mesh_num,test_case)
%Performs full FE solve for given parameter value and mesh number
% Input:
% param_num : 1=param_min/2=param_ref/3=param_max
% mesh_num : number of mesh refinement (0,1..4)
% Action:
% Writes the temperature solution to vtu files
% Compute mesh convergence metric and writes to file
[mem,vmem] = get_memory_usage()
mem_init = 0;%mem
vmem_init = 0;%vmem
fprintf(1,"Starting FE solve; Memory consumption: rss=%e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
get_memory_usage_from_qstat();

if (param_num ~= 1) && (param_num ~= 2) && (param_num ~=3)
    error("Invalid value provided for param_num");
end

if (mesh_num < 0) || (mesh_num > 4) || (mod(mesh_num,1) ~= 0)
    error("Invalid value provided for mesh_num");
end

param_num
mesh_num

param_label_S = ["min","ref","max"];
param_label_L = ["Min","Ref","Max"];

% make sure the correct directories are added to the search path before
% calling this function



if (test_case)
    test_suffix = "_test";
    test_mat_folder = "/transienttestcase";
else
    test_suffix = "";
    test_mat_folder = "";
end
output_file_name = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/param",param_label_L(param_num),test_suffix,"/mesh",int2str(mesh_num),"/");
node_coords_file_base = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/mesh_",int2str(mesh_num),"/mesh_node_coords");
node_connect_file_base = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/mesh_",int2str(mesh_num),"/mesh_node_connectivity");

mesh_dim = 3;
nodes_per_elem = 4;

% Read libmesh mesh data
load_mesh_start = tic;
[node_x, element_node, subdomain_ids, node_num, element_num, ~] = read_libmesh_mesh_data(node_coords_file_base,node_connect_file_base);
load_mesh_time = toc(load_mesh_start);
fprintf(1,"\nTime to load mesh: %f min\n",load_mesh_time/60.0);
[mem,vmem] = get_memory_usage();
fprintf(1,"Mesh loaded: Memory consumption: rss=%e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);
get_memory_usage_from_qstat();

node_num = length(node_x(1,:));
element_num = length(element_node(1,:));

 N_FE = node_num;
 L = 0.1;
 r = 0.003;
 l = 0.04;
 d = (8.0/3.0)*r;
 h = (4.0/3.0)*l;
  
 if (param_num == 1)
     r_0 = 4e-4;
     l_0 = 5e-3;
 end
 if (param_num == 2)
     r_0 = r;
     l_0 = l;
 end
 if (param_num == 3)
     r_0 = 5e-3;
     l_0 = 7e-2;
 end
 
  node_subd_file_path = strcat("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/libmesh_mesh_data",test_suffix,"/mesh_",int2str(mesh_num),"/");

  node_subdomain = readmatrix(strcat(node_subd_file_path,'node_subdomain.txt'));
  %start_mesh_deform = tic;
  %node_x_new_1 = deform_mesh(node_x, subdomain_ids, element_node, r_0, l_0);
  %mesh_deform_time = toc(start_mesh_deform);
  %fprintf(1,"\nTime for mesh deformation (Algorithm 1): %f min\n",mesh_deform_time/60.0);
  %[mem,vmem] = get_memory_usage();
  %fprintf(1,"Mesh deformed: Memory consumption: rss = %e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);

  start_mesh_deform = tic;
  node_x_new_2 = deform_mesh_2(node_x, node_subdomain, element_node, r_0, l_0);
  mesh_deform_time = toc(start_mesh_deform);
  fprintf(1,"\nTime for mesh deformation (Algorithm 2): %f min\n",mesh_deform_time/60.0);
  [mem,vmem] = get_memory_usage();
  fprintf(1,"Mesh deformed: Memory consumption: rss = %e Mb; vmem=%e Mb;\n",mem - mem_init,vmem - vmem_init);

  %max(max(abs(node_x_new_1 - node_x_new_2)))/max(max(abs(node_x_new_1)))
end

