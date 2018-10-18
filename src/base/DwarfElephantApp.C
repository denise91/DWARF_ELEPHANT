/// MOOSE includes
#include "Moose.h"
#include "AppFactory.h"
#include "Factory.h"
#include "ActionFactory.h"
#include "ModulesApp.h"   // remove for use in OpenDA
#include "MooseSyntax.h"

/// MOOSE includes (DwarfElephant package)
#include "DwarfElephantApp.h"
#include "DwarfElephantAppTypes.h"

//Actions
#include "DwarfElephantEIMFKernelsAction.h"

// Base
#include "DwarfElephantRBProblem.h"

//BCs
#include "DwarfElephantRBNodalBC.h"
#include "DwarfElephantRBDirichletBC.h"
#include "DwarfElephantRBFunctionDirichletBC.h"
#include "DwarfElephantRBPenaltyDirichletBC.h"
#include "DwarfElephantRBPresetNodalBC.h"
#include "DwarfElephantRBPresetBC.h"
#include "DwarfElephantRBFunctionPresetBC.h"
#include "DwarfElephantRBIntegratedBC.h"
#include "DwarfElephantRBNeumannBC.h"
#include "DwarfElephantRBNeumannBCND.h"
#include "DwarfElephantRBFunctionNeumannBC.h"

//ICs
#include "DwarfElephantFileIC.h"

// Kernels
#include "DwarfElephantFEThermalConduction.h"
#include "DwarfElephantFEConductionLiftingFunction.h"
#include "DwarfElephantFEElectricalConduction.h"
#include "DwarfElephantFEDarcy.h"
#include "DwarfElephantFEDarcyOpenDA.h"
#include "DwarfElephantRBDiffusion.h"
#include "DwarfElephantRBDiffusionND.h"
#include "DwarfElephantRBDiffusionLiftingFunction.h"
#include "DwarfElephantZeroKernel.h"
#include "DwarfElephantRBTimeDerivative.h"
#include "DwarfElephantEIMFKernel.h"
#include "DwarfElephantEIMAKernel.h"
#include "ExtractQpPointsKernel.h"
#include "RBInnerProductMatrix.h"
#include "DwarfElephantRBDiffusionXX.h"
#include "DwarfElephantRBDiffusionXY.h"
#include "DwarfElephantRBDiffusionXZ.h"
#include "DwarfElephantRBDiffusionYY.h"
#include "DwarfElephantRBDiffusionYZ.h"
#include "DwarfElephantRBDiffusionZZ.h"
#include "DwarfElephantRBDiffusionYX.h"
#include "DwarfElephantRBDiffusionZX.h"
#include "DwarfElephantRBDiffusionZY.h"
#include "DwarfElephantRBRFHeatsourceKernel.h"
#include "DwarfElephantRBPennesPerfusion.h"

// DiracKernels
#include "DwarfElephantRBConstantPointSource.h"

// Materials
#include "DwarfElephantSandStone.h"
#include "DwarfElephantShale.h"
#include "DwarfElephantFault.h"
#include "ExtractQpPoints.h"

// UserObjects
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantInitializeRBSystemTransient.h"
#include "DwarfElephantOfflineOnlineStageSteadyState.h"
#include "DwarfElephantOfflineOnlineStageTransient.h"
#include "DwarfElephantERTPreCalculations.h"
#include "DwarfElephantRBNodalVariableValue.h"
#include "DwarfElephantRBElementalVariableValue.h"
#include "DwarfElephantRBPointValue.h"
#include "DwarfElephantReducedToFullState.h"
#include "DwarfElephantComputeEIMInnerProductMatrixSteadyState.h"

// Functions
#include "DwarfElephantInitialConditionFileReader.h"

// Executioners
#include "DwarfElephantRBExecutioner.h"

// Outputs
#include "DwarfElephantDakotaOutput.h"
#include "DwarfElephantStateOutput.h"
#include "DwarfElephantRBOutput.h"

// VectorPostprocessors
#include "DwarfElephantElementalVariableValuesAlongLine.h"
#include "DwarfElephantAllElementalVariableValues.h"
#include "DwarfElephantNodalDifference.h"

template<>
InputParameters validParams<DwarfElephantApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.addCommandLineParam<bool>("disallow_test_objects",
                                   "--disallow-test-objects",
                                   false,
                                   "Don't register test objects and syntax");
  return params;
}

DwarfElephantApp::DwarfElephantApp(InputParameters parameters) :
    MooseApp(parameters)
{
  //bool use_test_objs = !getParam<bool>("disallow_test_objects");
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory); // remove for use in OpenDA
  Moose::registerExecFlags(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory); // remove for use in OpenDA
  DwarfElephantApp::associateSyntax(_syntax, _action_factory);
  DwarfElephantApp::registerObjects(_factory);
  DwarfElephantApp::registerExecFlags(_factory);
}

DwarfElephantApp::~DwarfElephantApp()
{
}

// External entry point for dynamic application loading
extern "C" void DwarfElephantApp__registerApps() { DwarfElephantApp::registerApps(); }
void
DwarfElephantApp::registerApps()
{
  registerApp(DwarfElephantApp);
}

// External entry point for dynamic object registration
extern "C" void DwarfElephantApp__registerObjects(Factory & factory) { DwarfElephantApp::registerObjects(factory); }
void
DwarfElephantApp::registerObjects(Factory & factory)
{
  // Base
  registerProblem(DwarfElephantRBProblem);

  // BCs
  registerBoundaryCondition(DwarfElephantRBNodalBC);
  registerBoundaryCondition(DwarfElephantRBDirichletBC);
  registerBoundaryCondition(DwarfElephantRBFunctionDirichletBC);
  registerBoundaryCondition(DwarfElephantRBPenaltyDirichletBC);
  registerBoundaryCondition(DwarfElephantRBPresetNodalBC);
  registerBoundaryCondition(DwarfElephantRBPresetBC);
  registerBoundaryCondition(DwarfElephantRBFunctionPresetBC);
  registerBoundaryCondition(DwarfElephantRBIntegratedBC);
  registerBoundaryCondition(DwarfElephantRBNeumannBC);
  registerBoundaryCondition(DwarfElephantRBNeumannBCND);
  registerBoundaryCondition(DwarfElephantRBFunctionNeumannBC);

  //ICs
  registerInitialCondition(DwarfElephantFileIC);

  // Kernels
  registerKernel(DwarfElephantFEThermalConduction);
  registerKernel(DwarfElephantFEConductionLiftingFunction);
  registerKernel(DwarfElephantFEElectricalConduction);
  registerKernel(DwarfElephantFEDarcy);
  registerKernel(DwarfElephantFEDarcyOpenDA);
  registerKernel(DwarfElephantRBDiffusion);
  registerKernel(DwarfElephantRBDiffusionND);
  registerKernel(DwarfElephantRBDiffusionLiftingFunction);
  registerKernel(DwarfElephantZeroKernel);
  registerKernel(DwarfElephantRBTimeDerivative);
  registerKernel(ExtractQpPointsKernel);
  registerKernel(DwarfElephantEIMFKernel);
  registerKernel(DwarfElephantEIMAKernel);
  registerKernel(RBInnerProductMatrix);
  registerKernel(DwarfElephantRBDiffusionXX);
  registerKernel(DwarfElephantRBDiffusionXY);
  registerKernel(DwarfElephantRBDiffusionXZ);
  registerKernel(DwarfElephantRBDiffusionYY);
  registerKernel(DwarfElephantRBDiffusionYZ);
  registerKernel(DwarfElephantRBDiffusionZZ);
  registerKernel(DwarfElephantRBDiffusionYX);
  registerKernel(DwarfElephantRBDiffusionZX);
  registerKernel(DwarfElephantRBDiffusionZY); 
  registerKernel(DwarfElephantRBRFHeatsourceKernel);
  registerKernel(DwarfElephantRBPennesPerfusion);
  //DiracKernels
  registerDiracKernel(DwarfElephantRBConstantPointSource);

  // Materials
  registerMaterial(DwarfElephantSandStone);
  registerMaterial(DwarfElephantShale);
  registerMaterial(DwarfElephantFault);
  registerMaterial(ExtractQpPoints);

  // UserObjects
  registerUserObject(DwarfElephantInitializeRBSystemSteadyState);
  registerUserObject(DwarfElephantInitializeRBSystemTransient);
  registerUserObject(DwarfElephantOfflineOnlineStageSteadyState);
  registerUserObject(DwarfElephantOfflineOnlineStageTransient);
  registerUserObject(DwarfElephantERTPreCalculations);
  registerUserObject(DwarfElephantRBNodalVariableValue);
  registerUserObject(DwarfElephantRBElementalVariableValue);
  registerUserObject(DwarfElephantRBPointValue);
  registerUserObject(DwarfElephantReducedToFullState);
  registerUserObject(DwarfElephantComputeEIMInnerProductMatrixSteadyState);

  // Functions
  registerFunction(DwarfElephantInitialConditionFileReader);

  // Executioners
  registerExecutioner(DwarfElephantRBExecutioner);

  // Outputs
  registerOutput(DwarfElephantDakotaOutput);
  registerOutput(DwarfElephantStateOutput);
  registerOutput(DwarfElephantRBOutput);

  // VectorPostprocessors
  registerVectorPostprocessor(DwarfElephantElementalVariableValuesAlongLine);
  registerVectorPostprocessor(DwarfElephantAllElementalVariableValues);
  registerVectorPostprocessor(DwarfElephantNodalDifference);

}

// External entry point for dynamic syntax association
extern "C" void DwarfElephantApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { DwarfElephantApp::associateSyntax(syntax, action_factory); }

void
DwarfElephantApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  /**
   * Registering an Action is a little different than registering the other MOOSE
   * objects.  First, you need to register your Action in the associateSyntax method.
   * Also, you register your Action class with an "action_name" that can be
   * satisfied by executing the Action (running the "act" virtual method).
   */
  registerAction(DwarfElephantEIMFKernelsAction, "add_kernel");

  /**
   * We need to tell the parser what new section name to look for and what
   * Action object to build when it finds it.  This is done directly on the syntax
   * with the registerActionSyntax method.
   *
   * The section name should be the "full path" of the parsed section but should NOT
   * contain a leading slash.  Wildcard characters can be used to replace a piece of the
   * path.
   */
  registerSyntax("DwarfElephantEIMFKernelsAction", "KernelsEIMFAction"); // AddEIMFKernels will be the name of the action block in the input file
}
extern "C" void
DwarfElephantApp__registerExecFlags(Factory & factory)
{
  DwarfElephantApp::registerExecFlags(factory);
}
void
DwarfElephantApp::registerExecFlags(Factory & factory)
{
  registerExecFlag(EXEC_EIM);
}
