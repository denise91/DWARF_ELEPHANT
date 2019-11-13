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
   type = DwarfElephantRBDirichletBC
   boundary = 'left'
   value = 0
   variable = temperature
   simulation_type = transient
 [../]

 [./Right]
   type = DwarfElephantRBNeumannBC
   boundary = 'right'
   value = 10
   variable = temperature
   simulation_type = transient
   ID_Fq = 0
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
  euler_theta = 1
  execute_on = 'initial'
  N_max = 50
  n_time_steps = 100
  delta_N = 1
  delta_t = 0.1
  POD_tol = 1e-6
  max_truth_solves = 20
  #offline_stage = false
  n_training_samples = 100
  rel_training_tolerance = 1.e-6
  parameter_names = 'mu_0'    # mu_0 is the perfusion coefficient for the large vessel which we wish to determine using the optimization routine; #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values = '0.1'
  parameter_max_values = '1.0'
  normalize_rb_bound_in_greedy = true
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #offline_stage = false
  #online_stage = false
  online_mu = '0.5'
  online_N = 10
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
