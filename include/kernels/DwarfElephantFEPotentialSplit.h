/**
 * This Kernel is implements the concept of the lifting function to avoid
 * problems caused by non-homogenous DirichletBC.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTFEPOTENTIALSPLIT_H
#define DWARFELEPHANTFEPOTENTIALSPLIT_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "Diffusion.h"
#include "Function.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantFEPotentialSplit;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEPotentialSplit>();

///This Kernel is implements the concept of the lifting function to avoid problems caused by non-homogenous DirichletBC.
class DwarfElephantFEPotentialSplit : public Diffusion
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFEPotentialSplit(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  /* Attributes */
  const Function * _stationary_potential;
  Real _scale;
  Real _norm_value;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTFEPOTENTIALSPLIT_H
