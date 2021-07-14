function [res_norm_direct] = ResDualNorm_Direct(mu,RB_Con, RB_Eval, uN, uN_prev)
% Assemble A_mu, M_mu and F_mu

dt = RB_Con.dt;
% Assemble Mass, stiffness matrices and load vector
Qm = RB_Con.Qm;
Qa = RB_Con.Qa;
Qf = RB_Con.Qf;

mat_qa_min = min(cell2mat(keys(RB_Con.Aq_mat_map))); 
mat_qm_min = min(cell2mat(keys(RB_Con.Mq_mat_map)));
mat_qf_min = min(cell2mat(keys(RB_Con.Fq_vec_map)));

theta_qa_min = min(cell2mat(keys(RB_Eval.RB_A_Theta_map))); 
theta_qm_min = min(cell2mat(keys(RB_Eval.RB_M_Theta_map)));
theta_qf_min = min(cell2mat(keys(RB_Eval.RB_F_Theta_map)));

M = sparse(RB_Con.N_FE,RB_Con.N_FE);

for q = 1:Qm
  M_Theta_handle = RB_Eval.RB_M_Theta_map(theta_qm_min - 1 + q);
  M = M + RB_Con.Mq_mat_map(mat_qm_min - 1 + q)*M_Theta_handle(mu);
end

A = sparse(RB_Con.N_FE,RB_Con.N_FE);

for k = 1:Qa
    A_Theta_handle = RB_Eval.RB_A_Theta_map(theta_qa_min - 1 + k);
    A = A + A_Theta_handle(mu)*RB_Con.Aq_mat_map(mat_qa_min - 1 + k);
end

F = zeros(RB_Con.N_FE,1);
FTheta_arr = zeros(Qf,1);

for qf = 1:Qf
  F_Theta_handle = RB_Eval.RB_F_Theta_map(theta_qf_min - 1 + qf);
  F = F + F_Theta_handle(mu)*RB_Con.Fq_vec_map(mat_qf_min - 1 + qf);
  FTheta_arr(qf) = F_Theta_handle(mu);
end

% Compute A_mu * u_curN, M_mu * d u_curN / dt
u_curN = RB_Eval.Z*uN;
u_curN_prev = RB_Eval.Z*uN_prev;
Au = A*u_curN;
Mu = M*u_curN;
Mu_prev = M*u_curN_prev;
res = F - Au - (Mu - Mu_prev)/dt;
% Compute X_inv * F_mu - X_inv A_mu * u_curN -  X_inv M_mu * d u_curN/dt
R = ichol(RB_Con.X_curN);
[X_inv_res,flag] = pcg(RB_Con.X_curN,res,RB_Con.l_rel_tol,RB_Con.l_max_its,R,R');
% Compute (F_mu - A_mu * u_curN - M_mu * d u_curN/dt)' * X_inv * (F_mu - A_mu * u_curN - M_mu * d u_curN/dt)
res_norm_direct = res'*X_inv_res;
end
