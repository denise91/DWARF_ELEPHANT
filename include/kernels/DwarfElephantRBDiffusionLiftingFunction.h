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
#ifndef DWARFELEPHANTRBDIFFUSIONLIFTINGFUNCTION_H
#define DWARFELEPHANTRBDIFFUSIONLIFTINGFUNCTION_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBKernel.h"
#include "Function.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBDiffusionLiftingFunction;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusionLiftingFunction>();

///-------------------------------------------------------------------------
class DwarfElephantRBDiffusionLiftingFunction : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBDiffusionLiftingFunction(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Function * _lifting_function;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBDIFFUSIONLIFTINGFUNCTION_H
