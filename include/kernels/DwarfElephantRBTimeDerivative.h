/**
 * This Kernel implements the TimeDerivative by using the RB method.
 * It is important to note that every PDE that will be used within the RB
 * method has to inherit from RBKernel and not from Kernel. Since all
 * RB related operations are performed in the RBTimeKernel class this class
 * is the same as the MOOSE provided class with the eception that it inherits
 * from DwarfElephantRBTimeKernel instead of TimeKernel.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBTIMEDERIVATIVE_H
#define DWARFELEPHANTRBTIMEDERIVATIVE_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBTimeKernel.h"

///-------------------------------------------------------------------------
// Forward Declaration
class DwarfElephantRBTimeDerivative;

///----------------------------INPUT PARAMETERS-----------------------------
template <>
InputParameters validParams<DwarfElephantRBTimeDerivative>();

///-------------------------------------------------------------------------
class DwarfElephantRBTimeDerivative : public DwarfElephantRBTimeKernel
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBTimeDerivative(const InputParameters & parameters);

  /*Methods*/
  virtual void computeJacobian() override;

//--------------------------------PROTECTED---------------------------------
protected:
  /*Methods*/
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  /*Attributes*/
  bool _lumping;
  Real _heat_capacity;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBTIMEDERIVATIVE_H
