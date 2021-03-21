clear all;

% allTransformationMatrices.mat contains allTransformationMatrices, the
% same variable as produced in reduced_order4_commented.m
% It is a 12x30 symbolic matrix in which each of the 30 columns contains
% the 12x1 transformation matrix for each of 30 tetrahedra (e.g. column 3
% is the transformation matrix for tetrahedron 3)

load('allTransformationMatrices.mat');
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

% c_matrix is a 3x30 symbolic matrix containing the values C1, C2, and C3
% from each transformation matrix
syms c_matrix;

% all_3x3 and inv_matrix are 30x1 cells that will contain a 3x3 symbolic
% matrix in each cell. Each symbolic matrix is a Gij matrix from one
% tetrahedron (or the inverse of a Gij matrix for inv_matrix)
syms all_3x3;
syms inv_matrix;

all_3x3 = cell(32,1);
inv_matrix = cell(32,1);

% current3x3 is a 3x3 symbolic matrix used temporarily to hold each 3x3
% Gij matrix. Set up as 
% [G11 G12 G13]
% [G21 G22 G23]
% [G31 G32 G33]

syms current3x3;

% determinants is a 30x1 symbolic matrix that holds the values of the
% determinants for each of the 30 Gij matrices for each of the 30
% tetrahedra
syms determinants;

% i = 1:30 cycles through each of the 30 tetrahedra. 
for i = 1:32
    c_matrix(1:3,i) = allTransformationMatrices(1:3,i);
    
    % Assigns each spot in current3x3 with a Gij element from the
    % tranformation matrix.
    current3x3(1,1) = allTransformationMatrices(4,i);
    current3x3(1,2) = allTransformationMatrices(5,i);
    current3x3(1,3) = allTransformationMatrices(6,i);
    current3x3(2,1) = allTransformationMatrices(7,i);
    current3x3(2,2) = allTransformationMatrices(8,i);
    current3x3(2,3) = allTransformationMatrices(9,i);
    current3x3(3,1) = allTransformationMatrices(10,i);
    current3x3(3,2) = allTransformationMatrices(11,i);
    current3x3(3,3) = allTransformationMatrices(12,i);
    
    % Assigns a cell in all_3x3 for the Gij matrix
    % corresponding to tetrahedron i and in inv_matrix for the Gij's inverse
    all_3x3(i) = {current3x3};
    inv_matrix(i) = {inv(current3x3)};
    
    % check should be the identity matrix for all 30, since a matrix times
    % its inverse should be the identity matrix. Uncomment check to see
     check = simplify(all_3x3{i}*inv_matrix{i})
    
    % The determinant is calculated and assigned in determinants for each
    % tetrahedron
    
    determinants(i) = simplify(det(current3x3));
    
end

% inversevalues is a 9x30 symbolic matrix that holds the Gij values for all
% 30 Gij inverse matrices
syms inverseValues;

% current_inv is a 3x3 symbolic matrix used to hold whatever inverse matrix
% is being examined at the given moment
syms current_inv;

for i = 1:30
    current_inv = inv_matrix{i};
    inverseValues(1,i) = current_inv(1,1);
    inverseValues(2,i) = current_inv(1,2);
    inverseValues(3,i) = current_inv(1,3);
    inverseValues(4,i) = current_inv(2,1);
    inverseValues(5,i) = current_inv(2,2);
    inverseValues(6,i) = current_inv(2,3);
    inverseValues(7,i) = current_inv(3,1);
    inverseValues(8,i) = current_inv(3,2);
    inverseValues(9,i) = current_inv(3,3);
end

% Simplifies answers
inverseValues = simplify(inverseValues);
% Converts inverseValues to cell
cellInverseValues = arrayfun(@char, inverseValues,'uniform',0);
% Converts to table
tableInverseValues = cell2table(cellInverseValues);
% Saves as .csv file named 'inverseTransformationMatrices.csv' 
writetable(tableInverseValues,'inverseTransformationMatrices.csv','WriteVariableNames',false);

% Similarly to above, saves determinants as 'determinants.csv'
cellDeterminants = arrayfun(@char, determinants,'uniform',0);
tableDeterminants = cell2table(cellDeterminants);
writetable(tableDeterminants,'determinants.csv','WriteVariableNames',false);


%To Do:
% Create transformation matrix for the inner bounding box and cylinder
% Create C file for non-affine heat source by taking into account the different geometrical transformations for each subdomain
% Create C file for actual transformations of the geometry. File format should be similar to the 2D case. This will be used for testing purposes.
% Create txt files storing the ATheta objects for all subdomains. No F theta objects are necessary since the F vector for the heat source is non-affine. The F vector for the boundary conditions has theta objects = 1

