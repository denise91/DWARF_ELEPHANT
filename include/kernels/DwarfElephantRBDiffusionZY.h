/**
 * This Kernel splits the diffusion operator into a sum of products of partial dervatives
  * This is for use with geometrical parametrizations
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBDIFFUSIONZY_H
#define DWARFELEPHANTRBDIFFUSIONZY_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBDiffusionZY;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionZY>();

///-------------------------------------------------------------------------
class DwarfElephantRBDiffusionZY : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBDiffusionZY(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBDIFFUSIONZY_H