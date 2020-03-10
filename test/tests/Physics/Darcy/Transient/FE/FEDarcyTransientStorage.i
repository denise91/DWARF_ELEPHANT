[Mesh]
 file = ../../../../Meshes/Darcy.msh
[]

[Variables]
  [./pressure]
  [../]
[]

[GlobalParams]
  variable = pressure
[]

[Kernels]
  [./Darcy0]
    type = DwarfElephantFEDarcy
    permeability = 1.e-07
    norm_value_permeability = 1.e-06
    block = 1
  [../]
  [./Conduction1]
    type = DwarfElephantFEDarcy
    permeability = 1.e-05
    norm_value_permeability = 1.e-06
    block = 2
  [../]
  [./Conduction2]
    type = DwarfElephantFEDarcy
    permeability = 1.e-07
    norm_value_permeability = 1.e-06
    block = 3
  [../]
  [./Storage0]
    type = DwarfElephantFEConstantSpecificStorage
    specific_storage = 1.6e-10
    norm_value = 1e-12
  [../]
[]

[BCs]
[./left]
  type = DirichletBC
  boundary = '3 4 5'
  value = 0.0
[../]
[./right]
  type = DirichletBC
  boundary = '6 7 8'
  value = 0.1
[../]
[]

[Executioner]
  type = Transient
  num_steps = 20
  dt = 10
  l_tol = 1.0e-10
  nl_rel_tol = 1.0e-10
  nl_rel_step_tol = 1.0e-10
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre boomeramg 101'
[]

[Outputs]
  perf_graph = true
  exodus = true
[]
