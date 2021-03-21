function write_geom_trafo_function(allTransformationMatrices)

fileID = fopen("apply_geom_trafo.m","w");

fprintf(fileID,"function  x_new = apply_geom_trafo(subdomain_id,x_old,r0,l0)\n");
fprintf(fileID,"L = 0.1;\n");
fprintf(fileID,"r = 3e-3;\n");
fprintf(fileID,"l = 4e-2;\n");
fprintf(fileID,"r_0 = r0;\n");
fprintf(fileID,"l_0 = l0;\n");
fprintf(fileID,"d = 3*r;\n");
fprintf(fileID,"h = 1.5*l;\n\n");

for subdomain_id = 1:32
   fprintf(fileID,strcat("if (subdomain_id==",int2str(subdomain_id),")\n"));
   fprintf(fileID,strcat("    matrix = [",char(allTransformationMatrices(4,subdomain_id))," ",char(allTransformationMatrices(5,subdomain_id))," ",char(allTransformationMatrices(6,subdomain_id)),"; ",char(allTransformationMatrices(7,subdomain_id))," ",char(allTransformationMatrices(8,subdomain_id))," ",char(allTransformationMatrices(9,subdomain_id)),"; ",char(allTransformationMatrices(10,subdomain_id))," ",char(allTransformationMatrices(11,subdomain_id))," ",char(allTransformationMatrices(12,subdomain_id)),"];\n"));
   fprintf(fileID,strcat("    vec = [",char(allTransformationMatrices(1,subdomain_id)),"; ",char(allTransformationMatrices(2,subdomain_id)),"; ", char(allTransformationMatrices(3,subdomain_id)),"];\n"));
   fprintf(fileID,"end \n\n");
end
fprintf(fileID,"x_new = matrix*x_old + vec;\n");
fprintf(fileID,"end \n");
end