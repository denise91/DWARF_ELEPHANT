#pragma once

#include "VectorIntegratedBC.h"

class DwarfElephantFEVectorRobinBC;

template <>
InputParameters validParams<DwarfElephantFEVectorRobinBC>();

class DwarfElephantFEVectorRobinBC : public VectorIntegratedBC
{
public:
  DwarfElephantFEVectorRobinBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const RealVectorValue & _value;
  const Real & _penalty;
};
