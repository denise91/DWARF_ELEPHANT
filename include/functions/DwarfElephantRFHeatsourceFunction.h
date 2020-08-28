#ifndef DWARFELEPHANTHEATSOURCEFUNCTION_H
#define DWARFELEPHANTHEATSOURCEFUNCTION_H

#include "Function.h"

class DwarfElephantRFHeatsourceFunction;

template<>
InputParameters validParams<DwarfElephantRFHeatsourceFunction>();

class DwarfElephantRFHeatsourceFunction : public Function
{
public:
  DwarfElephantRFHeatsourceFunction(const InputParameters & parameters);

  virtual Real value(Real t, const Point & p) const override;

protected:
  std::vector<Real> _needle_active_region_p1;
  std::vector<Real> _needle_active_region_p2;
  Real _needle_power;

};

#endif
