[Mesh]
 file = ../../../../Meshes/RB_mesh_3layers.e
[]

[Variables]
  [./temperature]
  [../]
[]

[GlobalParams]
  variable = temperature
[]

[Kernels]
  [./Conduction0]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 1
    block = 0
  [../]
  [./Conduction1]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 2.38
    block = 1
  [../]
  [./Conduction2]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 1
    block = 2
  [../]
  [./RadiogenicHeat0]
    type = DwarfElephantFEConstantRadiogenicHeatProduction
    radiogenic_heat_production = 1.0e-06
    norm_value_radiogenic_heat_production = 3e-05
    block = 0
  [../]
  [./RadiogenicHeat1]
    type = DwarfElephantFEConstantRadiogenicHeatProduction
    radiogenic_heat_production = 0.0
    norm_value_radiogenic_heat_production = 3e-05
    block = 1
  [../]
  [./RadiogenicHeat2]
    type = DwarfElephantFEConstantRadiogenicHeatProduction
    radiogenic_heat_production = 0.3e-06
    norm_value_radiogenic_heat_production = 3e-05
    block = 2
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
  value = 3.71
[../]
[]

[Executioner]
  type = Steady
  solve_type = 'Newton'
  l_tol = 1.0e-8
  nl_rel_tol = 1.0e-8
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[Outputs]
  exodus = true
  print_perf_log = true
  execute_on = 'timestep_end'
[]
