function [mu] = set_constant_params()
  mu = containers.Map('KeyType','char','ValueType','any');
  mu('L') = 0.1;
  mu('r') = 0.001414;
  mu('l') = 0.01871;
  mu('d') = (8.0/3.0)*mu('r');
  mu('h') = (4.0/3.0)*mu('l');
  mu('rho_C_t') = 3.82e6;
  mu('rho_C_b') = 3.798e6;
  mu('k_t') = 0.83;
  mu('k_b') = 0.52;
  %mu('omega_p') = 1e3;
end
