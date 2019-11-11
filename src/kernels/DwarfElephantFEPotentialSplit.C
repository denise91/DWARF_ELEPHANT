/**
 * This Kernel is implements the concept of the lifting function to avoid
 * problems caused by non-homogenous DirichletBC.
 */

 //---------------------------------INCLUDES-------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantFEPotentialSplit.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEPotentialSplit);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEPotentialSplit>()
{
  InputParameters params = validParams<Diffusion>();
  params.addClassDescription("The class implements a potential split.");
  params.addRequiredParam<FunctionName>("stationary_potential", "Stationary part of the potential");
  params.addRequiredParam<Real>("scale", "Defines the value of the scaling parameter.");
  params.addParam<Real>("norm_value", 1.0, "Defines the normalization value.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantFEPotentialSplit::DwarfElephantFEPotentialSplit(const InputParameters & parameters) :
  Diffusion(parameters),
  _stationary_potential(&getFunction("stationary_potential")),
  _scale(getParam<Real>("scale")),
  _norm_value(getParam<Real>("norm_value"))
{
}

//----------------------------------PDEs-----------------------------------
// Definition of the necessary PDE in the weak formulation

Real
DwarfElephantFEPotentialSplit::computeQpResidual()
{
  Real value = (_scale/_norm_value)*(_grad_test[_i][_qp]*(_stationary_potential->gradient(_fe_problem.time(),_q_point[_qp])));
  return value;
}

Real
DwarfElephantFEPotentialSplit::computeQpJacobian()
{
   return 0.0;
}
