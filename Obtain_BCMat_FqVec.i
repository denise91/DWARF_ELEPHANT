[Mesh]
  file = RBGeom_test_mesh4.msh
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./TissueDamage]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[GlobalParams]
  initial_rb_userobject = initializeRBSystem
  variable = temperature
[]
[Kernels]
[./HeatSource0]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 1
block = 1
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource1]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 2
block = 2
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource2]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 3
block = 3
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource3]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 4
block = 4
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource4]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 5
block = 5
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource5]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 6
block = 6
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource6]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 7
block = 7
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource7]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 8
block = 8
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource8]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 9
block = 9
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource9]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 10
block = 10
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource10]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 11
block = 11
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource11]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 12
block = 12
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource12]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 13
block = 13
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource13]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 14
block = 14
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource14]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 15
block = 15
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource15]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 16
block = 16
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource16]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 17
block = 17
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource17]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 18
block = 18
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource18]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 19
block = 19
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource19]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 20
block = 20
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource20]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 21
block = 21
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource21]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 22
block = 22
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource22]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 23
block = 23
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource23]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 24
block = 24
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource24]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 25
block = 25
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource25]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 26
block = 26
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource26]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 27
block = 27
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource27]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 28
block = 28
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource28]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 29
block = 29
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource29]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 30
block = 30
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource30]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 31
block = 31
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./HeatSource31]
  type = DwarfElephantRBRFHeatsourceKernel
ID_Fq = 32
block = 32
  simulation_type = transient
  needle_center_x = -0.012
  needle_center_y = 0
  needle_center_z = 0.0
  needle_axis_phi = 0.0
  needle_axis_theta = 1.57
  r0 = 00.005
  l0 = 00.07
  r = 0.001414
  l = 0.01871
[../]
[./DummyKernel]
  type = Diffusion
  variable = temperature
[../]
#[./RB_inner_product_matrix]
#  type = RBInnerProductMatrixTransient
#[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'gaussian'#'rf_heat_source'
    variable = TissueDamage
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
  solve_type = 'Newton'
  l_tol = 1e-8#1.0e-8
  nl_rel_tol = 1e-8#1.0e-8
  #offline_stage = false
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemTransient
  use_EIM = false#true#
  N_max_EIM = 0#5#50#50#
  n_training_samples_EIM = 0#50#300#
  rel_training_tolerance_EIM = 1e-8
  #abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12'# mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '3e-3 5e-2 -0.01 -0.01 -0.01 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'#'0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_EIM = '3e-3 5e-2 -0.01 -0.01 -0.01 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'#'0.005 0.006 0.02 0.02 0.02'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  euler_theta_RB = 1 #backward euler
  execute_on = 'initial'
  N_max_RB = 1
  n_time_steps_RB = 2
  delta_N_RB = 1
  delta_t_RB = 0.707106781187
  POD_tol = -1e-6 #should be negative for the transient case
  max_truth_solves_RB = 500
  #offline_stage_RB = false
  n_training_samples_RB = 1#50
  rel_training_tolerance_RB = 1.e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12' # r0 l0 x_n y_n z_n theta_n phi_n P_n omega_p r l k rhoC #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '00.005 00.07 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  parameter_max_values_RB = '00.005 00.07 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  normalize_rb_bound_in_greedy = true
  RB_RFA = true#
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #offline_stage = false
  online_stage = false
  online_mu = '00.005 00.07 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  mu_ref = '00.005 00.07 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  online_N = 0
  execute_on = 'timestep_end'
  num_online_solves = 1#3
  online_mu_0= '3e-3 5e-2 -0.01 -0.01 -0.01' 
  #online_mu_1= '2.2e-3 3e-2 -0.1 -0.1 -0.1 ' 
  #online_mu_2= '3.4e-3 5e-3 -0.1 -0.1 -0.1 '
  mesh_index = 0
  Aq_mat_offset = 253
  Mq_mat_offset = 0
  mesh_num = 4
  param_str = param_max
  vec_file_location = /home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/transienttestcase/
  mat_file_location = /home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/3DRBRFAMatrices/MeshConvMatrices/transienttestcase/
[../]
[]