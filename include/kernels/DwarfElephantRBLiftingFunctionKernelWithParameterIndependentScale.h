/**
 * This Kernel is implements the concept of the lifting function to avoid
 * problems caused by non-homogenous DirichletBC.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBLIFTINGFUNCTIONKERNELWITHPARAMETERINDEPENDENTSCALE_H
#define DWARFELEPHANTRBLIFTINGFUNCTIONKERNELWITHPARAMETERINDEPENDENTSCALE_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "DwarfElephantRBKernel.h"
#include "Function.h"

///-------------------------------------------------------------------------
class DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale>();

///This Kernel is implements the concept of the lifting function to avoid problems caused by non-homogenous DirichletBC. Note that the scale is fixed for all parameters.
class DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale : public DwarfElephantRBKernel
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBLiftingFunctionKernelWithParameterIndependentScale(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  /* Attributes */
  const Function * _lifting_function;

  Real _scale;
  Real _norm_value;

  bool _transient;

  Real _density;
  Real _specific_heat;
  Real _norm_value_density;
  Real _norm_value_specific_heat;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBLIFTINGFUNCTIONKERNELWITHPARAMETERINDEPENDENTSCALE_H
