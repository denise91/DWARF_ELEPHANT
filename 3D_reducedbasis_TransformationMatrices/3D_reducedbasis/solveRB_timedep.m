function [ u, sol_time ] = solveRB_timedep( mu, RB_Eval )
% solves RB system for time dependent case
% u is the solution matrix whose columns contain the spatial solution for
% each time step
% u: N x K

time_RB_solve_begin = tic;
K = RB_Eval.n_time_steps;
theta_qa_min = min(cell2mat(keys(RB_Eval.RB_A_Theta_map)));
theta_qm_min = min(cell2mat(keys(RB_Eval.RB_M_Theta_map)));
theta_qf_min = min(cell2mat(keys(RB_Eval.RB_F_Theta_map)));

F = zeros(max(size(RB_Eval.ANq{1})),1);
A = zeros(length(F));
M = zeros(length(F));
for q = 1:max(size(RB_Eval.ANq))
    A_Theta_handle = RB_Eval.RB_A_Theta_map(theta_qa_min - 1 + q);
    A = A + A_Theta_handle(mu)*RB_Eval.ANq{q};
end

for q = 1:max(size(RB_Eval.MNq))
    M_Theta_handle = RB_Eval.RB_M_Theta_map(theta_qm_min - 1 + q);
    M = M + M_Theta_handle(mu)*RB_Eval.MNq{q};
end

for q = 1:max(size(RB_Eval.FNq))
    F_Theta_handle = RB_Eval.RB_F_Theta_map(theta_qf_min - 1 + q);
    F = F + F_Theta_handle(mu)*RB_Eval.FNq{q};
end

tic;
sysmat = RB_Eval.dt*A + M;
g = RB_Eval.g_FE;
u = zeros(length(F), K);
RHS = M*RB_Eval.uN_init + RB_Eval.dt*F*g(1);
u(:,1) = sysmat \ RHS;
for k = 2:K
    u(:,k) = sysmat\(M*u(:,k-1) + RB_Eval.dt*F*g(k)); % use LU decomposition
end

sol_time = toc;
time_RB_solve = toc(time_RB_solve_begin);
%fprintf(1,'Time for RB solve: %f minutes\n',time_RB_solve/60.0);
end

