/**
 * This BC is required to use the RB method for the Robin BC.
 * Since all necessary operations are defined in the
 * DwarfElephantRBIntegratedBC class this class is the same as the
 * Robin BC provided by MOOSE except that it
 * inherits from the DwarfElephantRBIntegratedBC instead of the IntegratedBC
 * class.
 */


///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBROBINNEUMANNBC_H
#define DWARFELEPHANTRBROBINNEUMANNBC_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBIntegratedBC.h"

///This BC is required to use the RB method for the Penalty Dirichlet BC. Since all necessary operations are defined in the DwarfElephantRBIntegratedBC class this class is the same as the Penalty Dirichlet BC provided by MOOSE except that it inherits from the DwarfElephantRBIntegratedBC instead of the IntegratedBC class.
//Forward Declarations
class DwarfElephantRBRobinNeumannBC;
class Function;

///----------------------------INPUT PARAMETERS-----------------------------
template <>
InputParameters validParams<DwarfElephantRBRobinNeumannBC>();

///This BC is required to use the RB method for the Penalty Dirichlet BC. Since all necessary operations are defined in the DwarfElephantRBIntegratedBC class this class is the same as the Penalty Dirichlet BC provided by MOOSE except that it inherits from the DwarfElephantRBIntegratedBC instead of the IntegratedBC class.
class DwarfElephantRBRobinNeumannBC : public DwarfElephantRBIntegratedBC
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBRobinNeumannBC(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:
  /*Methods*/
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

//---------------------------------PRIVATE----------------------------------
private:
  /*Attributes*/
  Real _value;
};

#endif // DWARFELEPHANTRBROBINNEUMANNBC_H
