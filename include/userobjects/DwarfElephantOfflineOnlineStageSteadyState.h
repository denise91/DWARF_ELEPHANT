/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTOFFLINEONLINESTAGESTEADYSTATE_H
#define DWARFELEPHANTOFFLINEONLINESTAGESTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"

// MOOSE includes
#include "GeneralUserObject.h"
#include "DisplacedProblem.h"
#include "MooseMesh.h"
#include "MooseVariable.h"
#include "NonlinearSystemBase.h"
#include "NodalBC.h"
#include "Assembly.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBClassesSteadyState.h"
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantRBProblem.h"


///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  class EquationSystems;
  template <typename T> class SparseMatrix;
}

class MooseMesh;
class NonlinearSystemBase;
class Assembly;
class DwarfElephantOfflineOnlineStageSteadyState;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantOfflineOnlineStageSteadyState>();

///-------------------------------------------------------------------------
class DwarfElephantOfflineOnlineStageSteadyState :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantOfflineOnlineStageSteadyState(const InputParameters & params);


    /* Methods */
    void setAffineMatrices();
    void offlineStageEIM();
    void offlineStageRBOnly();
    void onlineStageEIM();
    void onlineStagehpEIM();
    void onlineStageRBOnly();
    void setOnlineParameters();
    void transferAffineVectors();
//    std::string getFileName();

    virtual void initialize() override;
    virtual void execute() override;
    virtual void finalize() override;

    ~DwarfElephantOfflineOnlineStageSteadyState()
    {
        
    }
//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_displaced;
    bool _store_basis_functions;
    bool _skip_matrix_assembly_in_rb_system;
    bool _skip_vector_assembly_in_rb_system;
    bool _compliant;
    bool _online_stage;
    bool _offline_error_bound;
    bool _output_file;
    bool _compute_output;
    bool _output_console;
    bool _output_csv;

    bool _norm_online_values;

    unsigned int _norm_id;
    unsigned int _n_outputs;
    unsigned int _online_N;

    std::string _system_name;

    EquationSystems & _es;
    TransientNonlinearImplicitSystem & _sys;
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system;

    MooseMesh * _mesh_ptr;

    const std::set<SubdomainID> & _subdomain_ids;
    std::vector<Number> _RB_outputs;

    Real _mu_bar;
    std::vector<Real> _online_mu_parameters;

    RBParameters _rb_online_mu;

    DwarfElephantRBProblem * _rb_problem;
    unsigned int _mesh_num;
    std::string _param_str;
    std::string _vec_file_location;


    friend class DwarfElephantDakotaOutput;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTOFFLINEONLINESTAGESTEADYSTATE_H
