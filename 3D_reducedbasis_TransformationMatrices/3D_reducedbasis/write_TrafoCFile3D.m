function [ output_args ] = write_TrafoCFile3D( allTransformationMatrices )
%Writes C file containing functions to transform a geometry based on the
%transformation contained in allTransformationMatrices
  syms zero;
  zero = 0;
  
  Trafo_CFile = fopen("Transformations_RBRFAGeom.C","w");
  fprintf(Trafo_CFile,'extern "C" double NewCoord(double OldCoordX, double OldCoordY, double OldCoordZ, double r_0, double l_0, double L, double r, double l, int subdomain, int Coord_Required)\n');
  fprintf(Trafo_CFile,'{\n  double matrix[3][3] = {0}, vec[3][1] = {0}, d = 3*r, h = 1.5*l;\n');
  for tet_num = 1:32
    matrix = [allTransformationMatrices(4,tet_num) allTransformationMatrices(5,tet_num) allTransformationMatrices(6,tet_num); allTransformationMatrices(7,tet_num) allTransformationMatrices(8,tet_num) allTransformationMatrices(9,tet_num); allTransformationMatrices(10,tet_num) allTransformationMatrices(11,tet_num) allTransformationMatrices(12,tet_num)];
      if (allTransformationMatrices(1,tet_num) ~= zero)
          temp_str = ccode(allTransformationMatrices(1,tet_num));
          ccode_vector = " vec[0][0]" + replace(temp_str,"t0 ","");
      else
          ccode_vector = "  vec[0][0] = 0;";
      end
      if (allTransformationMatrices(2,tet_num) ~= zero)
          temp_str = ccode(allTransformationMatrices(2,tet_num));
          ccode_vector = ccode_vector + " vec[1][0]" + replace(temp_str,"t0 ","");
      else
          ccode_vector = ccode_vector + " vec[1][0] = 0;";
      end
      if (allTransformationMatrices(3,tet_num) ~= zero)
          temp_str = ccode(allTransformationMatrices(3,tet_num));
          ccode_vector = ccode_vector + " vec[2][0]" + replace(temp_str,"t0 ","");
      else
          ccode_vector = ccode_vector + " vec[2][0] = 0;";
      end
    fprintf(Trafo_CFile,"  if (subdomain == "+int2str(tet_num)+")\n");
	fprintf(Trafo_CFile,'  {\n');
	fprintf(Trafo_CFile,"%s",ccode(matrix));
    fprintf(Trafo_CFile,"\n");
    fprintf(Trafo_CFile,"%s",ccode_vector);
	fprintf(Trafo_CFile,'\n  }\n');
  end
  fprintf(Trafo_CFile,'    return matrix[Coord_Required][0]*OldCoordX + matrix[Coord_Required][1]*OldCoordY + matrix[Coord_Required][2]*OldCoordZ + vec[Coord_Required][0];\n');
  fprintf(Trafo_CFile,'}\n');
  fclose(Trafo_CFile);
end

