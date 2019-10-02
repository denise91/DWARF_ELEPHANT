#include "VectorKernel.h"
#include "MaterialProperty.h"

// Forward Declaration
class DwarfElephantFEMaxwellEFieldForcingTerm;

template <>
InputParameters validParams<DwarfElephantFEMaxwellEFieldForcingTerm>();

class DwarfElephantFEMaxwellEFieldForcingTerm : public VectorKernel
{
public:
  DwarfElephantFEMaxwellEFieldForcingTerm(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  unsigned int _E_var;
  const VectorVariableValue & _E;

  Real _angular_freq;
  Real _elec_cond;
  Real _pre_factor;

  bool _imaginary_part;
};
