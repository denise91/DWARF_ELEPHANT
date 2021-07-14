/**
 * This Kernel implements the Diffusion problem by using the RB method.
 * It is important to note that every PDE that will be used within the RB
 * method has to inherit from RBKernel and not from Kernel.
 * Furthermore, one should recall that the stiffness matrix and the load
 * vector are constructed out of the parameter independent part of the
 * PDE. Therefore, the functions computeQpResidual() and computeQpJacobian()
 * should only contain this parameter independent part. Consequently, the
 * RBDiffusion Kernel is used for a Conduction problem.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBDIFFUSION_H
#define DWARFELEPHANTRBDIFFUSION_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBDiffusion;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusion>();

///-------------------------------------------------------------------------
class DwarfElephantRBDiffusion : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBDiffusion(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;

  /* Attributes */
  Real _thermal_conductivity;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBDIFFUSION_H
