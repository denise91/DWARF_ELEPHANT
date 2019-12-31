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
     FileName.write("   double k = 1;\n")
    if "d" in NewStructTheta:
     FileName.write("    double d = 3*r;\n")
    if "h" in NewStructTheta:
     FileName.write("    double h = 1.5*l;\n")
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
    RBThetaExpansionCFile.write("""#include "libmesh/transient_rb_theta_expansion.h"\n""")
    RBThetaExpansionCFile.write("\n")
    RBThetaExpansionCFile.write('#include "'+IncludeFileName[0]+'"\n')
    RBThetaExpansionCFile.write('#include "'+IncludeFileName[1]+'"\n')    
    RBThetaExpansionCFile.write("// Forward Declarations\n")
    RBThetaExpansionCFile.write("namespace libMesh\n")
    RBThetaExpansionCFile.write("{\n")
    RBThetaExpansionCFile.write("  class TransientRBThetaExpansion;\n")
    RBThetaExpansionCFile.write("}\n")
    RBThetaExpansionCFile.write("""///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct """+ThetaExpansionPrefix+"""RBThetaExpansion : TransientRBThetaExpansion
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
      print "  variable = "+variable#temperature
      print "  simulation_type = transient"
      print "  matrix_seperation_according_to_subdomains = false"
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

def AttachMqTheta(File, MThetaPrefix, Mq_object):
    File.write("  attach_M_theta(&"+MThetaPrefix+Mq_object[1]+"_0);\n")

def AttachAqTheta(File, AThetaPrefix, Aq_object):
    if (Aq_object[1] == "BoundaryTerms"):
      File.write("  attach_A_theta(&_rb_theta);\n")
    else: File.write("  attach_A_theta(&"+AThetaPrefix+Aq_object[1]+"_0);\n")

def AttachFqTheta(File, FThetaPrefix, Fq_object):
    File.write("  attach_F_theta(&"+FThetaPrefix+Fq_object[1]+"_0);\n")

def DeclareFqTheta(File, FThetaPrefix, Fq_object):
    File.write("  "+FThetaPrefix+Fq_object[1]+" "+FThetaPrefix+Fq_object[1]+"_0;\n")

def DeclareMqTheta(File, MThetaPrefix, Mq_object, DefaultThetaObjectExists):
    File.write("  "+MThetaPrefix+str(Mq_object[0]+1)+" "+MThetaPrefix+Mq_object[1]+"_0;\n")

def DeclareAqTheta(File, AThetaPrefix, Aq_object, DefaultThetaObjectExists):
    if (Aq_object[1] == "BoundaryTerms" and not(DefaultThetaObjectExists)):
      File.write("  RBTheta _rb_theta;\n")
      DefaultThetaObjectExists = True
    else: File.write("  "+AThetaPrefix+Aq_object[1]+" "+AThetaPrefix+Aq_object[1]+"_0;\n")

AdditionalKernels = """
[./RB_inner_product_matrix]
  type = RBInnerProductMatrixTransient
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
  simulation_type = 'transient'
  solve_type = 'Newton'
  l_tol = 1.0e-8
  nl_rel_tol = 1.0e-8
  #offline_stage = false
[]

[UserObjects]
[./initializeRBSystem]
  type = DwarfElephantInitializeRBSystemTransient
  use_EIM = true
  N_max_EIM = 30
  n_training_samples_EIM = 100
  rel_training_tolerance_EIM = 1e-4
  #abs_training_tolerance_EIM = 1e-4
  parameter_names_EIM = 'mu_0 mu_1 mu_2 mu_3 mu_4'# mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_EIM = '0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_EIM = '0.005 0.006 0.02 0.02 0.02'
  deterministic_training_EIM = false
  best_fit_type_EIM = projection
  euler_theta_RB = 1
  execute_on = 'initial'
  N_max_RB = 20
  n_time_steps_RB = 4
  delta_N_RB = 1
  delta_t_RB = 0.1
  POD_tol = -1e-6 #should be negative for the transient case
  max_truth_solves_RB = 500
  #offline_stage_RB = false
  n_training_samples_RB = 50
  rel_training_tolerance_RB = 1.e-3
  parameter_names_RB = 'mu_0 mu_1 mu_2 mu_3 mu_4' # mu_0 is r_0; mu_1 is l_0; mu_2 is x_prime; mu_3 is y_prime #Please name them mu_0 , mu_1 , ..., mu_n for the reusability
  parameter_min_values_RB = '0.001 0.002 -0.02 -0.02 -0.02'
  parameter_max_values_RB = '0.005 0.006 0.02 0.02 0.02'
  normalize_rb_bound_in_greedy = true
[../]
[./EIMInnerProductMatrixComputation]
  type = DwarfElephantComputeEIMInnerProductMatrixTransient
  execute_on = "EIM"
  initialize_rb_userobject = initializeRBSystem
[../]
[./performRBSystem ]
  type = DwarfElephantOfflineOnlineStageTransient
  #offline_stage = false
  online_stage = false
  online_mu = '0.003 0.004 -0.01 -0.01 -0.01'
  online_N = 6
  execute_on = 'timestep_end'
[../]
[]

#[Postprocessors]
#  [./average]
#    type = ElementAverageValue
#    variable = temperature
#    execute_on = 'custom'
#  [../]
#[]

[Outputs]
vtk = true
# csv = true   # only required for the PostProcessors
print_perf_log = true
  [./console]
    type = Console
    outlier_variable_norms = false
  [../]
[]
"""


