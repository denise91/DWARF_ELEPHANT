///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTRBEVALUATIONSTEADYSTATET3F3O1_H
#define TESTDWARFELEPHANTRBEVALUATIONSTEADYSTATET3F3O1_H

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

// libMesh includes
#include "DwarfElephantRBClassesSteadyState.h"
#include "TestDwarfElephantRBStructuresT3F3O1SteadyState.h"

///In this class the subclasse of RBEvaluation class is introduced. NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
class TestDwarfElephantRBEvaluationSteadyStateT3F3O1 : public DwarfElephantRBEvaluationSteadyState
{

//---------------------------------PUBLIC-----------------------------------
public:
  TestDwarfElephantRBEvaluationSteadyStateT3F3O1(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

    FEProblemBase & fe_problem;
    TestDwarfElephantRBT3F3O1SteadyStateExpansion _rb_theta_expansion;
};


///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTRBEVALUATIONSTEADYSTATET3F3O1_H
