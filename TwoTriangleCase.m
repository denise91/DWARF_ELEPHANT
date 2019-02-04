clear all
clc

syms L
syms l
syms r
syms l_new
syms r_new

new_coords = [-L/2; L/2; r_new; l_new/2; L/2; L/2];
old_coords_mat = [-L/2  L/2   0    0   1 0;
                    0    0  -L/2  L/2  0 1;
                    r   l/2   0    0   1 0;
                    0    0    r   l/2  0 1;
                   L/2  L/2   0    0   1 0;
                    0    0   L/2  L/2  0 1;];

trafo_mat_coeffs = old_coords_mat \ new_coords

trafo_mat = [trafo_mat_coeffs(1) trafo_mat_coeffs(2);
             trafo_mat_coeffs(3) trafo_mat_coeffs(4)];

Jacobian = det(trafo_mat);

inv_trafo_mat = inv(trafo_mat);
inv_trafo_mat_transpose(1,1) = inv_trafo_mat(1,1);
inv_trafo_mat_transpose(1,2) = inv_trafo_mat(2,1);
inv_trafo_mat_transpose(2,1) = inv_trafo_mat(1,2);
inv_trafo_mat_transpose(2,2) = inv_trafo_mat(2,2);

disp("inv_trafo_mat * trafo_mat");
simplify(inv_trafo_mat * trafo_mat)

disp("Theta objects");
for j = 1:2
    for k = 1:2
        disp("Theta_"+int2str(j)+int2str(k)+"=")
        theta_objects = 0;
        for i = 1:2
            theta_objects = theta_objects + abs(Jacobian) * inv_trafo_mat(j,i) * inv_trafo_mat_transpose(i,k);
        end
        ccode(theta_objects)
    end
end

surface_theta = ccode(simplify(sqrt(simplify(trafo_mat(1,1)^2 + trafo_mat(2,1)^2))))
disp("Transformed triangle vertices");
simplify(trafo_mat * [-L/2; L/2] + [trafo_mat_coeffs(5); trafo_mat_coeffs(6)])
simplify(trafo_mat * [r; l/2] + [trafo_mat_coeffs(5); trafo_mat_coeffs(6)])
simplify(trafo_mat * [L/2; L/2] + [trafo_mat_coeffs(5); trafo_mat_coeffs(6)])
