#include "DwarfElephantRBTimeDependentMuAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("DwarfElephantApp", DwarfElephantRBTimeDependentMuAction, "add_function");

template <>
InputParameters
validParams<DwarfElephantRBTimeDependentMuAction>()
{
  InputParameters params = validParams<Action>();
  params.addParam<std::vector<unsigned int>>("ID_time_dependent_param", std::vector<unsigned int> {0}, "The IDs of the time dependent paramters.");
params.addParam<unsigned int>("ID_time_scaling_param", 0, "The Is of the time scaling paramter.");
  return params;
}

DwarfElephantRBTimeDependentMuAction::DwarfElephantRBTimeDependentMuAction(InputParameters params) :
 Action(params),
 _time(0),
 _ID_time_dependent_param(getParam<std::vector<unsigned int>>("ID_time_dependent_param")),
 _ID_time_scaling_param(getParam<unsigned int>("ID_time_scaling_param"))
{}

RBParameters
DwarfElephantRBTimeDependentMuAction::calculateTimeDependency(const RBParameters mu)
{
  return mu;
}
