% - discretize parameter domain
% - Save all Aq matrices and inner product matrix in matlab sparse format (done)
% - Write matlab script to create a struct containing all sparse matrices with string keys. the name of the matrix is the string key used to refer to it. (done)
% - Write functions to compute the RBTheta objects (done)
% - for each point in discretized parameter domain
%   - Assemble A matrix (done)
%   - Solve generalized eigenvalue problem eigs(A,X,1,0)
%   - Lowest generalized eigenvalue is alpha_min_approx(mu)
%   - Update alpha_min_approx accordingly
clear all

cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis'
 L = 0.1;
 r = 0.003;
 l = 0.05;
% 
r_0_array = linspace(1e-3,5e-3,100)
l_0_array = linspace(0.001,0.07,100)
% 
A_mu = sparse(92,92)
% 
 Aq_mat_cell = cell(1,1);
 cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/';
 Inner_Prod_Mat = sparse(92,92);
 for q_a = 0:253
 	eval([strcat('RBRFA3DPerf_Aq_',int2str(q_a))]);
 	Aq_mat_cell{q_a+1} = eval([strcat('RBRFA3DPerf_Aq_',int2str(q_a),"_sp")]);
    Inner_Prod_Mat = Inner_Prod_Mat + feval(strcat('RBTheta_',int2str(q_a)),L,r,r,l,l,3*r,1.5*l,1.0) * Aq_mat_cell{q_a+1};
    q_a
    feval(strcat('RBTheta_',int2str(q_a)),L,r,r,l,l,3*r,1.5*l,1.0)
 end
 %eval([strcat('RBRFA3DNoPerf_InnerProdMat')]);
 %Inner_Prod_Mat = eval(['RBRFA3DNoPerf_InnerProdMat_sp']);
 
 cd '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis';
 
 alpha_mu = 0;
 alpha_mu_min_approx = 1e22;

for r_num = 1:length(r_0_array)
	for l_num = 1:length(l_0_array)
		for q_a = 0:253
			A_mu = A_mu + feval(strcat('RBTheta_',int2str(q_a)),L,r,r_0_array(r_num),l,l_0_array(l_num),3*r,1.5*l,1.0) * Aq_mat_cell{q_a+1};
            %A_mu = A_mu + Aq_mat_cell{q_a+1};
        end
        %A_mu = 0.5 * (A_mu + A_mu');
		alpha_mu = eigs(A_mu, Inner_Prod_Mat, 1, -0.1);
		if alpha_mu_min_approx > alpha_mu
			alpha_mu_min_approx = alpha_mu
        end
        A_mu = 0*A_mu;
	end
end
