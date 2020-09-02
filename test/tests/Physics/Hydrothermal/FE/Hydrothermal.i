[Mesh]
  file = ../../../Meshes/RB_mesh_3layers.e
[]

[Variables]
  [./pressure]
  [../]
  [./temp]
    initial_condition = 0.0
  [../]
[]

[AuxVariables]
  [./velocity_x]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./velocity_y]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./velocity_z]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./Peclet]
    order = CONSTANT
    family = MONOMIAL
    initial_condition = 0
  [../]
  [./CFL]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./entropy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./TBar]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  active = 'mass diff conv euler'
  [./mass]
    type = DwarfElephantFECoupledPressureDiffusion
    variable = pressure
    temperature = temp
    evaluation_component = 1
  [../]

  [./diff]
    type = DwarfElephantFECoupledTemperatureDiffusion
    variable = temp
    diffusivity = 1.0
  [../]

  [./conv]
    type = DwarfElephantFECoupledPressureConvection
    variable = temp
    pressure = pressure
    evaluation_component = 1
  [../]

  [./euler]
    type = DwarfElephantFEConstantSpecificStorage
    variable = temp
    specific_storage = 1.0
  [../]
[]

[AuxKernels]
  [./velocity_x_aux]
    type = DwarfElephantFECoupledDarcyVelocity
    variable = velocity_x
    pressure = pressure
    temperature = 0
    evaluation_component = 0
  [../]

  [./velocity_y_aux]
    type = DwarfElephantFECoupledDarcyVelocity
    variable = velocity_y
    pressure = pressure
    temperature = temp
    evaluation_component = 1
  [../]

  [./velocity_z_aux]
    type = DwarfElephantFECoupledDarcyVelocity
    variable = velocity_z
    pressure = pressure
    temperature = 0
    evaluation_component = 0
  [../]

  [./tbar]
    type = DwarfElephantFETBar
    T_top = 10
    T_bottom = 40
    variable = TBar
  [../]

  [./entropy_bottom_top]
    type = DwarfElephantFEEntropyProduction
    variable = entropy
    temp = temp
    velocity_x = velocity_x
    velocity_y = velocity_y
    velocity_z = velocity_z
    T_top = 10
    T_bottom = 40
    alpha = 1.6163e-4
    cf = 4184
    z_top = 0
    z_bottom = 1000
    block = '0 2'
    thermal_conductivity = 1.05
    entropy_generation_number = false
    thermal_part = true
    visc_part = false
  [../]
  [./entropy_middle]
    type = DwarfElephantFEEntropyProduction
    variable = entropy
    temp = temp
    velocity_x = velocity_x
    velocity_y = velocity_y
    velocity_z = velocity_z
    T_top = 10
    T_bottom = 40
    alpha = 1.6163e-4
    cf = 4184
    z_top = 0
    z_bottom = 1000
    block = '1'
    thermal_conductivity = 2.5
    entropy_generation_number = false
    thermal_part = true
    visc_part = false
  [../]
[]

[BCs]
  [./no_flux_bc]
    type = DirichletBC
    variable = pressure
    boundary = 2
    value = 0.0
  [../]

  [./top_temp]
    type = DirichletBC
    variable = temp
    boundary = 2
    value = 0
  [../]

  [./bottom_temp]
    type = DirichletBC
    variable = temp
    boundary = 1
    value = 3
  [../]
[]

[Materials]
  [./layer1]
    block = '0 2'
    type = DwarfElephantRayleighMaterial
    function = 4
    min = 0
    max = 0
    seed = 363192
  [../]
  [./layer2]
    type = DwarfElephantRayleighMaterial
    block = 1
    function = 6.5
    min = 0
    max = 0
    seed = 363192
  [../]
[]

[Preconditioning]
  active = 'FSP'
  [./SMP]
    type = SMP
    full = true
    solve_type = 'NEWTON'
    petsc_options_iname = '-pc_type -sub_pc_type -snes_linesearch_type -ksp_gmres_restart -pc_gamg_sym_graph'
    petsc_options_value = 'gasm hypre cp 301 true'
  [../]

  [./FSP]
    type = FSP
    full = true
    solve_type = 'NEWTON'
    topsplit = 'pt'
    [./pt]
      splitting = 'pressure temp'
    [../]
    [./pressure]
      vars = 'pressure'
      petsc_options_iname = '-pc_type -sub_pc_type -snes_linesearch_type -ksp_gmres_restart'
      petsc_options_value = 'gamg hypre cp 151'
    [../]
    [./temp]
      vars = 'temp'
      petsc_options_iname = '-pc_type -sub_pc_type -snes_linesearch_type -ksp_gmres_restart'
      petsc_options_value = 'gasm hypre cp 151'
    [../]
  [../]
[]

[Executioner]
  type = Transient
  start_time = 0
  num_steps = 15
  l_max_its = 60
  nl_max_its = 30
  dtmin = 2e-10

  nl_rel_tol = 1e-10
  nl_abs_tol = 1e-12

  [./TimeIntegrator]
    type = CrankNicolson
  [../]

  [./TimeStepper]
    growth_factor = 2.2
    dt = 2.5e-5
    cutback_factor = 0.8
    type = IterationAdaptiveDT
    optimal_iterations = 20
  [../]
[]

[Postprocessors]
  [./flux_top]
    type = SideFluxAverage
    boundary = 2
    diffusivity = 1.0
    variable = temp
  [../]
  [./flux_bottom]
    type = SideFluxAverage
    boundary = 1
    diffusivity = 1.0
    variable = temp
  [../]
  [./S_bottom]
    type = ElementAverageValue
    variable = entropy
    block = 0
  [../]
  [./S_middle]
    type = ElementAverageValue
    variable = entropy
    block = 1
  [../]
  [./S_top]
    type = ElementAverageValue
    variable = entropy
    block = 2
  [../]
  [./tbar_average]
    type = ElementAverageValue
    variable = TBar
  [../]
  [./eff_cond_bottom]
    type = DwarfElephantFECoupledEffectiveConductivity
    thermal_conductivity = 1.05
    entropy = S_bottom
    flux_top = flux_top
    flux_bottom = flux_bottom
    t_bar = tbar_average
  [../]
  [./eff_cond_middle]
    type = DwarfElephantFECoupledEffectiveConductivity
    thermal_conductivity = 2.5
    entropy = S_middle
    flux_top = flux_top
    flux_bottom = flux_bottom
    t_bar = tbar_average
  [../]
  [./eff_cond_top]
    type = DwarfElephantFECoupledEffectiveConductivity
    thermal_conductivity = 1.05
    entropy = S_top
    flux_top = flux_top
    flux_bottom = flux_bottom
    t_bar = tbar_average
  [../]
[]

[Outputs]
  perf_graph = true
  execute_on = 'timestep_end'
  csv = true
  [./out]
    type = Exodus
  [../]
[]
