#pragma once

#include "DwarfElephantRBTimeStepperAction.h"

class DwarfElephantRBTimeSequenceAction : public DwarfElephantRBTimeStepperAction
{
public:
  DwarfElephantRBTimeSequenceAction(InputParameters params);

  virtual void act() override;

protected:
  std::vector<Real> _time_sequence;
};

template <>
InputParameters validParams<DwarfElephantRBTimeSequenceAction>();
