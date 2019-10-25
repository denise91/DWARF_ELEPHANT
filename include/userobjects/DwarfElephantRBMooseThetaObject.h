#pragma once

// MOOSE includes
#include "NodalUserObject.h"

// Forward Declarations
class DwarfElephantRBMooseThetaObject;

template <>
InputParameters validParams<DwarfElephantRBMooseThetaObject>();

class DwarfElephantRBMooseThetaObject : public NodalUserObject
{
public:
  DwarfElephantRBMooseThetaObject(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override;
  virtual void finalize() override {}
  virtual void threadJoin(const UserObject & uo) override {}

protected:
  const Function & _func;

  std::string _simulation_type;

  unsigned int _ID_moose_theta_object;

  // const DwarfElephantInitializeRBSystemSteadyState * _initialize_rb_system;
  const DwarfElephantInitializeRBSystemTransient * _initialize_rb_system_transient;
};
