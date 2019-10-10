/**
 * This Kernel is implements the concept of the lifting function to avoid
 * problems caused by non-homogenous DirichletBC.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBLiftingFunctionKernelFunctionParameter.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBLiftingFunctionKernelFunctionParameter);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBLiftingFunctionKernelFunctionParameter>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("The class implements a lifting function.");
  params.addRequiredParam<FunctionName>("lifting_function", "Name of the lifting function two account for the inhomogeneous Dirichlet boundary conditions.");
  params.addRequiredParam<FunctionName>("function", "Name of the function that describes the parameter dependence.");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBLiftingFunctionKernelFunctionParameter::DwarfElephantRBLiftingFunctionKernelFunctionParameter(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
  _lifting_function(&getFunction("lifting_function")),
  _func(getFunction("function"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation

Real
DwarfElephantRBLiftingFunctionKernelFunctionParameter::computeQpResidual()
{
  Real dependency = _func.value(_fe_problem.time(),_q_point[_qp]);
    return  -(_grad_test[_i][_qp]* dependency * (_lifting_function->gradient(_fe_problem.time(),_q_point[_qp])));
}

Real
DwarfElephantRBLiftingFunctionKernelFunctionParameter::computeQpJacobian()
{
   return 0.0;
}
