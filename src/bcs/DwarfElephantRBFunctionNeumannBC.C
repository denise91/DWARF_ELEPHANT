#include "DwarfElephantRBFunctionNeumannBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBFunctionNeumannBC);

template<>
InputParameters validParams<DwarfElephantRBFunctionNeumannBC>()
{
  InputParameters params = validParams<DwarfElephantRBIntegratedBC>();
  params.addRequiredParam<FunctionName>("function", "The function.");
  return params;
}

DwarfElephantRBFunctionNeumannBC::DwarfElephantRBFunctionNeumannBC(const InputParameters & parameters) :
    DwarfElephantRBIntegratedBC(parameters),
    _func(getFunction("function"))
{
}

Real
DwarfElephantRBFunctionNeumannBC::computeQpResidual()
{
  return _test[_i][_qp] * _func.value(_t, _q_point[_qp]);
}
