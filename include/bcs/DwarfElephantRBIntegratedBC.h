/**
 * This BC is required to use the RB method as it is provided by the
 * RB libMesh package. The RBIntegratedBC inherits from the IntegratedBC
 * class. It overwrites the function computeJacobian because for the RB
 * method the stiffness matrix is needed separated in its subdomain
 * contributions. In addition it overwrites the function computeResidual.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBINTEGRATEDBC_H
#define DWARFELEPHANTRBINTEGRATEDBC_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "IntegratedBC.h"
#include "BlockRestrictable.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantInitializeRBSystemTransient.h"
#include "MooseVariableScalar.h"

///-------------------------------------------------------------------------
// Forward declarations
class DwarfElephantInitializeRBSystemSteadyState;
class DwarfElephantInitializeRBSystemTransient;
class DwarfElephantRBIntegratedBC;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBIntegratedBC>();

///This BC is required to use the RB method as it is provided by the RB libMesh package. The RBIntegratedBC inherits from the IntegratedBC class. It overwrites the function computeJacobian because for the RB method the stiffness matrix is needed separated in its subdomain contributions. In addition it overwrites the function computeResidual.
class DwarfElephantRBIntegratedBC :
  public IntegratedBC
{
//----------------------------------PUBLIC----------------------------------
public:

  DwarfElephantRBIntegratedBC(const InputParameters & parameters);

  virtual ~DwarfElephantRBIntegratedBC();

  /*Methods*/
  virtual void computeResidual() override;
  virtual void computeJacobian() override;
  virtual void computeOutput();
  virtual void computeJacobianBlock(unsigned int jvar) override;
  void computeJacobianBlockScalar(unsigned int jvar) override;
  virtual void computeNonlocalJacobian() override {}
  virtual void computeNonlocalOffDiagJacobian(unsigned int /* jvar */) override {}
  virtual void initialSetup() override;

//--------------------------------PROTECTED---------------------------------
protected:

  /*Methods*/
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  /*Attributes*/
  bool _use_displaced;
  bool _matrix_seperation_according_to_subdomains;
  bool _compute_output;
  bool _compliant;

  std::string _simulation_type;

  unsigned int _ID_first_block;
  unsigned int _ID_Aq;
  unsigned int _ID_Mq;
  unsigned int _ID_Fq;
  unsigned int _ID_Oq;

  DenseVector<Number> _local_out;
  EquationSystems & _es;

  const DwarfElephantInitializeRBSystemSteadyState * _initialize_rb_system;
  const DwarfElephantInitializeRBSystemTransient * _initialize_rb_system_transient;
};

///-------------------------------------------------------------------------
#endif /* DWARFELEPHANTRBINTEGRATEDBC_H */
