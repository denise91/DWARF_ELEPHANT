from HelperModule import *

AThetaPrefix = "Geom2DRB_ATheta_"
FThetaPrefix = "Geom2DRB_FTheta_"
ThetaExpansionPrefix = "Geom2D"
RBThetaCFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/include/userobjects/DwarfElephantGeom2DRBTheta_RBNICS.h"
IncludeGaurdName = "DWARFELEPHANTGEOM2DRBTHETA_RBNICS_H"
with open(RBThetaCFileName,"w") as RBThetaCFile:
  InitializeRBThetaCFile(RBThetaCFile,IncludeGaurdName)

mesh_block_ids = [
                 ['11', "max_z_line"],
                 ['12', "max_x_line"],
                 ['13', "min_z_line"],
                 ['14', "min_x_line"],
                 ['15', "max_z_line_inner"],
                 ['16', "max_x_line_inner"],
                 ['17', "min_z_line_inner"],
                 ['18', "min_x_line_inner"],
                 ['1' , "maxZ1"],
                 ['2' , "maxZ2"],
                 ['3' , "maxX1"],
                 ['4' , "maxX2"],
                 ['5' , "minZ1"],
                 ['6' , "minZ2"],
                 ['7' , "minX1"],
                 ['8' , "minX2"]]#,
                # ['9' , "BoundingBox"]
		#		 ] # Different for 2D and 3D
diffusion_kernel_suffix = ["XX","XY","YX","YY"]#"XZ","YX","YY","YZ","ZX","ZY","ZZ"] # Different for 2D and 3D
BC_done = False
ID_Aq = 0
ID_Fq = 0
Aq_objects_list = []
Fq_objects_list = []
for block_num in range(len(mesh_block_ids)): 
  
  if (block_num >= 0) and (block_num <= 3) and (not(BC_done)): # Different for 2D and 3D # Write convection BC block to input file
    PrintConvectionBCBlock(mesh_block_ids,ID_Aq,0,1.0,"temperature")
    Aq_objects_list.append([ID_Aq,"BoundaryTerms"])
    ID_Aq = ID_Aq + 1
    BC_done = True
  
  if (block_num >= 4) and (block_num <= 7):
    PrintNeumannBCBlock(mesh_block_ids[block_num],ID_Fq,1,"temperature")
    #Fq_objects_list.append([ID_Fq,"BoundaryTerms"])
    
    with open(mesh_block_ids[block_num][1]+"_RBFTheta.txt","r") as RBFThetaTextFile:
        FThetaDefinition = ReadRBFThetaTextFile(RBFThetaTextFile)
    Fq_objects_list.append([ID_Fq,"NeumannBC_"+mesh_block_ids[block_num][1]])
    Fq_object_name = "NeumannBC_"+mesh_block_ids[block_num][1]
    with open(RBThetaCFileName,"a") as RBThetaCFile:
      WriteRBThetaCFile(RBThetaCFile, FThetaPrefix+Fq_object_name, FThetaDefinition)
    ID_Fq = ID_Fq + 1
  
  if (block_num >= 8) and (block_num <= 15):  # Different for 2D and 3D
    with open(mesh_block_ids[block_num][1]+"_RBAThetas.txt","r") as RBAThetaTextFile: # Read the definition of the ATheta object from the text files written by matlab
        AThetaDefinition = ReadRBAThetaTextFile(RBAThetaTextFile)
        #print AThetaDefinition
    iATheta = 0
    for suffix in diffusion_kernel_suffix: 
      PrintDiffusionBlock(suffix,mesh_block_ids,block_num,ID_Aq)
      Aq_objects_list.append([ID_Aq,"Diffusion"+suffix+"_"+mesh_block_ids[block_num][1]])
      Aq_object_name = "Diffusion"+suffix+"_"+mesh_block_ids[block_num][1]
      with open(RBThetaCFileName,"a") as RBThetaCFile:
        WriteRBThetaCFile(RBThetaCFile, AThetaPrefix+Aq_object_name, AThetaDefinition[iATheta])
      iATheta = iATheta + 1
      ID_Aq = ID_Aq + 1
    
    #with open(mesh_block_ids[block_num][1]+"_RBFTheta.txt","r") as RBFThetaTextFile: # Read the definition of the ATheta object from the text files written by matlab
    #  FThetaDefinition = ReadRBFThetaTextFile(RBFThetaTextFile)
      #print FThetaDefinition
    #PrintHeatSourceBlock(mesh_block_ids,block_num,ID_Fq,"temperature")
    #Fq_objects_list.append([ID_Fq,"HeatSource_"+mesh_block_ids[block_num][1]])
    #Fq_object_name = "HeatSource_"+mesh_block_ids[block_num][1]
    #with open(RBThetaCFileName,"a") as RBThetaCFile:
    #  WriteRBThetaCFile(RBThetaCFile, FThetaPrefix+Fq_object_name, FThetaDefinition)
    #ID_Fq = ID_Fq + 1
  
#  if (block_num == 12): # Different for 2D and 3D # Theta object C file pending
#    AThetaDefinition = ["r*l_0*k/(r_0*l)","r_0*l*k/(r*l_0)"]
#    iATheta = 0
#    for suffix in diffusion_kernel_suffix:
#      if (suffix == "XX") or (suffix == "YY"):
#        PrintDiffusionBlock(suffix,mesh_block_ids,block_num,ID_Aq)
#        Aq_objects_list.append([ID_Aq,"Diffusion"+suffix+"_"+mesh_block_ids[block_num][1]])
#        Aq_object_name = "Diffusion"+suffix+"_"+mesh_block_ids[block_num][1]
#        with open(RBThetaCFileName,"a") as RBThetaCFile:
#          WriteRBThetaCFile(RBThetaCFile, AThetaPrefix+Aq_object_name, AThetaDefinition[iATheta])
#        ID_Aq = ID_Aq + 1
#        iATheta = iATheta + 1

#    AThetaDefinition = "r_0*l_0/(r*l)"
#    PrintPerfusionBlock(mesh_block_ids,block_num,ID_Aq)
#    Aq_objects_list.append([ID_Aq,"Perfusion_"+mesh_block_ids[block_num][1]])
#    Aq_object_name = "Perfusion_"+mesh_block_ids[block_num][1]
#    with open(RBThetaCFileName,"a") as RBThetaCFile:
#      WriteRBThetaCFile(RBThetaCFile, AThetaPrefix+Aq_object_name, AThetaDefinition)
#    ID_Aq = ID_Aq + 1
    
#    FThetaDefinition = "r_0*l_0/(r*l)"
#    PrintHeatSourceBlock(mesh_block_ids, block_num, ID_Fq, "temperature")
#    Fq_objects_list.append([ID_Fq,"HeatSource_"+mesh_block_ids[block_num][1]])
#    Fq_object_name = "HeatSource_"+mesh_block_ids[block_num][1]
#    with open(RBThetaCFileName,"a") as RBThetaCFile:
#      WriteRBThetaCFile(RBThetaCFile, FThetaPrefix+Fq_object_name, FThetaDefinition)
#    ID_Fq = ID_Fq + 1

Aq_objects_list.sort(key=AffineObject_sort_key)
Fq_objects_list.sort(key=AffineObject_sort_key)


with open(RBThetaCFileName,"a") as RBThetaCFile:
    FinalizeRBThetaCFile(RBThetaCFile, IncludeGaurdName)

RBThetaExpansionCFileName = "/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/include/userobjects/DwarfElephantGeom2DRBThetaExpansion_RBNICS.h"
IncludeFileName = "DwarfElephantGeom2DRBTheta_RBNICS.h"
IncludeGaurdName = "DWARFELEPHANTGEOM2DRBTHETAEXPANSION_RBNICS_H"

with open(RBThetaExpansionCFileName,"w") as RBThetaExpansionCFile:
  InitializeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeFileName, ThetaExpansionPrefix, IncludeGaurdName)
  
  for Aq_object in Aq_objects_list:
    AttachAqTheta(RBThetaExpansionCFile, AThetaPrefix, Aq_object)


  for Fq_object in Fq_objects_list:
    AttachFqTheta(RBThetaExpansionCFile, FThetaPrefix, Fq_object)
    if (Fq_object[0]+1 == len(Fq_objects_list)):
      RBThetaExpansionCFile.write("  }\n")

  for Aq_object in Aq_objects_list:
    DeclareAqTheta(RBThetaExpansionCFile, AThetaPrefix, Aq_object)
  
  for Fq_object in Fq_objects_list:
    DeclareFqTheta(RBThetaExpansionCFile, FThetaPrefix, Fq_object)
    #if (Fq_object[0] + 1 == len(Fq_objects_list)):
    #  RBThetaExpansionCFile.write("""};\n
#//------------------------------
##endif // """+IncludeGaurdName)

  FinalizeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeGaurdName)
    
