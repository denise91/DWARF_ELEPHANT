/* This class was taken from the MOOSE Application beagle written by Powei Huang.
   We transferred it to this package to ensure that all classes are running with
   the same MOOSE version. */

#ifndef DWARFELEPHANTFEGRAVITYGRADIENTCOMPONENT_H
#define DWARFELEPHANTFEGRAVITYGRADIENTCOMPONENT_H

#include "AuxKernel.h"


//Forward Declarations
class DwarfElephantFEGravityGradientComponent;

template<>
InputParameters validParams<DwarfElephantFEGravityGradientComponent>();

/**
 * Coupled auxiliary value
 */
class DwarfElephantFEGravityGradientComponent : public AuxKernel
{
public:
  DwarfElephantFEGravityGradientComponent(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;
  const VariableGradient & _grad_gravity;
  unsigned _component;
};

#endif
