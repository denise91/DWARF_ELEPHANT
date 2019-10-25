#include "DwarfElephantRBFunctionTimeMuAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("DwarfElephantApp", DwarfElephantRBFunctionTimeMuAction, "add_function");

template <>
InputParameters
validParams<DwarfElephantRBFunctionTimeMuAction>()
{
  InputParameters params = validParams<DwarfElephantRBTimeDependentMuAction>();
  params.addRequiredParam<std::string>("function", "The function.");
  return params;
}

DwarfElephantRBFunctionTimeMuAction::DwarfElephantRBFunctionTimeMuAction(InputParameters params) :
 DwarfElephantRBTimeDependentMuAction(params),
 _func_name(getParam<std::string>("function"))
 {
 }

RBParameters
DwarfElephantRBFunctionTimeMuAction::calculateTimeDependency(const RBParameters mu)
{
  RBParameters & mu_time = const_cast<RBParameters&>(mu);
  Real pre_factor = 1;

  _func = &_problem->getFunction(_func_name);

  // if(_time!=0)
    pre_factor *= _func->value(_problem->time(),0) * _time;

  for(unsigned int i = 0; i < _ID_time_dependent_param.size(); i++)
  {
    const std::string mu_name = "mu_" + std::to_string(_ID_time_dependent_param[i]);
    Real _time_dependency = pre_factor * mu_time.get_value(mu_name);
    mu_time.set_value(mu_name, _time_dependency);
  }

  return mu_time;
}
