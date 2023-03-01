/* This class was taken from the MOOSE Application beagle written by Powei Huang.
   We transferred it to this package to ensure that all classes are running with
   the same MOOSE version. */

#include "DwarfElephantRayleighMaterial.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRayleighMaterial);

template<>
InputParameters validParams<DwarfElephantRayleighMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<FunctionName>("function", "The initial condition function.");
  params.addParam<Real>("min", 0.0, "Lower bound of the randomly generated values");
  params.addParam<Real>("max", 1.0, "Upper bound of the randomly generated values");
  params.addParam<unsigned int>("seed", 0, "Seed value for the random number generator");

  return params;
}

DwarfElephantRayleighMaterial::DwarfElephantRayleighMaterial(const InputParameters & parameters) :
    Material(parameters),
    _Ra(declareProperty<Real>("rayleigh_material")),
    _func(getFunction("function")),
    _min(getParam<Real>("min")),
    _max(getParam<Real>("max")),
    _range(_max - _min)
{}



void
DwarfElephantRayleighMaterial::computeQpProperties()
{
  Real rand_num = MooseRandom::rand();

  // Between 0 and range
  rand_num *= _range;

  // Between min and max
  rand_num += _min;

  _Ra[_qp] = _func.value(_t, _q_point[_qp]) + rand_num;
}
