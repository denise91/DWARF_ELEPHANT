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
        StructTheta.append(TempString[7:-1:1])
    return StructTheta

def ReadRBFThetaTextFile(InputFile):
    RBFThetaString = InputFile.readline()
    return RBFThetaString[7:-1:1]

def ReadRBMThetaTextFile(InputFile):
    RBMThetaStrings = InputFile.readlines()
    StructMTheta = []
    for string in RBMThetaStrings:
        TempString = string.rstrip("\n")
        StructMTheta.append(TempString[7:-1:1])
    return StructMTheta


def WriteRBThetaCFile(FileName, ThetaName, ThetaDefinition):
    FileName.write("struct "+ThetaName+" : RBTheta\n")
    FileName.write("{\n")
    FileName.write("  virtual Number evaluate (const RBParameters & _mu)\n")
    FileName.write("  {\n")
    TempStructTheta = ThetaDefinition.replace("r_0","!@#$")#"""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace("l_0",")(*&")#"""_mu.get_value("mu_1")""")
    
    if "r" in NewStructTheta:
     FileName.write("    double r = 0.003;\n") 
    if "l" in NewStructTheta:
     FileName.write("  double  l = 0.05;\n") 
    if "L" in NewStructTheta:
     FileName.write("  double L = 0.1;\n")
    if "k" in NewStructTheta:
     FileName.write("   double k = 0.52;\n")
    if "d" in NewStructTheta:
     FileName.write("    double d = 3*r;\n")
    if "h" in NewStructTheta:
     FileName.write("    double h = 1.5*l;\n")
    TempStructTheta = NewStructTheta.replace("!@#$","""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace(")(*&","""_mu.get_value("mu_1")""")
    FileName.write("    return "+NewStructTheta+";\n")
    FileName.write("  }\n")
    FileName.write("};\n")

def WriteRBThetaCFile_Perf(FileName, ThetaName, ThetaDefinition):
    FileName.write("struct "+ThetaName+" : RBTheta\n")
    FileName.write("{\n")
    FileName.write("  virtual Number evaluate (const RBParameters & _mu)\n")
    FileName.write("  {\n")
    TempStructTheta = ThetaDefinition.replace("r_0","!@#$")#"""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace("l_0",")(*&")#"""_mu.get_value("mu_1")""")
    
    if "r" in NewStructTheta:
     FileName.write("    Real r = 0.003;\n") 
    if "l" in NewStructTheta:
     FileName.write("  Real  l = 0.05;\n") 
    if "L" in NewStructTheta:
     FileName.write("  Real L = 0.1;\n")
    FileName.write("   Real omega = 1.9e5;\n")
    if "d" in NewStructTheta:
     FileName.write("    Real d = 3*r;\n")
    if "h" in NewStructTheta:
     FileName.write("    Real h = 1.5*l;\n")
    TempStructTheta = NewStructTheta.replace("!@#$","""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace(")(*&","""_mu.get_value("mu_1")""")
    FileName.write("    return "+NewStructTheta+";\n")
    FileName.write("  }\n")
    FileName.write("};\n")

def WriteRBThetaCFile_M(FileName, ThetaNum, ThetaDefinition):
    FileName.write("struct MTheta_subdomain_"+str(ThetaNum)+": RBTheta\n")
    FileName.write("{\n")
    FileName.write("  virtual Number evaluate (const RBParameters & _mu)\n")
    FileName.write("  {\n")
    TempStructTheta = ThetaDefinition.replace("r_0","!@#$")#"""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace("l_0",")(*&")#"""_mu.get_value("mu_1")""")
    
    if "r" in NewStructTheta:
     FileName.write("    Real r = 0.003;\n") 
    if "l" in NewStructTheta:
     FileName.write("  Real  l = 0.05;\n") 
    if "L" in NewStructTheta:
     FileName.write("  Real L = 0.1;\n")
    FileName.write("   Real rho_C = 3.82e6;\n")
    if "d" in NewStructTheta:
     FileName.write("    Real d = 3*r;\n")
    if "h" in NewStructTheta:
     FileName.write("    Real h = 1.5*l;\n")
    TempStructTheta = NewStructTheta.replace("!@#$","""_mu.get_value("mu_0")""")
    NewStructTheta = TempStructTheta.replace(")(*&","""_mu.get_value("mu_1")""")
    FileName.write("    return rho_C * "+NewStructTheta+";\n")
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
    RBThetaExpansionCFile.write('#include "'+IncludeFileName[0]+'"\n')
    RBThetaExpansionCFile.write('#include "'+IncludeFileName[1]+'"\n')    
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
  

def AppendToBCList(BCList,mesh_block_ids,ID_Aq,value,penalty,variable):
      BCList.append("[./Convection_BC]\n")
      BCList.append("  type = DwarfElephantRBPenaltyDirichletBC\n")
      boundary_string = """  boundary = '"""
      for boundary in mesh_block_ids[:4]:
        boundary_string = boundary_string + boundary[0] + " "
      boundary_string = boundary_string + """' """
      BCList.append(boundary_string + "\n")
      BCList.append("  ID_Aq = "+str(ID_Aq) + "\n")#37
      BCList.append("  value = "+str(value) + "\n")#0
      BCList.append("  penalty = "+str(penalty) + "\n")#6
      BCList.append(" variable = "+variable + "\n")#temperature
      BCList.append("matrix_seperation_according_to_subdomains = false" + "\n")
      BCList.append("[../]" + "\n")

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

def AppendToKernelList(KernelList, bln_form,suffix,mesh_block_ids,block_num,ID_Aq,matrix_type):
      KernelList.append("[./"+bln_form+suffix+"_"+mesh_block_ids[block_num][1]+"]\n")
      KernelList.append("  type = DwarfElephantRB"+ bln_form+suffix + "\n")
      if matrix_type == "mass":
            KernelList.append("  ID_Mq = "+str(ID_Aq) + "\n")
      elif matrix_type == "stiffness":
            KernelList.append("  ID_Aq = "+str(ID_Aq) + "\n")
      else:
            print """matrix_type argument is wrong. Choose one of two options: 1."mass"; 2."stiffness"."""
            quit()
      KernelList.append("  simulation_type = transient\n")
      KernelList.append("  block = "+mesh_block_ids[block_num][0] + "\n")
      KernelList.append("matrix_seperation_according_to_subdomains = false" + "\n")
      KernelList.append("[../]" + "\n")

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

def DeclareAqTheta(File, AThetaPrefix, Aq_object, DefaultThetaObjectExists):
    if (Aq_object[1] == "BoundaryTerms" and not(DefaultThetaObjectExists)):
      File.write("  RBTheta _rb_theta;\n")
      DefaultThetaObjectExists = True
    else: File.write("  "+AThetaPrefix+Aq_object[1]+" "+AThetaPrefix+Aq_object[1]+"_0;\n")

def get_iATheta(subscript):
    if (subscript == 'XX'):
      result = 0
    elif (subscript == 'XY'):
      result = 1
    elif (subscript == 'XZ'):
      result = 2
    elif (subscript == 'YX'):
      result = 3
    elif (subscript == 'YY'):
      result = 4
    elif (subscript == 'YZ'):
      result = 5
    elif (subscript == 'ZX'):
      result = 6
    elif (subscript == 'ZY'):
      result = 7
    elif (subscript == 'ZZ'):
      result = 8
    else:
      print "Error: Invalid argument for subscript in get_iATheta()"
      quit()
    return result

AdditionalKernels = """
[./RB_inner_product_matrix]
  type = RBInnerProductMatrix
[../]
"""

AfterKernelText = """[AuxKernels]
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
"""

AfterBCText = """[Problem]
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
"""


