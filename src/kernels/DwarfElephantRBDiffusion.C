/**
 * This Kernel implements the Diffusion problem by using the RB method.
 * It is important to note that every PDE that will be used within the RB
 * method has to inherit from RBKernel and not from Kernel.
 * Furthermore, one should recall that the stiffness matrix and the load
 * vector are constructed out of the parameter independent part of the
 * PDE. Therefore, the functions computeQpResidual() and computeQpJacobian()
 * should only contain this parameter independent part. Consequently, the
 * RBDiffusion Kernel is used for a Conduction problem.
 */

//---------------------------------INCLUDES--------------------------------
//MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBDiffusion.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBDiffusion);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBDiffusion>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a Diffusion problem using \
                             the RBKernel.");
  params.addParam<Real>("density", 1.0, "Defines the bulk density.");
  params.addParam<Real>("specific_heat", 1.0, "Defines the bulk specific heat.");
  params.addParam<Real>("norm_value_density", 1.0, "Defines the normalization value.");
  params.addParam<Real>("norm_value_specific_heat", 1.0, "Defines the normalization value.");
  params.addParam<bool>("transient", false, "Determines whether the problem is transient or steady state.");
  return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBDiffusion::DwarfElephantRBDiffusion(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
  _transient(getParam<bool>("transient")),
  _density(getParam<Real>("density")),
  _specific_heat(getParam<Real>("specific_heat")),
  _norm_value_density(getParam<Real>("norm_value_density")),
  _norm_value_specific_heat(getParam<Real>("norm_value_specific_heat"))
{
}

//----------------------------------PDEs-----------------------------------
Real
DwarfElephantRBDiffusion::computeQpResidual()
{
  if(!_transient)
    return -(_grad_u[_qp] * _grad_test[_i][_qp]);
  else
    return -((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat)) *
         (_grad_u[_qp] * _grad_test[_i][_qp]);
}

Real
DwarfElephantRBDiffusion::computeQpJacobian()
{
  if(!_transient)
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp];
  else
    return ((_norm_value_density*_norm_value_specific_heat)/(_density*_specific_heat)) *
           _grad_phi[_j][_qp] * _grad_test[_i][_qp];
}

Real
DwarfElephantRBDiffusion::computeQpOutput()
{
  return 1;
}
