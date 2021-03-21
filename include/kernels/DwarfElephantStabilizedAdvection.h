//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef DWARFELEPHANTSTABILIZEDADVECTION_H
#define DWARFELEPHANTSTABILIZEDADVECTION_H

#include "INSBase.h"

// Forward Declarations
class DwarfElephantStabilizedAdvection;

template <>
InputParameters validParams<DwarfElephantStabilizedAdvection>();

/**
 * This class is responsible for solving the scalar advection
 * equation, possibly with a forcing function.
 */
class DwarfElephantStabilizedAdvection : public INSBase
{
public:
  DwarfElephantStabilizedAdvection(const InputParameters & parameters);

  virtual ~DwarfElephantStabilizedAdvection() {}

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned /*jvar*/) override { return 0; }
  virtual Real tau() override;

  const Function & _ffn;
  MooseEnum _tau_type;

private:
  const Function & _Xvelocity;
  const Function & _Yvelocity;
  const Function & _Zvelocity;

  const VariableSecond & _second_u;
  const MaterialProperty<Real> & _rhoC;
  const MaterialProperty<Real> & _kappa;
  const bool _stabilized;
};

#endif
