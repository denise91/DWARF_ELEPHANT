from HelperModule import *

AqObjectsList = []

BilinearForms = ['Diffusion', 'Perfusion', 'Convection']

#GeomSubdomains = [ # Edit according to the geometry under consideration (EDIT FOR 3D GEOM)
#                 ['11', "max_z_line"], 
#                 ['12', "max_x_line"], 
#                 ['13', "min_z_line"], 
#                 ['14', "min_x_line"], 
#                 ['1' , "maxZ1"], 
#                 ['2' , "maxZ2"], 
#                 ['3' , "maxX1"], 
#                 ['4' , "maxX2"], 
#                 ['5' , "minZ1"], 
#                 ['6' , "minZ2"], 
#                 ['7' , "minX1"],
#                 ['8' , "minX2"], 
#                 ['9' , "BoundingBox"] ]

GeomSubdomains = [ 
                 ["1", "maxZ1"],
                 ["2", "maxZ2"],
                 ["3", "maxZ3"],
                 ["4", "maxZ4"],
                 ["5", "maxZ5"],
                 ["6", "minX1"],
                 ["7", "minX2"],
                 ["8", "minX3"],
                 ["9", "minX4"],
                 ["10", "minX5"],
                 ["11", "maxY1"],
                 ["12", "maxY2"],
                 ["13", "maxY3"],
                 ["14", "maxY4"],
                 ["15", "maxY5"],
                 ["16", "maxX1"],
                 ["17", "maxX2"],
                 ["18", "maxX3"],
                 ["19", "maxX4"],
                 ["20", "maxX5"],
                 ["21", "minY1"],
                 ["22", "minY2"],
                 ["23", "minY3"],
                 ["24", "minY4"],
                 ["25", "minY5"],
                 ["26", "minZ1"],
                 ["27", "minZ2"],
                 ["28", "minZ3"],
                 ["29", "minZ4"],
                 ["30", "minZ5"],
                 ["31", "VesselCyl"],
                 ["32", "BoundingBox"],
                 ["33", "maxZ1_outersurface"],
                 ["34", "maxZ2_outersurface"],
                 ["35", "minZ1_outersurface"],
                 ["36", "minZ2_outersurface"],
                 ["37", "maxY1_outersurface"],
                 ["38", "maxY2_outersurface"],
                 ["39", "minY1_outersurface"],
                 ["40", "minY2_outersurface"],
                 ["41", "maxX1_outersurface"],
                 ["42", "maxX2_outersurface"],
                 ["43", "minX1_outersurface"],
                 ["44", "minX2_outersurface"]]


SubdomainApplicability = {'Diffusion': [1,32], # (EDIT FOR 3D GEOM)
                          'Perfusion': [45, 45],
                          'Convection': [33,44]}# for convection BC

TermsOfBilinearForm = {'Diffusion':['XX','XY','XZ','YX','YY','YZ','ZX','ZY','ZZ'], #(EDIT FOR 3D GEOM)
                       'Perfusion':['Perf'],
                       'Convection':['Conv']}

KernelList = ["[Kernels]\n"]
BCList = ["""[BCs]
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = '"""]

ID_Aq = 0
ConvectionBCFlag = False
AThetaPrefix = "Geom3DRB_ATheta_" #(EDIT FOR 3D GEOM)

RBThetaCFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/include/userobjects/DwarfElephantGeom3DRBTheta_RFA.h" # (EDIT FOR 3D GEOM)

IncludeGaurdName = "DWARFELEPHANTGEOM3DRBTHETA_RFA_H" # EDIT FOR 3D GEOM
with open(RBThetaCFileName,"w") as RBThetaCFile:
  InitializeRBThetaCFile(RBThetaCFile,IncludeGaurdName)
ThetaExpansionPrefix = "Geom3D" # EDIT FOR 3D GEOM

DefaultThetaObjectExists = False # boolean flag required while writing RB theta expansion file. Used to make sure that the default RB theta object _rb_theta is declared only once.

for bln_form in BilinearForms:
  for block_num in range(len(GeomSubdomains)):#subdomain in GeomSubdomains:
    if (SubdomainApplicability[bln_form][0] <= int(GeomSubdomains[block_num][0])) and (int(GeomSubdomains[block_num][0]) <= SubdomainApplicability[bln_form][1]):
      if bln_form == 'Diffusion':
        iATheta = 0       
        with open("./3DRBModel_ThetaObjects/"+GeomSubdomains[block_num][1]+"_RBAThetas_Diffusion.txt","r") as RBAThetaTextFile: # Read the definition of the ATheta object from the text files written by matlab
          AThetaDefinition = ReadRBAThetaTextFile(RBAThetaTextFile) # returns list of ATheta definitions
        print AThetaDefinition

        for suffix in TermsOfBilinearForm[bln_form]: 
          print "bilin form: ", bln_form, "; subdomain name :", GeomSubdomains[block_num][1], "; suffix list: ", TermsOfBilinearForm[bln_form], "; suffix: ", suffix, "; A Theta: ", AThetaDefinition[iATheta], "; AThetaPrefix: ", AThetaPrefix
          if AThetaDefinition[iATheta].strip() != "0":
            AppendToKernelList(KernelList, bln_form,suffix,GeomSubdomains,block_num,ID_Aq)
            AqObjectsList.append([ID_Aq,"Diffusion"+suffix+"_"+GeomSubdomains[block_num][1]])
            Aq_object_name = "Diffusion"+suffix+"_"+GeomSubdomains[block_num][1]
            with open(RBThetaCFileName,"a") as RBThetaCFile:
              WriteRBThetaCFile(RBThetaCFile, AThetaPrefix+Aq_object_name, AThetaDefinition[iATheta]) # write theta object definition to C file
            ID_Aq = ID_Aq + 1
          iATheta = iATheta + 1

      #if bln_form == 'Perfusion':
      #  print "bilin form: ", bln_form, "; subdomain name :", GeomSubdomains[block_num][1], "; suffix list: ", TermsOfBilinearForm[bln_form], "; suffix: ", suffix, "; A Theta: ", AThetaDefinition, "; AThetaPrefix: ", AThetaPrefix
      #  AThetaDefinition = "r_0*l_0/(r*l)"
      #  AppendToKernelList(KernelList, "Pennes"+bln_form,"",GeomSubdomains,block_num,ID_Aq)
      #  AqObjectsList.append([ID_Aq,"Perfusion_"+GeomSubdomains[block_num][1]])
      #  Aq_object_name = "Perfusion_"+GeomSubdomains[block_num][1]
      #  with open(RBThetaCFileName,"a") as RBThetaCFile:
      #    WriteRBThetaCFile(RBThetaCFile, AThetaPrefix+Aq_object_name, AThetaDefinition) # write theta object definition to C file
      #  ID_Aq = ID_Aq + 1
      
      if bln_form == 'Convection': # theta object is 1 for this particular case. use default rb theta object _rb_theta
        BCList.append(' ' + GeomSubdomains[block_num][0])
        if not(ConvectionBCFlag):
          AqObjectsList.append([ID_Aq,"BoundaryTerms"])
          ConvectionBCFlag = True

for subdomain in range(1,33):
  KernelList.append("""
  [./EIM_""" + str(subdomain) + """]
    type = DwarfElephantEIMFKernel
    block = """ + str(subdomain) + """
  [../]
   """)

AqObjectsList.sort(key=AffineObject_sort_key)
KernelList.append(AdditionalKernels)
KernelList.append("[]\n\n")
BCList.append("""'
ID_Aq = """ + str(ID_Aq)  + 
"""
  value = 0
  penalty = 1.0
 variable = temperature
matrix_seperation_according_to_subdomains = false
[../]
[]\n\n""")
ID_Aq = ID_Aq + 1

with open(RBThetaCFileName,"a") as RBThetaCFile:
    FinalizeRBThetaCFile(RBThetaCFile, IncludeGaurdName) # C file containing theta object definitions complete

RBThetaExpansionCFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/include/userobjects/DwarfElephantGeom3DRBThetaExpansion_RFA.h" #(EDIT FOR 3D GEOM)
IncludeFileName = ["DwarfElephantGeom3DRBTheta_RFA.h", "DwarfElephantMeshSubdomainJacobians.h"] #(EDIT FOR 3D GEOM)
IncludeGaurdName = "DWARFELEPHANTGEOM3DRBTHETAEXPANSION_RFA_H" #(EDIT FOR 3D GEOM)

with open(RBThetaExpansionCFileName,"w") as RBThetaExpansionCFile: # write RB theta expansion file
  InitializeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeFileName, ThetaExpansionPrefix, IncludeGaurdName)
  
  for Aq_object in AqObjectsList:
    AttachAqTheta(RBThetaExpansionCFile, AThetaPrefix, Aq_object)
  
  for subdomain in range(1,33):
    RBThetaExpansionCFile.write("    subdomain_jac_rbthetas.push_back(rbtheta_subdomain_"+str(subdomain)+");\n")
  RBThetaExpansionCFile.write("    num_subdomains = 32;\n")
  RBThetaExpansionCFile.write("}\n")

  for Aq_object in AqObjectsList:
    DeclareAqTheta(RBThetaExpansionCFile, AThetaPrefix, Aq_object, DefaultThetaObjectExists)

  # add for loop to define subdomain jacobian rbthetas in the rbtheta expansion struct
  RBThetaExpansionCFile.write("public:\n")
  for subdomain in range(1,33):
    RBThetaExpansionCFile.write("    subdomain_"+str(subdomain)+" rbtheta_subdomain_"+str(subdomain)+";\n")

  RBThetaExpansionCFile.write("    std::vector<RBTheta> subdomain_jac_rbthetas;\n")
  RBThetaExpansionCFile.write("    unsigned int num_subdomains;\n")
    

  FinalizeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeGaurdName) # C file containing RB theta expansion complete

# Write input file using the kernel list and BC list
InputFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/RBRFAModel3D.i"
MeshFile = "ReducedBasisGeom3D_7_fullylabeled_debug.msh"

PreKernelText = """[Mesh]
 file = """+MeshFile+"""
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
"""

with open(InputFileName,"w") as InputFile:
  InputFile.writelines(PreKernelText)
  for Lines in KernelList:
    InputFile.writelines(Lines)
  InputFile.writelines(AfterKernelText) # EDIT for 3D case
  for Lines in BCList:
    InputFile.writelines(Lines)
  InputFile.writelines(AfterBCText) # EDIT for 3D case
  
