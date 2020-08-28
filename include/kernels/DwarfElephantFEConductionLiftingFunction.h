/**
 * This Kernel is implements a thermal conduction problem using the full
 * Finite Element solution. It is included in this package for validation
 * purposes.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTFECONDUCTIONLIFTINGFUNCTION_H
#define DWARFELEPHANTFECONDUCTIONLIFTINGFUNCTION_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "Diffusion.h"
#include "Function.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantFEConductionLiftingFunction;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEConductionLiftingFunction>();

///-------------------------------------------------------------------------
class DwarfElephantFEConductionLiftingFunction : public Diffusion
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFEConductionLiftingFunction(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;


  /* Attributes */
  const MaterialProperty<Real> &_lambda;

  const Function * _lifting_function;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTFECONDUCTIONLIFTINGFUNCTION_H
