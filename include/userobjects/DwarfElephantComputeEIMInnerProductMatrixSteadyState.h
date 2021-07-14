#ifndef DWARFELEPHANTCOMPUTEEIMINNERPRODUCTMATRIXSTEADYSTATE_H
#define DWARFELEPHANTCOMPUTEEIMINNERPRODUCTMATRIXSTEADYSTATE_H

#include "ElementUserObject.h"
#include "MooseVariableInterface.h"

#include "libmesh/sparse_matrix.h"

#include "DwarfElephantInitializeRBSystemSteadyState.h"

namespace libMesh
{
  template<typename T> class SparseMatrix;
}

class DwarfElephantComputeEIMInnerProductMatrixSteadyState;

template <>
InputParameters validParams<DwarfElephantComputeEIMInnerProductMatrixSteadyState> ();

class DwarfElephantComputeEIMInnerProductMatrixSteadyState : public ElementUserObject,
                            public MooseVariableInterface<Real>
{
public:
  DwarfElephantComputeEIMInnerProductMatrixSteadyState(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void execute() override;
  virtual void threadJoin(const UserObject & y) override;
  virtual void finalize() override;

  virtual Real getValue();
  DenseMatrix <Number> _local_ke;

protected:
  virtual Real computeIntegral(unsigned int _i, unsigned int _j);
  


  unsigned int _qp;
  unsigned int _i;
  unsigned int _j;
  unsigned int _num_elems;

  MooseVariable & _var;
  const VariableTestValue & _test;

  const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system;
  const std::string _param_str;
  
  //mutable DwarfElephanthpEIMNode *_hp_eim_node;
  //mutable DwarfElephanthpEIMBinaryTree *_hp_eim_bt;
};

#endif //DWARFELEPHANTCOMPUTEEIMINNERPRODUCTMATRIXSTEADYSTATE_H
