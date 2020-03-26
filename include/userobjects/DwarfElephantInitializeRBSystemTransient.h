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
#include "DwarfElephantRBClassesSteadyState.h"
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
class DwarfElephantRBConstructionSteadyState;
class DwarfElephantInitializeRBSystemTransient;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantInitializeRBSystemTransient>();

///This UserObject is required to initialitze the RB system structure and transfer for the transient case.
class DwarfElephantInitializeRBSystemTransient :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantInitializeRBSystemTransient(const InputParameters & params);

    /* Methods */

    void processParameters();

    // Initializes all required matrices and vectors for the RB solve.
    void initializeOfflineStage();

    // Initializes the RB System.
    // virtual void initialize() override;
    void initialize();

    // Method not used in this UserObject.
    // virtual void execute() override;
    void execute();

    // Method not used in this UserObject.
    // virtual void finalize() override;
    void finalize();

    std::vector<std::vector<NumericVector <Number> *> > getOutputs() const {return _outputs;}

    DwarfElephantRBConstructionTransient * get_rb_con_ptr() const {return _rb_con_ptr;}
    bool get_parameter_dependent_IC() const {return _parameter_dependent_IC;}
    bool get_varying_timesteps() const {return _varying_timesteps;}
    Real getDeltaTime() const {return _delta_time;}

    unsigned int getQa() const {return _qa;}
    unsigned int getQm() const {return _qm;}
    unsigned int getQf() const {return _qf;}
    unsigned int getQIc() const {return _q_ic;}
    std::vector<unsigned int> getQl() const {return _ql;}
    SparseMatrix <Number> * getInnerProductMatrix() const {return _inner_product_matrix;}
    SparseMatrix <Number> * getL2Matrix() const {return _L2_matrix;}
    std::vector<SparseMatrix <Number> *> getJacobianSubdomain() const {return _jacobian_subdomain;}
    std::vector<SparseMatrix <Number> *> getMassMatrixSubdomain() const {return _mass_matrix_subdomain;}
    std::vector<NumericVector <Number> *> getResiduals() const {return _residuals;}
    bool getOfflineStage() const {return _offline_stage;}
    std::vector<NumericVector <Number> *> getInitialConditions() const {return _inital_conditions;}

//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_displaced;
    bool _offline_stage;
    bool _parameter_dependent_IC;
    bool _initialized;

    unsigned int _n_outputs;
    unsigned int _qa;
    unsigned int _qm;
    unsigned int _qf;
    unsigned int _q_ic;
    std::vector<unsigned int> _ql;

    Real _delta_time;
    std::vector<Real> _continuous_parameter_min_values;
    std::vector<Real> _continuous_parameter_max_values;
    std::vector<Real> _discrete_parameter_values_in;

    std::string _system_name;
    std::vector<std::string> _continuous_parameters;
    std::vector<std::string> _discrete_parameters;
    std::map< std::string, std::vector<Real> > _discrete_parameter_values;

    EquationSystems & _es;
    MooseMesh * _mesh_ptr;
    TransientNonlinearImplicitSystem * _sys;
    DwarfElephantRBConstructionTransient * _rb_con_ptr;

    bool _varying_timesteps;
    bool _time_dependent_parameter;
    std::vector<unsigned int> _ID_time_dependent_param;
    Real _start_time;
    Real _end_time;

    SparseMatrix <Number> * _inner_product_matrix;
    SparseMatrix <Number> * _L2_matrix;
    std::vector<SparseMatrix <Number> *> _jacobian_subdomain;
    std::vector<SparseMatrix <Number> *> _mass_matrix_subdomain;
    std::vector<NumericVector <Number> *> _residuals;
    std::vector<NumericVector <Number> *> _inital_conditions;
    std::vector<std::vector<NumericVector <Number> *> > _outputs;


    // friend class DwarfElephantRBTimeKernel;
    // friend class DwarfElephantOfflineOnlineStageTransient;
    // friend class DwarfElephantRBExecutioner;
    // friend class DwarfElephantDakotaOutput;
    // friend class DwarfElephantRBInitialCondition;
    // friend class DwarfElephantRBProblem;
    // friend class DwarfElephantRBFilePointValues;
    // friend class DwarfElephantRBIterationAdaptiveDT;
    // friend class DwarfElephantRBEvaluationTransient;
    // friend class DwarfElephantRBStartEndTimeMuAction;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTINITIALIZERBSYSTEMTRANSIENT_H
