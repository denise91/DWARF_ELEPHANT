/**
 * This BC is required to use the RB method for the Robin BC.
 * Since all necessary operations are defined in the
 * DwarfElephantRBIntegratedBC class this class is the same as the
 * Robin BC provided by MOOSE except that it
 * inherits from the DwarfElephantRBIntegratedBC instead of the IntegratedBC
 * class.
 */


///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBROBINDIRICHLETBC_H
#define DWARFELEPHANTRBROBINDIRICHLETBC_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBIntegratedBC.h"

///This BC is required to use the RB method for the Penalty Dirichlet BC. Since all necessary operations are defined in the DwarfElephantRBIntegratedBC class this class is the same as the Penalty Dirichlet BC provided by MOOSE except that it inherits from the DwarfElephantRBIntegratedBC instead of the IntegratedBC class.
//Forward Declarations
class DwarfElephantRBRobinDirichletBC;
class Function;

///----------------------------INPUT PARAMETERS-----------------------------
template <>
InputParameters validParams<DwarfElephantRBRobinDirichletBC>();

///This BC is required to use the RB method for the Penalty Dirichlet BC. Since all necessary operations are defined in the DwarfElephantRBIntegratedBC class this class is the same as the Penalty Dirichlet BC provided by MOOSE except that it inherits from the DwarfElephantRBIntegratedBC instead of the IntegratedBC class.
class DwarfElephantRBRobinDirichletBC : public DwarfElephantRBIntegratedBC
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBRobinDirichletBC(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:
  /*Methods*/
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

//---------------------------------PRIVATE----------------------------------
private:
  /*Attributes*/
  const Real & _alpha;
};

#endif // DWARFELEPHANTRBROBINDIRICHLETBC_H
