/**
 * This Kernel is implements a thermal conduction problem using the
 * reduced basis solution. It is included in this package for validation
 * purposes.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "DwarfElephantRBDiffusion.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBElectricalConduction;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBElectricalConduction>();

///This Kernel is implements a thermal conduction problem using the reduced basis solution. Note that the thermal conductivity is fixed for all parameters.
class DwarfElephantRBElectricalConduction : public DwarfElephantRBDiffusion
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBElectricalConduction(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  /* Attributes */
  Real _resistivity;
  Real _norm_value;
};
