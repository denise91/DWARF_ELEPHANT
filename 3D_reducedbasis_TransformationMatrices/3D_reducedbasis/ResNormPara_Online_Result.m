function [res_norm_sq] = ResNormPara_Online_Result(CmuT_X_Cmu, CmuT_X_Amu, CmuT_X_Mmu, MmuT_X_Mmu, MmuT_X_Amu, MmuT_X_Cmu, AmuT_X_Amu, AmuT_X_Mmu, AmuT_X_Cmu, uN_k, uN_kPrev, gk, dt)

res_norm_sq = CmuT_X_Cmu*gk*gk;
res_norm_sq = res_norm_sq + 1./dt^2*(uN_k - uN_kPrev)'*MmuT_X_Mmu*(uN_k - uN_kPrev);
res_norm_sq = res_norm_sq + 1./dt*(uN_k-uN_kPrev)'*MmuT_X_Amu*uN_k;
res_norm_sq = res_norm_sq - 1./dt*(uN_k-uN_kPrev)' * MmuT_X_Cmu*gk;
res_norm_sq = res_norm_sq + uN_k'*AmuT_X_Amu*uN_k;
res_norm_sq = res_norm_sq + 1./dt*uN_k'*AmuT_X_Mmu*(uN_k - uN_kPrev);
res_norm_sq = res_norm_sq - uN_k'*AmuT_X_Cmu*gk;
res_norm_sq = res_norm_sq - CmuT_X_Amu*uN_k*gk;
res_norm_sq = res_norm_sq - CmuT_X_Mmu*(uN_k - uN_kPrev)/dt*gk;
%fprintf(1,'ResNormPara_Result diff = %e\n',(res_norm_sq -(CmuT_X_Cmu*gk*gk + 1./dt^2*(uN_k - uN_kPrev)'*MmuT_X_Mmu*(uN_k - uN_kPrev) + 2./dt*(uN_k-uN_kPrev)'*MmuT_X_Amu*uN_k - 2./dt*(uN_k-uN_kPrev)' * MmuT_X_Cmu*gk + uN_k'*AmuT_X_Amu*uN_k - 2.0*uN_k'*AmuT_X_Cmu*gk))/res_norm_sq);
end
