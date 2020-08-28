#ifndef EXAMPLEGENERALUSEROBJECT_H
#define EXAMPLEGENERALUSEROBJECT_H

#include "GeneralUserObject.h"
#include "MooseVariableInterface.h"

#include "libmesh/sparse_matrix.h"

namespace libMesh
{
  template <typename T> class SparseMatrix;
}

class ExampleGeneralUserObject;

template<>
InputParameters validParams <ExampleGeneralUserObject> ();

class ExampleGeneralUserObject : public GeneralUserObject,
                                 public MooseVariableInterface<Real>
{
public:
  ExampleGeneralUserObject(const InputParameters & validParams);

  virtual void initialize() override;
  virtual void execute() override;
  virtual void finalize() override;

  SparseMatrix <Number> * _inner_product_matrix;
  DenseMatrix <Number> _local_ke;
  
protected:
  MooseVariable & _var;
  const MooseArray<Real> & _JxW;
  const MooseArray<Real> & _coord;
  const VariablePhiValue & _phi;
  const VariableTestValue & _test;

  const QBase *const & _qrule;
  unsigned int _qp;
  unsigned int _i;
  unsigned int _j;
  
};

#endif
