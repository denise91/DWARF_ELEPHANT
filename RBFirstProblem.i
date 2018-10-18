[Mesh]
 file = RB_mesh_3layers.e
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
  [./RB_inner_product_matrix]
    type = RBInnerProductMatrix
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
  type = DwarfElephantInitializeRBSystemSteadyState
  execute_on = 'initial'
  N_max_RB = 20
  n_training_samples_RB = 100
  rel_training_tolerance_RB = 1.e-5
  parameter_names_RB = 'mu_0 mu_1 mu_2'    #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '1.0 1.0 1.0'
  parameter_max_values_RB = '5.15 7.15 5.15'
  normalize_rb_bound_in_greedy_RB = false
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  online_mu = '1.05 2.5 1.05'
  online_N = 20
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
