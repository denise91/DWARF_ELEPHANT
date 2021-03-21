[Mesh]
 file = RBRFAGeom3D_r3e-3_l5e-2_L1e-1_d3r_h15e-1l_Test1.msh
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
[./DiffusionXY_maxZ1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 1
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 2
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 3
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 4
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 5
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 6
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 7
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 8
  block = 1
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 9
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 10
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 11
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 12
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 13
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 14
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 15
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 16
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 17
  block = 2
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 18
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 19
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 20
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 21
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 22
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 23
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 24
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 25
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 26
  block = 3
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 27
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 28
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 29
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 30
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 31
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 32
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 33
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 34
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 35
  block = 4
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxZ5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 36
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxZ5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 37
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxZ5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 38
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxZ5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 39
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxZ5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 40
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxZ5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 41
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxZ5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 42
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxZ5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 43
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxZ5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 44
  block = 5
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 45
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 46
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 47
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 48
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 49
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 50
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 51
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 52
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 53
  block = 6
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 54
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 55
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 56
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 57
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 58
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 59
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 60
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 61
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 62
  block = 7
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 63
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 64
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 65
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 66
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 67
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 68
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 69
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 70
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 71
  block = 8
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 72
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 73
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 74
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 75
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 76
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 77
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 78
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 79
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 80
  block = 9
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minX5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 81
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minX5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 82
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minX5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 83
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minX5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 84
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minX5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 85
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minX5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 86
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minX5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 87
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minX5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 88
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minX5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 89
  block = 10
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 90
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 91
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 92
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 93
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 94
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 95
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 96
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 97
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 98
  block = 11
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 99
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 100
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 101
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 102
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 103
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 104
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 105
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 106
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 107
  block = 12
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 108
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 109
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 110
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 111
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 112
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 113
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 114
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 115
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 116
  block = 13
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 117
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 118
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 119
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 120
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 121
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 122
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 123
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 124
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 125
  block = 14
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxY5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 126
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxY5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 127
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxY5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 128
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxY5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 129
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxY5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 130
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxY5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 131
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxY5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 132
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxY5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 133
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxY5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 134
  block = 15
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 135
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 136
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 137
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 138
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 139
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 140
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 141
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 142
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 143
  block = 16
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 144
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 145
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 146
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 147
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 148
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 149
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 150
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 151
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 152
  block = 17
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 153
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 154
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 155
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 156
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 157
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 158
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 159
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 160
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 161
  block = 18
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 162
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 163
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 164
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 165
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 166
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 167
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 168
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 169
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 170
  block = 19
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_maxX5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 171
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_maxX5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 172
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_maxX5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 173
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_maxX5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 174
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_maxX5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 175
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_maxX5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 176
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_maxX5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 177
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_maxX5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 178
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_maxX5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 179
  block = 20
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 180
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 181
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 182
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 183
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 184
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 185
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 186
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 187
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 188
  block = 21
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 189
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 190
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 191
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 192
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 193
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 194
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 195
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 196
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 197
  block = 22
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 198
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 199
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 200
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 201
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 202
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 203
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 204
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 205
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 206
  block = 23
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 207
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 208
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 209
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 210
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 211
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 212
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 213
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 214
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 215
  block = 24
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minY5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 216
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minY5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 217
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minY5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 218
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minY5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 219
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minY5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 220
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minY5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 221
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minY5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 222
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minY5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 223
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minY5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 224
  block = 25
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ1]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 225
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ1]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 226
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ1]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 227
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ1]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 228
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ1]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 229
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ1]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 230
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ1]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 231
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ1]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 232
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ1]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 233
  block = 26
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ2]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 234
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ2]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 235
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ2]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 236
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ2]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 237
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ2]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 238
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ2]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 239
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ2]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 240
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ2]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 241
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ2]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 242
  block = 27
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ3]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 243
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ3]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 244
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ3]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 245
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ3]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 246
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ3]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 247
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ3]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 248
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ3]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 249
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ3]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 250
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ3]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 251
  block = 28
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ4]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 252
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ4]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 253
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ4]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 254
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ4]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 255
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ4]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 256
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ4]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 257
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ4]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 258
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ4]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 259
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ4]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 260
  block = 29
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_minZ5]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 261
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_minZ5]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 262
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_minZ5]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 263
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_minZ5]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 264
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_minZ5]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 265
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_minZ5]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 266
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_minZ5]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 267
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_minZ5]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 268
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_minZ5]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 269
  block = 30
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_VesselCyl]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 270
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_VesselCyl]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 271
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_VesselCyl]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 272
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_VesselCyl]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 273
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_VesselCyl]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 274
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_VesselCyl]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 275
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_VesselCyl]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 276
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_VesselCyl]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 277
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_VesselCyl]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 278
  block = 31
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXX_BoundingBox]
  type = DwarfElephantRBDiffusionXX
  ID_Aq = 279
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXY_BoundingBox]
  type = DwarfElephantRBDiffusionXY
  ID_Aq = 280
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionXZ_BoundingBox]
  type = DwarfElephantRBDiffusionXZ
  ID_Aq = 281
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYX_BoundingBox]
  type = DwarfElephantRBDiffusionYX
  ID_Aq = 282
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYY_BoundingBox]
  type = DwarfElephantRBDiffusionYY
  ID_Aq = 283
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionYZ_BoundingBox]
  type = DwarfElephantRBDiffusionYZ
  ID_Aq = 284
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZX_BoundingBox]
  type = DwarfElephantRBDiffusionZX
  ID_Aq = 285
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZY_BoundingBox]
  type = DwarfElephantRBDiffusionZY
  ID_Aq = 286
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./DiffusionZZ_BoundingBox]
  type = DwarfElephantRBDiffusionZZ
  ID_Aq = 287
  block = 32
matrix_seperation_according_to_subdomains = false
[../]
[./EIMF]
  type = DwarfElephantEIMFKernel
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
ID_Aq = 288
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
  N_max_EIM = 30
  n_training_samples_EIM = 64
  rel_training_tolerance_EIM = 1e-4
  abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4'# mu_2'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.001 0.002 -0.02 -0.02 -0.02'# 0.01'
  parameter_max_values_EIM = '0.005 0.006 0.02 0.02 0.02'# 1.0'
  #parameter_names_EIM = 'mu_0 mu_1'
  #parameter_min_values_EIM = '-1 -1'
  #parameter_max_values_EIM = '-0.01 -0.01'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  execute_on = 'initial'
  N_max_RB = 20
  #offline_stage = false
  n_training_samples_RB = 64
  rel_training_tolerance_RB = 1.e-3
  abs_training_tolerance_RB = 1e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4'    # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_RB = '0.005 0.006 0.02 0.02 0.02'
  #parameter_names_RB = 'mu_0 mu_1'
  #parameter_min_values_RB = '-1 -1'
  #parameter_max_values_RB = '-0.01 -0.01'
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
  online_mu = '0.003 0.0.004 -0.01 -0.01 -0.01'
  online_N = 40
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
