[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  ymin = 0
  xmax = 1
  ymax = 1
  nx = 30
  ny = 30
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

  [./EIM_F]
    type = DwarfElephantEIMFKernelTransient
  [../]

  #[./InnerProductMatrix]
  #  type = RBInnerProductMatrix
  #  simulation_type = transient
  #[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'rf_heat_source'
    variable = HeatSourceVis
    execute_on = 'timestep_end'
  [../]
[]

[Functions]
  [./rf_heat_source]
    type = DwarfElephantRFHeatsourceFunction
    needle_active_region_p1 = '0 0 0.01'
    needle_active_region_p2 = '0 0 -0.01'
    needle_power = 2.618e-7 # actually the power scaling divided by \rho*C for the tissue
  [../]
  [./test_heat_source]
    type = ParsedFunction
    value = '100'#exp(-x^2 - y^2)'
  [../]
[]

[BCs]
 [./Left]
   type = DwarfElephantRBPenaltyDirichletBC
   boundary = 'left'
   value = 0
   penalty = 1
   variable = temperature
   simulation_type = transient
   ID_Aq = 1
 [../]

 [./Right]
   type = DwarfElephantRBPenaltyDirichletBC
   boundary = 'right'
   value = 0
   penalty = 1
   variable = temperature
   simulation_type = transient
   ID_Aq = 1
 [../]

 [./Top]
   type = DwarfElephantRBPenaltyDirichletBC
   boundary = 'top'
   value = 0
   penalty = 1
   variable = temperature
   simulation_type = transient
   ID_Aq = 1
 [../]

 [./Bottom]
   type = DwarfElephantRBPenaltyDirichletBC
   boundary = 'bottom'
   value = 0
   penalty = 1
   variable = temperature
   simulation_type = transient
   ID_Aq = 1
 [../]
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
  RB_RFA = false
  use_EIM = true
  N_max_EIM = 30
  n_training_samples_EIM = 60
  rel_training_tolerance_EIM = 1e-6
  #abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '1 0 0'# 0.01'
  parameter_max_values_EIM = '1 1 1'# 1.0'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  euler_theta_RB = 1
  execute_on = 'initial'
  N_max_RB = 4#0
  n_time_steps_RB = 4#100
  #delta_N_RB = 1
  delta_t_RB = 0.1
  POD_tol = -1e-6 #should be negative for the transient case
  max_truth_solves_RB = 500
  #offline_stage_RB = false
  n_training_samples_RB = 8#0
  rel_training_tolerance_RB = 1.e-6
  parameter_names_RB = 'mu_0 mu_1 mu_2'    # mu_0 is the perfusion coefficient for the large vessel which we wish to determine using the optimization routine; #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '1 0 0'
  parameter_max_values_RB = '1 1 1'
  normalize_rb_bound_in_greedy = false#true
[../]
[./EIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixTransient
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #offline_stage = false
  online_stage = false
  online_mu = '1 1.267719e-01 9.636189e-01'
  online_N = 50
  execute_on = 'timestep_end'
  mesh_num = 0
  vec_file_location = ""
  param_str = ''
  Aq_mat_offset = 0
  Mq_mat_offset = 0
  mu_ref = '1.0 0 0'
  num_online_solves = 0
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
