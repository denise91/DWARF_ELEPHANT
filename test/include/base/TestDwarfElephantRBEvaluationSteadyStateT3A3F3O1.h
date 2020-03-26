///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------

// libMesh includes
#include "DwarfElephantRBClassesSteadyState.h"
#include "TestDwarfElephantRBStructuresT3A3F3O1SteadyState.h"

///In this class the subclasse of RBEvaluation class is introduced. NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
class TestDwarfElephantRBEvaluationSteadyStateT3A3F3O1 : public DwarfElephantRBEvaluationSteadyState
{

//---------------------------------PUBLIC-----------------------------------
public:
  TestDwarfElephantRBEvaluationSteadyStateT3A3F3O1(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

    FEProblemBase & fe_problem;
    TestDwarfElephantRBT3A3F3O1SteadyStateExpansion _rb_theta_expansion;
};
