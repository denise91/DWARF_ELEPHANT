#ifndef DWARFELEPHANTNODALDIFFERENCE_H
#define DWARFELEPHANTNODALDIFFERENCE_H

//libMesh includes
#include "libmesh/sparse_matrix.h"

#include "NodalVectorPostprocessor.h"

// Forward Declarations
namespace libMesh
{
  template <typename T> class SparseMatrix;
}

class DwarfElephantNodalDifference;

template <>
InputParameters validParams<DwarfElephantNodalDifference>();

class DwarfElephantNodalDifference : public NodalVectorPostprocessor
{
public:
  DwarfElephantNodalDifference(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override;
  virtual void finalize() override;
  virtual void threadJoin (const UserObject &/*uo*/) override {}

protected:
  const Function & _func;
  NumericVector<Number> * _nodal_solution;
  VectorPostprocessorValue & _nodal_difference;
  std::string _system;
};

#endif // DWARFELEPHANTNODALDIFFERENCE_H
