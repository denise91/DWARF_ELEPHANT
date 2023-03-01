/* This class was taken from the MOOSE Application beagle written by Powei Huang.
   We transferred it to this package to ensure that all classes are running with
   the same MOOSE version. */

#ifndef DWARFELEPHANTRAYLEIGHMATERIAL_H
#define DWARFELEPHANTRAYLEIGHMATERIAL_H

#include "Material.h"
#include "Function.h"
#include "MooseRandom.h"

//Forward Declarations
class DwarfElephantRayleighMaterial;
class Function;

template<>
InputParameters validParams<DwarfElephantRayleighMaterial>();

class DwarfElephantRayleighMaterial : public Material
{
public:
  DwarfElephantRayleighMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

  MaterialProperty<Real> & _Ra;
  const Function & _func;
  Real _min;
  Real _max;
  Real _range;
};

#endif //DwarfElephantRayleighMaterial_H
