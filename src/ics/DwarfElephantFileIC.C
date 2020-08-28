#include "DwarfElephantFileIC.h"
#include "DwarfElephantInitialConditionFileReader.h"
#include "Function.h"

template <>
InputParameters
validParams<DwarfElephantFileIC>()
{
  InputParameters params = validParams<FunctionIC>();
  return params;
}

DwarfElephantFileIC::DwarfElephantFileIC(const InputParameters & parameters)
  : FunctionIC(parameters)
{
}

Real
DwarfElephantFileIC::value(const Point & /*p*/)
{
  const DwarfElephantInitialConditionFileReader & _file_func = cast_ref<const DwarfElephantInitialConditionFileReader &>(_func);
  return _file_func.value(*_current_node);
}
