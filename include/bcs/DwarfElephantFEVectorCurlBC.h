#include "VectorIntegratedBC.h"

class DwarfElephantFEVectorCurlBC;

template <>
InputParameters validParams<DwarfElephantFEVectorCurlBC>();

class DwarfElephantFEVectorCurlBC : public VectorIntegratedBC
{
public:
  DwarfElephantFEVectorCurlBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Function & _curl_value;
};
