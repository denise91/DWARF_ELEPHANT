#include "VectorKernel.h"
#include "MaterialProperty.h"

// Forward Declaration
class DwarfElephantFEMaxwellHFieldDiffusionTerm;

template <>
InputParameters validParams<DwarfElephantFEMaxwellHFieldDiffusionTerm>();

class DwarfElephantFEMaxwellHFieldDiffusionTerm : public VectorKernel
{
public:
  DwarfElephantFEMaxwellHFieldDiffusionTerm(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _elec_cond;
};
