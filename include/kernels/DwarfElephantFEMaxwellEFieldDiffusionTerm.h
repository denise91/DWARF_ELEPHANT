#include "VectorKernel.h"
#include "MaterialProperty.h"

// Forward Declaration
class DwarfElephantFEMaxwellEFieldDiffusionTerm;

template <>
InputParameters validParams<DwarfElephantFEMaxwellEFieldDiffusionTerm>();

class DwarfElephantFEMaxwellEFieldDiffusionTerm : public VectorKernel
{
public:
  DwarfElephantFEMaxwellEFieldDiffusionTerm(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _mag_perm;
};
