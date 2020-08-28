/**
 * This BC is required to use the RB method for the Function Dirichlet BC.
 * Since all necessary operations are defined in the DwarfElephantRBNodalBC
 * class this class is the same as the Function Dirichlet BC provided by
 * MOOSE except that it inherits from the DwarfElephantRBNodalBC instead of
 * the NodalBC class.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBFUNCTIONDIRICHLETBC_H
#define DWARFELEPHANTRBFUNCTIONDIRICHLETBC_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBNodalBC.h"

///-------------------------------------------------------------------------
//Forward Declarations
class DwarfElephantRBFunctionDirichletBC;
class Function;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBFunctionDirichletBC>();

///-------------------------------------------------------------------------
class DwarfElephantRBFunctionDirichletBC : public DwarfElephantRBNodalBC
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBFunctionDirichletBC(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:
  /* Methods */
  Real f();

  virtual Real computeQpResidual() override;

  /* Attributes */
  const Function & _func;
};

///-------------------------------------------------------------------------
#endif //DWARFELEPHANTRBFUNCTIONDIRICHLETBC_H
