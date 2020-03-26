///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

// libMesh includes
#include "DwarfElephantRBClassesSteadyState.h"
#include "TestDwarfElephantRBStructuresT3A3F2O1InverseSteadyState.h"

///In this class the subclasse of RBEvaluation class is introduced. NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
class TestDwarfElephantRBEvaluationSteadyStateT3A3F2O1Inverse : public DwarfElephantRBEvaluationSteadyState
{

//---------------------------------PUBLIC-----------------------------------
public:
  TestDwarfElephantRBEvaluationSteadyStateT3A3F2O1Inverse(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

    FEProblemBase & fe_problem;
    TestDwarfElephantRBT3A3F2O1InverseSteadyStateExpansion _rb_theta_expansion;
};
