/**
 * This BC is required to use the RB method for the Function Neumann BC.
 * Since all necessary operations are defined in the DwarfElephantRBIntegratedBC
 * class this class is the same as the Function Neumann BC provided by
 * MOOSE except that it inherits from the DwarfElephantRBIntegratedBC instead of
 * the IntegratedBC class.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBFUNCTIONNEUMANNBC_H
#define DWARFELEPHANTRBFUNCTIONNEUMANNBC_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBIntegratedBC.h"

///-------------------------------------------------------------------------
//Forward Declarations
class DwarfElephantRBFunctionNeumannBC;
class Function;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBFunctionNeumannBC>();

///-------------------------------------------------------------------------
class DwarfElephantRBFunctionNeumannBC : public DwarfElephantRBIntegratedBC
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBFunctionNeumannBC(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:
  /* Methods */
  virtual Real computeQpResidual() override;

  /* Attributes */
  const Function & _func;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBFUNCTIONNEUMANNBC_H
