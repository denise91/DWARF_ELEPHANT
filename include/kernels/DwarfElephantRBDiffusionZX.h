/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
  * This is for use with geometrical parametrizations
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBDIFFUSIONZX_H
#define DWARFELEPHANTRBDIFFUSIONZX_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBDiffusionZX;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionZX>();

///-------------------------------------------------------------------------
class DwarfElephantRBDiffusionZX : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBDiffusionZX(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBDIFFUSIONZX_H