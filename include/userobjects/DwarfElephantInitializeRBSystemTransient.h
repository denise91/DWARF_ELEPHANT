/* This UserObject is required to initialitze the RB system structure
 * and transfer for the transient case.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTINITIALIZERBSYSTEMTRANSIENT_H
#define DWARFELEPHANTINITIALIZERBSYSTEMTRANSIENT_H

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

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantSystem.h"
#include "DwarfElephantRBClassesTransient.h"

#include <unistd.h>
#include <ios>
///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  class EquationSystems;
//  class RBConstruction;
  template <typename T> class SparseMatrix;
  template <typename T> class PetscMatrix;
  template <typename T> class PetscVector;
}

class MooseMesh;
class DwarfElephantSystem;
class DwarfElephantRBConstructionTransient;
class DwarfElephantRBEvaluationTransient;
//class DwarfElephantRBConstructionSteadyState;
//class DwarfElephantRBEvaluationSteadyState;
class DwarfElephantInitializeRBSystemTransient;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantInitializeRBSystemTransient>();

///-------------------------------------------------------------------------
class DwarfElephantInitializeRBSystemTransient :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantInitializeRBSystemTransient(const InputParameters & params);

    ~DwarfElephantInitializeRBSystemTransient();
    
    /* Methods */

    void processParameters() const;
    void processEIMParameters();
    void initializeEIM();
    // Initializes all required matrices and vectors for the RB solve.
    void initializeOfflineStage();
    void initializeOfflineStageEIM();

    // Initializes the RB System.
    // virtual void initialize() override;
    void initialize();

    // Method not used in this UserObject.
    // virtual void execute() override;
    void execute();

    // Method not used in this UserObject.
    // virtual void finalize() override;
    void finalize();
    
    void AssignAffineMatricesAndVectors() const;

    std::vector<std::vector<NumericVector <Number> *> > getOutputs() const;
    
    void process_mem_usage(double& vm_usage, double& resident_set);

//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_displaced;
    bool _skip_matrix_assembly_in_rb_system;
    bool _skip_vector_assembly_in_rb_system;
    bool _offline_stage;
    bool _deterministic_training;
    bool _quiet_mode;
    bool _normalize_rb_bound_in_greedy;
    bool _nonzero_initialization;
    bool _parameter_dependent_IC;
    bool _use_EIM; 
    bool _deterministic_training_EIM; 
    bool _quiet_mode_EIM; 
    bool _normalize_EIM_bound_in_greedy;  

    int _max_truth_solves;
    unsigned int _n_training_samples;
    unsigned int _training_parameters_random_seed;
    unsigned int _N_max;
    unsigned int _n_time_steps;
    unsigned int _delta_N;
    mutable unsigned int _n_outputs;
    mutable unsigned int _qa;
    mutable unsigned int _qm;
    mutable unsigned int _qf;
    unsigned int _n_training_samples_EIM; //done
    unsigned int _training_parameters_random_seed_EIM;  //done
    unsigned int _N_max_EIM; //done
    mutable std::vector<unsigned int> _ql;

    Real _rel_training_tolerance;
    Real _abs_training_tolerance;
    Real _delta_time;
    Real _euler_theta;
    Real _POD_tol;
    std::vector<Real> _continuous_parameter_min_values;
    std::vector<Real> _continuous_parameter_max_values;
    std::vector<Real> _discrete_parameter_values_in;
    
    Real _rel_training_tolerance_EIM; //done
    Real _abs_training_tolerance_EIM; //done
    std::vector<Real> _continuous_parameter_min_values_EIM; // done
    std::vector<Real> _continuous_parameter_max_values_EIM; //done
    std::vector<Real> _discrete_parameter_values_in_EIM; // done

    std::string _system_name;
//    std::string _parameters_filename;
    std::string _best_fit_type_EIM; //done
    std::string _init_filename;
    
    std::vector<std::string> _continuous_parameters; 
    std::vector<std::string> _discrete_parameters; 
    mutable std::map< std::string, std::vector<Real> > _discrete_parameter_values;
    
    std::vector<std::string> _continuous_parameters_EIM;// done
    std::vector<std::string> _discrete_parameters_EIM;// done
    std::map< std::string, std::vector<Real> > _discrete_parameter_values_EIM; //done
    

    EquationSystems & _es;
    MooseMesh * _mesh_ptr;
    TransientNonlinearImplicitSystem * _sys;
    mutable DwarfElephantRBConstructionTransient * _rb_con_ptr;
    DwarfElephantRBEvaluationTransient * _rb_eval_ptr;
    DwarfElephantEIMConstructionSteadyState * _eim_con_ptr;
    DwarfElephantEIMEvaluationSteadyState * _eim_eval_ptr;

    mutable SparseMatrix <Number> * _inner_product_matrix_eim;
    mutable SparseMatrix <Number> * _inner_product_matrix;
    mutable SparseMatrix <Number> * _L2_matrix;
    mutable std::vector<SparseMatrix <Number> *> _jacobian_subdomain;
    mutable std::vector<SparseMatrix <Number> *> _mass_matrix_subdomain;
    mutable std::vector<NumericVector <Number> *> _residuals;
    mutable std::vector<std::vector<NumericVector <Number> *> > _outputs;
    mutable NumericVector<Number> * _fullFEnonAffineF;
    mutable std::vector<dof_id_type> _temp_averaging_node_ids;
    
    bool _RB_RFA;

    /*Friend Classes*/
    friend class DwarfElephantRBKernel;
    friend class DwarfElephantRBDiracKernel;
    friend class DwarfElephantRBTimeKernel;
    friend class DwarfElephantRBNodalBC;
    friend class DwarfElephantRBIntegratedBC;
    friend class DwarfElephantOfflineOnlineStageTransient;
    friend class DwarfElephantRBExecutioner;
    friend class DwarfElephantDakotaOutput;
    friend class DwarfElephantEIMFKernelTransient;
    friend class DwarfElephantComputeEIMInnerProductMatrixTransient;
    friend class DwarfElephantRBEvaluationSteadyState;
    friend class RBInnerProductMatrixTransient;
    friend class DwarfElephantFTestKernelTransient;
    friend class DwarfElephantRBRFHeatsourceKernel;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTINITIALIZERBSYSTEMTRANSIENT_H
