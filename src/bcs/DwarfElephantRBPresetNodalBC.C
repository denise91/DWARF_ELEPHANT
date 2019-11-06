#include "DwarfElephantRBPresetNodalBC.h"

#include "libmesh/numeric_vector.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBPresetNodalBC);

template<>
InputParameters validParams<DwarfElephantRBPresetNodalBC>()
{
  InputParameters p = validParams<DwarfElephantRBNodalBC>();
  return p;
}


DwarfElephantRBPresetNodalBC::DwarfElephantRBPresetNodalBC(const InputParameters & parameters) :
  DwarfElephantRBNodalBC(parameters)
{

}

void
DwarfElephantRBPresetNodalBC::computeValue(NumericVector<Number> & current_solution)
{
  const dof_id_type & dof_idx = _var.nodalDofIndex();
  _qp = 0;
  current_solution.set(dof_idx, computeQpValue());
}

Real
DwarfElephantRBPresetNodalBC::computeQpResidual()
{
  return _u[_qp] - computeQpValue();
}

Real
DwarfElephantRBPresetNodalBC::computeQpValue()
{
  return 0;
}
