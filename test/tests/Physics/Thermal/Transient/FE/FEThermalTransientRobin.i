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
    thermal_conductivity = 3.4e-2 #1.0
    # density = 2700
    # specific_heat = 1093
    block = 0
  [../]
  [./Conduction2]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 8.4e-2 #2.38
    # density = 2705
    # specific_heat = 1033
    block = 1
  [../]
  [./Conduction3]
    type = DwarfElephantFEThermalConduction
    thermal_conductivity = 3.1e-2 #1.0
    # density = 2690
    # specific_heat = 1186
    block = 2
  [../]
  [./Time]
    type = TimeDerivative
  [../]
[]

[BCs]
[./top]
  type = DwarfElephantFERobinBC
  boundary = 2
  value = -1
  alpha = 0.95
[../]

[./bottom]
  type = DirichletBC
  boundary = 1
  value = 0
[../]
[]

  [Executioner]
    type = Transient
    solve_type = 'Newton'
    l_tol = 1.0e-8
    nl_rel_tol = 1.0e-8
    start_time = 0.0
    dt = 1
    num_steps = 5
    petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
    petsc_options_value = 'hypre    boomeramg      101'
  []

  [Outputs]
    perf_graph = true
    exodus = true
  []
