/* This class was taken from the MOOSE Application beagle written by Powei Huang.
   We transferred it to this package to ensure that all classes are running with
   the same MOOSE version. */

#include "DwarfElephantFEGravityGradientComponent.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEGravityGradientComponent);

template<>
InputParameters validParams<DwarfElephantFEGravityGradientComponent>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("gravity", "The potential field.");
  params.addParam<unsigned>("gradient_component", 2, "Provide the gradient component. Per default vertical component of 3D model.");

  return params;
}

DwarfElephantFEGravityGradientComponent::DwarfElephantFEGravityGradientComponent(const InputParameters & parameters) :
    AuxKernel(parameters),
    _grad_gravity(coupledGradient("gravity")),
    _component(getParam<unsigned>("gradient_component"))
{}

Real
DwarfElephantFEGravityGradientComponent::computeValue()
{
  return -_grad_gravity[_qp](_component);
}
