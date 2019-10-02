#pragma once

#include "VectorIntegratedBC.h"

class DwarfElephantFEVectorNeumannBC;

template <>
InputParameters validParams<DwarfElephantFEVectorNeumannBC>();

class DwarfElephantFEVectorNeumannBC : public VectorIntegratedBC
{
public:
  DwarfElephantFEVectorNeumannBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  const RealVectorValue & _value;
};
