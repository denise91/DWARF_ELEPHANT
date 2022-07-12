/**
 * This Kernel is implements the source term for the calculation of the
 * gravitation field using the full
 * Finite Element solution. It is included in this package for validation
 * purposes.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTFEGRAVITYFIELDSOURCETERM_H
#define DWARFELEPHANTFEGRAVITYFIELDSOURCETERM_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "Kernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantFEGravityFieldSourceTerm;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEGravityFieldSourceTerm>();

class DwarfElephantFEGravityFieldSourceTerm : public Kernel
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFEGravityFieldSourceTerm(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _density;
  Real _gravitational_constant;
  Real _norm_value_density;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTFECONSTANTRADIOGENICHEATPRODUCTION_H
