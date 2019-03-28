from HelperModule import *

AqObjectsList = []

BilinearForms = ['Diffusion', 'Perfusion', 'Convection']

GeomSubdomains = [ # Edit according to the geometry under consideration
                 ['11', "max_z_line"], 
                 ['12', "max_x_line"], 
                 ['13', "min_z_line"], 
                 ['14', "min_x_line"], 
                 ['1' , "maxZ1"], 
                 ['2' , "maxZ2"], 
                 ['3' , "maxX1"], 
                 ['4' , "maxX2"], 
                 ['5' , "minZ1"], 
                 ['6' , "minZ2"], 
                 ['7' , "minX1"],
                 ['8' , "minX2"], 
                 ['9' , "BoundingBox"] ] 

SubdomainApplicability = {'Diffusion': [1,9], 
                          'Perfusion': [9, 9],
                          'Convection': [11,14]}

TermsOfBilinearForm = {'Diffusion':['XX','XY','YX','YY'],#['XX','XY','XZ','YX','YY','YZ','ZX','ZY','ZZ']
                       'Perfusion':['Perf'],
                       'Convection':['Conv']}

KernelList = ["[Kernels]\n"]
BCList = ["""[BCs]
[./Convection_BC]
  type = DwarfElephantRBPenaltyDirichletBC
  boundary = '"""]

ID_Aq = 0
ConvectionBCFlag = False
AThetaPrefix = "Geom2DRB_ATheta_"

RBThetaCFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/include/userobjects/DwarfElephantGeom2DRBTheta_RFA.h"

IncludeGaurdName = "DWARFELEPHANTGEOM2DRBTHETA_RFA_H"
with open(RBThetaCFileName,"w") as RBThetaCFile:
  InitializeRBThetaCFile(RBThetaCFile,IncludeGaurdName)
ThetaExpansionPrefix = "Geom2D"

DefaultThetaObjectExists = False # boolean flag required while writing RB theta expansion file. Used to make sure that the default RB theta object _rb_theta is declared only once.

for bln_form in BilinearForms:
  for block_num in range(len(GeomSubdomains)):#subdomain in GeomSubdomains:
    if (SubdomainApplicability[bln_form][0] <= int(GeomSubdomains[block_num][0])) and (int(GeomSubdomains[block_num][0]) <= SubdomainApplicability[bln_form][1]):
      if bln_form == 'Diffusion':
        iATheta = 0       
        with open(GeomSubdomains[block_num][1]+"_RBAThetas.txt","r") as RBAThetaTextFile: # Read the definition of the ATheta object from the text files written by matlab
          AThetaDefinition = ReadRBAThetaTextFile(RBAThetaTextFile) # returns list of ATheta definitions
        print AThetaDefinition

        for suffix in TermsOfBilinearForm[bln_form]: 
          print "bilin form: ", bln_form, "; subdomain name :", GeomSubdomains[block_num][1], "; suffix list: ", TermsOfBilinearForm[bln_form], "; suffix: ", suffix, "; A Theta: ", AThetaDefinition[iATheta], "; AThetaPrefix: ", AThetaPrefix
          if AThetaDefinition[iATheta] != "0":
            AppendToKernelList(KernelList, bln_form,suffix,GeomSubdomains,block_num,ID_Aq)
            AqObjectsList.append([ID_Aq,"Diffusion"+suffix+"_"+GeomSubdomains[block_num][1]])
            Aq_object_name = "Diffusion"+suffix+"_"+GeomSubdomains[block_num][1]
            with open(RBThetaCFileName,"a") as RBThetaCFile:
              WriteRBThetaCFile(RBThetaCFile, AThetaPrefix+Aq_object_name, AThetaDefinition[iATheta]) # write theta object definition to C file
            ID_Aq = ID_Aq + 1
          iATheta = iATheta + 1

      if bln_form == 'Perfusion':
        print "bilin form: ", bln_form, "; subdomain name :", GeomSubdomains[block_num][1], "; suffix list: ", TermsOfBilinearForm[bln_form], "; suffix: ", suffix, "; A Theta: ", AThetaDefinition, "; AThetaPrefix: ", AThetaPrefix
        AThetaDefinition = "r_0*l_0/(r*l)"
        AppendToKernelList(KernelList, "Pennes"+bln_form,"",GeomSubdomains,block_num,ID_Aq)
        AqObjectsList.append([ID_Aq,"Perfusion_"+GeomSubdomains[block_num][1]])
        Aq_object_name = "Perfusion_"+GeomSubdomains[block_num][1]
        with open(RBThetaCFileName,"a") as RBThetaCFile:
          WriteRBThetaCFile(RBThetaCFile, AThetaPrefix+Aq_object_name, AThetaDefinition) # write theta object definition to C file
        ID_Aq = ID_Aq + 1
      
      if bln_form == 'Convection': # theta object is 1 for this particular case. use default rb theta object _rb_theta
        BCList.append(' ' + GeomSubdomains[block_num][0])
        if not(ConvectionBCFlag):
          AqObjectsList.append([ID_Aq,"BoundaryTerms"])
          ConvectionBCFlag = True

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

RBThetaExpansionCFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/include/userobjects/DwarfElephantGeom2DRBThetaExpansion_RFA.h"
IncludeFileName = "DwarfElephantGeom2DRBTheta_RFA.h"
IncludeGaurdName = "DWARFELEPHANTGEOM2DRBTHETAEXPANSION_RFA_H"

with open(RBThetaExpansionCFileName,"w") as RBThetaExpansionCFile: # write RB theta expansion file
  InitializeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeFileName, ThetaExpansionPrefix, IncludeGaurdName)
  
  for Aq_object in AqObjectsList:
    AttachAqTheta(RBThetaExpansionCFile, AThetaPrefix, Aq_object)
  RBThetaExpansionCFile.write("}\n")

  for Aq_object in AqObjectsList:
    DeclareAqTheta(RBThetaExpansionCFile, AThetaPrefix, Aq_object, DefaultThetaObjectExists)

  FinalizeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeGaurdName) # C file containing RB theta expansion complete

# Write input file using the kernel list and BC list
InputFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/RFAModel2D.i"
MeshFile = "RFAGeom2D_L1e-1_r3e-2_l6e-2.msh"

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
  InputFile.writelines(AfterKernelText)
  for Lines in BCList:
    InputFile.writelines(Lines)
  InputFile.writelines(AfterBCText)
  
