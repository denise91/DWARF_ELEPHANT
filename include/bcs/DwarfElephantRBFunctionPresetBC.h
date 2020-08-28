/**
 * This BC is required to use the RB method for the Function Preset BC.
 * Since all necessary operations are defined in the DwarfElephantRBNodalBC
 * class this class is the same as the Function Preset BC provided by
 * MOOSE except that it inherits from the DwarfElephantRBNodalBC instead of
 * the NodalBC class.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBFUNCTIONPRESETBC_H
#define DWARFELEPHANTRBFUNCTIONPRESETBC_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBPresetNodalBC.h"

///-------------------------------------------------------------------------
//Forward Declarations
class DwarfElephantRBFunctionPresetBC;
class Function;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBFunctionPresetBC>();

///-------------------------------------------------------------------------
class DwarfElephantRBFunctionPresetBC : public DwarfElephantRBPresetNodalBC
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBFunctionPresetBC(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:
  /* Methods */
  virtual Real computeQpValue() override;

  /* Attributes */
  const Function & _func;
};

///-------------------------------------------------------------------------
#endif //DWARFELEPHANTRBFUNCTIONPRESETBC_H
