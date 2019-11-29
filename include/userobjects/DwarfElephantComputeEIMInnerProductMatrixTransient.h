/* 
 * File:   DwarfElephantComputeEIMInnerProductMatrixTransient.h
 * Author: 310246696
 *
 * Created on November 21, 2019, 3:20 PM
 */

#ifndef DWARFELEPHANTCOMPUTEEIMINNERPRODUCTMATRIXTRANSIENT_H
#define	DWARFELEPHANTCOMPUTEEIMINNERPRODUCTMATRIXTRANSIENT_H

#include "ElementUserObject.h"
#include "MooseVariableInterface.h"

#include "libmesh/sparse_matrix.h"

#include "DwarfElephantInitializeRBSystemTransient.h"

namespace libMesh
{
  template<typename T> class SparseMatrix;
}

class DwarfElephantComputeEIMInnerProductMatrixTransient;

template <>
InputParameters validParams<DwarfElephantComputeEIMInnerProductMatrixTransient> ();


class DwarfElephantComputeEIMInnerProductMatrixTransient : public ElementUserObject,
                            public MooseVariableInterface<Real>
{
public:
  DwarfElephantComputeEIMInnerProductMatrixTransient(const InputParameters & parameters);

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
  
  const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system;
  
  //mutable DwarfElephanthpEIMNode *_hp_eim_node;
  //mutable DwarfElephanthpEIMBinaryTree *_hp_eim_bt;
};



#endif	/* DWARFELEPHANTCOMPUTEEIMINNERPRODUCTMATRIXTRANSIENT_H */

