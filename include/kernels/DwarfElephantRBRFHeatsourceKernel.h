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

  //Function & _function;
  Real _needle_center_x;
  Real _needle_center_y;
  Real _needle_center_z;
  Real _needle_axis_theta;
  Real _needle_axis_phi;
  Real r_0;
  Real l_0;
  Real r;
  Real l;
};

#endif
