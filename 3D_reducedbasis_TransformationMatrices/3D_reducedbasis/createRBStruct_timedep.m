function [ RB_Eval ] = createRBStruct_timedep( Z, RB_Con, RB_Eval )
% Creates a structure containing RB matrices
%   Detailed explanation goes here
    Qm = RB_Con.Qm;
    Qa = RB_Con.Qa;
    Qf = RB_Con.Qf;
	
    qa_min = min(cell2mat(keys(RB_Con.Aq_mat_map))); 
    qm_min = min(cell2mat(keys(RB_Con.Mq_mat_map)));
    qf_min = min(cell2mat(keys(RB_Con.Fq_vec_map)));
	
    RB_Eval.MNq = cell(Qm,1);
    RB_Eval.ANq = cell(Qa,1);
    RB_Eval.FNq = cell(Qf,1);
	
	
    for q = 1:Qm
      RB_Eval.MNq{q} = Z'*RB_Con.Mq_mat_map(qm_min - 1 + q)*Z;
    end
	
    for q = 1:Qa
        RB_Eval.ANq{q} = Z'*RB_Con.Aq_mat_map(qa_min - 1 + q)*Z;
    end
	
    for q = 1:Qf
        RB_Eval.FNq{q} = Z'*RB_Con.Fq_vec_map(qf_min - 1 + q);
    end
    
    RB_Eval.Z = Z;
    RB_Eval.N = length(Z(1,:));
    RB_Eval.uN_init = Z'*RB_Con.u_init;
end

