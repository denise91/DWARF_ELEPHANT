[Mesh]
 file = RBnicsGeom_test.msh#ReducedBasisGeom2D_test.msh
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
[./DiffusionXX_1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 1
  block = 1
[../]
[./DiffusionXY_1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 2
  block = 1
[../]
[./DiffusionYX_1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 3
  block = 1
[../]
[./DiffusionYY_1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 4
  block = 1
[../]

[./DiffusionXX_2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 5
  block = 2
[../]
[./DiffusionXY_2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 6
  block = 2
[../]
[./DiffusionYX_2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 7
  block = 2
[../]
[./DiffusionYY_2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 8
  block = 2
[../]

[./EIMF]
  type = DwarfElephantEIMFKernel
  ID_Fq = 1
[../]

[./RB_inner_product_matrix]
  type = RBInnerProductMatrix
[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'constantFunction'#'rf_heat_source'
    variable = HeatSourceVis
    execute_on = 'timestep_end'
  [../]
[]

[Functions]
  [./constantFunction]
    type = ParsedFunction
    value = '10000'
  [../]
[]

[BCs]
[./HeatFlux_BC1]
  type = DwarfElephantRBNeumannBC
  boundary = '15' 
  ID_Fq = 0
  value = 1.0 # positive for heat flow into the domain and negative for heat flow outside the domain
  variable = temperature
[../]

[./Outer_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = '11' 
  ID_Aq = 0
  penalty = 1.0
  value = 0.0
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
  offline_stage = false
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = true
  N_max_EIM = 48
  n_training_samples_EIM = 625
  rel_training_tolerance_EIM = 1e-8
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.8 1.6 -2 1'# 0.01'
  parameter_max_values_EIM = '1.2 2.4 2 2.'# 1.0'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 20
  offline_stage = false
  n_training_samples_RB = 64
  rel_training_tolerance_RB = 1.e-5
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.8 1.6 -2 1'# 0.01'
  parameter_max_values_RB = '1.2 2.4 2 2.'# 1.0'
  normalize_rb_bound_in_greedy = false
  deterministic_training_RB = false
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  online_stage = true
  online_mu = '1 2 0 1.5'
  online_N = 20
  offline_stage = false
  execute_on = 'timestep_end'
[../]
[]

[Outputs]
exodus = true
# csv = true   # only required for the PostProcessors
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
