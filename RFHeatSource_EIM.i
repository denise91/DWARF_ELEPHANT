[Mesh]
 #file = RFAGeom2D_L1e-1_r3e-2_l6e-2.msh
 type = GeneratedMesh
 nx = 110
 ny = 110
 xmin = -0.05
 xmax = 0.05
 ymin = -0.05
 ymax = 0.05
 dim = 2
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./HeatSource_EIM]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]

[Kernels]
  [./DiffusionXX_maxZ1]
    type = DwarfElephantRBDiffusion
    ID_Aq = 0
    #block = 1
    matrix_seperation_according_to_subdomains = false
  [../]

  #[./PennesPerfusion_BoundingBox]
  #  type = DwarfElephantRBPennesPerfusion
  #  ID_Aq = 1
  #  block = 9
  #  matrix_seperation_according_to_subdomains = false
  #[../]

  #[./HeatSource]
  #  type = DwarfElephantRBRFHeatsourceKernel
  #  ID_Fq = 0
  #  heat_source_function = gaussian
  #[../]

  [./EIMF]
   type = DwarfElephantEIMFKernel
  [../]

  #[./RB_inner_product_matrix]
  #  type = RBInnerProductMatrix
  #[../]
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
  boundary = 'left right'# top bottom'#'11 12 13 14'
  ID_Aq = 1#2
  value = 0
  penalty = 6.0
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
  #offline_stage = false # comment this line out in case you are testing hp EIM
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  RB_RFA = true
  use_EIM = true
  use_hp_EIM = false#true
  #hp_EIM_testing = true #only use during the online phase
  #offline_stage = false
  N_max_EIM = 200
  n_training_samples_EIM = 120
  rel_training_tolerance_EIM = 1e-2
  #abs_training_tolerance_EIM = 1e-8
  parameter_names_EIM = 'mu_0 mu_1 mu_2' #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0 -0.0 -0.262'# -0.05 0.'
  parameter_max_values_EIM = '0.01 0.01 0.262'# 0.05 3.14'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 20
  n_training_samples_RB = 50
  rel_training_tolerance_RB = 1e-2
  #abs_training_tolerance_RB = 1e-6
  parameter_names_RB = 'mu_0 mu_1 mu_2' #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0 -0.0 -0.262'# 3.14e-3'# -0.05 0.'
  parameter_max_values_RB = '0.01 0.01 0.262'# 3.14e-3'# 0.05 3.14'
  deterministic_training_RB = false
  normalize_rb_bound_in_greedy = true
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  execute_on = "EIM"
  variable = temperature
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_mu = '0.005 0.002 0.19'# 2.0'# -0.021 0.1'
  online_N = 20
  #offline_stage = false
  execute_on = 'timestep_end'
  mesh_num = 0
  vec_file_location = ""
  param_str = ''
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
