function [mesh_conv_metric] = compute_mesh_conv_metric(T_mu,node_ids,inner_product_matrix,dt)
% Computes the time integral of the inner-product-norm of the temperature
% the inner-product-norm is computed at every time-step for the time
% integration
% Input:
% T_mu : the temperature-time data (num_FE_dofs,num_time_steps)
% node_ids : the ids of the nodes to be considered in the calcuation (num_nodes,1)
% (typically) the "relevant" region of the domain
% inner_product_matrix: inner product matrix (num_FE_dofs,num_FE_dofs)
% dt : time step
% Output:
% mesh_conv_metric: the time-average of the inner-product norm of the temperature in K (scalar)

num_time_steps = length(T_mu(1,:));
mesh_conv_metric = 0;

for i = 1:num_time_steps
    T_norm_t = sqrt(T_mu(:,i)'*inner_product_matrix*T_mu(:,i));
    mesh_conv_metric = mesh_conv_metric + T_norm_t*dt;
end
mesh_conv_metric = 310.15 + mesh_conv_metric / 540.;
end
