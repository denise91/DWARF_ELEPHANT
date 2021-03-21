[Mesh]
  type = GeneratedMesh
  dim = 3
  xmin = 0
  xmax = 1
  ymin = 0
  ymax = 1
  zmin = 0
  zmax = 1
  nx = 25
  ny = 25
  nz = 10
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
[./TimeDerivative_maxZ1]
  type = DwarfElephantRBTimeDerivative
  ID_Mq = 0
  simulation_type = transient
  matrix_seperation_according_to_subdomains = false
[../]
[./Diffusion]
  type = DwarfElephantRBDiffusion
  ID_Aq = 0
  simulation_type = transient
  matrix_seperation_according_to_subdomains = false
[../]
#[./AdvectionX]
#  type = DwarfElephantRBAdvectionX
#  ID_Aq = 1
#  simulation_type = transient
#[../]
#[./AdvectionY]
#  type = DwarfElephantRBAdvectionY
#  ID_Aq = 2
#  simulation_type = transient
#[../]
[./heatsource]
  type = DwarfElephantRBRFHeatsourceKernel
  ID_Fq = 1
  simulation_type = transient
  heat_source_function = 'heatsourcefunc'
[../]
[]

[Functions]
  [./heatsourcefunc]
    type = ParsedFunction
    value = '3'
  [../]
[]

[BCs]
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = 'left right top bottom front back'
  ID_Aq = 1
  value = 0.0
  penalty = 1.0
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
  l_abs_tol = 1.0e-8
  nl_abs_tol = 1.0e-8
  #offline_stage = false
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemTransient
  use_EIM = false#true
  N_max_EIM = 0#30
  n_training_samples_EIM = 0#100
  rel_training_tolerance_EIM = 1e-6
  abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4'# mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_EIM = '0.005 0.006 0.02 0.02 0.02'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  euler_theta_RB = 1 #1.0 corresponds to backward euler
  execute_on = 'initial'
  N_max_RB = 20
  n_time_steps_RB = 1#00
  delta_N_RB = 1
  delta_t_RB = 0.000001
  POD_tol = -1e-6 #should be negative for the transient case
  #max_truth_solves_RB = 500
  #offline_stage_RB = false
  n_training_samples_RB = 100
  rel_training_tolerance_RB = 1.e-4
  parameter_names_RB = 'mu_0 mu_1' # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '-2 -2'
  parameter_max_values_RB = '2 2'
  normalize_rb_bound_in_greedy = true
  deterministic_training_RB = true
  RB_RFA = false
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
  online_mu = '0 0'
  mu_ref = '1 1'
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
  execute_on = 'timestep_end'
  #exodus = true
  vtk = true
# csv = true   # only required for the PostProcessors
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
