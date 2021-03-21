function [alpha_min] = get_alpha_min_est(RB_Con,RB_Eval)

% - discretize parameter domain
% - Save all Aq matrices and inner product matrix in matlab sparse format (done)
% - Write matlab script to create a struct containing all sparse matrices with string keys. the name of the matrix is the string key used to refer to it. (done)
% - Write functions to compute the RBTheta objects (done)
% - for each point in discretized parameter domain
%   - Assemble A matrix (done)
%   - Solve generalized eigenvalue problem eigs(A,X,1,0)
%   - Lowest generalized eigenvalue is alpha_min_approx(mu)
%   - Update alpha_min_approx accordingly
  mu = set_constant_params();

  % 
  r_0_array = linspace(1e-3,5e-3,100);
  l_0_array = linspace(0.001,0.07,100);
  % 

  alpha_mu_min_approx = 1e22;
 
  A_mu = 0*RB_Con.X_curN;
  
  mat_qa_min = min(cell2mat(keys(RB_Con.Aq_mat_map)));
  theta_qa_min = min(cell2mat(keys(RB_Eval.RB_A_Theta_map)));
  
  for r_num = length(r_0_array)
    mu('r_0') = r_0_array(r_num);
  	for l_num = length(l_0_array)
		mu('l_0') = l_0_array(l_num);
  		for q_a = 1:RB_Con.Qa
		    A_theta_handle = RB_Eval.RB_A_Theta_map(theta_qa_min - 1 + q_a);
  			A_mu = A_mu + A_theta_handle(mu) * RB_Con.Aq_mat_map(mat_qa_min - 1 + q_a);
        end
  		alpha_mu = eigs(A_mu, RB_Con.X_curN, 1, -0.1);
  		if alpha_mu_min_approx > alpha_mu
  			alpha_mu_min_approx = alpha_mu;
        end
        A_mu = 0*A_mu;
  	end
  end
  alpha_min = alpha_mu_min_approx;
end
