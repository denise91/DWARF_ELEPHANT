#include "DwarfElephantRBTimeSequenceAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("DwarfElephantApp", DwarfElephantRBTimeSequenceAction, "add_function");

template <>
InputParameters
validParams<DwarfElephantRBTimeSequenceAction>()
{
  InputParameters params = validParams<DwarfElephantRBTimeStepperAction>();
  params.addRequiredParam<std::vector<Real>>("time_sequence", "Time sequence for the time stepper.");
  return params;
}

DwarfElephantRBTimeSequenceAction::DwarfElephantRBTimeSequenceAction(InputParameters params) :
 DwarfElephantRBTimeStepperAction(params),
 _time_sequence(getParam<std::vector<Real>>("time_sequence"))
 {
 }

void
DwarfElephantRBTimeSequenceAction::act()
{
  Real new_time = _time_sequence[_time_level];
  _dt = new_time - _time;
}
