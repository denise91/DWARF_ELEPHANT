addpath(strcat('/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/mesh',int2str(0)));
 
Qm = 31;
 disp("Reading Matrices")
 % load Mq matrices
 Mq_mat_cell = cell(Qm+1,1);
 for q_m = 0:Qm %For loop can be parallelized
    run(strcat('Mq_',int2str(q_m)));
    Mq_mat_cell{q_m+1} = eval([strcat('Mq_',int2str(q_m),'_sp')]);
    eval(strcat('clear Mq_',int2str(q_m),'_sp'));
    eval(strcat('clear Mq_',int2str(q_m),'_nz'));
 end
