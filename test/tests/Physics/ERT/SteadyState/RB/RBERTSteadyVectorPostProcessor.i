[Mesh]
  file = ../../../../Meshes/RB_mesh_3layers.e
[]

[Variables]
  [./potential]
  [../]
[]

[GlobalParams]
  variable = potential
  initial_rb_userobject = initializeRBSystem
[]

[Kernels]
  [./PotentialKernel]
    type = DwarfElephantRBDiffusion
  [../]
[]

[DiracKernels]
  [./InputElectrode_pos]
    type = DwarfElephantRBConstantPointSource
    value = 0.1
    point = '0.5 0.45 0.95'
  [../]
  [./InputElectrode_neg]
    type = DwarfElephantRBConstantPointSource
    value = -0.1
    point = '0.5 0.55 0.95'
  [../]
[]

[BCs]
  [./Dirichlet]
    type = DwarfElephantRBDirichletBC
    boundary = 2
    value = 0
  [../]
[]

[UserObjects]
  [./initializeRBSystem]
    type = TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O21Inverse
    execute_on = 'initial'
    N_max = 100
    n_training_samples = 300
    rel_training_tolerance = 1.e-4
    parameter_names = 'mu_0 mu_1 mu_2'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
    parameter_min_values = '0.125 0.5 0.026'
    parameter_max_values = '0.375 1.5 0.081'
    normalize_rb_bound_in_greedy = true
    training_parameters_random_seed = 400
  [../]
  [./potential_electrodes]
    type = DwarfElephantRBFilePointValues
    execute_on = 'timestep_end'
    file = '../../coordinates.csv'
  [../]
  [./performRBSystem]
    type = TestDwarfElephantOfflineOnlineStageSteadyStateT3A3F1O21Inverse
    online_mu = '0.25 1.0 0.05357142857142857' # resistivity divided by reference value of 280 Ohm m
    execute_on = 'timestep_end'
    offline_data_name = 'offline_data_0'
    output_console = true
    n_outputs = 21
  [../]
[]

[Executioner]
  type = DwarfElephantRBExecutioner
  solve_type = 'Newton'
  l_tol = 1.0e-08
  nl_rel_tol = 1.0e-08
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value =  'hypre boomeramg 101'
[]

[Problem]
  type = DwarfElephantRBProblem
[]

[Outputs]
perf_graph = true
exodus = true
execute_on = 'TIMESTEP_END'
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
