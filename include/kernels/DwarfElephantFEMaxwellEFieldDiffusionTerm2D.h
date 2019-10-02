#include "Kernel.h"
#include "MaterialProperty.h"

// Forward Declaration
class DwarfElephantFEMaxwellEFieldDiffusionTerm2D;

template <>
InputParameters validParams<DwarfElephantFEMaxwellEFieldDiffusionTerm2D>();

class DwarfElephantFEMaxwellEFieldDiffusionTerm2D : public Kernel
{
public:
  DwarfElephantFEMaxwellEFieldDiffusionTerm2D(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _mag_perm;
};
