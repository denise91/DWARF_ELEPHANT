#pragma once

#include "DwarfElephantRBTimeDependentMuAction.h"
#include "DwarfElephantInitializeRBSystemTransient.h"

class DwarfElephantInitializeRBSystemTransient;

class DwarfElephantRBStartEndTimeMuAction : public DwarfElephantRBTimeDependentMuAction
{
public:
  DwarfElephantRBStartEndTimeMuAction(InputParameters params);

  virtual void act() override {}
  virtual RBParameters calculateTimeDependency(const RBParameters mu) override;


protected:
  Real _start_time;
  Real _end_time;

  std::string _userobject_name;

  const DwarfElephantInitializeRBSystemTransient * _initialize_rb_system;
};

template <>
InputParameters validParams<DwarfElephantRBStartEndTimeMuAction>();
