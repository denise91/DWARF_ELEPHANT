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
  simulation_type = transient
[]

[Kernels]
  [./Condcution]
    type = DwarfElephantRBDiffusion
  [../]
  [./Lifting0]
    type = DwarfElephantRBLiftingFunctionKernel
    lifting_function = liftingFunction
    matrix_seperation_according_to_subdomains = false
    ID_Aq = 0
    ID_Fq = 0
    block = 1
  [../]
  [./Lifting1]
    type = DwarfElephantRBLiftingFunctionKernel
    lifting_function = liftingFunction
    matrix_seperation_according_to_subdomains = false
    ID_Aq = 1
    ID_Fq = 1
    block = 2
  [../]
  [./Lifting2]
    type = DwarfElephantRBLiftingFunctionKernel
    lifting_function = liftingFunction
    matrix_seperation_according_to_subdomains = false
    ID_Aq = 2
    ID_Fq = 2
    block = 3
  [../]
  [./Storage]
    type = DwarfElephantRBConstantSpecificStorage
    specific_storage = 1.6e2
  [../]
[]

[DiracKernels]
  [./Produktion]
    type = DwarfElephantRBPointSource
    point = '0.5 0.5 0.5'
    ID_Fq = 3
    sink = true
  [../]
[]

[Functions]
  [./liftingFunction]
    type = SolutionFunction
    solution = liftingFunctionUserobject
  [../]
[]

[BCs]
[./RBleft]
  type = DwarfElephantRBDirichletBC
  boundary = '3 4 5 6 7 8'
  value = 0.00
  ID_Fq = '0 1 2'
  ID_Aq = '0 1 2'
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
  type = TestDwarfElephantInitializeRBSystemTransientT4A3F4O1M1
  execute_on = 'initial'
  N_max = 100
  n_training_samples = 100
  rel_training_tolerance = 1.e-3
  n_time_steps = 20
  delta_t = 10
  euler_theta = 1
  parameter_names = 'mu_0 mu_1 mu_2 mu_3'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values = '1.0e-3 0.1 1.0e-3 0.01'
  parameter_max_values = '1.0e-1 10 1.0e-1 0.03'
  normalize_rb_bound_in_greedy = true
  training_parameters_random_seed = 200
[../]
[./liftingFunctionUserobject]
  type = SolutionUserObject
  mesh = LiftingFunction_out.e
  timestep = LATEST
  execute_on = initial
[../]
[./performRBSystem]
  type = TestDwarfElephantOfflineOnlineStageTransientT4A3F4O1M1
  online_mu = '1.0e-2 1 1.0e-2 0.02'
  execute_on = 'timestep_end'
  output_console = false
  output_file = true
[../]
[]

[VectorPostprocessors]
  [./reverseLiftingFunction]
    type = DwarfElephantReverseLiftingFunctionAndDimensionalize
    dimensionalize = false
    reverse_lifting_function = true
    lifting_function = liftingFunction
    unique_node_execute = true
    execute_on = 'custom'
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
