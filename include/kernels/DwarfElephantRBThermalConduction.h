/**
 * This Kernel is implements a thermal conduction problem using the
 * reduced basis solution. It is included in this package for validation
 * purposes.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBTHERMALCONDUCTION_H
#define DWARFELEPHANTRBTHERMALCONDUCTION_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "DwarfElephantRBDiffusion.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBThermalConduction;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBThermalConduction>();

///-------------------------------------------------------------------------
class DwarfElephantRBThermalConduction : public DwarfElephantRBDiffusion
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBThermalConduction(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  /* Attributes */
  Real _lambda;
  Real _norm_value;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBTHERMALCONDUCTION_H
