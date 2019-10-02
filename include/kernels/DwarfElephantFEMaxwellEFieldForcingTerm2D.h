#include "Kernel.h"
#include "MaterialProperty.h"

// Forward Declaration
class DwarfElephantFEMaxwellEFieldForcingTerm2D;

template <>
InputParameters validParams<DwarfElephantFEMaxwellEFieldForcingTerm2D>();

class DwarfElephantFEMaxwellEFieldForcingTerm2D : public Kernel
{
public:
  DwarfElephantFEMaxwellEFieldForcingTerm2D(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  unsigned int _E_var;
  const VariableValue & _E;

  Real _angular_freq;
  Real _elec_cond;
  Real _pre_factor;

  bool _imaginary_part;
};
