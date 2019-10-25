#pragma once

#include "IntegratedBC.h"

class DwarfElephantFERobinBC;
class Function;

template <>
InputParameters validParams<DwarfElephantFERobinBC>();

class DwarfElephantFERobinBC : public IntegratedBC
{
public:
  DwarfElephantFERobinBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real _alpha;
  const Real & _value;
};
