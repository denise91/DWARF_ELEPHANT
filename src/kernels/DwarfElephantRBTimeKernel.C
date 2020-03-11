#include "DwarfElephantRBTimeKernel.h"

// MOOSE includes
#include "Assembly.h"
#include "MooseVariable.h"
#include "SystemBase.h"

// libMesh includes
#include "libmesh/quadrature.h"

template <>
InputParameters
validParams<DwarfElephantRBTimeKernel>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  return params;
}

DwarfElephantRBTimeKernel::DwarfElephantRBTimeKernel(const InputParameters & parameters) :
DwarfElephantRBKernel(parameters)//,
// _u_dot(_var.uDot()),
// _du_dot_du(_var.duDotDu())
{}

void
DwarfElephantRBTimeKernel::computeResidual()
{
  DenseVector<Number> & re = _assembly.residualBlock(_var.number());
  // for older MOOSE versions that still have Moose::KT_TIME
  // DenseVector<Number> & re = _assembly.residualBlock(_var.number(), Moose::KT_TIME);
  _local_re.resize(re.size());
  _local_re.zero();

  precalculateResidual();
  for (_i = 0; _i < _test.size(); _i++)
    for (_qp = 0; _qp < _qrule->n_points(); _qp++)
      _local_re(_i) += _JxW[_qp] * _coord[_qp] * computeQpResidual();

  re += _local_re;

  if (_has_save_in)
  {
    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (unsigned int i = 0; i < _save_in.size(); i++)
      _save_in[i]->sys().solution().add_vector(_local_re, _save_in[i]->dofIndices());
  }
}

void
DwarfElephantRBTimeKernel::computeJacobian()
{
  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());
  _local_ke.resize(ke.m(), ke.n());
  _local_ke.zero();

  precalculateJacobian();
  for (_i = 0; _i < _test.size(); _i++)
    for (_j = 0; _j < _phi.size(); _j++)
      for (_qp = 0; _qp < _qrule->n_points(); _qp++)
        _local_ke(_i, _j) += _JxW[_qp] * _coord[_qp] * computeQpJacobian();

  ke += _local_ke;

  if(_simulation_type == "steady")  // Steady State
  {
    mooseError("This Kernel can only be operated in the transient mode");
  }

  else if(_simulation_type == "transient") // Transient
  {
    const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

    if (_ID_Mq >= _initialize_rb_system.getQm())
      mooseError("The number of mass matrices you defined here is not matching the number of mass matrices you specified in the RBClasses Class.");

    if(_initialize_rb_system.getOfflineStage())
    // Add the calculated matrices to the Aq matrices from the RB system.
    if (_fe_problem.getNonlinearSystemBase().getCurrentNonlinearIterationNumber() == 0)
    {
      _initialize_rb_system.getMassMatrixSubdomain()[_ID_Mq] -> add_matrix(_local_ke, _var.dofIndices());
    }
  }

 if (_has_diag_save_in)
  {
    unsigned int rows = ke.m();
    DenseVector<Number> diag(rows);
    for (unsigned int i=0; i<rows; i++)
      diag(i) = _local_ke(i,i);

    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (const auto & var : _diag_save_in)
      var->sys().solution().add_vector(diag, var->dofIndices());
  }
}
