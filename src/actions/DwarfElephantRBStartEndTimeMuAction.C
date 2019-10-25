#include "DwarfElephantRBStartEndTimeMuAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"

registerMooseAction("DwarfElephantApp", DwarfElephantRBStartEndTimeMuAction, "add_function");

template <>
InputParameters
validParams<DwarfElephantRBStartEndTimeMuAction>()
{
  InputParameters params = validParams<DwarfElephantRBTimeDependentMuAction>();
  params.addParam<Real>("start_time", 0.0,"The start time for the time dependent parameter.");
  params.addParam<Real>("end_time", 0.0,"The end time for the time dependent parameter.");
  params.addRequiredParam<std::string>("initial_rb_userobject", "Name of the UserObject for initializing the RB system.");
  return params;
}

DwarfElephantRBStartEndTimeMuAction::DwarfElephantRBStartEndTimeMuAction(InputParameters params) :
 DwarfElephantRBTimeDependentMuAction(params),
 _start_time(getParam<Real>("start_time")),
 _end_time(getParam<Real>("end_time")),
 _userobject_name(getParam<std::string>("initial_rb_userobject"))
 {
 }

RBParameters
DwarfElephantRBStartEndTimeMuAction::calculateTimeDependency(const RBParameters mu)
{
  RBParameters & mu_time = const_cast<RBParameters&>(mu);
  _initialize_rb_system = &_problem->getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(_userobject_name);
  Real _dt = _initialize_rb_system->_rb_con_ptr->get_delta_t();

  Real pre_factor = 1.0;

  if (_time < _start_time || _time - _dt >= _end_time)
    pre_factor = 0.0;
  else if (_time - _dt < _start_time)
  {
    if (_time <= _end_time)
      pre_factor *= (_time - _start_time) / _dt;
    else
      pre_factor *= (_end_time - _start_time) / _dt;
  }
  else if (_time > _end_time)
    pre_factor *= (_end_time - (_time - _dt)) / _dt;

  for(unsigned int i = 0; i < _ID_time_dependent_param.size(); i++)
  {
    const std::string mu_name = "mu_" + std::to_string(_ID_time_dependent_param[i]);
    Real _time_dependency = pre_factor * mu_time.get_value(mu_name);
    mu_time.set_value(mu_name, _time_dependency);
  }

  return mu_time;
}
