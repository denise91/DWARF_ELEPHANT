[Mesh]
 file = ReducedBasisGeom3D_7_fullylabeled_debug.msh
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
[./DiffusionXX_maxZ1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 0
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 1
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 2
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 3
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 4
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 5
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 6
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 7
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 8
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 9
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 10
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 11
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 12
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 13
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 14
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 15
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 16
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 17
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 18
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 19
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 20
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 21
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 22
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 23
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 24
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 25
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 26
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 27
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 28
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 29
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 30
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 31
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 32
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 33
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 34
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 35
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 36
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 37
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 38
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 39
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 40
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 41
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 42
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 43
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 44
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 45
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 46
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 47
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 48
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 49
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 50
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 51
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 52
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 53
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 54
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 55
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 56
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 57
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 58
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 59
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 60
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 61
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 62
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 63
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 64
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 65
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 66
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 67
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 68
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 69
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 70
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 71
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 72
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 73
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 74
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 75
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 76
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 77
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 78
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 79
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 80
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 81
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 82
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 83
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 84
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 85
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 86
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 87
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 88
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 89
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_VesselCyl]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 90
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_VesselCyl]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 91
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_VesselCyl]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 92
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_BoundingBox]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 93
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_BoundingBox]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 94
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_BoundingBox]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 95
  block = 32
matrix_seperation_according_to_subdomains = false
[../]

  [./EIM_1]
    type = DwarfElephantEIMFKernel
    block = 1
  [../]
   
  [./EIM_2]
    type = DwarfElephantEIMFKernel
    block = 2
  [../]
   
  [./EIM_3]
    type = DwarfElephantEIMFKernel
    block = 3
  [../]
   
  [./EIM_4]
    type = DwarfElephantEIMFKernel
    block = 4
  [../]
   
  [./EIM_5]
    type = DwarfElephantEIMFKernel
    block = 5
  [../]
   
  [./EIM_6]
    type = DwarfElephantEIMFKernel
    block = 6
  [../]
   
  [./EIM_7]
    type = DwarfElephantEIMFKernel
    block = 7
  [../]
   
  [./EIM_8]
    type = DwarfElephantEIMFKernel
    block = 8
  [../]
   
  [./EIM_9]
    type = DwarfElephantEIMFKernel
    block = 9
  [../]
   
  [./EIM_10]
    type = DwarfElephantEIMFKernel
    block = 10
  [../]
   
  [./EIM_11]
    type = DwarfElephantEIMFKernel
    block = 11
  [../]
   
  [./EIM_12]
    type = DwarfElephantEIMFKernel
    block = 12
  [../]
   
  [./EIM_13]
    type = DwarfElephantEIMFKernel
    block = 13
  [../]
   
  [./EIM_14]
    type = DwarfElephantEIMFKernel
    block = 14
  [../]
   
  [./EIM_15]
    type = DwarfElephantEIMFKernel
    block = 15
  [../]
   
  [./EIM_16]
    type = DwarfElephantEIMFKernel
    block = 16
  [../]
   
  [./EIM_17]
    type = DwarfElephantEIMFKernel
    block = 17
  [../]
   
  [./EIM_18]
    type = DwarfElephantEIMFKernel
    block = 18
  [../]
   
  [./EIM_19]
    type = DwarfElephantEIMFKernel
    block = 19
  [../]
   
  [./EIM_20]
    type = DwarfElephantEIMFKernel
    block = 20
  [../]
   
  [./EIM_21]
    type = DwarfElephantEIMFKernel
    block = 21
  [../]
   
  [./EIM_22]
    type = DwarfElephantEIMFKernel
    block = 22
  [../]
   
  [./EIM_23]
    type = DwarfElephantEIMFKernel
    block = 23
  [../]
   
  [./EIM_24]
    type = DwarfElephantEIMFKernel
    block = 24
  [../]
   
  [./EIM_25]
    type = DwarfElephantEIMFKernel
    block = 25
  [../]
   
  [./EIM_26]
    type = DwarfElephantEIMFKernel
    block = 26
  [../]
   
  [./EIM_27]
    type = DwarfElephantEIMFKernel
    block = 27
  [../]
   
  [./EIM_28]
    type = DwarfElephantEIMFKernel
    block = 28
  [../]
   
  [./EIM_29]
    type = DwarfElephantEIMFKernel
    block = 29
  [../]
   
  [./EIM_30]
    type = DwarfElephantEIMFKernel
    block = 30
  [../]
   
  [./EIM_31]
    type = DwarfElephantEIMFKernel
    block = 31
  [../]
   
  [./EIM_32]
    type = DwarfElephantEIMFKernel
    block = 32
  [../]
   
[./RB_inner_product_matrix]
  type = RBInnerProductMatrix
[../]
[]

[AuxKernels]
  [./HeatSourceVisAux]
    type = FunctionAux
    function = 'gaussian'#'rf_heat_source'
    variable = HeatSourceVis
    execute_on = 'timestep_end'
  [../]
[]

[Functions]
  [./gaussian]
    type = ParsedFunction
    value = 'exp(-(x + 0.1)^2 - (y + 0.1)^2)'
  [../]
[]
[BCs]
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = ' 33 34 35 36 37 38 39 40 41 42 43 44'
ID_Aq = 96
  value = 0
  penalty = 1.0
 variable = temperature
matrix_seperation_according_to_subdomains = false
[../]
[]

[Problem]
  type = DwarfElephantRBProblem
[]

[Executioner]
  type = DwarfElephantRBExecutioner
  solve_type = 'Newton'
  l_tol = 1.0e-8
  nl_rel_tol = 1.0e-8
  #offline_stage = false
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre    boomeramg      101'
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemSteadyState
  use_EIM = true
  use_hp_EIM = false
  #hp_EIM_testing = true # Testing of hp EIM implementation possbile only during the online phase
  N_max_EIM = 3
  n_training_samples_EIM = 6
  rel_training_tolerance_EIM = 1e-4
  #abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.001 0.002 -0.02 -0.02 -0.02'# 0.01'
  parameter_max_values_EIM = '0.005 0.006 0.02 0.02 0.02'# 1.0'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 12
  #offline_stage = false
  n_training_samples_RB = 40
  rel_training_tolerance_RB = 1.e-3
  #abs_training_tolerance_RB = 1e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_RB = '0.005 0.006 0.02 0.02 0.02'
  deterministic_training_RB = false
  normalize_rb_bound_in_greedy = false
[../]

[./jEIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixSteadyState
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]

[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageSteadyState
  #online_stage = true
  online_mu = '0.003 0.004 -0.01 -0.01 -0.01'
  online_N = 5
  #offline_stage = false
  execute_on = 'timestep_end'
[../]
[]

[Outputs]
exodus = true
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
