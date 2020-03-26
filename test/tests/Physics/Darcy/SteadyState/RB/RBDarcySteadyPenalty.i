[Mesh]
 file = ../../../../Meshes/Darcy.msh
[]

[Variables]
  [./pressure]
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = pressure
[]

[Kernels]
  [./Condcution]
    type = DwarfElephantRBDiffusion
  [../]
[]

[BCs]
[./RBleft]
  type = DwarfElephantRBDirichletBC
  boundary = '3 4 5'
  value = 0.00
  ID_Aq = '0 1 2'
  matrix_seperation_according_to_subdomains = false
[../]
[./RBright]
  type = DwarfElephantRBPenaltyDirichletBC
  penalty = 2
  boundary = '6 7 8'
  value = 0.1
  ID_Aq = '3'
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
  type = TestDwarfElephantInitializeRBSystemSteadyStateT3A4F1O1
  execute_on = 'initial'
  N_max = 100
  n_training_samples = 100
  rel_training_tolerance = 1.e-3
  parameter_names = 'mu_0 mu_1 mu_2'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values = '1.0e-3 0.1 1.0e-3'
  parameter_max_values = '1.0e-1 10 1.0e-1'
  normalize_rb_bound_in_greedy = true
  training_parameters_random_seed = 200
[../]
[./performRBSystem]
  type = TestDwarfElephantOfflineOnlineStageSteadyStateT3A4F1O1
  online_mu = '1.0e-2 1 1.0e-2'
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
