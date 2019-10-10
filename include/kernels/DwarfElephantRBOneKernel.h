
///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBONEKERNEL_H
#define DWARFELEPHANTRBONEKERNEL_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBOneKernel;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBOneKernel>();

///
class DwarfElephantRBOneKernel : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBOneKernel(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  bool _transient;

  Real _density;
  Real _specific_heat;
  Real _norm_value_density;
  Real _norm_value_specific_heat;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBONEKERNEL_H
