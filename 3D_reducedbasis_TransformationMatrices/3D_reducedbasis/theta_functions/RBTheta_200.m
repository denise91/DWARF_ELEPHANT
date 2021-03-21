function out1 = RBTheta_200(mu)
%RBTHETA_200
%    OUT1 = RBTHETA_200(L,D,H,K_T,L,L_0,R,R_0)

%    This function was generated by the Symbolic Math Toolbox version 8.3.
%    02-Nov-2020 12:33:12
rho_C_t = mu("rho_C_t");
rho_C_b = mu("rho_C_b");
k_b = mu("k_b");
k_t = mu("k_t");
h = mu("h");
d = mu("d");
l_0 = mu("l_0");
r_0 = mu("r_0");
l = mu("l");
r = mu("r");
L = mu("L");

t2 = d.*l.*r_0;
t3 = h.*l_0.*r;
t4 = t2+t3;
t5 = 1.0./t4.^2;
out1 = (k_t.*1.0./abs(r).^2.*abs(t4.*(L.*r-d.*r_0)).*(r.^2.*t5.*(d.*l+h.*l_0).^2+d.^2.*l.^2.*t5.*(r-r_0).^2))./(abs(d+h).*abs(l).*abs(L-d));