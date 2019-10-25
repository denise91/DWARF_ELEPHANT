#pragma once

#include "DwarfElephantRBTimeStepperAction.h"

class DwarfElephantRBGrowthRateAction : public DwarfElephantRBTimeStepperAction
{
public:
  DwarfElephantRBGrowthRateAction(InputParameters params);

  virtual void act() override;

protected:
  Real _growth_rate;
  Real _threshold;
};

template <>
InputParameters validParams<DwarfElephantRBGrowthRateAction>();
