#ifndef DWARFELEPHANTPICEWISEFUNCTION_H
#define DWARFELEPHANTPICEWISEFUNCTION_H

#include "Function.h"

class DwarfElephantPicewiseFunction;

template <>
InputParameters validParams<DwarfElephantPicewiseFunction>();

///This function is responsible for reading initial condition values from file.
class DwarfElephantPicewiseFunction : public Function
{
public:
  DwarfElephantPicewiseFunction(const InputParameters & parameters);
  virtual Real value(Real t, const Point & p) const override;

protected:
  std::vector<Real> _thresholds;
  std::vector<const Function *> _funcs;

};

#endif // DwarfElephantPicewiseFunction_H
