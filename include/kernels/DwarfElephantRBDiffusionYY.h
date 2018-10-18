/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
 * This is for use with geometrical parametrizations
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBDIFFUSIONYY_H
#define DWARFELEPHANTRBDIFFUSIONYY_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBDiffusionYY;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionYY>();

///-------------------------------------------------------------------------
class DwarfElephantRBDiffusionYY : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBDiffusionYY(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBDIFFUSIONYY_H
