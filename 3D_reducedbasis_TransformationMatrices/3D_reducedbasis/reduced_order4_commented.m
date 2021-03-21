clear all

% twelvebytwelve.mat contains:
% the coordinates x1, y1, and z1 through x4,
% y4, and z4 as symbolic variables, as well as the transformed versions of
% these coordinates (x1_0, y1_0, etc.)

% twelvebytwelve, a 12x12 matrix containing the original
% coordinates of the four points of each tetrahedron 

% transformed, the 12x1 matrix containing the coordinates of the transformed 
% tetrahedron

% transformationMatrix, a 12x1 symbolic matrix obtained by
% solving twelvebytwelve and transformed (e.g.twelvebytwelve\transformed)
% transformationMatrix contains the symbolic solution for transforming any 
% of the 30 tetrahedra given the original coordinates of each of the four
% points as well as the transformed coordinates (e.g. transformationMatrix
% is in terms of x1, y1, z1, x2, .... x4_0, y4_0, z4_0)

load('twelvebytwelve.mat');

% tetrahedrondata.mat contains: 

% coordinates, a 16x3 symbolic matrix. Rows correspond to point numbers
% (e.g. row 1 holds the coordinates of point 1). 
% Column 1 contains x-coordinates, column 2 contains
% y-coordinates, and column 3 contains z-coordinates. 

% transformedCoordinates, which is similarly formatted (16x3 symbolic
% matrix) and contains the transformed coordinates of each point (e.g.
% outer cube points are not scaled, bounding box points are scaled by r_0/r
% or l_0/l

% pointnumbers, a 30x4 double matrix. Row numbers correspond to tetrahedron
% numbers and columns correspond to the points that are in that
% tetrahedron. As such, pointnumbers(5,:) = [2 4 5 7] because tetrahedron 5
% contains points 2, 4, 5, and 7
% Tetrahedron numbers are described in tetrahedronNumbers.csv and also
% correspond with the gmsh model's Physical Volumes
% 
% Relevant d, h, l, L, l_0, r, and r_0 are defined as syms in this data set as well
% l is the length of the cylinder, l_0 is the scaled cylinder length, r is
% the cylinder radius, r_0 is the scaled radius, L is the side length of
% the outer cube, d is the length/width (x- and y-directions) of the
% bounding box, and h is the height (z-direction) of the bounding box

load('tetrahedrondata.mat');

% These are temporary-use variables to hold x, y, z, x_0, y_0, and z_0
% coordinates 

syms tx ty tz tx_0 ty_0 tz_0 

% This produces 30 x 12 matrix to hold all the transformation matrices (30 columns 
% of 12x1 transformation matrices) and
% fills it with the general form of the transformation matrix

for i = 1:30
    allTransformationMatrices(:,i) = transformationMatrix;
end

% Substitutes in values to produce the transformation matrix for each individual tetrahedron
% i corresponds to tetrahedron number

for i = 1:30
    
    % Reads in the coordinates and the transformed coordinates for each
    % tetrahedron from data files. Each t__ matrix is 4x1 and holds four symbol coordinates,
    % for each of the four points in the tetrahedron.
    
    for j = 1:4
        tx(j) = coordinates(pointnumbers(i,j),1);
        ty(j) = coordinates(pointnumbers(i,j),2);
        tz(j) = coordinates(pointnumbers(i,j),3);
        tx_0(j) = transformedCoordinates(pointnumbers(i,j),1);
        ty_0(j) = transformedCoordinates(pointnumbers(i,j),2);
        tz_0(j) = transformedCoordinates(pointnumbers(i,j),3);
    
    end
    
    % substitute in the values for the coordinates and transformed
    % coordinates into the transformation matrix to obtain the specific
    % transformation matrix for each. Each column corresponds to a
    % transformation matrix for a different tetrahedron (column 1 is the
    % transformation matrix for tetrahedron 1, and so on). 
  
    allTransformationMatrices(:,i) = subs(allTransformationMatrices(:,i), {x1,x2,x3,x4,x1_0,x2_0,x3_0,x4_0,y1,y2,y3,y4,y1_0,y2_0,y3_0,y4_0,z1,z2,z3,z4,z1_0,z2_0,z3_0,z4_0},[tx(1),tx(2),tx(3),tx(4),tx_0(1),tx_0(2),tx_0(3),tx_0(4),ty(1),ty(2),ty(3),ty(4),ty_0(1),ty_0(2),ty_0(3),ty_0(4),tz(1),tz(2),tz(3),tz(4),tz_0(1),tz_0(2),tz_0(3),tz_0(4)]);

end

% simplify the end result
allTransformationMatrices = simplify(allTransformationMatrices);
% Turn the result into a cell 
cellTransformationMatrices = arrayfun(@char, allTransformationMatrices,'uniform',0);
% Turn the cell into a table
tableTransformationMatrices = cell2table(cellTransformationMatrices);
% Export the table in a .csv file named "transformationMatrices.csv"
% This file is arranged in the same way as allTransformationMatrices (see
% above)
writetable(tableTransformationMatrices,'transformationMatrices.csv','WriteVariableNames',false);

% transformationMatrices.csv contains the same information, but the names
% of each variable in the transformation matrix and the names of each
% tetrahedron are labeled
