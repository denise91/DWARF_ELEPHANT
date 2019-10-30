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
  params.addRequiredParam<std::vector<std::string>>("function", "The function.");
  params.addParam<std::vector<Real>>("thresholds", "The thresholds for the if condition.");
  return params;
}

DwarfElephantRBFunctionTimeMuAction::DwarfElephantRBFunctionTimeMuAction(InputParameters params) :
 DwarfElephantRBTimeDependentMuAction(params),
 _func_name(getParam<std::vector<std::string>>("function")),
 _thresholds(getParam<std::vector<Real>>("thresholds"))
 {
   _func.resize(_func_name.size());
 }

RBParameters
DwarfElephantRBFunctionTimeMuAction::calculateTimeDependency(const RBParameters mu)
{
  RBParameters & mu_time = const_cast<RBParameters&>(mu);
  Real pre_factor = 0;

  for(unsigned int i = 0; i < _func_name.size(); i++)
    _func[i] = &_problem->getFunction(_func_name[i]);

  // if(_time < _thresholds[0])
  //   pre_factor += _func[0]->value(_time,0);
  // else if(_time >= _thresholds[0] && _time<_thresholds[1]){
  //   pre_factor += _func[1]->value(_time,0) * pow(_time, 2);
  //   pre_factor += _func[2]->value(_time,0) * _time;
  //   pre_factor += _func[3]->value(_time,0);
  // }else if(_time >= _thresholds[1] && _time<_thresholds[2]){
  //   pre_factor += _func[4]->value(_time,0) * pow(_time, 3);
  //   pre_factor += _func[5]->value(_time,0) * pow(_time, 2);
  //   pre_factor += _func[6]->value(_time,0) * _time;
  //   pre_factor += _func[7]->value(_time,0);
  // }else{
    pre_factor += _func[0]->value(_time,0) * pow(_time, 4);
    pre_factor += _func[1]->value(_time,0) * pow(_time, 3);
    pre_factor += _func[2]->value(_time,0) * pow(_time, 2);
    pre_factor += _func[3]->value(_time,0) * _time;
    pre_factor += _func[4]->value(_time,0);
  // }


  // if(_time!=0)
    // pre_factor *= _func->value(_time,0) * _time;

  for(unsigned int i = 0; i < _ID_time_dependent_param.size(); i++)
  {
    const std::string mu_name = "mu_" + std::to_string(_ID_time_dependent_param[i]);
    const std::string mu_scale = "mu_" + std::to_string(_ID_time_scaling_param);
    Real _time_dependency = pre_factor + mu_time.get_value(mu_scale)*_time;
    mu_time.set_value(mu_name, _time_dependency);
  }

  return mu_time;
}
