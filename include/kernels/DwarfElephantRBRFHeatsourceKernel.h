#ifndef DWARFELEPHANTRBRFHEATSOURCEKERNEL_H
#define DWARFELEPHANTRBRFHEATSOURCEKERNEL_H

#include "DwarfElephantRBRFHeatsourceKernel.h"

class DwarfElephantRBRFHeatsourceKernel;

template<>
InputParameters validParams<DwarfElephantRBRFHeatsourceKernel>();

class DwarfElephantRBRFHeatsourceKernel : public DwarfElephantRBKernel
{
public:
  DwarfElephantRBRFHeatsourceKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Function & _function;
};

#endif
