#include "VectorKernel.h"
#include "MaterialProperty.h"

// Forward Declaration
class DwarfElephantFEMaxwellHFieldForcingTerm;

template <>
InputParameters validParams<DwarfElephantFEMaxwellHFieldForcingTerm>();

class DwarfElephantFEMaxwellHFieldForcingTerm : public VectorKernel
{
public:
  DwarfElephantFEMaxwellHFieldForcingTerm(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  unsigned int _H_var;
  const VectorVariableValue & _H;

  Real _angular_freq;
  Real _mag_perm;
  Real _pre_factor;

  bool _imaginary_part;
};
