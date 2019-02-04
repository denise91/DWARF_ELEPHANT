[Mesh]
 type = GeneratedMesh
 dim = 1
 xmin = -1
 xmax = 1
 nx = 30
 ny = 30
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
 [./Diffusion]
   type = DwarfElephantRBDiffusion
   ID_Aq = 1
   matrix_seperation_according_to_subdomains = false
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
  boundary = 'left' 
  ID_Fq = 0
  value = 1.0 # positive for heat flow into the domain and negative for heat flow outside the domain
  variable = temperature
[../]

[./Outer_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = 'right' 
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
  #offline_stage = false
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = true
  execute_on = 'initial'
  N_max_RB = 20
  #offline_stage = false
  n_training_samples_RB = 25
  rel_training_tolerance_RB = 1.e-5
  parameter_names_RB = 'mu_0 mu_1' # mu_0: domain half-length; mu_1 translation of heatsource #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.5'
  parameter_max_values_RB = '1.5'
  normalize_rb_bound_in_greedy = false
  deterministic_training_RB = true
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  online_stage = true
  online_mu = '1'
  online_N = 4
  execute_on = 'timestep_end'
[../]
[]

#[Postprocessors]
#  [./average]
#    type = ElementAverageValue
#    variable = temperature
#    execute_on = 'custom'
#  [../]
#[]

[Outputs]
exodus = true
# csv = true   # only required for the PostProcessors
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]

