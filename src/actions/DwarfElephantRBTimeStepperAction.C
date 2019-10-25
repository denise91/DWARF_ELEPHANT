#include "DwarfElephantRBTimeStepperAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("DwarfElephantApp", DwarfElephantRBTimeStepperAction, "add_function");

template <>
InputParameters
validParams<DwarfElephantRBTimeStepperAction>()
{
  InputParameters params = validParams<Action>();
  return params;
}

DwarfElephantRBTimeStepperAction::DwarfElephantRBTimeStepperAction(InputParameters params) :
 Action(params),
 _dt(0),
 _time(0),
 _time_level(0)
{}

void
DwarfElephantRBTimeStepperAction::act()
{
}
