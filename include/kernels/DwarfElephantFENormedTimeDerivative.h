///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTFENORMEDTIMEDERIVATIVE_H
#define DWARFELEPHANTFENORMEDTIMEDERIVATIVE_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "TimeDerivative.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantFENormedTimeDerivative;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFENormedTimeDerivative>();

///This Kernel is implements a constant radiogenic heat production using the full Finite Element solution. It is included in this package for validation purposes.
class DwarfElephantFENormedTimeDerivative : public TimeDerivative
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFENormedTimeDerivative(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _norm_value;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTFENORMEDTIMEDERIVATIVE_H
