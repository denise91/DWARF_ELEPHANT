/**
 * This Problem class is required to use the RB system instead of the FE
 * system.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBPROBLEM_H
#define DWARFELEPHANTRBPROBLEM_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "FEProblemBase.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantSystem.h"
#include "DwarfElephantRBAssembly.h"
#include "DwarfElephantInitializeRBSystemTransient.h"
#include "DwarfElephantRBClassesTransient.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBProblem;
class NonlinearSystem;
class DwarfElephantInitializeRBSystemTransient;
class DwarfElephantRBEvaluationTransient;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBProblem>();

///This Problem class is required to use the RB system instead of the FE system.
class DwarfElephantRBProblem :
  public FEProblemBase
{
//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantRBProblem(const InputParameters & params);

    virtual ~DwarfElephantRBProblem();

    /* Methods */
    virtual void solve () override;

    virtual void setInputParametersFEProblem(InputParameters & parameters) override;

    NonlinearSystem & getNonlinearSystem() override { return *_nl_sys; }

    virtual DwarfElephantRBAssembly & rbAssembly(unsigned int subdomain_id) { return *_rb_assembly[subdomain_id]; }

    virtual void newRBAssemblyArray(NonlinearSystemBase & nl);

    void setReducedInitialCondition();

    bool getUseReducedInitialCondition(){return _use_reduced_initial_condition;}

    void fileParser(DwarfElephantRBEvaluationTransient & _rb_eval);

    UserObjectName _initial_rb_userobject;
    UserObjectName _offline_online_rb_userobject;

    // virtual MooseVariable & getVariable(THREAD_ID tid, const std::string & var_name) override;

//--------------------------------PROTECTED---------------------------------
  protected:
    /* Attributes */
    std::shared_ptr<NonlinearSystem> _nl_sys;
    // In case you are using a MOOSE version that is older than August 11 please replace the
    // line above with this line:
    //NonlinearSystem * _nl_sys;

    std::vector<DwarfElephantRBAssembly *> _rb_assembly;

    bool _use_reduced_initial_condition;
    bool _user_defined_assembly_size;

    unsigned int _assembly_size;

    std::string _file;
    std::string _offline_data_name;

    // friend class DwarfElephantRBEvaluationTransient;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBPROBLEM_H
