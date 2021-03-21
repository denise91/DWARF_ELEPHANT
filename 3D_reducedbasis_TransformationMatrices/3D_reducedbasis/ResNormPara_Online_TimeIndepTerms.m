function [CmupT_X_Cmuq, CmupT_X_Amuq, CmupT_X_Mmuq, MmupT_X_Mmuq, MmupT_X_Amuq, MmupT_X_Cmuq, AmupT_X_Amuq, AmupT_X_Mmuq, AmupT_X_Cmuq] = ResNormPara_Online_TimeIndepTerms(mu, RB_Eval)
% This function performs the online phase calculations for the time dependent residual norm.
% uN_t and uN_tprev have dimension non-curly N
% pass function handle cell arrays as input arguments

% SEPARATE TIME DEPENDENT TERMS FROM THE TIME INDEPENDENT TERMS

time_ResNorm_TimeIndep_begin = tic;
N = length(RB_Eval.Z(1,:));
CmupT_X_Cmuq = 0;
CmupT_X_Amuq = zeros(1,N);
CmupT_X_Mmuq = zeros(1,N);
MmupT_X_Mmuq = zeros(N,N); 
MmupT_X_Amuq = zeros(N,N); 
MmupT_X_Cmuq = zeros(N,1); 
AmupT_X_Amuq = zeros(N,N); 
AmupT_X_Mmuq = zeros(N,N);
AmupT_X_Cmuq = zeros(N,1); 

FTheta_arr = zeros(RB_Eval.Qf,1);
MTheta_arr = zeros(RB_Eval.Qm,1);
ATheta_arr = zeros(RB_Eval.Qa,1);

p_min = min(cell2mat(keys(RB_Eval.RB_F_Theta_map)));
for q = 1:RB_Eval.Qf
  q_prime = p_min - 1 + q;
  temp_handle = RB_Eval.RB_F_Theta_map(q_prime);
  FTheta_arr(q) = temp_handle(mu);
end

p_min = min(cell2mat(keys(RB_Eval.RB_M_Theta_map)));
for q = 1:RB_Eval.Qm
  q_prime = p_min - 1 + q;
  temp_handle = RB_Eval.RB_M_Theta_map(q_prime);
  MTheta_arr(q) = temp_handle(mu);
end

p_min = min(cell2mat(keys(RB_Eval.RB_A_Theta_map)));
for q = 1:RB_Eval.Qa
  q_prime = p_min - 1 + q;
  temp_handle = RB_Eval.RB_A_Theta_map(q_prime);
  ATheta_arr(q) = temp_handle(mu);
end

CmupT_X_Cmuq = FTheta_arr'*RB_Eval.CpT_X_Cq*FTheta_arr;

for n = 1:N
	MmupT_X_Cmuq(n) = MmupT_X_Cmuq(n) + MTheta_arr'*squeeze(RB_Eval.MpT_X_Cq(n,:,:))*FTheta_arr;
	AmupT_X_Cmuq(n) = AmupT_X_Cmuq(n) + ATheta_arr'*squeeze(RB_Eval.ApT_X_Cq(n,:,:))*FTheta_arr;
	CmupT_X_Amuq(n) = CmupT_X_Amuq(n) + FTheta_arr'*squeeze(RB_Eval.CpT_X_Aq(n,:,:))*ATheta_arr;
	CmupT_X_Mmuq(n) = CmupT_X_Mmuq(n) + FTheta_arr'*squeeze(RB_Eval.CpT_X_Mq(n,:,:))*MTheta_arr;
	for m = 1:N
		MmupT_X_Mmuq(m,n) = MmupT_X_Mmuq(m,n) + MTheta_arr'*squeeze(RB_Eval.MpT_X_Mq(m,n,:,:))*MTheta_arr;
		MmupT_X_Amuq(m,n) = MmupT_X_Amuq(m,n) + MTheta_arr'*squeeze(RB_Eval.MpT_X_Aq(m,n,:,:))*ATheta_arr;
		AmupT_X_Amuq(m,n) = AmupT_X_Amuq(m,n) + ATheta_arr'*squeeze(RB_Eval.ApT_X_Aq(m,n,:,:))*ATheta_arr;
		AmupT_X_Mmuq(m,n) = AmupT_X_Mmuq(m,n) + ATheta_arr'*squeeze(RB_Eval.ApT_X_Mq(m,n,:,:))*MTheta_arr;
	end
end

time_ResNorm_TimeIndep = toc(time_ResNorm_TimeIndep_begin);
fprintf(1,'Time to compute ResNorm time-indep terms: %f minutes\n',time_ResNorm_TimeIndep/60.0);
end
