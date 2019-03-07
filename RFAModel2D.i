[Mesh]
 file = RFAGeom2D_L1_r3e-1_l6e-1.msh
[]

[Variables]
  [./temperature]
    order = FIRST
    TYPE = LAGRANGE
  [../]
[]

[AuxVariables]
  [./HeatSourceVis]
    order = FIRST
    type = LAGRANGE
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]
[Kernels]
[./DiffusionXX_maxZ1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 0
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 1
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 2
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 3
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 4
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 5
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 6
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 7
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 8
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 9
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 10
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 11
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 12
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 13
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 14
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 15
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 16
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 17
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 18
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 19
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 20
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 21
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 22
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 23
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 24
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 25
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 26
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 27
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 28
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 29
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 30
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 31
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_BoundingBox]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 32
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_BoundingBox]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 33
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./PennesPerfusion_BoundingBox]
  type = DwarfElephantRBPennesPerfusion
  ID_Aq = 34
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./EIMF]
  type = DwarfElephantEIMFKernel
[../]

[./RB_inner_product_matrix]
  type = RBInnerProductMatrix
[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'gaussian'#'rf_heat_source'
    variable = HeatSourceVis
    execute_on = 'timestep_end'
  [../]
[]

[Functions]
  [./gaussian]
    type = ParsedFunction
    value = 'exp(-(x + 0.1)^2 - (y + 0.1)^2)'
  [../]
[]
[BCs]
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = ' 11 12 13 14'
ID_Aq = 35
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
  #offline_stage = false
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = true
  N_max_EIM = 60
  n_training_samples_EIM = 256
  rel_training_tolerance_EIM = 1e-8
  abs_training_tolerance_EIM = 1e-8
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.1 0.2 -1 -1'# 0.01'
  parameter_max_values_EIM = '0.5 1.0 -0.1 -0.1'# 1.0'
  #parameter_names_EIM = 'mu_0 mu_1'
  #parameter_min_values_EIM = '-1 -1'
  #parameter_max_values_EIM = '-0.01 -0.01'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 50
  #offline_stage = false
  n_training_samples_RB = 128
  rel_training_tolerance_RB = 1.e-6
  abs_training_tolerance_RB = 1e-6
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.1 0.2 -1. -1.'
  parameter_max_values_RB = '0.5 1.0 -0.1 -0.1'
  #parameter_names_RB = 'mu_0 mu_1'
  #parameter_min_values_RB = '-1 -1'
  #parameter_max_values_RB = '-0.01 -0.01'
  deterministic_training_RB = false
  normalize_rb_bound_in_greedy = false
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_mu = '0.3 0.6 -0.6 -0.3'
  online_N = 30
  #offline_stage = false
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
