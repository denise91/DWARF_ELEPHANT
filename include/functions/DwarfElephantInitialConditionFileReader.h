#ifndef DWARFELEPHANTINITIALCONDITIONFILEREADER_H
#define DWARFELEPHANTINITIALCONDITIONFILEREADER_H

#include "Function.h"

class DwarfElephantInitialConditionFileReader;

template <>
InputParameters validParams<DwarfElephantInitialConditionFileReader>();

class DwarfElephantInitialConditionFileReader : public Function
{
public:
  DwarfElephantInitialConditionFileReader(const InputParameters & parameters);
  virtual Real value(Real t, const Point & p) const override;
  virtual Real value(const Node & n) const;

protected:
  const std::string _file;
  std::vector<std::vector<Real>> _values;

private:
  void fileReader();
};

#endif // DWARFELEPHANTINITIALCONDITIONFILEREADER_H
