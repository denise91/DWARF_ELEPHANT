function [RB_Con, RB_Eval] = Initialize_Riesz_representors(RB_Con, RB_Eval) 
   time_init_riesz_begin = tic; 
   Qa = RB_Con.Qa;
   Qm = RB_Con.Qm; 
   Qf = RB_Con.Qf;
   
   RB_Eval.MpT_X_Mq = zeros(1,1,Qm,Qm);
   RB_Eval.MpT_X_Aq = zeros(1,1,Qm,Qa);
   RB_Eval.MpT_X_Cq = zeros(1,Qm,Qf);
   RB_Eval.ApT_X_Aq = zeros(1,1,Qa,Qa);
   RB_Eval.ApT_X_Mq = zeros(1,1,Qa,Qa);
   RB_Eval.ApT_X_Cq = zeros(1,Qa,Qf);
   RB_Eval.CpT_X_Aq = zeros(1,Qf,Qa);
   RB_Eval.CpT_X_Mq = zeros(1,Qf,Qm);

   RB_Eval.CpT_X_Cq = zeros(Qf,Qf);
   
   RB_Con.Mq_representors = cell(1,1);
   RB_Con.Aq_representors = cell(1,1);

   qf_min = min(cell2mat(keys(RB_Con.Fq_vec_map)));
   curN = RB_Con.N_FE;
   X_curN_ichol = ichol(RB_Con.X_curN);

   RB_Con.Fq_representors = zeros(curN,Qf);
   for qf = 1:Qf
     [RB_Con.Fq_representors(:,qf),flag] = pcg(RB_Con.X_curN,RB_Con.Fq_vec_map(qf_min - 1 + qf),RB_Con.l_rel_tol,RB_Con.l_max_its,X_curN_ichol,X_curN_ichol');
   end
   time_init_riesz = toc(time_init_riesz_begin);
   fprintf(1,'Time to initialize Riesz representors: %f minutes\n',time_init_riesz/60.0);
end
