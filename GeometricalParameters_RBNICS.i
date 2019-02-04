[Mesh]
 file = RBNICSGeom_full.msh
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
[./DiffusionXX_3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 9
  block = 3
[../]
[./DiffusionXY_3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 10
  block = 3
[../]
[./DiffusionYX_3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 11
  block = 3
[../]
[./DiffusionYY_3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 12
  block = 3
[../]
[./DiffusionXX_4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 13
  block = 4
[../]
[./DiffusionXY_4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 14
  block = 4
[../]
[./DiffusionYX_4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 15
  block = 4
[../]
[./DiffusionYY_4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 16
  block = 4
[../]
[./DiffusionXX_5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 17
  block = 5
[../]
[./DiffusionXY_5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 18
  block = 5
[../]
[./DiffusionYX_5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 19
  block = 5
[../]
[./DiffusionYY_5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 20
  block = 5
[../]
[./DiffusionXX_6]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 21
  block = 6
[../]
[./DiffusionXY_6]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 22
  block = 6
[../]
[./DiffusionYX_6]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 23
  block = 6
[../]
[./DiffusionYY_6]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 24
  block = 6
[../]
[./DiffusionXX_7]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 25
  block = 7
[../]
[./DiffusionXY_7]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 26
  block = 7
[../]
[./DiffusionYX_7]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 27
  block = 7
[../]
[./DiffusionYY_7]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 28
  block = 7
[../]
[./DiffusionXX_8]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 29
  block = 8
[../]
[./DiffusionXY_8]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 30
  block = 8
[../]
[./DiffusionYX_8]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 31
  block = 8
[../]
[./DiffusionYY_8]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 32
  block = 8
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
[./HeatFlux_BC_0]
  type = DwarfElephantRBNeumannBC
  boundary = '15'
  ID_Fq = 0
  value = 1
  variable = temperature
[../]
[./HeatFlux_BC_1]
  type = DwarfElephantRBNeumannBC
  boundary = '16'
  ID_Fq = 1
  value = 1
  variable = temperature
[../]
[./HeatFlux_BC_2]
  type = DwarfElephantRBNeumannBC
  boundary = '17'
  ID_Fq = 2
  value = 1
  variable = temperature
[../]
[./HeatFlux_BC_3]
  type = DwarfElephantRBNeumannBC
  boundary = '18'
  ID_Fq = 3
  value = 1
  variable = temperature
[../]


[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = '11 12 13 14 ' 
  ID_Aq = 0
  value = 0
  penalty = 1.0
 variable = temperature
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
  use_EIM = false
  execute_on = 'initial'
  N_max_RB = 20
  #offline_stage = false
  n_training_samples_RB = 25
  rel_training_tolerance_RB = 1.e-5
  parameter_names_RB = 'mu_0 mu_1'# mu_2'    # mu_0 is r_0 and mu_1 is l_0 #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.2 0.4'
  parameter_max_values_RB = '0.4 0.8'
  normalize_rb_bound_in_greedy = false
  deterministic_training_RB = true
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_mu = '0.25 0.7'
  online_N = 20
  #offline_stage = false
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
