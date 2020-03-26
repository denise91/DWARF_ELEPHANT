[Mesh]
  file = ../../../../Meshes/RB_mesh_3layers.e
[]

[Variables]
  [./potential]
  [../]
[]

[GlobalParams]
  variable = potential
[]

[Kernels]
  [./PotentialKernelRest]
    type = DwarfElephantFEElectricalConduction
    resistivity = 70
    norm_value = 280 # reference resistivity
    block = '0'
  [../]
  [./PotentialKernelSand]
    type = DwarfElephantFEElectricalConduction
    resistivity = 280
    norm_value = 280 # reference resistivity
    block = '1'
  [../]
  [./PotentialKernelTop]
    type = DwarfElephantFEElectricalConduction
    resistivity = 15
    norm_value = 280 # reference resistivity
    block = '2'
  [../]
[]

[DiracKernels]
  [./InputElectrode_pos]
    type = ConstantPointSource
    value = 0.1
    point = '0.5 0.45 0.95'
  [../]
  [./InputElectrode_neg]
    type = ConstantPointSource
    value = -0.1
    point = '0.5 0.55 0.95'
  [../]
[]


[BCs]
  [./Dirichlets]
    type = DirichletBC
    boundary = 2
    value = 0
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'Newton'
  l_tol = 1.0e-8
  nl_rel_tol = 1.0e-8
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value =  'hypre boomeramg 101'
[]

[Outputs]
  perf_graph = true
  execute_on = 'TIMESTEP_END'
  exodus = true
[]
