function [RB_Con,RB_Eval] = ResNormPara_Offline( RB_Con, RB_Eval)
        
   % Performs offline phase calculations for dual norm of the residual for the   
   % time dependent case   
   %   
   time_ResNormPara_Offline_begin = tic;
   Qm = RB_Con.Qm;
   Qa = RB_Con.Qa;
   Qf = RB_Con.Qf;
   FE_nodes = RB_Con.N_FE;
   N = length(RB_Eval.Z(1,:));
   curN = FE_nodes;
   X_curN_ichol = ichol(RB_Con.X_curN);
   
   qa_min = min(cell2mat(keys(RB_Con.Aq_mat_map))); 
   qm_min = min(cell2mat(keys(RB_Con.Mq_mat_map)));
   qf_min = min(cell2mat(keys(RB_Con.Fq_vec_map)));

   
   MpT_X_Mq = zeros(N,N,Qm,Qm);
   MpT_X_Aq = zeros(N,N,Qm,Qa);
   MpT_X_Cq = zeros(N,Qm,Qf);
   ApT_X_Aq = zeros(N,N,Qa,Qa);
   ApT_X_Mq = zeros(N,N,Qa,Qm);
   ApT_X_Cq = zeros(N,Qa,Qf);
   CpT_X_Aq = zeros(N,Qf,Qa);
   CpT_X_Mq = zeros(N,Qf,Qm);

   if (N > 1)
     MpT_X_Mq(1:N-1,1:N-1,:,:) = RB_Eval.MpT_X_Mq;
     MpT_X_Aq(1:N-1,1:N-1,:,:) = RB_Eval.MpT_X_Aq;
     MpT_X_Cq(1:N-1,:,:) = RB_Eval.MpT_X_Cq; 
     ApT_X_Aq(1:N-1,1:N-1,:,:) = RB_Eval.ApT_X_Aq;
	 ApT_X_Mq(1:N-1,1:N-1,:,:) = RB_Eval.ApT_X_Mq;
     ApT_X_Cq(1:N-1,:,:) = RB_Eval.ApT_X_Cq;
	 CpT_X_Aq(1:N-1,:,:) = RB_Eval.CpT_X_Aq;
	 CpT_X_Mq(1:N-1,:,:) = RB_Eval.CpT_X_Mq;
   end

   RB_Con.Mq_representors{N} = zeros(curN,Qm);
   RB_Con.Aq_representors{N} = zeros(curN,Qa);
  
   for qa = 1:Qa
       [RB_Con.Aq_representors{N}(:,qa),flag] = pcg(RB_Con.X_curN,RB_Con.Aq_mat_map(qa_min - 1 + qa)*RB_Eval.Z(:,N),RB_Con.l_rel_tol,RB_Con.l_max_its,X_curN_ichol,X_curN_ichol'); 
   end
   fprintf(1,'Aq Riesz representors computed.\n');

   for qm = 1:Qm
       [RB_Con.Mq_representors{N}(:,qm),flag] = pcg(RB_Con.X_curN,RB_Con.Mq_mat_map(qm_min - 1 + qm)*RB_Eval.Z(:,N),RB_Con.l_rel_tol,RB_Con.l_max_its,X_curN_ichol,X_curN_ichol');
   end
   fprintf(1,'Mq Riesz representors computed.\n');

   for qm = 1:Qm
     for pm = 1:Qm
       for n = 1:N
         MpT_X_Mq(N,n,pm,qm) = RB_Eval.Z(:,N)'*RB_Con.Mq_mat_map(qm_min - 1 + pm)*RB_Con.Mq_representors{n}(:,qm);
		 if n ~= N
           MpT_X_Mq(n,N,pm,qm) = RB_Eval.Z(:,n)'*RB_Con.Mq_mat_map(qm_min - 1 + pm)*RB_Con.Mq_representors{N}(:,qm);
		 end
       end
     end
   end
   fprintf(1,'Computed MpT_X_Mq\n');

   for qa = 1:Qa
     for qm = 1:Qm
       for n = 1:N
         MpT_X_Aq(N,n,qm,qa) = RB_Eval.Z(:,N)'*RB_Con.Mq_mat_map(qm_min - 1 + qm)*RB_Con.Aq_representors{n}(:,qa);
		 if (n ~= N)
           MpT_X_Aq(n,N,qm,qa) = RB_Eval.Z(:,n)'*RB_Con.Mq_mat_map(qm_min - 1 + qm)*RB_Con.Aq_representors{N}(:,qa);
	     end
       end
     end
   end
   fprintf(1,'Computed MpT_X_Aq terms\n');
   
   for qf = 1:Qf
     for pm = 1:Qm
       m = N;
       MpT_X_Cq(m,pm,qf) = RB_Eval.Z(:,m)'*RB_Con.Mq_mat_map(qm_min - 1 + pm)*RB_Con.Fq_representors(:,qf);
     end
   end
   fprintf(1,'Computed MpT_X_Cq\n');


   for qa = 1:Qa
     for pa = 1:Qa
       for n = 1:N
         ApT_X_Aq(N,n,pa,qa) = RB_Eval.Z(:,N)'*RB_Con.Aq_mat_map(qa_min - 1 + pa)*RB_Con.Aq_representors{n}(:,qa);
         if n ~= N
		   ApT_X_Aq(n,N,pa,qa) = RB_Eval.Z(:,n)'*RB_Con.Aq_mat_map(qa_min - 1 + pa)*RB_Con.Aq_representors{N}(:,qa);
         end
       end
     end 
   end
   fprintf(1,'Computed ApT_X_Aq terms\n');
 
   for qm = 1:Qm
     for pa = 1:Qa
       for n = 1:N
         ApT_X_Mq(N,n,pa,qm) = RB_Eval.Z(:,N)'*RB_Con.Aq_mat_map(qa_min - 1 + pa)*RB_Con.Mq_representors{n}(:,qm);
         if n ~= N 
           ApT_X_Mq(n,N,pa,qm) = RB_Eval.Z(:,n)'*RB_Con.Aq_mat_map(qa_min - 1 + pa)*RB_Con.Mq_representors{N}(:,qm);
		 end
       end
     end 
   end
   fprintf(1,'Computed ApT_X_Mq terms\n');

   for qf = 1:Qf
     for qa = 1:Qa
       m = N;
       ApT_X_Cq(m,qa,qf) = RB_Eval.Z(:,m)'*RB_Con.Aq_mat_map(qa_min - 1 + qa)*RB_Con.Fq_representors(:,qf);
     end
   end 
   fprintf(1,'Computed ApT_X_Cq terms\n');

  
   if (N == 1) 
     for qf = 1:Qf
       for pf = 1:Qf
         RB_Eval.CpT_X_Cq(pf,qf) = RB_Con.Fq_vec_map(qf_min - 1 + pf)'*RB_Con.Fq_representors(:,qf);
       end
     end
   end
   
   for qa = 1:Qa
     for qf = 1:Qf
       m = N;
       CpT_X_Aq(m,qf,qa) = RB_Con.Fq_vec_map(qf_min - 1 + qf)'*RB_Con.Aq_representors{m}(:,qa); 
	 end
   end
   fprintf(1,'Computed CpT_X_Aq\n');
  
   for qm = 1:Qm
     for qf = 1:Qf
       m = N;
       CpT_X_Mq(m,qf,qm) = RB_Con.Fq_vec_map(qf_min - 1 + qf)'*RB_Con.Mq_representors{m}(:,qm); 
	 end
   end
   fprintf(1,'Computed CpT_X_Mq\n');

   RB_Eval.ApT_X_Aq = ApT_X_Aq;
   RB_Eval.ApT_X_Mq = ApT_X_Mq;
   RB_Eval.ApT_X_Cq = ApT_X_Cq;
   RB_Eval.MpT_X_Mq = MpT_X_Mq;
   RB_Eval.MpT_X_Aq = MpT_X_Aq;
   RB_Eval.MpT_X_Cq = MpT_X_Cq;
   RB_Eval.CpT_X_Aq = CpT_X_Aq;
   RB_Eval.CpT_X_Mq = CpT_X_Mq;

   time_ResNormPara_Offline = toc(time_ResNormPara_Offline_begin);
   fprintf(1,'Time for ResNormPara_Offline: %f minutes\n',time_ResNormPara_Offline/60.0);
end
