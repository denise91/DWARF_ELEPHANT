function [ POD_modes ] = POD_X( e_Nproj, n, X_curN, K )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

C_POD = 1./K * e_Nproj'*X_curN*e_Nproj;

[eigVec, ~] = eigs(C_POD,1,'LM'); % compute largest eigenvalue of the projection error correlation matrix

%eigVal = abs(diag(eigVal));
%[~,I] = sort(-eigVal);

%eigVec = eigVec(:,I);
%eigVal = eigVal(I);
POD_modes = e_Nproj*eigVec(:,1);

end

