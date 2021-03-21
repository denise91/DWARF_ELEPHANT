function [RB_Eval] = compute_EIM_theta_objects(mu,RB_Eval,EIM_data)
  time_compute_EIM_thetas_begin = tic;
  g = evaluate_non_affine_function(mu,EIM_data);
  eim_theta_vec = EIM_data.B_matrix \ g';
  
  L = mu('L');
  r = mu('r');
  l = mu('l');
  r_0 = mu('r_0');
  l_0 = mu('l_0');
  d = mu('d');
  h = mu('h');
  
  num_subdomains = EIM_data.num_subdomains;
  matrix_cell_array = cell(32,1);
  %vec_cell_array = cell(32,1);
    %if (interpolation_points_subdomains==1)
      matrix_cell_array{1} = [1 0 -(d*(r - r_0))/(r*(L - h)); 0 1 (d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{1} = [(L*d*(r - r_0))/(2*r*(L - h)); -(L*d*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==2)
      matrix_cell_array{2} = [1 0 (d*(r - r_0))/(r*(L - h)); 0 1 -(d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{2} = [-(L*d*(r - r_0))/(2*r*(L - h)); (L*d*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==3)
      matrix_cell_array{3} = [r_0/r 0 (L*(r - r_0))/(r*(L - h)); 0 r_0/r (L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{3} = [-(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==4)
      matrix_cell_array{4} = [r_0/r 0 -(L*(r - r_0))/(r*(L - h)); 0 r_0/r -(L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{4} = [(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==5)
      matrix_cell_array{5} = [(r + r_0)/(2*r) (r - r_0)/(2*r) 0; (r - r_0)/(2*r) (r + r_0)/(2*r) 0; 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{5} = [0; 0; -(L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==6)
      matrix_cell_array{6} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(d*(r - r_0))/(r*(L - d)) 1 0; -(h*(l - l_0))/(l*(L - d)) 0 1];
      %vec_cell_array{6} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==7)
      matrix_cell_array{7} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (d*(r - r_0))/(r*(L - d)) 1 0; (h*(l - l_0))/(l*(L - d)) 0 1];
      %vec_cell_array{7} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==8)
      matrix_cell_array{8} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (L*(r - r_0))/(r*(L - d)) r_0/r 0; -(L*(l - l_0))/(l*(L - d)) 0 l_0/l];
      %vec_cell_array{8} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==9)
      matrix_cell_array{9} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(L*(r - r_0))/(r*(L - d)) r_0/r 0; (L*(l - l_0))/(l*(L - d)) 0 l_0/l];
      %vec_cell_array{9} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==10)
      matrix_cell_array{10} = [(L*r - d*r_0)/(r*(L - d)) 0 0; 0 (d*r_0 + h*r)/(r*(d + h)) -(d*(r - r_0))/(r*(d + h)); 0 -(h*(l - l_0))/(l*(d + h)) (d*l + h*l_0)/(l*(d + h))];
      %vec_cell_array{10} = [(L*d*(r - r_0))/(2*r*(L - d)); 0; 0];
    %end 

    %if (interpolation_points_subdomains==11)
      matrix_cell_array{11} = [1 -(d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (h*(l - l_0))/(l*(L - d)) 1];
      %vec_cell_array{11} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==12)
      matrix_cell_array{12} = [1 (d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(h*(l - l_0))/(l*(L - d)) 1];
      %vec_cell_array{12} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==13)
      matrix_cell_array{13} = [r_0/r (L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (L*(l - l_0))/(l*(L - d)) l_0/l];
      %vec_cell_array{13} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==14)
      matrix_cell_array{14} = [r_0/r -(L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(L*(l - l_0))/(l*(L - d)) l_0/l];
      %vec_cell_array{14} = [(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==15)
      matrix_cell_array{15} = [(d*r_0 + h*r)/(r*(d + h)) 0 (d*(r - r_0))/(r*(d + h)); 0 (L*r - d*r_0)/(r*(L - d)) 0; (h*(l - l_0))/(l*(d + h)) 0 (d*l + h*l_0)/(l*(d + h))];
      %vec_cell_array{15} = [0; -(L*d*(r - r_0))/(2*r*(L - d)); 0];
    %end 

    %if (interpolation_points_subdomains==16)
      matrix_cell_array{16} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(d*(r - r_0))/(r*(L - d)) 1 0; (h*(l - l_0))/(l*(L - d)) 0 1];
      %vec_cell_array{16} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==17)
      matrix_cell_array{17} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (d*(r - r_0))/(r*(L - d)) 1 0; -(h*(l - l_0))/(l*(L - d)) 0 1];
      %vec_cell_array{17} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==18)
      matrix_cell_array{18} = [(L*r - d*r_0)/(r*(L - d)) 0 0; (L*(r - r_0))/(r*(L - d)) r_0/r 0; (L*(l - l_0))/(l*(L - d)) 0 l_0/l];
      %vec_cell_array{18} = [-(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==19)
      matrix_cell_array{19} = [(L*r - d*r_0)/(r*(L - d)) 0 0; -(L*(r - r_0))/(r*(L - d)) r_0/r 0; -(L*(l - l_0))/(l*(L - d)) 0 l_0/l];
      %vec_cell_array{19} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==20)
      matrix_cell_array{20} = [(L*r - d*r_0)/(r*(L - d)) 0 0; 0 (d*r_0 + h*r)/(r*(d + h)) (d*(r - r_0))/(r*(d + h)); 0 (h*(l - l_0))/(l*(d + h)) (d*l + h*l_0)/(l*(d + h))];
      %vec_cell_array{20} = [-(L*d*(r - r_0))/(2*r*(L - d)); 0; 0];
    %end 

    %if (interpolation_points_subdomains==21)
      matrix_cell_array{21} = [1 -(d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(h*(l - l_0))/(l*(L - d)) 1];
      %vec_cell_array{21} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==22)
      matrix_cell_array{22} = [1 (d*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (h*(l - l_0))/(l*(L - d)) 1];
      %vec_cell_array{22} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*h*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==23)
      matrix_cell_array{23} = [r_0/r -(L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 (L*(l - l_0))/(l*(L - d)) l_0/l];
      %vec_cell_array{23} = [-(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); (L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==24)
       matrix_cell_array{24} = [r_0/r (L*(r - r_0))/(r*(L - d)) 0; 0 (L*r - d*r_0)/(r*(L - d)) 0; 0 -(L*(l - l_0))/(l*(L - d)) l_0/l];
      %vec_cell_array{24} = [(L*d*(r - r_0))/(2*r*(L - d)); (L*d*(r - r_0))/(2*r*(L - d)); -(L*d*(l - l_0))/(2*l*(L - d))];
    %end 

    %if (interpolation_points_subdomains==25)
      matrix_cell_array{25} = [(d*r_0 + h*r)/(r*(d + h)) 0 -(d*(r - r_0))/(r*(d + h)); 0 (L*r - d*r_0)/(r*(L - d)) 0; -(h*(l - l_0))/(l*(d + h)) 0 (d*l + h*l_0)/(l*(d + h))];
      %vec_cell_array{25} = [0; (L*d*(r - r_0))/(2*r*(L - d)); 0];
    %end 

    %if (interpolation_points_subdomains==26)
      matrix_cell_array{26} = [1 0 (d*(r - r_0))/(r*(L - h)); 0 1 (d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{26} = [(L*d*(r - r_0))/(2*r*(L - h)); (L*d*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==27)
      matrix_cell_array{27} = [1 0 -(d*(r - r_0))/(r*(L - h)); 0 1 -(d*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{27} = [-(L*d*(r - r_0))/(2*r*(L - h)); -(L*d*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==28)
      matrix_cell_array{28} = [r_0/r 0 (L*(r - r_0))/(r*(L - h)); 0 r_0/r -(L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{28} = [(L*h*(r - r_0))/(2*r*(L - h)); -(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==29)
      matrix_cell_array{29} = [r_0/r 0 -(L*(r - r_0))/(r*(L - h)); 0 r_0/r (L*(r - r_0))/(r*(L - h)); 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{29} = [-(L*h*(r - r_0))/(2*r*(L - h)); (L*h*(r - r_0))/(2*r*(L - h)); (L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==30)
      matrix_cell_array{30} = [(r + r_0)/(2*r) -(r - r_0)/(2*r) 0; -(r - r_0)/(2*r) (r + r_0)/(2*r) 0; 0 0 (L*l - h*l_0)/(l*(L - h))];
      %vec_cell_array{30} = [0; 0; (L*h*(l - l_0))/(2*l*(L - h))];
    %end 

    %if (interpolation_points_subdomains==31)
      matrix_cell_array{31} = [r_0/r 0 0; 0 r_0/r 0; 0 0 l_0/l];
      %vec_cell_array{31} = [0; 0; 0];
    %end 

    %if (interpolation_points_subdomains==32)
      matrix_cell_array{32} = [r_0/r 0 0; 0 r_0/r 0; 0 0 l_0/l];
      %vec_cell_array{32} = [0; 0; 0];
    %end
  q_begin = RB_Eval.EIM_qf_begin;
  for n = 1:num_subdomains
    for m = 1:EIM_data.M
      RB_Eval.RB_F_Theta_map(q_begin + m - 1 + (n - 1)*EIM_data.M) = @(mu) eim_theta_vec(m)*abs(det(matrix_cell_array{n}));%;
    end
  end
  time_compute_EIM_thetas = toc(time_compute_EIM_thetas_begin);
  fprintf(1,'Time to compute EIM thetas: %f minutes\n',time_compute_EIM_thetas/60.0);
end
