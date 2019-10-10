/**
 * This Kernel is implements the concept of the lifting function to avoid
 * problems caused by non-homogenous DirichletBC.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBLiftingFunctionKernel.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBLiftingFunctionKernel);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBLiftingFunctionKernel>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("The class implements a lifting function.");
  params.addRequiredParam<FunctionName>("lifting_function", "Name of the lifting function two account for the inhomogeneous Dirichlet boundary conditions.");
  params.addParam<Real>("density", 1.0, "Defines the bulk density.");
  params.addParam<Real>("specific_heat", 1.0, "Defines the bulk specific heat.");
  params.addParam<Real>("norm_value_density", 1.0, "Defines the normalization value.");
  params.addParam<Real>("norm_value_specific_heat", 1.0, "Defines the normalization value.");
  params.addParam<bool>("transient", false, "Determines whether the problem is transient or steady state.");

  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBLiftingFunctionKernel::DwarfElephantRBLiftingFunctionKernel(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
  _lifting_function(&getFunction("lifting_function")),
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
DwarfElephantRBLiftingFunctionKernel::computeQpResidual()
{
  if(!_transient)
    return  -(_grad_test[_i][_qp]*(_lifting_function->gradient(_fe_problem.time(),_q_point[_qp])));
  else
    return -(((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat))*_grad_test[_i][_qp]*(_lifting_function->gradient(_fe_problem.time(),_q_point[_qp])));
}

Real
DwarfElephantRBLiftingFunctionKernel::computeQpJacobian()
{
   return 0.0;
}
