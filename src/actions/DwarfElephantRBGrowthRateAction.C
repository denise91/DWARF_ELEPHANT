#include "DwarfElephantRBGrowthRateAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("DwarfElephantApp", DwarfElephantRBGrowthRateAction, "add_function");

template <>
InputParameters
validParams<DwarfElephantRBGrowthRateAction>()
{
  InputParameters params = validParams<DwarfElephantRBTimeStepperAction>();
  params.addParam<Real>("growth_rate", 1.0,"The growth rate for the timesteps.");
  params.addParam<Real>("threshold", 1.0e30,"Threshold for the growth of dt.");
  return params;
}

DwarfElephantRBGrowthRateAction::DwarfElephantRBGrowthRateAction(InputParameters params) :
 DwarfElephantRBTimeStepperAction(params),
 _growth_rate(getParam<Real>("growth_rate")),
 _threshold(getParam<Real>("threshold"))
 {
 }

void
DwarfElephantRBGrowthRateAction::act()
{
  if(_dt < _threshold)
    _dt *= _growth_rate;
}
