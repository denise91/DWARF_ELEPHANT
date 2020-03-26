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
  [./Conduction]
    type = DwarfElephantRBDiffusion
  [../]
  [./RadiogenicHeat0]
    type = DwarfElephantRBConstantRadiogenicHeatProduction
    radiogenic_heat_production = 1.1295223250087538e-08
    block = 0
  [../]
  [./RadiogenicHeat1]
    type = DwarfElephantRBOneKernel
    ID_Fq = 1
    block = 1
  [../]
  [./RadiogenicHeat2]
    type = DwarfElephantRBOneKernel
    ID_Fq = 2
    block = 2
  [../]
  [./Euler]
    type = DwarfElephantRBTimeDerivative
  [../]
[]

[BCs]
[./top]
  type = DwarfElephantRBDirichletBC
  boundary = 2
  value = 0.00
  ID_Fq = '0 2'
[../]

[./bottom]
  type = DwarfElephantRBNeumannBC
  boundary = 1
  value = 0.0000016
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
  type = TestDwarfElephantInitializeRBSystemTransientT5A3F3O1M1
  execute_on = 'initial'
  N_max = 100
  n_training_samples = 100
  rel_training_tolerance = 1.e-5
  n_time_steps = 20
  delta_t = 100000
  euler_theta = 1
  parameter_names = 'mu_0 mu_1 mu_2 mu_3 mu_4'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values = '1.7e-7 4.2e-7 1.55e-7 0.0 1.57e-9'
  parameter_max_values = '5.1e-7 1.26e-6 4.65e-7 1.0e-9 4.7e-9'
  normalize_rb_bound_in_greedy = true
  training_parameters_random_seed = 200
[../]
[./performRBSystem]
  type = TestDwarfElephantOfflineOnlineStageTransientT5A3F3O1M1
  online_mu = '3.4e-7 8.4e-7 3.1e-7 0.0 3.1344621576383705e-09'
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
