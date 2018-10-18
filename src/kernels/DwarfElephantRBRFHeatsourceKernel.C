#include "DwarfElephantRBRFHeatsourceKernel.h"
#include "Function.h"

template<>
InputParameters
validParams<DwarfElephantRBRFHeatsourceKernel>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a RF heatsource function using the RBKernel.");
  params.addRequiredParam<FunctionName>("heat_source_function","Name of the function approximating the RF heat source.");

  return params;
}

DwarfElephantRBRFHeatsourceKernel::DwarfElephantRBRFHeatsourceKernel(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
  _function(getFunction("heat_source_function"))
{
}

Real DwarfElephantRBRFHeatsourceKernel::computeQpResidual()
{
  return _function.value(_t,_q_point[_qp]) * _test[_i][_qp];
}

Real DwarfElephantRBRFHeatsourceKernel::computeQpJacobian()
{
  return 0;
}
