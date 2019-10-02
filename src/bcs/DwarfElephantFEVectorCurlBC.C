#include "DwarfElephantFEVectorCurlBC.h"
#include "Function.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEVectorCurlBC);

template <>
InputParameters
validParams<DwarfElephantFEVectorCurlBC>()
{
  InputParameters params = validParams<VectorIntegratedBC>();
  params.addRequiredParam<FunctionName>("curl_value", "Value of field curl on the boundary.");
  return params;
}

DwarfElephantFEVectorCurlBC::DwarfElephantFEVectorCurlBC(const InputParameters & parameters):
  VectorIntegratedBC(parameters),
  _curl_value(getFunction("curl_value"))
{
}

Real
DwarfElephantFEVectorCurlBC::computeQpResidual()
{
  return _test[_i][_qp] * _normals[_qp].cross(_curl_value.vectorCurl(_t, _q_point[_qp]));
}

Real
DwarfElephantFEVectorCurlBC::computeQpJacobian()
{
  return 0.0;
}
