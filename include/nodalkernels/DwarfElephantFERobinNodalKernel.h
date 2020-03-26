#pragma once

#include "NodalKernel.h"

// Forward Declarations
class DwarfElephantFERobinNodalKernel;

template <>
InputParameters validParams<DwarfElephantFERobinNodalKernel>();

class DwarfElephantFERobinNodalKernel : public NodalKernel
{
public:
  static InputParameters validParams();

  DwarfElephantFERobinNodalKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  const Real & _alpha;
};
