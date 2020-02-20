[Mesh]
  file = RBRFAGeom3D_r3e-3_l5e-2_L1e-1_d3r_h15e-1l_Test_coarse.msh#RBRFAGeom3D_r3e-3_l5e-2_L1e-1_d3r_h15e-1l_Test_coarse.msh#ReducedBasisGeom3D_7_fullylabeled_debug.msh#RBRFAGeom3D_r3e-3_l5e-2_L1e-1_d3r_h15e-1l_fine_new.msh#
  #type = GeneratedMesh
  #dim = 3
  #xmin = 0
  #ymin = 0
  #zmin = 0
  #xmax = 1
  #ymax = 1
  #zmax = 1
  #nx = 30
  #ny = 30
  #nz = 30
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
  [./TimeDerivative]
    type = DwarfElephantRBTimeDerivative
    variable = temperature
    simulation_type = transient
    ID_Mq = 0
  [../]

  [./RBDiffusion]
    type = DwarfElephantRBDiffusion
    variable = temperature
    simulation_type = transient
    ID_Aq = 0
  [../]

  #[./InnerProductMatrix]
  #  type = RBInnerProductMatrix
  #  simulation_type = transient
  #[../]
[]

#[AuxKernels]
#  [./HeatSourceVisAux]
#    type = FunctionAux
#    function = 'rf_heat_source'
#    variable = HeatSourceVis
#    execute_on = 'timestep_end'
#  [../]
#[]

#[Functions]
#  [./rf_heat_source]
#    type = DwarfElephantRFHeatsourceFunction
#    needle_active_region_p1 = '0 0 0.01'
#    needle_active_region_p2 = '0 0 -0.01'
#    needle_power = 2.618e-7 # actually the power scaling divided by \rho*C for the tissue
#  [../]
#  [./test_heat_source]
#    type = ParsedFunction
#    value = '100'#exp(-x^2 - y^2)'
#  [../]
#[]

[BCs]
 [./Left]
   type = DwarfElephantRBPenaltyDirichletBC
   #boundary = 'left right top bottom front back'
   boundary = '33 34 35 36 37 38 39 40 41 42 43 44' 
   value = 5.0
   penalty = 1.0
   variable = temperature
   simulation_type = transient
   ID_Fq = 0
   ID_Aq = 1
 [../]

 #[./Right]
 #  type = DwarfElephantRBNeumannBC
 #  boundary = 'right'
 #  value = 10
 #  variable = temperature
 #  simulation_type = transient
 #  ID_Fq = 0
 #[../]
[]

#[ICs]
#  [./ConstantIC]
#    type = DwarfElephantRBConstantIC
#    value = 0
#  [../]
#[]

[Problem]
  type = DwarfElephantRBProblem
[]

[Executioner]
  type = DwarfElephantRBExecutioner
  simulation_type = 'transient'
  solve_type = 'Newton'
  l_tol = 1.0e-8
  nl_rel_tol = 1.0e-8
  #offline_stage = false
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemTransient
  use_EIM = false#true#
  N_max_EIM = 0#60#
  n_training_samples_EIM = 0#200#
  rel_training_tolerance_EIM = 1e-11
  #abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4'# mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '1e-3 3e-2 -0.01 -0.01 -0.01'#'0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_EIM = '5e-3 7e-2 0.01 0.01 0.01'#'0.005 0.006 0.02 0.02 0.02'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  euler_theta_RB = 1 #backward euler
  execute_on = 'initial'
  N_max_RB = 20
  n_time_steps_RB = 5
  delta_N_RB = 1
  delta_t_RB = 0.1
  POD_tol = -1e-6 #should be negative for the transient case
  max_truth_solves_RB = 500
  #offline_stage_RB = false
  n_training_samples_RB = 50
  rel_training_tolerance_RB = 1.e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4' # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '1e-3 3e-2 -0.01 -0.01 -0.01'#'0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_RB = '5e-3 7e-2 0.01 0.01 0.01'#'0.005 0.006 0.02 0.02 0.02'
  normalize_rb_bound_in_greedy = true
  RB_RFA = true#
[../]
#[./EIMInnerProductMatrixComputation]
#  type = DwarfElephantComputeEIMInnerProductMatrixTransient
#  execute_on = "EIM"
#  initialize_rb_userobject = initializeRBSystem
#[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #offline_stage = false
  online_stage = false
  online_mu = '3e-03 5e-2 0.01 0.01 0.01'#'0.003 0.004 -0.01 -0.01 -0.01'
  mu_ref = '3e-3 5e-2 0 0 0'
  online_N = 0
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
