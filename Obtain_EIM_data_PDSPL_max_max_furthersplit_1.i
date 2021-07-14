[Mesh]
  file = RBGeom_r0.001939mm_l0.02602mm_d_8by3r_h_4by3l_mesh2_new.msh#RBGeom_test_r0.001939mm_l0.02602mm_d_8by3r_h_4by3l_mesh2.msh#
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./HeatSourceVis]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]
[Kernels]
[./DiffusionXX_maxZ1]
  type = DwarfElephantRBDiffusion
  ID_Aq = 1
  block = '1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 32'
[../]

[./Diffusion_vessel]
  type = DwarfElephantRBDiffusion
  ID_Aq = 2
  block = '31'
[../]

[./Perfusion]
  type = DwarfElephantRBPennesPerfusion
  ID_Aq = 3
  block = '31'
[../]

  [./EIM_1]
    type = DwarfElephantEIMFKernel
    block = 1
    EIM_offset = 1
  [../]
   
  [./EIM_2]
    type = DwarfElephantEIMFKernel
    block = 2
    EIM_offset = 1
  [../]
   
  [./EIM_3]
    type = DwarfElephantEIMFKernel
    block = 3
    EIM_offset = 1
  [../]
   
  [./EIM_4]
    type = DwarfElephantEIMFKernel
    block = 4
    EIM_offset = 1
  [../]
   
  [./EIM_5]
    type = DwarfElephantEIMFKernel
    block = 5
    EIM_offset = 1
  [../]
   
  [./EIM_6]
    type = DwarfElephantEIMFKernel
    block = 6
    EIM_offset = 1
  [../]
   
  [./EIM_7]
    type = DwarfElephantEIMFKernel
    block = 7
    EIM_offset = 1
  [../]
   
  [./EIM_8]
    type = DwarfElephantEIMFKernel
    block = 8
    EIM_offset = 1
  [../]
   
  [./EIM_9]
    type = DwarfElephantEIMFKernel
    block = 9
    EIM_offset = 1
  [../]
   
  [./EIM_10]
    type = DwarfElephantEIMFKernel
    block = 10
    EIM_offset = 1
  [../]
   
  [./EIM_11]
    type = DwarfElephantEIMFKernel
    block = 11
    EIM_offset = 1
  [../]
   
  [./EIM_12]
    type = DwarfElephantEIMFKernel
    block = 12
    EIM_offset = 1
  [../]
   
  [./EIM_13]
    type = DwarfElephantEIMFKernel
    block = 13
    EIM_offset = 1
  [../]
   
  [./EIM_14]
    type = DwarfElephantEIMFKernel
    block = 14
    EIM_offset = 1
  [../]
   
  [./EIM_15]
    type = DwarfElephantEIMFKernel
    block = 15
    EIM_offset = 1
  [../]
   
  [./EIM_16]
    type = DwarfElephantEIMFKernel
    block = 16
    EIM_offset = 1
  [../]
   
  [./EIM_17]
    type = DwarfElephantEIMFKernel
    block = 17
    EIM_offset = 1
  [../]
   
  [./EIM_18]
    type = DwarfElephantEIMFKernel
    block = 18
    EIM_offset = 1
  [../]
   
  [./EIM_19]
    type = DwarfElephantEIMFKernel
    block = 19
    EIM_offset = 1
  [../]
   
  [./EIM_20]
    type = DwarfElephantEIMFKernel
    block = 20
    EIM_offset = 1
  [../]
   
  [./EIM_21]
    type = DwarfElephantEIMFKernel
    block = 21
    EIM_offset = 1
  [../]
   
  [./EIM_22]
    type = DwarfElephantEIMFKernel
    block = 22
    EIM_offset = 1
  [../]
   
  [./EIM_23]
    type = DwarfElephantEIMFKernel
    block = 23
    EIM_offset = 1
  [../]
   
  [./EIM_24]
    type = DwarfElephantEIMFKernel
    block = 24
    EIM_offset = 1
  [../]
   
  [./EIM_25]
    type = DwarfElephantEIMFKernel
    block = 25
    EIM_offset = 1
  [../]
   
  [./EIM_26]
    type = DwarfElephantEIMFKernel
    block = 26
    EIM_offset = 1
  [../]
   
  [./EIM_27]
    type = DwarfElephantEIMFKernel
    block = 27
    EIM_offset = 1
  [../]
   
  [./EIM_28]
    type = DwarfElephantEIMFKernel
    block = 28
    EIM_offset = 1
  [../]
   
  [./EIM_29]
    type = DwarfElephantEIMFKernel
    block = 29
    EIM_offset = 1
  [../]
   
  [./EIM_30]
    type = DwarfElephantEIMFKernel
    block = 30
    EIM_offset = 1
  [../]
   
  [./EIM_31]
    type = DwarfElephantEIMFKernel
    block = 31
    EIM_offset = 1
  [../]
   
  [./EIM_32]
    type = DwarfElephantEIMFKernel
    block = 32
    EIM_offset = 1
  [../]
   
[./RB_inner_product_matrix]
  type = RBInnerProductMatrix
[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'gaussian'#'rf_heat_source'
    variable = HeatSourceVis
    execute_on = 'timestep_end'
  [../]
[]

[Functions]
  [./gaussian]
    type = ParsedFunction
    value = 'exp(-(x + 0.1)^2 - (y + 0.1)^2)'
  [../]
[]
[BCs]
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = ' 33 34 35 36 37 38 39 40 41 42 43 44'
  ID_Aq = 0
  ID_Fq = 0
  value = 0
  penalty = 6.0
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
  l_tol = 1.0e-6
  nl_rel_tol = 1.0e-8
  #offline_stage = false
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  RB_RFA = true
  use_EIM = true
  use_hp_EIM = false
  #hp_EIM_testing = true # Testing of hp EIM implementation possbile only during the online phase
  N_max_EIM = 200
  n_training_samples_EIM = 1000#50#
  rel_training_tolerance_EIM = 1e-40
  abs_training_tolerance_EIM = 0.01
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.001414 0.01871 0.0 0.0 -0.045 0.0 0.0 0.1 1.9e5 0.001939 0.02602 0.8 3.82e6'# r_0 l_0 min 0.001 0.015
  parameter_max_values_EIM = '2.659e-3 3.619e-2 0.01125 0.0 0.0 1.57080 3.14159 2.0 1.9e5 0.001939 0.02602 0.8 3.82e6'# r_0 l_0 needle center coords max vals 0.002 0.02 0.01 0.01 0.01 0.1 0.1
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 12
  #offline_stage = false
  n_training_samples_RB = 40
  rel_training_tolerance_RB = 1.e-3
  #abs_training_tolerance_RB = 1e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12' # r0 l0 x_n y_n z_n theta_n phi_n P_n omega_p r l k rhoC #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.001414 0.01871 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  parameter_max_values_RB = '0.001414 0.01871 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  deterministic_training_RB = false
  normalize_rb_bound_in_greedy = false
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  variable = temperature
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
  param_str = 'max_max_furthersplit_1'
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_mu = '0.001414 0.01871 0.01 0.01 0.01 0 0 1.0 1.9e5 0.001414 0.01871 0.8 3.82e6'
  online_N = 5
  #offline_stage = false
  execute_on = 'timestep_end'
  mesh_num = 2
  param_str = 'max_max_furthersplit_1'
  vec_file_location = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/PDSplit/'#check if testcase
[../]
[]

[Outputs]
exodus = true
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
