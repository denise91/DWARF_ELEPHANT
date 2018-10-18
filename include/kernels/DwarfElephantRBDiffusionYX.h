/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
  * This is for use with geometrical parametrizations
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBDIFFUSIONYX_H
#define DWARFELEPHANTRBDIFFUSIONYX_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBDiffusionYX;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionYX>();

///-------------------------------------------------------------------------
class DwarfElephantRBDiffusionYX : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBDiffusionYX(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBDIFFUSIONYX_H