#pragma once

#include "Function.h"
#include "DwarfElephantRBTimeDependentMuAction.h"

class DwarfElephantInitializeRBSystemTransient;

class DwarfElephantRBFunctionTimeMuAction : public DwarfElephantRBTimeDependentMuAction
{
public:
  DwarfElephantRBFunctionTimeMuAction(InputParameters params);

  virtual void act() override {}
  virtual RBParameters calculateTimeDependency(const RBParameters mu) override;

protected:
  std::string _func_name;
  const Function * _func;

};

template <>
InputParameters validParams<DwarfElephantRBFunctionTimeMuAction>();
