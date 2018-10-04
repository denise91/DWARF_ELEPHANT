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
  
  [./EIMF]
    type = DwarfElephantEIMFKernel
  [../]

  [./EIMA] # For EIM example in Martin's publication
    type = DwarfElephantEIMAKernel
  [../]

  [./RB_inner_product_matrix]
    type = RBInnerProductMatrix
  [../]
[]

[BCs] # To be changed
[./top]
  type = DwarfElephantRBDirichletBC
  boundary = top
  value = 0.00
[../]

[./bottom]
  type = DwarfElephantRBDirichletBC
  boundary = bottom
  value = 0
[../]

[./left]
  type = DwarfElephantRBDirichletBC
  boundary = left
  value = 0.00
[../]

[./right]
  type = DwarfElephantRBDirichletBC
  boundary = right
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

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = true
  execute_on = 'initial'
  N_max_EIM = 48
  n_training_samples_EIM = 225
  rel_training_tolerance_EIM = 1e-8
  parameter_names_EIM = 'mu_0 mu_1'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '-1 -1'
  parameter_max_values_EIM = '-0.01 -0.01'
  deterministic_training_EIM = true
  best_fit_type_EIM = projection
  n_training_samples_RB = 225
  N_max_RB = 20
  rel_training_tolerance_RB = 1e-8
  parameter_names_RB = 'mu_0 mu_1'
  parameter_min_values_RB = '-1.0 -1.0'
  parameter_max_values_RB = '-0.01 -0.01'
  deterministic_training_RB = true
  #offline_stage = false
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_N = 20
  online_mu = '-0.43241 -0.63241'
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
