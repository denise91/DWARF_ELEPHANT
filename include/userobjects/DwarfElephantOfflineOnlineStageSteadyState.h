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
  template <typename T> class NumericVector;
}

class MooseMesh;
class NonlinearSystemBase;
class Assembly;
class DwarfElephantOfflineOnlineStageSteadyState;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantOfflineOnlineStageSteadyState>();

///This UserObject implements the Offline and Online stage of the RB method for the steady state case.
class DwarfElephantOfflineOnlineStageSteadyState :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantOfflineOnlineStageSteadyState(const InputParameters & params);


    /* Methods */
    void setAffineMatrices();
    void offlineStage();
    void setOnlineParameters();
    void transferAffineVectors();
//    std::string getFileName();

    virtual void initialize() override;
    virtual void execute() override;
    virtual void finalize() override;

//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_displaced;
    bool _store_basis_functions;
    bool _store_basis_functions_sorted;
    bool _skip_matrix_assembly_in_rb_system;
    bool _skip_vector_assembly_in_rb_system;
    bool _offline_stage;
    bool _online_stage;
    bool _offline_error_bound;
    bool _output_file;
    bool _output_console;
    bool _output_csv;
    bool _compliant;
    bool _norm_online_values;
    bool _load_basis_function;
    bool _write_output;

    unsigned int _norm_id;
    unsigned int _n_outputs;
    unsigned int _online_N;
    unsigned int _basis_function_number;

    std::string _system_name;
    std::string _offline_data_name;

    EquationSystems & _es;
    TransientNonlinearImplicitSystem & _sys;
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system;
    DwarfElephantRBConstructionSteadyState * _rb_con_ptr;

    MooseMesh * _mesh_ptr;

    const std::set<SubdomainID> & _subdomain_ids;
    std::vector<Number> _RB_outputs;

    Real _mu_bar;
    std::vector<Real> _online_mu_parameters;

    RBParameters _rb_online_mu;

    DwarfElephantRBProblem * _rb_problem;

    Real _norm_factor;

    std::vector<std::vector<Real>> _basis_functions;
    Real _n_bfs;

    // for MOOSE version that operate on the PerfLog comment out the following two lines
    PerfID _online_stage_timer;
    PerfID _data_transfer_timer;

    friend class DwarfElephantDakotaOutput;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTOFFLINEONLINESTAGESTEADYSTATE_H
