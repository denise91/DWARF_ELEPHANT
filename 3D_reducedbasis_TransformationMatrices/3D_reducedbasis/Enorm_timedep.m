function [ Enorm_result ] = Enorm_timedep( uN, mu, RB_Eval, dt, k )
% Returns the spatio-temporal energy norm of the transient solution
% Input:
% uN: RB solution (N,n_time_steps)
% mu: parameter values
% M: Cell array of reduced mass matrices {Qm+1}x(N,N)
% A: Cell array of reduced stiffness matrices {Qa+1}x(N,N)
% dt: time step size
% k: time step number 

Qa = max(size(RB_Eval.ANq));
Qm = max(size(RB_Eval.MNq));

Enorm_sq = 0;

q_min = min(cell2mat(keys(RB_Eval.RB_M_Theta_map)));
for q = 1:Qm
  q_prime = q + q_min - 1;
  MTheta_func_handle = RB_Eval.RB_M_Theta_map(q_prime);
  Enorm_sq = Enorm_sq + uN(:,k)'*MTheta_func_handle(mu)*RB_Eval.MNq{q_prime}*uN(:,k);
end

q_min = min(cell2mat(keys(RB_Eval.RB_A_Theta_map)));
for k_pr = 1:k
    for q = 1:Qa
	    q_prime = q_min - 1 + q;
		ATheta_func_handle = RB_Eval.RB_A_Theta_map(q_prime);
        Enorm_sq = Enorm_sq + dt*ATheta_func_handle(mu)*uN(:,k_pr)'*RB_Eval.ANq{q_prime}*uN(:,k_pr);
    end
end
Enorm_result = sqrt(Enorm_sq);
end

