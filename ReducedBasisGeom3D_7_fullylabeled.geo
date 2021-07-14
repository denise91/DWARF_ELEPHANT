// Gmsh project created on Thu Jun 14 14:08:08 2018

// Constructs 3D reduced basis model of blood vessel in tissue. Consists of an outer cube containing a bounding box
// Bounding box in turn contains a cylinder
// All are of variable dimensions
Mesh.MshFileVersion = 2.2;

// L is the length/width of the outer cube
L = DefineNumber[ 0.1, Name "Parameters/L" ];
l = DefineNumber[ 0.02602 , Name "Parameters/l" ];
r = DefineNumber[ 0.00306 , Name "Parameters/r" ];
d = DefineNumber[ 0.008159999999999999 , Name "Parameters/d" ];
h = DefineNumber[ 0.03469333333333333 , Name "Parameters/h" ];

cube_meshsize = DefineNumber[ 0.0021249999999999997 , Name "Parameters/cube_meshsize" ];

bounding_box_mesh_size = DefineNumber[ 0.0009999999999999998 , Name "Parameters/bounding_box_mesh_size" ];

cylinder_mesh_size = DefineNumber[ 0.0004999999999999999 , Name "Parameters/cylinder_mesh_size" ];


// Creating points for the outer cube

point_1 = newp;
Point(point_1) = {-L/2, L/2, L/2, cube_meshsize};
point_2 = newp;
Point(point_2) = {L/2, L/2, L/2, cube_meshsize};
point_3 = newp;
Point(point_3) = {L/2, -L/2, L/2, cube_meshsize};
point_4 = newp;
Point(point_4) = {-L/2, -L/2, L/2, cube_meshsize};
point_13 = newp;
Point(point_13) = {-L/2, L/2, -L/2, cube_meshsize};
point_14 = newp;
Point(point_14) = {L/2, L/2, -L/2, cube_meshsize};
point_15 = newp;
Point(point_15) = {L/2, -L/2, -L/2, cube_meshsize};
point_16 = newp;
Point(point_16) = {-L/2, -L/2, -L/2, cube_meshsize};

//lines top
line_1_2 = newl;
Line(line_1_2) = {point_1, point_2};
line_2_3 = newl;
Line(line_2_3) = {point_2, point_3};
line_3_4 = newl;
Line(line_3_4) = {point_3, point_4};
line_1_4 = newl;
Line(line_1_4) = {point_1, point_4};

//lines vertical
line_1_13 = newl;
Line(line_1_13) = {point_1, point_13};
line_2_14 = newl;
Line(line_2_14) = {point_2, point_14};
line_3_15 = newl;
Line(line_3_15) = {point_3, point_15};
line_4_16 = newl;
Line(line_4_16) = {point_4, point_16};

//lines bottom
line_13_14 = newl;
Line(line_13_14) = {point_13, point_14};
line_14_15 = newl;
Line(line_14_15) = {point_14, point_15};
line_15_16 = newl;
Line(line_15_16) = {point_15, point_16};
line_13_16 = newl;
Line(line_13_16) = {point_13, point_16};


point_5 = newp;
Point(point_5) = {-d/2, d/2, h/2, bounding_box_mesh_size};
point_6 = newp;
Point(point_6) = {d/2, d/2, h/2, bounding_box_mesh_size};
point_7 = newp;
Point(point_7) = {d/2, -d/2, h/2, bounding_box_mesh_size};
point_8 = newp;
Point(point_8) = {-d/2, -d/2, h/2, bounding_box_mesh_size};
point_9 = newp;
Point(point_9) = {-d/2, d/2, -h/2, bounding_box_mesh_size};
point_10 = newp;
Point(point_10) = {d/2, d/2, -h/2, bounding_box_mesh_size};
point_11 = newp;
Point(point_11) = {d/2, -d/2, -h/2, bounding_box_mesh_size};
point_12 = newp;
Point(point_12) = {-d/2, -d/2, -h/2, bounding_box_mesh_size};

Printf("points 1, 9, 13: %g, %g, %g",point_1,point_9,point_13);

line_5_6 = newl;
Line(line_5_6) = {point_5, point_6};
line_6_7 = newl;
Line(line_6_7) = {point_6, point_7};
line_7_8 = newl;
Line(line_7_8) = {point_7, point_8};
line_5_8 = newl;
Line(line_5_8) = {point_5, point_8};

// lines inner cube
line_5_9 = newl;
Line(line_5_9) = {point_5, point_9};
line_6_10 = newl;
Line(line_6_10) = {point_6, point_10};
line_7_11 = newl;
Line(line_7_11) = {point_7, point_11};
line_8_12 = newl;
Line(line_8_12) = {point_8, point_12};

line_9_10 = newl;
Line(line_9_10) = {point_9, point_10};
line_10_11 = newl;
Line(line_10_11) = {point_10, point_11};
line_11_12 = newl;
Line(line_11_12) = {point_11, point_12};
line_9_12 = newl;
Line(line_9_12) = {point_9, point_12};

// lines between cubes
line_1_5 = newl;
Line(line_1_5) = {point_1, point_5};
line_2_6 = newl;
Line(line_2_6) = {point_2, point_6};
line_3_7 = newl;
Line(line_3_7) = {point_3, point_7};
line_4_8 = newl;
Line(line_4_8) = {point_4, point_8};

line_9_13 = newl;
Line(line_9_13) = {point_9, point_13};
line_10_14 = newl;
Line(line_10_14) = {point_10, point_14};
line_11_15 = newl;
Line(line_11_15) = {point_11, point_15};
line_12_16 = newl;
Line(line_12_16) = {point_12, point_16};

// drawing cylinder
cyl_z_max_center = newp;
Point(cyl_z_max_center) = {0, 0, l/2, cylinder_mesh_size};

cyl_z_max_point_1 = newp;
Point(cyl_z_max_point_1) = {0, r, l/2, cylinder_mesh_size};

cyl_z_max_point_2 = newp;
Point(cyl_z_max_point_2) = {r, 0, l/2, cylinder_mesh_size};

cyl_z_max_point_3 = newp;
Point(cyl_z_max_point_3) = {0, -r, l/2, cylinder_mesh_size};

cyl_z_max_point_4 = newp;
Point(cyl_z_max_point_4) = {-r, 0, l/2, cylinder_mesh_size};

cyl_z_max_circle_1 = newl;
Circle(cyl_z_max_circle_1) = {cyl_z_max_point_1, cyl_z_max_center, cyl_z_max_point_2};
cyl_z_max_circle_2 = newl;
Circle(cyl_z_max_circle_2) = {cyl_z_max_point_2, cyl_z_max_center, cyl_z_max_point_3};
cyl_z_max_circle_3 = newl;
Circle(cyl_z_max_circle_3) = {cyl_z_max_point_3, cyl_z_max_center, cyl_z_max_point_4};
cyl_z_max_circle_4 = newl;
Circle(cyl_z_max_circle_4) = {cyl_z_max_point_4, cyl_z_max_center, cyl_z_max_point_1};

cyl_z_max_lineloop = news;
Line Loop(cyl_z_max_lineloop) = {cyl_z_max_circle_1,cyl_z_max_circle_2,cyl_z_max_circle_3,cyl_z_max_circle_4};
cyl_z_max_surface = news;
Surface(cyl_z_max_surface) = {cyl_z_max_lineloop};

cylinder[] = Extrude {0, 0, -l} { Surface{cyl_z_max_surface}; };
Physical Volume("cylinder",31) = {cylinder[1]};

//lines
//maxZ1
line_2_4 = newl;
Line(line_2_4) = {point_2, point_4};
line_2_5 = newl;
Line(line_2_5) = {point_2, point_5};
line_4_5 = newl;
Line(line_4_5) = {point_4, point_5};

//maxZ2

line_2_7 = newl;
Line(line_2_7) = {point_2, point_7};
line_4_7 = newl;
Line(line_4_7) = {point_4, point_7};

//max Z3
line_5_7 = newl;
Line(line_5_7) = {point_5, point_7};

//minX1
line_4_13 = newl;
Line(line_4_13) = {point_4, point_13};
line_5_13 = newl;
Line(line_5_13) = {point_5, point_13};

//minX2
line_4_12 = newl;
Line(line_4_12) = {point_4, point_12};
line_12_13 = newl;
Line(line_12_13) = {point_12, point_13};

//minX3
line_5_12 = newl;
Line(line_5_12) = {point_5, point_12};

//minx4


//maxY1
line_2_13 = newl;
Line(line_2_13) = {point_2, point_13};

//maxY2
line_2_10 = newl;
Line(line_2_10) = {point_2, point_10};
line_10_13 = newl;
Line(line_10_13) = {point_10, point_13};

//maxY3
line_5_10 = newl;
Line(line_5_10) = {point_5, point_10};

//maxX1
line_2_15 = newl;
Line(line_2_15) = {point_2, point_15};
line_7_15 = newl;
Line(line_7_15) = {point_7, point_15};

//maxX2
line_10_15 = newl;
Line(line_10_15) = {point_10, point_15};

//maxX3
line_7_10 = newl;
Line(line_7_10) = {point_7, point_10};

//maxX4

//minY1
line_4_15 = newl;
Line(line_4_15) = {point_4, point_15};

//minY2
line_12_15 = newl;
Line(line_12_15) = {point_12, point_15};

//minY1
line_7_12 = newl;
Line(line_7_12) = {point_7, point_12};

//minZ1
line_13_15 = newl;
Line(line_13_15) = {point_13, point_15};

//minZ3
line_10_12 = newl;
Line(line_10_12) = {point_10, point_12};



// maxZ1

lineloop_1_2_4 = news;
Line Loop(lineloop_1_2_4) = {line_1_2,line_2_4,-line_1_4};
surface_1_2_4 = news;
Surface(surface_1_2_4) = {lineloop_1_2_4};

lineloop_1_2_5 = news;
Line Loop(lineloop_1_2_5) = {line_1_2,line_2_5,-line_1_5};
surface_1_2_5 = news;
Surface(surface_1_2_5) = {lineloop_1_2_5};

lineloop_1_4_5 = news;
Line Loop(lineloop_1_4_5) = {line_1_4,line_4_5,-line_1_5};
surface_1_4_5 = news;
Surface(surface_1_4_5) = {lineloop_1_4_5};

lineloop_2_4_5 = news;
Line Loop(lineloop_2_4_5) = {line_2_4,line_4_5,-line_2_5};
surface_2_4_5 = news;
Surface(surface_2_4_5) = {lineloop_2_4_5};

// maxZ2

lineloop_2_3_4 = news;
Line Loop(lineloop_2_3_4) = {line_2_3,line_3_4,-line_2_4};
surface_2_3_4 = news;
Surface(surface_2_3_4) = {lineloop_2_3_4};

lineloop_2_3_7 = news;
Line Loop(lineloop_2_3_7) = {line_2_3,line_3_7,-line_2_7};
surface_2_3_7 = news;
Surface(surface_2_3_7) = {lineloop_2_3_7};

lineloop_2_4_7 = news;
Line Loop(lineloop_2_4_7) = {line_2_4,line_4_7,-line_2_7};
surface_2_4_7 = news;
Surface(surface_2_4_7) = {lineloop_2_4_7};

lineloop_3_4_7 = news;
Line Loop(lineloop_3_4_7) = {line_3_4,line_4_7,-line_3_7};
surface_3_4_7 = news;
Surface(surface_3_4_7) = {lineloop_3_4_7};

// maxZ3

lineloop_2_5_6 = news;
Line Loop(lineloop_2_5_6) = {line_2_5,line_5_6,-line_2_6};
surface_2_5_6 = news;
Surface(surface_2_5_6) = {lineloop_2_5_6};

lineloop_2_5_7 = news;
Line Loop(lineloop_2_5_7) = {line_2_5,line_5_7,-line_2_7};
surface_2_5_7 = news;
Surface(surface_2_5_7) = {lineloop_2_5_7};

lineloop_2_6_7 = news;
Line Loop(lineloop_2_6_7) = {line_2_6,line_6_7,-line_2_7};
surface_2_6_7 = news;
Surface(surface_2_6_7) = {lineloop_2_6_7};

lineloop_5_6_7 = news;
Line Loop(lineloop_5_6_7) = {line_5_6,line_6_7,-line_5_7};
surface_5_6_7 = news;
Surface(surface_5_6_7) = {lineloop_5_6_7};

// maxZ4

lineloop_4_5_7 = news;
Line Loop(lineloop_4_5_7) = {line_4_5, line_5_7, -line_4_7};
surface_4_5_7 = news;
Surface(surface_4_5_7) = {lineloop_4_5_7};

lineloop_4_5_8 = news;
Line Loop(lineloop_4_5_8) = {line_4_5, line_5_8, -line_4_8};
surface_4_5_8 = news;
Surface(surface_4_5_8) = {lineloop_4_5_8};

lineloop_4_7_8 = news;
Line Loop(lineloop_4_7_8) = {line_4_7, line_7_8, -line_4_8};
surface_4_7_8 = news;
Surface(surface_4_7_8) = {lineloop_4_7_8};

lineloop_5_7_8 = news;
Line Loop(lineloop_5_7_8) = {line_5_7, line_7_8, -line_5_8};
surface_5_7_8 = news;
Surface(surface_5_7_8) = {lineloop_5_7_8};

// maxZ5

// minX1

lineloop_1_4_13 = news;
Line Loop(lineloop_1_4_13) = {line_1_4, line_4_13, -line_1_13};
surface_1_4_13 = news;
Surface(surface_1_4_13) = {lineloop_1_4_13};

lineloop_1_5_13 = news;
Line Loop(lineloop_1_5_13) = {line_1_5, line_5_13, -line_1_13};
surface_1_5_13 = news;
Surface(surface_1_5_13) = {lineloop_1_5_13};

lineloop_4_5_13 = news;
Line Loop(lineloop_4_5_13) = {line_4_5, line_5_13, -line_4_13};
surface_4_5_13 = news;
Surface(surface_4_5_13) = {lineloop_4_5_13};

// minX2
lineloop_4_12_13 = news;
Line Loop(lineloop_4_12_13) = {line_4_12, line_12_13, -line_4_13};
surface_4_12_13 = news;
Surface(surface_4_12_13) = {lineloop_4_12_13};

lineloop_4_12_16 = news;
Line Loop(lineloop_4_12_16) = {line_4_12, line_12_16, -line_4_16};
surface_4_12_16 = news;
Surface(surface_4_12_16) = {lineloop_4_12_16};

lineloop_4_13_16 = news;
Line Loop(lineloop_4_13_16) = {line_4_13, line_13_16, -line_4_16};
surface_4_13_16 = news;
Surface(surface_4_13_16) = {lineloop_4_13_16};

lineloop_12_13_16 = news;
Line Loop(lineloop_12_13_16) = {line_12_13, line_13_16, -line_12_16};
surface_12_13_16 = news;
Surface(surface_12_13_16) = {lineloop_12_13_16};

// minX3

lineloop_4_5_12 = news;
Line Loop(lineloop_4_5_12) = {line_4_5, line_5_12, -line_4_12};
surface_4_5_12 = news;
Surface(surface_4_5_12) = {lineloop_4_5_12};

lineloop_4_8_12 = news;
Line Loop(lineloop_4_8_12) = {line_4_8, line_8_12, -line_4_12};
surface_4_8_12 = news;
Surface(surface_4_8_12) = {lineloop_4_8_12};

lineloop_5_8_12 = news;
Line Loop(lineloop_5_8_12) = {line_5_8, line_8_12, -line_5_12};
surface_5_8_12 = news;
Surface(surface_5_8_12) = {lineloop_5_8_12};

// minX4

lineloop_5_9_12 = news;
Line Loop(lineloop_5_9_12) = {line_5_9, line_9_12, -line_5_12};
surface_5_9_12 = news;
Surface(surface_5_9_12) = {lineloop_5_9_12};

lineloop_5_9_13 = news;
Line Loop(lineloop_5_9_13) = {line_5_9, line_9_13, -line_5_13};
surface_5_9_13 = news;
Surface(surface_5_9_13) = {lineloop_5_9_13};

lineloop_5_12_13 = news;
Line Loop(lineloop_5_12_13) = {line_5_12, line_12_13, -line_5_13};
surface_5_12_13 = news;
Surface(surface_5_12_13) = {lineloop_5_12_13};

lineloop_9_12_13 = news;
Line Loop(lineloop_9_12_13) = {line_9_12, line_12_13, -line_9_13};
surface_9_12_13 = news;
Surface(surface_9_12_13) = {lineloop_9_12_13};

// minX5

// maxY1
lineloop_1_2_13 = news;
Line Loop(lineloop_1_2_13) = {line_1_2, line_2_13, -line_1_13};
surface_1_2_13 = news;
Surface(surface_1_2_13) = {lineloop_1_2_13};

lineloop_2_5_13 = news;
Line Loop(lineloop_2_5_13) = {line_2_5, line_5_13, -line_2_13};
surface_2_5_13 = news;
Surface(surface_2_5_13) = {lineloop_2_5_13};

// maxY2

lineloop_2_10_13 = news;
Line Loop(lineloop_2_10_13) = {line_2_10, line_10_13, -line_2_13};
surface_2_10_13 = news;
Surface(surface_2_10_13) = {lineloop_2_10_13};

lineloop_2_10_14 = news;
Line Loop(lineloop_2_10_14) = {line_2_10, line_10_14, -line_2_14};
surface_2_10_14 = news;
Surface(surface_2_10_14) = {lineloop_2_10_14};

lineloop_2_13_14 = news;
Line Loop(lineloop_2_13_14) = {line_2_13, line_13_14, -line_2_14};
surface_2_13_14 = news;
Surface(surface_2_13_14) = {lineloop_2_13_14};

lineloop_10_13_14 = news;
Line Loop(lineloop_10_13_14) = {line_10_13, line_13_14, -line_10_14};
surface_10_13_14 = news;
Surface(surface_10_13_14) = {lineloop_10_13_14};

// maxY3

lineloop_2_5_10 = news;
Line Loop(lineloop_2_5_10) = {line_2_5, line_5_10, -line_2_10};
surface_2_5_10 = news;
Surface(surface_2_5_10) = {lineloop_2_5_10};

lineloop_2_6_10 = news;
Line Loop(lineloop_2_6_10) = {line_2_6, line_6_10, -line_2_10};
surface_2_6_10 = news;
Surface(surface_2_6_10) = {lineloop_2_6_10};

lineloop_5_6_10 = news;
Line Loop(lineloop_5_6_10) = {line_5_6, line_6_10, -line_5_10};
surface_5_6_10 = news;
Surface(surface_5_6_10) = {lineloop_5_6_10};

// maxY4

lineloop_5_9_10 = news;
Line Loop(lineloop_5_9_10) = {line_5_9, line_9_10, -line_5_10};
surface_5_9_10 = news;
Surface(surface_5_9_10) = {lineloop_5_9_10};

lineloop_5_10_13 = news;
Line Loop(lineloop_5_10_13) = {line_5_10, line_10_13, -line_5_13};
surface_5_10_13 = news;
Surface(surface_5_10_13) = {lineloop_5_10_13};

lineloop_9_10_13 = news;
Line Loop(lineloop_9_10_13) = {line_9_10, line_10_13, -line_9_13};
surface_9_10_13 = news;
Surface(surface_9_10_13) = {lineloop_9_10_13};

// maxY5

// maxX1

lineloop_2_3_15 = news;
Line Loop(lineloop_2_3_15) = {line_2_3, line_3_15, -line_2_15};
surface_2_3_15 = news;
Surface(surface_2_3_15) = {lineloop_2_3_15};

lineloop_2_7_15 = news;
Line Loop(lineloop_2_7_15) = {line_2_7, line_7_15, -line_2_15};
surface_2_7_15 = news;
Surface(surface_2_7_15) = {lineloop_2_7_15};

lineloop_3_7_15 = news;
Line Loop(lineloop_3_7_15) = {line_3_7, line_7_15, -line_3_15};
surface_3_7_15 = news;
Surface(surface_3_7_15) = {lineloop_3_7_15};

// maxX2

lineloop_2_10_15 = news;
Line Loop(lineloop_2_10_15) = {line_2_10, line_10_15, -line_2_15};
surface_2_10_15 = news;
Surface(surface_2_10_15) = {lineloop_2_10_15};

lineloop_2_14_15 = news;
Line Loop(lineloop_2_14_15) = {line_2_14, line_14_15, -line_2_15};
surface_2_14_15 = news;
Surface(surface_2_14_15) = {lineloop_2_14_15};

lineloop_10_14_15 = news;
Line Loop(lineloop_10_14_15) = {line_10_14, line_14_15, -line_10_15};
surface_10_14_15 = news;
Surface(surface_10_14_15) = {lineloop_10_14_15};

// maxX3

lineloop_2_7_10 = news;
Line Loop(lineloop_2_7_10) = {line_2_7, line_7_10, -line_2_10};
surface_2_7_10 = news;
Surface(surface_2_7_10) = {lineloop_2_7_10};

lineloop_6_7_10 = news;
Line Loop(lineloop_6_7_10) = {line_6_7, line_7_10, -line_6_10};
surface_6_7_10 = news;
Surface(surface_6_7_10) = {lineloop_6_7_10};

// maxX4

lineloop_7_10_11 = news;
Line Loop(lineloop_7_10_11) = {line_7_10, line_10_11, -line_7_11};
surface_7_10_11 = news;
Surface(surface_7_10_11) = {lineloop_7_10_11};

lineloop_7_10_15 = news;
Line Loop(lineloop_7_10_15) = {line_7_10, line_10_15, -line_7_15};
surface_7_10_15 = news;
Surface(surface_7_10_15) = {lineloop_7_10_15};

lineloop_7_11_15 = news;
Line Loop(lineloop_7_11_15) = {line_7_11, line_11_15, -line_7_15};
surface_7_11_15 = news;
Surface(surface_7_11_15) = {lineloop_7_11_15};

lineloop_10_11_15 = news;
Line Loop(lineloop_10_11_15) = {line_10_11, line_11_15, -line_10_15};
surface_10_11_15 = news;
Surface(surface_10_11_15) = {lineloop_10_11_15};

// maxX5

// minY1

lineloop_3_4_15 = news;
Line Loop(lineloop_3_4_15) = {line_3_4, line_4_15, -line_3_15};
surface_3_4_15 = news;
Surface(surface_3_4_15) = {lineloop_3_4_15};
lineloop_4_7_15 = news;
Line Loop(lineloop_4_7_15) = {line_4_7, line_7_15, -line_4_15};
surface_4_7_15 = news;
Surface(surface_4_7_15) = {lineloop_4_7_15};

// minY2

lineloop_4_12_15 = news;
Line Loop(lineloop_4_12_15) = {line_4_12, line_12_15, -line_4_15};
surface_4_12_15 = news;
Surface(surface_4_12_15) = {lineloop_4_12_15};

lineloop_4_15_16 = news;
Line Loop(lineloop_4_15_16) = {line_4_15, line_15_16, -line_4_16};
surface_4_15_16 = news;
Surface(surface_4_15_16) = {lineloop_4_15_16};

lineloop_12_15_16 = news;
Line Loop(lineloop_12_15_16) = {line_12_15, line_15_16, -line_12_16};
surface_12_15_16 = news;
Surface(surface_12_15_16) = {lineloop_12_15_16};

// minY3
lineloop_7_11_12 = news;
Line Loop(lineloop_7_11_12) = {line_7_11, line_11_12, -line_7_12};
surface_7_11_12 = news;
Surface(surface_7_11_12) = {lineloop_7_11_12};

lineloop_7_12_15 = news;
Line Loop(lineloop_7_12_15) = {line_7_12, line_12_15, -line_7_15};
surface_7_12_15 = news;
Surface(surface_7_12_15) = {lineloop_7_12_15};

lineloop_11_12_15 = news;
Line Loop(lineloop_11_12_15) = {line_11_12, line_12_15, -line_11_15};
surface_11_12_15 = news;
Surface(surface_11_12_15) = {lineloop_11_12_15};

// minY4

lineloop_7_8_12 = news;
Line Loop(lineloop_7_8_12) = {line_7_8, line_8_12, -line_7_12};
surface_7_8_12 = news;
Surface(surface_7_8_12) = {lineloop_7_8_12};

lineloop_4_7_12 = news;
Line Loop(lineloop_4_7_12) = {line_4_7, line_7_12, -line_4_12};
surface_4_7_12 = news;
Surface(surface_4_7_12) = {lineloop_4_7_12};

// minY5

// minZ1

lineloop_12_13_15 = news;
Line Loop(lineloop_12_13_15) = {line_12_13, line_13_15, -line_12_15};
surface_12_13_15 = news;
Surface(surface_12_13_15) = {lineloop_12_13_15};

lineloop_13_15_16 = news;
Line Loop(lineloop_13_15_16) = {line_13_15, line_15_16, -line_13_16};
surface_13_15_16 = news;
Surface(surface_13_15_16) = {lineloop_13_15_16};

// minZ2
lineloop_10_13_15 = news;
Line Loop(lineloop_10_13_15) = {line_10_13, line_13_15, -line_10_15};
surface_10_13_15 = news;
Surface(surface_10_13_15) = {lineloop_10_13_15};

lineloop_13_14_15 = news;
Line Loop(lineloop_13_14_15) = {line_13_14, line_14_15, -line_13_15};
surface_13_14_15 = news;
Surface(surface_13_14_15) = {lineloop_13_14_15};

// minZ3

lineloop_9_10_12 = news;
Line Loop(lineloop_9_10_12) = {line_9_10, line_10_12, -line_9_12};
surface_9_10_12 = news;
Surface(surface_9_10_12) = {lineloop_9_10_12};

lineloop_10_12_13 = news;
Line Loop(lineloop_10_12_13) = {line_10_12, line_12_13, -line_10_13};
surface_10_12_13 = news;
Surface(surface_10_12_13) = {lineloop_10_12_13};

// minZ4

lineloop_10_11_12 = news;
Line Loop(lineloop_10_11_12) = {line_10_11, line_11_12, -line_10_12};
surface_10_11_12 = news;
Surface(surface_10_11_12) = {lineloop_10_11_12};

lineloop_10_12_15 = news;
Line Loop(lineloop_10_12_15) = {line_10_12, line_12_15, -line_10_15};
surface_10_12_15 = news;
Surface(surface_10_12_15) = {lineloop_10_12_15};

// minZ5


// Volumes of tetrahedra

//maxZ1
surfaceloop_maxZ1 = newsl;
Surface Loop(surfaceloop_maxZ1) = {surface_1_2_4, surface_1_2_5, surface_1_4_5, surface_2_4_5};
volume_maxZ1 = newv;
Volume(volume_maxZ1) = {surfaceloop_maxZ1};
Physical Volume("maxZ1",1) = {volume_maxZ1};


//maxZ2
surfaceloop_maxZ2 = newsl;
Surface Loop(surfaceloop_maxZ2) = {surface_2_3_4, surface_2_4_7, surface_2_3_7, surface_3_4_7};
volume_maxZ2 = newv;
Volume(volume_maxZ2) = {surfaceloop_maxZ2};
Physical Volume("maxZ2",2) = {volume_maxZ2};

//maxZ3
surfaceloop_maxZ3 = newsl;
Surface Loop(surfaceloop_maxZ3) = {surface_2_5_6, surface_2_5_7, surface_2_6_7, surface_5_6_7};
volume_maxZ3 = newv;
Volume(volume_maxZ3) = {surfaceloop_maxZ3};
Physical Volume("maxZ3",3) = {volume_maxZ3};

//maxZ4
surfaceloop_maxZ4 = newsl;
Surface Loop(surfaceloop_maxZ4) = {surface_4_5_7, surface_4_5_8, surface_4_7_8, surface_5_7_8};
volume_maxZ4 = newv;
Volume(volume_maxZ4) = {surfaceloop_maxZ4};
Physical Volume("maxZ4",4) = {volume_maxZ4};

//maxZ5
surfaceloop_maxZ5 = newsl;
Surface Loop(surfaceloop_maxZ5) = {surface_2_4_7, surface_2_5_7, surface_4_5_7, surface_2_4_5};
volume_maxZ5 = newv;
Volume(volume_maxZ5) = {surfaceloop_maxZ5};
Physical Volume("maxZ5",5) = {volume_maxZ5};

//minX1
surfaceloop_minX1 = newsl;
Surface Loop(surfaceloop_minX1) = {surface_1_4_5, surface_1_5_13, surface_1_4_13, surface_4_5_13};
volume_minX1 = newv;
Volume(volume_minX1) = {surfaceloop_minX1};
Physical Volume("minX1",6) = {volume_minX1};

//minX2
surfaceloop_minX2 = newsl;
Surface Loop(surfaceloop_minX2) = {surface_4_12_13, surface_4_12_16, surface_4_13_16, surface_12_13_16};
volume_minX2 = newv;
Volume(volume_minX2) = {surfaceloop_minX2};
Physical Volume("minX2",7) = {volume_minX2};

//minX3
surfaceloop_minX3 = newsl;
Surface Loop(surfaceloop_minX3) = {surface_4_5_8, surface_4_8_12, surface_4_5_12, surface_5_8_12};
volume_minX3 = newv;
Volume(volume_minX3) = {surfaceloop_minX3};
Physical Volume("minX3",8) = {volume_minX3};

//minX4
surfaceloop_minX4 = newsl;
Surface Loop(surfaceloop_minX4) = {surface_5_9_12, surface_5_9_13, surface_5_12_13, surface_9_12_13};
volume_minX4 = newv;
Volume(volume_minX4) = {surfaceloop_minX4};
Physical Volume("minX4",9) = {volume_minX4};

//minX5
surfaceloop_minX5 = newsl;
Surface Loop(surfaceloop_minX5) = {surface_4_5_12, surface_4_5_13, surface_4_12_13, surface_5_12_13};
volume_minX5 = newv;
Volume(volume_minX5) = {surfaceloop_minX5};
Physical Volume("minX5",10) = {volume_minX5};

//maxY1
surfaceloop_maxY1 = newsl;
Surface Loop(surfaceloop_maxY1) = {surface_1_2_5, surface_1_2_13, surface_1_5_13, surface_2_5_13};
volume_maxY1 = newv;
Volume(volume_maxY1) = {surfaceloop_maxY1};
Physical Volume("maxY1",11) = {volume_maxY1};

//maxY2
surfaceloop_maxY2 = newsl;
Surface Loop(surfaceloop_maxY2) = {surface_2_10_13, surface_2_10_14, surface_2_13_14, surface_10_13_14};
volume_maxY2 = newv;
Volume(volume_maxY2) = {surfaceloop_maxY2};
Physical Volume("maxY2",12) = {volume_maxY2};

//maxY3
surfaceloop_maxY3 = newsl;
Surface Loop(surfaceloop_maxY3) = {surface_2_5_6, surface_2_5_10, surface_2_6_10, surface_5_6_10};
volume_maxY3 = newv;
Volume(volume_maxY3) = {surfaceloop_maxY3};
Physical Volume("maxY3",13) = {volume_maxY3};

//maxY4
surfaceloop_maxY4 = newsl;
Surface Loop(surfaceloop_maxY4) = {surface_5_9_10, surface_5_9_13, surface_5_10_13, surface_9_10_13};
volume_maxY4 = newv;
Volume(volume_maxY4) = {surfaceloop_maxY4};
Physical Volume("maxY4",14) = {volume_maxY4};

//maxY5
surfaceloop_maxY5 = newsl;
Surface Loop(surfaceloop_maxY5) = {surface_2_5_10, surface_2_5_13, surface_2_10_13, surface_5_10_13};
volume_maxY5 = newv;
Volume(volume_maxY5) = {surfaceloop_maxY5};
Physical Volume("maxY5",15) = {volume_maxY5};

// maxX volumes

surfaceloop_maxX1 = newsl;
Surface Loop(surfaceloop_maxX1) = {surface_2_3_7,surface_2_3_15,surface_2_7_15,surface_3_7_15};
volume_maxX1 = newv;
Volume(volume_maxX1) = {surfaceloop_maxX1};
Physical Volume("maxX1",16) = {volume_maxX1};

surfaceloop_maxX2 = newsl;
Surface Loop(surfaceloop_maxX2) = {surface_2_10_14,surface_2_10_15,surface_2_14_15,surface_10_14_15};
volume_maxX2 = newv;
Volume(volume_maxX2) = {surfaceloop_maxX2};
Physical Volume("maxX2",17) = {volume_maxX2};

surfaceloop_maxX3 = newsl;
Surface Loop(surfaceloop_maxX3) = {surface_2_6_7,surface_2_6_10,surface_2_7_10,surface_6_7_10};
volume_maxX3 = newv;
Volume(volume_maxX3) = {surfaceloop_maxX3};
Physical Volume("maxX3",18) = {volume_maxX3};

surfaceloop_maxX4 = newsl;
Surface Loop(surfaceloop_maxX4) = {surface_7_10_11,surface_7_10_15,surface_7_11_15,surface_10_11_15};
volume_maxX4 = newv;
Volume(volume_maxX4) = {surfaceloop_maxX4};
Physical Volume("maxX4",19) = {volume_maxX4};

surfaceloop_maxX5 = newsl;
Surface Loop(surfaceloop_maxX5) = {surface_2_7_10,surface_2_10_15,surface_2_7_15,surface_7_10_15};
volume_maxX5 = newv;
Volume(volume_maxX5) = {surfaceloop_maxX5};
Physical Volume("maxX5",20) = {volume_maxX5};

// minY Volumes

surfaceloop_minY1 = newsl;
Surface Loop(surfaceloop_minY1) = {surface_3_4_7,surface_3_7_15,surface_3_4_15,surface_4_7_15};
volume_minY1 = newv;
Volume(volume_minY1) = {surfaceloop_minY1};
Physical Volume("minY1",21) = {volume_minY1};

surfaceloop_minY2 = newsl;
Surface Loop(surfaceloop_minY2) = {surface_4_12_15,surface_4_12_16,surface_4_15_16,surface_12_15_16};
volume_minY2 = newv;
Volume(volume_minY2) = {surfaceloop_minY2};
Physical Volume("minY2",22) = {volume_minY2};


surfaceloop_minY3 = newsl;
Surface Loop(surfaceloop_minY3) = {surface_7_12_15,surface_7_11_15,surface_7_11_12,surface_11_12_15};
volume_minY3 = newv;
Volume(volume_minY3) = {surfaceloop_minY3};
Physical Volume("minY3",23) = {volume_minY3};

surfaceloop_minY4 = newsl;
Surface Loop(surfaceloop_minY4) = {surface_4_7_8,surface_4_7_12,surface_4_8_12,surface_7_8_12};
volume_minY4 = newv;
Volume(volume_minY4) = {surfaceloop_minY4};
Physical Volume("minY4",24) = {volume_minY4};

surfaceloop_minY5 = newsl;
Surface Loop(surfaceloop_minY5) = {surface_4_7_12,surface_4_7_15,surface_4_12_15,surface_7_12_15};
volume_minY5 = newv;
Volume(volume_minY5) = {surfaceloop_minY5};
Physical Volume("minY5",25) = {volume_minY5};

// minZ volumes

surfaceloop_minZ1 = newsl;
Surface Loop(surfaceloop_minZ1) = {surface_12_13_15,surface_12_13_16,surface_12_15_16,surface_13_15_16};
volume_minZ1 = newv;
Volume(volume_minZ1) = {surfaceloop_minZ1};
Physical Volume("minZ1",26) = {volume_minZ1};

surfaceloop_minZ2 = newsl;
Surface Loop(surfaceloop_minZ2) = {surface_10_13_14,surface_10_13_15,surface_10_14_15,surface_13_14_15};
volume_minZ2 = newv;
Volume(volume_minZ2) = {surfaceloop_minZ2};
Physical Volume("minZ2",27) = {volume_minZ2};


surfaceloop_minZ3 = newsl;
Surface Loop(surfaceloop_minZ3) = {surface_9_10_12,surface_9_10_13,surface_9_12_13,surface_10_12_13};
volume_minZ3 = newv;
Volume(volume_minZ3) = {surfaceloop_minZ3};
Physical Volume("minZ3",28) = {volume_minZ3};


surfaceloop_minZ4 = newsl;
Surface Loop(surfaceloop_minZ4) = {surface_10_11_12,surface_10_11_15,surface_10_12_15,surface_11_12_15};
volume_minZ4 = newv;
Volume(volume_minZ4) = {surfaceloop_minZ4};
Physical Volume("minZ4",29) = {volume_minZ4};


surfaceloop_minZ5 = newsl;
Surface Loop(surfaceloop_minZ5) = {surface_10_12_13,surface_10_12_15,surface_10_13_15,surface_12_13_15};
volume_minZ5 = newv;
Volume(volume_minZ5) = {surfaceloop_minZ5};
Physical Volume("minZ5",30) = {volume_minZ5};


Printf("maxZ1 = %g, maxZ2 = %g, maxZ3 = %g, maxZ4 = %g, maxZ5 = %g",volume_maxZ1,volume_maxZ2,volume_maxZ3,volume_maxZ4,volume_maxZ5);
Printf("minX1 = %g, minX2 = %g, minX3 = %g, minX4 = %g, minX5 = %g",volume_minX1,volume_minX2,volume_minX3,volume_minX4,volume_minX5);
Printf("maxY1 = %g, maxY2 = %g, maxY3 = %g, maxY4 = %g, maxY5 = %g",volume_maxY1,volume_maxY2,volume_maxY3,volume_maxY4,volume_maxY5);
Printf("maxX1 = %g, maxX2 = %g, maxX3 = %g, maxX4 = %g, maxX5 = %g",volume_maxX1,volume_maxX2,volume_maxX3,volume_maxX4,volume_maxX5);
Printf("minY1 = %g, minY2 = %g, minY3 = %g, minY4 = %g, minY5 = %g",volume_minY1,volume_minY2,volume_minY3,volume_minY4,volume_minY5);
Printf("minZ1 = %g, minZ2 = %g, minZ3 = %g, minZ4 = %g, minZ5 = %g",volume_minZ1,volume_minZ2,volume_minZ3,volume_minZ4,volume_minZ5);

// volume inside bounding box

bounding_maxX_lineloop = newll;
Line Loop(bounding_maxX_lineloop) = {line_6_7,line_7_11,-line_10_11,-line_6_10};
bounding_maxX_surface = news;
Surface(bounding_maxX_surface) = {bounding_maxX_lineloop};

bounding_maxY_lineloop = newll;
Line Loop(bounding_maxY_lineloop) = {line_5_6,line_6_10,-line_9_10,-line_5_9};
bounding_maxY_surface = news;
Surface(bounding_maxY_surface) = {bounding_maxY_lineloop};

bounding_maxZ_lineloop = newll;
Line Loop(bounding_maxZ_lineloop) = {line_5_6,line_6_7,line_7_8,-line_5_8};
bounding_maxZ_surface = news;
Surface(bounding_maxZ_surface) = {bounding_maxZ_lineloop};

bounding_minX_lineloop = newll;
Line Loop(bounding_minX_lineloop) = {line_5_8,line_8_12,-line_9_12,-line_5_9};
bounding_minX_surface = news;
Surface(bounding_minX_surface) = {bounding_minX_lineloop};

bounding_minY_lineloop = newll;
Line Loop(bounding_minY_lineloop) = {line_7_8,line_8_12,-line_11_12,-line_7_11};
bounding_minY_surface = news;
Surface(bounding_minY_surface) = {bounding_minY_lineloop};

bounding_minZ_lineloop = newll;
Line Loop(bounding_minZ_lineloop) = {line_9_10,line_10_11,line_11_12,-line_9_12};
bounding_minZ_surface = news;
Surface(bounding_minZ_surface) = {bounding_minZ_lineloop};

bounding_surfaceloop = newsl;

Surface Loop(bounding_surfaceloop) = {surface_6_7_10,surface_7_10_11,surface_5_6_10,surface_5_9_10,surface_5_6_7,surface_5_7_8,surface_5_8_12,surface_5_9_12,surface_7_8_12,surface_7_11_12,surface_10_11_12,surface_9_10_12};

cylinder_surfaceloop = newsl;
Surface Loop(cylinder_surfaceloop) = {cyl_z_max_surface,cylinder[0],cylinder[2],cylinder[3],cylinder[4],cylinder[5]};

bounding_volume = newv;
Volume(bounding_volume) = {bounding_surfaceloop, cylinder_surfaceloop};
Physical Volume("bounding box",32) = {bounding_volume};

// Physical surfaces for outside of the cube

Physical Surface("maxZ1_outersurface",33) = {surface_1_2_4};
Physical Surface("maxZ2_outersurface",34) = {surface_2_3_4};
Physical Surface("minZ1_outersurface",35) = {surface_13_15_16};
Physical Surface("minZ2_outersurface",36) = {surface_13_14_15};
Physical Surface("maxY1_outersurface",37) = {surface_1_2_13};
Physical Surface("maxY2_outersurface",38) = {surface_2_13_14};
Physical Surface("minY1_outersurface",39) = {surface_3_4_15};
Physical Surface("minY2_outersurface",40) = {surface_4_15_16};
Physical Surface("maxX1_outersurface",41) = {surface_2_3_15};
Physical Surface("maxX2_outersurface",42) = {surface_2_14_15};
Physical Surface("minX1_outersurface",43) = {surface_1_4_13};
Physical Surface("minX2_outersurface",44) = {surface_4_13_16};
