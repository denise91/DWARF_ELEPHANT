// MOOSE Includes
#include "DwarfElephantApp.h"
#include "AppFactory.h"
#include "ActionFactory.h" // <- Actions are special (they have their own factory)
#include "MooseSyntax.h"

template <>
InputParameters
validParams<DwarfElephantApp>()
{
  InputParameters params = validParams<MooseApp>();
  params.set<bool>("automatic_automatic_scaling") = false;
  return params;
}

DwarfElephantApp::DwarfElephantApp(InputParameters parameters) : MooseApp(parameters)
{
  srand(processor_id());
  DwarfElephantApp::registerAll(_factory, _action_factory, _syntax);
}

void
DwarfElephantApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  Registry::registerObjectsTo(f, {"DwarfElephantApp"});
  Registry::registerActionsTo(af, {"DwarfElephantApp"});

  /**
   * An Action is a little different than registering the other MOOSE
   * objects.  First, you need to register your Action like normal in its file with
   * the registerMooseAction macro. - e.g.:
   *
   *     registerMooseAction("ExampleApp", ConvectionDiffusionAction, "add_kernel");
   *
   * Then we need to tell the parser what new section name to look for and what
   * Action object to build when it finds it.  This is done directly on the syntax
   * with the registerActionSyntax method.
   *
   * The section name should be the "full path" of the parsed section but should NOT
   * contain a leading slash.  Wildcard characters can be used to replace a piece of the
   * path.
   */
  registerSyntax("DwarfElephantRBTimeStepperAction", "RBTimeStepper");
  registerSyntax("DwarfElephantRBGrowthRateAction", "RBTimeStepper/GrowthRate");
  registerSyntax("DwarfElephantRBTimeSequenceAction", "RBTimeStepper/TimeSequence");

  registerSyntax("DwarfElephantRBTimeDependentMuAction", "RBTimeDependentMu");
  registerSyntax("DwarfElephantRBStartEndTimeMuAction", "RBTimeDependentMu/RBStartEndTimeMu");
  registerSyntax("DwarfElephantRBFunctionTimeMuAction", "RBTimeDependentMu/RBFunctionTimeMu");
}

void
DwarfElephantApp::registerApps()
{
  registerApp(DwarfElephantApp);
}
