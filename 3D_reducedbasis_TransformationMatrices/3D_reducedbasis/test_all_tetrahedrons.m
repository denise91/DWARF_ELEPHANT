clear all; 

load('allTransformationMatrices.mat');
load('tetrahedrondata.mat');
load('twelvebytwelve.mat');

syms testMatrixResults;
for i = 1:30
    
    for j = 1:4
        tx(j) = coordinates(pointnumbers(i,j),1);
        ty(j) = coordinates(pointnumbers(i,j),2);
        tz(j) = coordinates(pointnumbers(i,j),3);
    end

    testMatrix = subs(twelvebytwelve,{x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4},[tx(1),tx(2),tx(3),tx(4),ty(1),ty(2),ty(3),ty(4),tz(1),tz(2),tz(3),tz(4)]);
    disp(i)
    matrixResult = testMatrix*allTransformationMatrices(:,i);
    simplify(matrixResult)
   
    
end


