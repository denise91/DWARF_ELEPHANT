function [ u, sol_time ] = solve_FEM_timedep( mu, RB_Con, RB_Eval )
% Finds the transient FEM solution
time_FE_solve_begin = tic;

g = RB_Con.g_FE;
dt = RB_Con.dt;
k_max = RB_Con.n_time_steps;
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

for qf = 1:Qf
  F_Theta_handle = RB_Eval.RB_F_Theta_map(theta_qf_min - 1 + qf);
  F = F + F_Theta_handle(mu)*RB_Con.Fq_vec_map(mat_qf_min - 1 + qf);
end

sysmat = A;%dt*A + M;

R = ichol(sysmat);

% allocate space to store the transient solution
u = zeros(RB_Con.N_FE,k_max);
% Actual time integration
tic;
[u(:,1),flag] = pcg(sysmat,M*RB_Con.u_init + dt*F*g(1),RB_Con.l_rel_tol,RB_Con.l_max_its,R,R');
[u(:,1),flag] = pcg(sysmat,F,RB_Con.l_rel_tol,RB_Con.l_max_its,R,R'); % debug line
for k = 2:k_max
    [u(:,k),flag] = pcg(sysmat,(M*u(:,k-1) + dt*F*g(k)),RB_Con.l_rel_tol,RB_Con.l_max_its,R,R');
end
 
sol_time = toc;
time_FE_solve = toc(time_FE_solve_begin);
fprintf(1,'Time for FE solve: %f minutes\n',time_FE_solve/60.0);
end
