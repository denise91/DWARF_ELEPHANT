[Mesh]
 file = RBGeom_test_deformed_max.msh#RBGeom_test_r0.00306mm_l0.02602mm_d_8by3r_h_4by3l_mesh2.msh#RBGeom_test_mesh4.msh#RBGeom_r3e-3mm_l4e-2mm_d_8by3r_h_4by3l_mesh0_new.msh#
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
[./TimeDerivative_tissue]
  type = DwarfElephantRBTimeDerivative
  ID_Mq = 0
  simulation_type = transient
  block = '1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 32'
  heat_capacity = 3.82e6
  matrix_seperation_according_to_subdomains = false
[../]
[./TimeDerivative_blood]
  type = DwarfElephantRBTimeDerivative
  ID_Mq = 0
  simulation_type = transient
  heat_capacity = 3.798e6
  block = 31
  matrix_seperation_according_to_subdomains = false
[../]
[./Diffusion_tissue]
  type = DwarfElephantRBDiffusion
  ID_Aq = 0
  simulation_type = transient
  block = '1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 32'
  thermal_conductivity = 0.83
  matrix_seperation_according_to_subdomains = false
[../]
[./Diffusion_blood]
  type = DwarfElephantRBDiffusion
  ID_Aq = 0
  simulation_type = transient
  block = 31
  thermal_conductivity = 0.52
  matrix_seperation_according_to_subdomains = false
[../]

[./PennesPerfusion_VesselCyl]
  type = DwarfElephantRBPennesPerfusion
  ID_Aq = 0
  simulation_type = transient
  perfusion_coeff = 1.9e5
  block = 31
  matrix_seperation_according_to_subdomains = false
[../]
     
[./RB_inner_product_matrix]
  type = RBInnerProductMatrixTransient
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
  value = 0.0
  penalty = 6.0
  variable = temperature
  matrix_seperation_according_to_subdomains = false
  simulation_type = transient
  ID_Fq = 0
[../]
[]

[Problem]
  type = DwarfElephantRBProblem
[]

[Executioner]
  type = DwarfElephantRBExecutioner
  simulation_type = 'transient'
  solve_type = 'PJFNK'
  l_tol = 1e-8#1.0e-8
  nl_rel_tol = 1e-8#1.0e-8
  #offline_stage = false
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemTransient
  RB_RFA = true
  use_EIM = true
  use_hp_EIM = false
  #hp_EIM_testing = true # Testing of hp EIM implementation possbile only during the online phase
  N_max_EIM = 30
  delta_t_RB = 0.125
  n_time_steps_RB = 1
  n_training_samples_EIM = 100#25#00
  rel_training_tolerance_EIM = 1e-3
  abs_training_tolerance_EIM = 1e-40
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12 mu_13 mu_14'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.0025 0.03 0.01 0.01 0.01 0 0 1.0 1.9e5 0.003 0.04 0.8 3.82e6 0.52 3.798e6'# r_0 l_0 min 0.001 0.015
  parameter_max_values_EIM = '0.0035 0.05 0.011 0.011 0.011 0.01 0.01 1.0 1.9e5 0.003 0.04 0.8 3.82e6 0.52 3.798e6'# r_0 l_0 needle center coords max vals 0.002 0.02 0.01 0.01 0.01 0.1 0.1
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 12
  #offline_stage = false
  n_training_samples_RB = 40
  rel_training_tolerance_RB = 1.e-3
  #abs_training_tolerance_RB = 1e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12 mu_13 mu_14' # r0 l0 x_n y_n z_n theta_n phi_n P_n omega_p r l k_t rhoC_t k_b rhoC_b #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.001414 0.01871 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6 0.52 3.798e6'
  parameter_max_values_RB = '0.001414 0.01871 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6 0.52 3.798e6'
  deterministic_training_RB = false
  normalize_rb_bound_in_greedy = false
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixTransient
  variable = temperature
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #online_stage = true
  online_mu = '0.001414 0.01871 0.0105 0.0105 0.0105 0.005 0.005  1.0 1.9e5 0.001414 0.01871 0.8 3.82e6 0.52 3.798e6'
  online_N = 5
  #offline_stage = false
  execute_on = 'timestep_end'
  mesh_num = 2
  param_str = ''
  vec_file_location = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/'
  mat_file_location = '/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3D_reducedbasis_TransformationMatrices/3D_reducedbasis/'
  Aq_mat_offset = 0
  Mq_mat_offset = 0
  mu_ref = '0.001414 0.01871 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6 0.52 3.798e6'
  num_online_solves = 1 
[../]
[]

[Outputs]
#exodus = true
vtk = true
# csv = true   # only required for the PostProcessors
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
