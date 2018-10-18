/**
 * This Kernel is implements a Pennes Perfusion term using the
 * reduced basis method.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBPENNESPERFUSION_H
#define DWARFELEPHANTRBPENNESPERFUSION_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "DwarfElephantRBDiffusion.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBPennesPerfusion;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBPennesPerfusion>();

///-------------------------------------------------------------------------
class DwarfElephantRBPennesPerfusion : public DwarfElephantRBKernel
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBPennesPerfusion(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBPENNESPERFUSION_H
