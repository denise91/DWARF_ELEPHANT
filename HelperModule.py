def InitializeRBThetaCFile(RBThetaCFile, IncludeGaurdName):
    RBThetaCFile.write("///-------------------------------------------------------------------------\n")
    RBThetaCFile.write("#ifndef "+IncludeGaurdName+"\n")
    RBThetaCFile.write("#define "+IncludeGaurdName+"\n")
    RBThetaCFile.write("\n")
    RBThetaCFile.write("///---------------------------------INCLUDES--------------------------------\n")
    RBThetaCFile.write("// libMesh includes (RB package)\n")
    RBThetaCFile.write("""#include "libmesh/rb_theta.h"\n""")
    RBThetaCFile.write("""#include "libmesh/rb_assembly_expansion.h"\n""")
    RBThetaCFile.write("\n")
    RBThetaCFile.write("// Forward Declarations\n")
    RBThetaCFile.write("namespace libMesh\n")
    RBThetaCFile.write("{\n")
    RBThetaCFile.write("  class RBParameters;\n")
    RBThetaCFile.write("  class RBTheta;\n")
    RBThetaCFile.write("}\n")

def FinalizeRBThetaCFile(RBThetaCFile,IncludeGaurdName):
    RBThetaCFile.write("#endif //"+IncludeGaurdName)

def ReadRBAThetaTextFile(InputFile):
    RBThetaStrings = InputFile.readlines()
    StructTheta = []
    for string in RBThetaStrings:
        TempString = string.rstrip("\n")
        StructTheta.append(TempString[12:-1:1])
    return StructTheta

def ReadRBFThetaTextFile(InputFile):
    RBFThetaString = InputFile.readline()
    return RBFThetaString[7:-1:1]

def WriteRBThetaCFile(FileName, ThetaName, ThetaDefinition):
    FileName.write("struct "+ThetaName+" : RBTheta\n")
    FileName.write("{\n")
    FileName.write("  virtual Number evaluate (const RBParameters & _mu)\n")
    FileName.write("  {\n")
    TempStructTheta = ThetaDefinition.replace("r_0","!@#$")#"""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace("l_0",")(*&")#"""_mu.get_value("mu_1")""")
    
    if "r" in NewStructTheta:
     FileName.write("    double r = 0.3;\n") 
    if "l" in NewStructTheta:
     FileName.write("  double  l = 0.6;\n") 
    if "L" in NewStructTheta:
     FileName.write("  double L = 1;\n")
    if "k" in NewStructTheta:
     FileName.write("   double k = 1;\n")
    TempStructTheta = NewStructTheta.replace("!@#$","""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace(")(*&","""_mu.get_value("mu_1")""")
    FileName.write("    return "+NewStructTheta+";\n")
    FileName.write("  }\n")
    FileName.write("};\n")

def AffineObject_sort_key(Aq_object):
    return Aq_object[0]

def InitializeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeFileName, ThetaExpansionPrefix, IncludeGaurdName):
    RBThetaExpansionCFile.write("/**\n")
    RBThetaExpansionCFile.write("  * The structures are defined for an elliptic PDE with the following restrictions:\n")
    RBThetaExpansionCFile.write("  *  1. The number of thetas is equal to one (T1).\n")
    RBThetaExpansionCFile.write("  *  2. The problem contains one load vector (F1) and one output (O1).\n")
    RBThetaExpansionCFile.write("  *\n")
    RBThetaExpansionCFile.write("  * The structures defined are:\n")
    RBThetaExpansionCFile.write("  * 1. Theta --> parameter-dependent part of the PDE\n")
    RBThetaExpansionCFile.write("  * 2. RBThetaExpansion\n")
    RBThetaExpansionCFile.write("  */\n")
    RBThetaExpansionCFile.write("\n")
    RBThetaExpansionCFile.write("///-------------------------------------------------------------------------\n")
    RBThetaExpansionCFile.write("#ifndef "+IncludeGaurdName+"\n")
    RBThetaExpansionCFile.write("#define "+IncludeGaurdName+"\n") 
    RBThetaExpansionCFile.write("\n")
    RBThetaExpansionCFile.write("///---------------------------------INCLUDES--------------------------------\n")
    RBThetaExpansionCFile.write("// libMesh includes (RB package)\n")
    RBThetaExpansionCFile.write("""#include "libmesh/rb_theta.h"\n""")
    RBThetaExpansionCFile.write("""#include "libmesh/rb_assembly_expansion.h"\n""")
    RBThetaExpansionCFile.write("\n")
    RBThetaExpansionCFile.write('#include "'+IncludeFileName+'"\n')    
    RBThetaExpansionCFile.write("// Forward Declarations\n")
    RBThetaExpansionCFile.write("namespace libMesh\n")
    RBThetaExpansionCFile.write("{\n")
    RBThetaExpansionCFile.write("  class RBThetaExpansion;\n")
    RBThetaExpansionCFile.write("}\n")
    RBThetaExpansionCFile.write("""///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct """+ThetaExpansionPrefix+"""RBThetaExpansion : RBThetaExpansion
{
  """+ThetaExpansionPrefix+"""RBThetaExpansion()
  {\n""")

def FinalizeRBThetaExpansionCFile(RBThetaExpansionCFile, IncludeGaurdName):
  RBThetaExpansionCFile.write("""};\n
//------------------------------
#endif // """+IncludeGaurdName)
  


def PrintConvectionBCBlock(mesh_block_ids,ID_Aq,value,penalty,variable): 
      print "[./Convection_BC]"
      print "  type = DwarfElephantRBPenaltyDirichletBC"
      boundary_string = """  boundary = '"""
      for boundary in mesh_block_ids[:4]:
        boundary_string = boundary_string + boundary[0] + " "
      boundary_string = boundary_string + """' """
      print boundary_string
      print "  ID_Aq = "+str(ID_Aq)#37
      print "  value = "+str(value)#0
      print "  penalty = "+str(penalty)#6
      print " variable = "+variable#temperature
      print "matrix_seperation_according_to_subdomains = false"
      print "[../]"

def PrintNeumannBCBlock(mesh_block_ids, ID_Fq, value,variable):
      print "[./HeatFlux_BC_"+str(ID_Fq)+"]"
      print "  type = DwarfElephantRBNeumannBC"
      boundary_string = """  boundary = '""" + mesh_block_ids[0] + """'"""
      print boundary_string
      print "  ID_Fq = "+str(ID_Fq)
      print "  value = "+str(value)
      print "  variable = "+variable
      print "matrix_seperation_according_to_subdomains = false"
      print "[../]"      

def PrintDiffusionBlock(suffix,mesh_block_ids,block_num,ID_Aq):
      print "[./Diffusion"+suffix+"_"+mesh_block_ids[block_num][0]+"]"
      print "  type = DwarfElephantRBDiffusion"+suffix
      print "  ID_Aq = "+str(ID_Aq)
      print "  block = "+mesh_block_ids[block_num][0]
      print "matrix_seperation_according_to_subdomains = false"
      print "[../]"

def PrintHeatSourceBlock(mesh_block_ids,block_num,ID_Fq,variable):
  print """[./HeatSource_"""+mesh_block_ids[block_num][0]+"""]
  type = DwarfElephantRBRFHeatsourceKernel
  variable = """+variable+"""
  heat_source_function = constantFunction
  ID_Fq = """+str(ID_Fq)+"""
  block = """+mesh_block_ids[block_num][0]+"""
  matrix_seperation_according_to_subdomains = false
[../]"""

def PrintPerfusionBlock(mesh_block_ids,block_num,ID_Aq):
  print """[./Perfusion_"""+mesh_block_ids[block_num][0]+"""]
  type = DwarfElephantRBPennesPerfusion
  ID_Aq = """+str(ID_Aq)+"""
  block = """+mesh_block_ids[block_num][0]+"""
  matrix_seperation_according_to_subdomains = false
[../]"""

def AttachAqTheta(File, AThetaPrefix, Aq_object):
    if (Aq_object[1] == "BoundaryTerms"):
      File.write("  attach_A_theta(&_rb_theta);\n")
    else: File.write("  attach_A_theta(&"+AThetaPrefix+Aq_object[1]+"_0);\n")

def AttachFqTheta(File, FThetaPrefix, Fq_object):
    File.write("  attach_F_theta(&"+FThetaPrefix+Fq_object[1]+"_0);\n")

def DeclareFqTheta(File, FThetaPrefix, Fq_object):
    File.write("  "+FThetaPrefix+Fq_object[1]+" "+FThetaPrefix+Fq_object[1]+"_0;\n")

def DeclareAqTheta(File, AThetaPrefix, Aq_object):
    if (Aq_object[1] == "BoundaryTerms"):
      File.write("  RBTheta _rb_theta;\n")
    else: File.write("  "+AThetaPrefix+Aq_object[1]+" "+AThetaPrefix+Aq_object[1]+"_0;\n")
