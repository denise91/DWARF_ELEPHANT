[Mesh]
 file = ../../../../Meshes/RB_mesh_3layers.e
[]

[Variables]
  [./temperature]
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
  simulation_type = transient
[]

[Kernels]
  [./Condcution]
    type = DwarfElephantRBDiffusion
  [../]
  [./Euler]
    type = DwarfElephantRBTimeDerivative
  [../]
[]

[BCs]
[./top]
  type = DwarfElephantRBRobinBC
  alpha = 0.95
  boundary = 2
  value = -1
  ID_Aq = 3
  matrix_seperation_according_to_subdomains = false
[../]

[./bottom]
  type = DwarfElephantRBDirichletBC
  boundary = 1
  value = 0.0
  matrix_seperation_according_to_subdomains = false
[../]
[]

[Problem]
  type = DwarfElephantRBProblem
[]

[Executioner]
  type = DwarfElephantRBExecutioner
  solve_type = 'Newton'
  l_tol = 1.0e-8
  nl_rel_tol = 1.0e-8
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre boomeramg 101'
[]

[UserObjects]
[./initializeRBSystem]
  type = TestDwarfElephantInitializeRBSystemTransientT3A4F1O1M1
  execute_on = 'initial'
  N_max = 100
  n_training_samples = 100
  rel_training_tolerance = 1.e-5
  n_time_steps = 5
  delta_t = 1
  euler_theta = 1
  parameter_names = 'mu_0 mu_1 mu_2'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values = '1.7e-2 4.2e-2 1.55e-2'
  parameter_max_values = '5.1e-2 1.26e-1 4.65e-2'
  normalize_rb_bound_in_greedy = true
  training_parameters_random_seed = 200
[../]
[./performRBSystem]
  type = TestDwarfElephantOfflineOnlineStageTransientT3A4F1O1M1
  online_mu = '3.4e-2 8.4e-2 3.1e-2'
  execute_on = 'timestep_end'
  output_console = false
  output_file = true
[../]
[]

[Outputs]
execute_on = timestep_end
exodus = true
perf_graph = true
  [./Console]
      type = Console
      outlier_variable_norms = false
  [../]
[]
