[Mesh]
 #file = libMesh_EIM_example_mesh2.msh
 type = GeneratedMesh
 dim = 2
 xmin = 0
 xmax = 1
 ymin = 0
 ymax = 1
 nx = 100
 ny = 100
[]

[Variables]
  [./temperature]
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]

[Kernels]
  [./RBConduction]
    type = DwarfElephantRBDiffusion
  [../]
  
  #[./EIMF]
  #  type = DwarfElephantEIMFKernel
  #[../]

  #[./EIMA] # For EIM example in Martin's publication
  #  type = DwarfElephantEIMAKernel
  #[../]

[./HeatSource_4]
  type = DwarfElephantRBRFHeatsourceKernel
  variable = temperature
  heat_source_function = constantFunction
[../]

  [./RB_inner_product_matrix]
    type = RBInnerProductMatrix
  [../]
[]

[BCs] # To be changed
[./top]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = top
  value = 0.00
  penalty = 6
[../]

[./bottom]
  type = DwarfElephantRBNeumannBC
  boundary = bottom
  value = 2
[../]

[./left]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = left
penalty = 6
  value = 0.00
[../]

[./right]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = right
penalty = 6
  value = 0.00
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
[]

[Functions]
  #[./rf_heat_source]
  #  type = DwarfElephantRFHeatsourceFunction
  #  needle_active_region_p1 = '0 0 0.01'
  #  needle_active_region_p2 = '0 0 -0.01'
  #  needle_power = 1.0
  #[../]
  #[./test_heat_source]
  #  type = ParsedFunction
  #  value = '100'#exp(-x^2 - y^2)'
  #[../]
  [./constantFunction]
    type = ParsedFunction
    value = '10000*exp(-x^2 - y^2)'
  [../]
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = false
  execute_on = 'initial'
  normalize_rb_bound_in_greedy = true
  n_training_samples_RB = 225
  N_max_RB = 20
  rel_training_tolerance_RB = 1e-8
  parameter_names_RB = 'mu_0'
  parameter_min_values_RB = '0.1'
  parameter_max_values_RB = '0.9'
  deterministic_training_RB = false
  #offline_stage = false
[../]

#[./jEIMInnerProductMatrixComputation]
#  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
#  execute_on = "EIM"
# initialize_rb_userobject = initializeRBSystem
#../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_N = 20
  online_mu = '0.5'
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
