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
[]

[Kernels]
  [./RBConduction]
    type = DwarfElephantRBDiffusion
  [../]
  [./RadiogenicHeat0]
    type = DwarfElephantRBConstantRadiogenicHeatProduction
    radiogenic_heat_production = 1.0e-06
    norm_value_radiogenic_heat_production = 3e-05
    block = 0
  [../]
  [./RadiogenicHeat1]
    type = DwarfElephantRBConstantRadiogenicHeatProduction
    radiogenic_heat_production = 0.0
    norm_value_radiogenic_heat_production = 3e-05
    block = 1
  [../]
  [./RadiogenicHeat2]
    type = DwarfElephantRBConstantRadiogenicHeatProduction
    radiogenic_heat_production = 0.3e-06
    norm_value_radiogenic_heat_production = 3e-05
    block = 2
  [../]
[]

[BCs]
[./top]
  type = DwarfElephantRBDirichletBC
  boundary = 2
  value = 0.00
[../]

[./bottom]
  type = DwarfElephantRBNeumannBC
  boundary = 1
  value = 3.71
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
[]

[UserObjects]
[./initializeRBSystem]
  type = TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O1
  execute_on = 'initial'
  N_max = 10
  n_training_samples = 20
  rel_training_tolerance = 1.e-5
  parameter_names = 'mu_0 mu_1 mu_2'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values = '1.0 1.0 1.0'
  parameter_max_values = '5.15 7.15 5.15'
  normalize_rb_bound_in_greedy = true
  training_parameters_random_seed = 200
[../]
[./performRBSystem]
  type = TestDwarfElephantOfflineOnlineStageSteadyStateT3A3F1O1
  online_mu = '1.0 2.38 1.0'
  execute_on = 'timestep_end'
[../]
[]

[Outputs]
execute_on = 'timestep_end'
perf_graph = true
exodus = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
