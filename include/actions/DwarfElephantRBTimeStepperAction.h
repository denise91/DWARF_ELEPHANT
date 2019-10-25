#pragma once

#include "Action.h"

class DwarfElephantRBTimeStepperAction : public Action
{
public:
  DwarfElephantRBTimeStepperAction(InputParameters params);

  virtual void act() override;

  void setDT(Real dt){_dt = dt;}
  void setTime(Real t){_time = t;}
  void setTimeLevel(unsigned int time_level){_time_level=time_level;}
  Real getDT(){return _dt;}
  Real getTime(){return _time;}
  unsigned int getTimeLevel(){return _time_level;}

protected:
  Real _dt;
  Real _time;
  unsigned int _time_level;
};

template <>
InputParameters validParams<DwarfElephantRBTimeStepperAction>();
