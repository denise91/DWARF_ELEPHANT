/**
 * This Kernel is implements the concept of the lifting function to avoid
 * problems caused by non-homogenous DirichletBC.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("The class implements a lifting function.");
  params.addRequiredParam<FunctionName>("lifting_function", "Name of the lifting function two account for the inhomogeneous Dirichlet boundary conditions.");
  params.addRequiredParam<Real>("scale", "Defines the value of the scaling parameter.");
  params.addParam<Real>("norm_value", 1.0, "Defines the normalization value.");
  params.addParam<Real>("density", 1.0, "Defines the bulk density.");
  params.addParam<Real>("specific_heat", 1.0, "Defines the bulk specific heat.");
  params.addParam<Real>("norm_value_density", 1.0, "Defines the normalization value.");
  params.addParam<Real>("norm_value_specific_heat", 1.0, "Defines the normalization value.");
  params.addParam<bool>("transient", false, "Determines whether the problem is transient or steady state.");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale::DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
  _lifting_function(&getFunction("lifting_function")),
  _scale(getParam<Real>("scale")),
  _norm_value(getParam<Real>("norm_value")),
  _transient(getParam<bool>("transient")),
  _density(getParam<Real>("density")),
  _specific_heat(getParam<Real>("specific_heat")),
  _norm_value_density(getParam<Real>("norm_value_density")),
  _norm_value_specific_heat(getParam<Real>("norm_value_specific_heat"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation

Real
DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale::computeQpResidual()
{
  if(!_transient)
    return  -((_scale/_norm_value)*(_grad_test[_i][_qp]*(_lifting_function->gradient(_fe_problem.time(),_q_point[_qp]))));
  else
    return -((_scale/_norm_value) * ((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat)) * (_grad_test[_i][_qp]*(_lifting_function->gradient(_fe_problem.time(),_q_point[_qp]))));
}

Real
DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale::computeQpJacobian()
{
   return 0.0;
}
