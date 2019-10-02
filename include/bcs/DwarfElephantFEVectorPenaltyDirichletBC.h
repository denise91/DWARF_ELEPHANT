#pragma once

#include "VectorIntegratedBC.h"

class DwarfElephantFEVectorPenaltyDirichletBC;

template <>
InputParameters validParams<DwarfElephantFEVectorPenaltyDirichletBC>();

class DwarfElephantFEVectorPenaltyDirichletBC : public VectorIntegratedBC
{
public:
  DwarfElephantFEVectorPenaltyDirichletBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const RealVectorValue & _value;
  const Real & _penalty;
};
