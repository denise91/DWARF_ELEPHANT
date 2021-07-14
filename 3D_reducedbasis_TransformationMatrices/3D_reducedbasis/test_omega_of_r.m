omega_data = [56.43 1.6295547198e+02 140.0 121.0 110.0 100.33 110.47 109.86 107.78  5.7109357378e+01];
r_data = [0.00055 0.00070287 0.00089823 0.00114789 0.00146693 0.00187466 0.00239571 0.00306158 0.00391253 0.005];

r_cont = linspace(0.55,5,1000);
omega_cont = zeros(1,1000);
for i = 1:1000
   omega_cont(i) = omega_of_r_final(r_cont(i));
end

plot(r_data,omega_data,"r");
hold on
plot(r_cont,omega_cont,"b");
