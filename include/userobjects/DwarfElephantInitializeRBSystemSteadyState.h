/* This UserObject is required to initialitze the RB system structure
 * and transfer for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H
#define DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/petsc_vector.h"

// MOOSE includes
#include "GeneralUserObject.h"
#include "DisplacedProblem.h"
#include "MooseMesh.h"
#include "MooseVariable.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantSystem.h"
#include "DwarfElephantRBClassesSteadyState.h"

///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  class EquationSystems;
  template <typename T> class SparseMatrix;
  template <typename T> class PetscMatrix;
  template <typename T> class PetscVector;
}

class MooseMesh;
class DwarfElephantSystem;
class DwarfElephantRBKernel;
class DwarfElephantRBConstructionSteadyState;
class DwarfElephantRBEvaluationSteadyState;
class DwarfElephantEIMConstructionSteadyState;
class DwarfElephantEIMEvaluationSteadyState;
class DwarfElephantInitializeRBSystemSteadyState;
class DwarfElephantEIMFKernel;
class DwarfElephantEIMFKernelsAction;
class DwarfElephantComputeEIMInnerProductMatrixSteadyState;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantInitializeRBSystemSteadyState>();

///-------------------------------------------------------------------------
class DwarfElephantInitializeRBSystemSteadyState :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantInitializeRBSystemSteadyState(const InputParameters & params);
    DwarfElephantInitializeRBSystemSteadyState & operator=(const DwarfElephantInitializeRBSystemSteadyState &);
    /* Methods */

    // Initializes all required matrices and vectors for the RB solve.
    void initializeOfflineStage();

    void processEIMParameters();
	
	void AssignAffineMatricesAndVectors() const;

    // Initializes the RB System.
    virtual void initialize() override;

    // Method not used in this UserObject.
    virtual void execute() override;

    // Method not used in this UserObject.
    virtual void finalize() override;

   std::vector<std::vector<NumericVector <Number> *> > getOutputs() const;
//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_displaced;
    bool _skip_matrix_assembly_in_rb_system;
    bool _skip_vector_assembly_in_rb_system;
    bool _offline_stage;

    bool _deterministic_training_EIM;
    bool _quiet_mode_EIM;
    bool _normalize_EIM_bound_in_greedy;



    unsigned int _n_training_samples_EIM;
    unsigned int _training_parameters_random_seed_EIM;
    unsigned int _N_max_EIM;

    mutable unsigned int _n_outputs;
    mutable unsigned int _qa;
    mutable unsigned int _qf;
    mutable std::vector<unsigned int> _ql;

    Real _rel_training_tolerance_EIM;
    Real _abs_training_tolerance_EIM;
    std::vector<Real> _continuous_parameter_min_values_EIM;
    std::vector<Real> _continuous_parameter_max_values_EIM;
    std::vector<Real> _discrete_parameter_values_in_EIM;

    std::vector<std::string> _continuous_parameters_EIM;
    std::vector<std::string> _discrete_parameters_EIM;
    std::map< std::string, std::vector<Real> > _discrete_parameter_values_EIM;
    std::string _best_fit_type_EIM;

    EquationSystems & _es;
    MooseMesh * _mesh_ptr;
    //TransientNonlinearImplicitSystem * _sys;
    DwarfElephantRBConstructionSteadyState * _rb_con_ptr;
    DwarfElephantEIMConstructionSteadyState * _eim_con_ptr;
    DwarfElephantRBEvaluationSteadyState *_rb_eval_ptr;
    DwarfElephantEIMEvaluationSteadyState *_eim_eval_ptr;

    SparseMatrix <Number> * _inner_product_matrix_eim;

    mutable SparseMatrix <Number> * _inner_product_matrix;
    mutable std::vector<SparseMatrix <Number> *> _jacobian_subdomain;
    mutable std::vector<NumericVector <Number> *> _residuals;
    mutable std::vector<std::vector<NumericVector <Number> *> > _outputs;

    /*Friend Classes*/
    friend class DwarfElephantRBKernel;
    friend class DwarfElephantRBDiracKernel;
    friend class DwarfElephantRBNodalBC;
    friend class DwarfElephantRBIntegratedBC;
    friend class DwarfElephantOfflineOnlineStageSteadyState;
    friend class DwarfElephantRBEvaluationSteadyState;
    friend class DwarfElephantComputeEIMInnerProductMatrixSteadyState;
    friend class DwarfElephantEIMFKernel;
    friend class DwarfElephantEIMFKernelsAction;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H
