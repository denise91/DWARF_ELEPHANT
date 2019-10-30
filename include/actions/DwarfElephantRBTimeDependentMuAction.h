#pragma once

#include "Action.h"
#include "libmesh/rb_parametrized.h"

class DwarfElephantRBTimeDependentMuAction : public Action
{
public:
  DwarfElephantRBTimeDependentMuAction(InputParameters params);

  virtual void act() override {}
  virtual RBParameters calculateTimeDependency(const RBParameters mu);

  void setTime(Real time){_time=time;}
  Real getTime(){return _time;}

protected:
  Real _time;
  std::vector<unsigned int> _ID_time_dependent_param;
  unsigned int _ID_time_scaling_param;
};

template <>
InputParameters validParams<DwarfElephantRBTimeDependentMuAction>();
