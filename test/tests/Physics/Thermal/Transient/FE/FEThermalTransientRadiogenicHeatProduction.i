[Mesh]
  file = ../../../../Meshes/RB_mesh_3layers.e
[]

[Variables]
  [./temperature]
  [../]
[]

[GlobalParams]
  variable = temperature
  transient = true
[]

[Kernels]
  [./Conduction1]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 1.0
    density = 2700
    specific_heat = 1093
    block = 0
  [../]
  [./Conduction2]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 2.38
    density = 2705
    specific_heat = 1033
    block = 1
  [../]
  [./Conduction3]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 1.0
    density = 2690
    specific_heat = 1186
    block = 2
  [../]
  [./RadiogenicHeat0]
    type = DwarfElephantFEConstantRadiogenicHeatProduction
    radiogenic_heat_production = 1.0e-06
    norm_value_radiogenic_heat_production = 3e-05
    density = 2700
    specific_heat = 1093
    block = 0
  [../]
  [./RadiogenicHeat1]
    type = DwarfElephantFEConstantRadiogenicHeatProduction
    radiogenic_heat_production = 0.0
    density = 2705
    specific_heat = 1033
    norm_value_radiogenic_heat_production = 3e-05
    block = 1
  [../]
  [./RadiogenicHeat2]
    type = DwarfElephantFEConstantRadiogenicHeatProduction
    radiogenic_heat_production = 0.3e-06
    norm_value_radiogenic_heat_production = 3e-05
    density = 2690
    specific_heat = 1186
    block = 2
  [../]
  [./Time]
    type = TimeDerivative
  [../]
[]

[BCs]
[./top]
  type = DirichletBC
  boundary = 2
  value = 0.00
[../]

[./bottom]
  type = NeumannBC
  boundary = 1
  value = 0.0000016
[../]
[]

  [Executioner]
    type = Transient
    solve_type = 'Newton'
    l_tol = 1.0e-8
    nl_rel_tol = 1.0e-8
    start_time = 0.0
    dt = 100000
    num_steps = 20
    petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
    petsc_options_value = 'hypre    boomeramg      101'
  []

  [Outputs]
    perf_graph = true
    exodus = true
  []
