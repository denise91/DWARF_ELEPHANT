[Mesh]
  file = FourSquare.msh
[]

[Variables]
  [./temperature]
    order = FIRST
    TYPE = LAGRANGE
  [../]
[]

[AuxVariables]
  [./HeatSource_EIM]
    order = FIRST
    type = LAGRANGE
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]

[Kernels]
  [./Diffusion]
    type = DwarfElephantRBDiffusion
    ID_Aq = 0
    matrix_seperation_according_to_subdomains = false
  [../]

  [./EIMF]
   type = DwarfElephantEIMFKernel
  [../]
[]

[Functions]
  [./gaussian]
    type = ParsedFunction
    value = 'exp(-(x-0.5)^2 -(y-0.5)^2)'
  [../]
[]

[BCs]
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = '1 2 3 4 5 6 7 8'
  ID_Aq = 0
  value = 0
  penalty = 1.0
  variable = temperature
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
  offline_stage = false # comment this line out in case you are testing hp EIM
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = true
  use_hp_EIM = false#true
  #hp_EIM_testing = true #only use during the online phase
  offline_stage = false
  N_max_EIM = 30
  n_training_samples_EIM = 120
  rel_training_tolerance_EIM = 1e-10
  #abs_training_tolerance_EIM = 1e-8
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3' #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '-10 10 -10 10'
  parameter_max_values_EIM = '-1 50 -1 50'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 20
  n_training_samples_RB = 100
  rel_training_tolerance_RB = 1e-2
  #abs_training_tolerance_RB = 1e-6
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3' #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '-10 10 -10 10'
  parameter_max_values_RB = '-1 50 -1 50'
  deterministic_training_RB = false
  normalize_rb_bound_in_greedy = true
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  online_stage = true
  online_mu = '-5 20 -5 20'
  online_N = 4
  offline_stage = false
  execute_on = 'timestep_end'
[../]
[]

[Outputs]
exodus = true
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
