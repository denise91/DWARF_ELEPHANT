r_0_array = linspace(1e-3,5e-3,15)
l_0_array = linspace(0.002,0.006,15)

for r_num = 1:length(r_0_array)
	for l_num = 1:length(l_0_array)
		for q_a = 1:9
			%A_mu = A_mu + feval(strcat('DiffusionRBTheta_',int2str(q_a)),L,r,r_0_array(r_num),l,l_0_array(l_num),3*r,1.5*l,1.0) * Aq_mat_cell{q_a};
			feval(strcat('DiffusionRBTheta_',int2str(q_a)),L,r,r_0_array(r_num),l,l_0_array(l_num),3*r,1.5*l,1.0)
		end
		%alpha_mu = eigs(A_mu, Inner_Prod_Mat, 1, -0.1)
		%if (alpha_mu_min_approx > alpha_mu)
		%	alpha_min_approx = alpha_mu
		%end
	end
end
