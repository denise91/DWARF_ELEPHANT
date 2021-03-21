function [tissue_damage,survival_fraction] = compute_Arrhenius_tissue_damage(T_mu,dt,A,E_a,k)
% Compute Arrhenius tissue damage
%   Input:
%   T_mu : temperature-time data (num_FE_nodes,num_time_steps)
%   dt : time step (scalar)
%   A : frequency factor (scalar)
%   E_a : activation energy (scalar)
%   k : boltzmann constant (scalar)

%   Output:
%   tissue_damage : tissue damage field (num_FE_nodes,1)
num_time_steps = length(T_mu(1,:));
num_FE_nodes = length(T_mu(:,1));
integral = zeros(num_FE_nodes,1);
for time_step = 1:num_time_steps
    integrand = -A.*exp(-E_a./(k.*(T_mu(:,time_step) + 310.15)));
    integral = integral + integrand*dt;
end
survival_fraction = exp(integral);


%tissue_damage = zeros(1,num_FE_nodes);
tissue_damage = 1 - heaviside(- exp(-1) + survival_fraction);
%for node = 1:num_FE_nodes
%   if (survival_fraction(node) < exp(-1))
%       tissue_damage(node) = 1;
%   end
%end


