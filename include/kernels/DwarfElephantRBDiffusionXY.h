/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
 * This is for use with geometrical parametrizations
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBDIFFUSIONXY_H
#define DWARFELEPHANTRBDIFFUSIONXY_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBDiffusionXY;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionXY>();

///-------------------------------------------------------------------------
class DwarfElephantRBDiffusionXY : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBDiffusionXY(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBDIFFUSIONXY_H
