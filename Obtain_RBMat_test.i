[Mesh]
  file = RBGeom_Test.msh# RBRFAGeom3D_r3e-3_l5e-2_L1e-1_d3r_h15e-1l_Test_coarse.msh#RBGeom_r3e-3mm_l4e-2mm_d_3r_h_3by2l_mesh0.msh#
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
[./Kernel_0]
  type = DwarfElephantRBTimeDerivative
  simulation_type = transient
  block = '1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 32'
  ID_Mq = 0
  matrix_seperation_according_to_subdomains = false
[../]
[./Kernel_1]
  type = DwarfElephantRBTimeDerivative
  simulation_type = transient
  block = '31'
  ID_Mq = 1
  matrix_seperation_according_to_subdomains = false
[../]
[./TissueDiffusion]
  type = DwarfElephantRBDiffusion
  block = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 32"
  variable = temperature
  ID_Aq = 0
  matrix_seperation_according_to_subdomains = false
  simulation_type = transient
[../]

[./VesselPerfusion]
  type = DwarfElephantRBPennesPerfusion
  simulation_type = transient
  variable = temperature
  ID_Aq = 1
  block = 31
  matrix_seperation_according_to_subdomains = false
[../]

[./VesselDiffusion]
  type = DwarfElephantRBDiffusion
  block = 31
  variable = temperature
  ID_Aq = 2
#  ID_Aq = 1
  matrix_seperation_according_to_subdomains = false
  simulation_type = transient
[../]

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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  r0 = 0.003
  l0 = 0.04
  r = 0.003
  l = 0.04
  vector_seperation_according_to_subdomains = false
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
  boundary = '33 34 35 36 37 38 39 40 41 42 43 44'
  ID_Aq = 3
  #ID_Aq = 1
  value = 0.0
  penalty = 6.0
  variable = temperature
  matrix_seperation_according_to_subdomains = false
  split_boundary_according_to_subdomains = false
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
  n_time_steps_RB = 2#400
  delta_N_RB = 1
  delta_t_RB = 0.707106781187
  POD_tol = -1e-6 #should be negative for the transient case
  max_truth_solves_RB = 500
  #offline_stage_RB = false
  n_training_samples_RB = 1#50
  rel_training_tolerance_RB = 1.e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4 mu_5 mu_6 mu_7 mu_8 mu_9 mu_10 mu_11 mu_12' # r0 l0 x_n y_n z_n theta_n phi_n P_n omega_p r l k rhoC #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '00.003 00.04 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  parameter_max_values_RB = '00.003 00.04 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  normalize_rb_bound_in_greedy = true
  RB_RFA = true#
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #offline_stage = false
  online_stage = false
  online_mu = '00.003 00.04 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  mu_ref = '00.003 00.04 0.001 0.001 0.001 1.57 1.57 1.0 1.9e5 3e-3 4e-2 0.8 3.82e6'
  online_N = 0
  execute_on = 'timestep_end'
  num_online_solves = 1#3
  online_mu_0= '3e-3 5e-2 -0.01 -0.01 -0.01' 
  #online_mu_1= '2.2e-3 3e-2 -0.1 -0.1 -0.1 ' 
  #online_mu_2= '3.4e-3 5e-3 -0.1 -0.1 -0.1 '
  mesh_index = 0
  Aq_mat_offset = 0
  Mq_mat_offset = 0
[../]
[]
