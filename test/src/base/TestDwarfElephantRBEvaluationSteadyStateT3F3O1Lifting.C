/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

 //-------------------------------------------------------------------------
 #include "TestDwarfElephantRBEvaluationSteadyStateT3F3O1Lifting.h"

TestDwarfElephantRBEvaluationSteadyStateT3F3O1Lifting::TestDwarfElephantRBEvaluationSteadyStateT3F3O1Lifting(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    DwarfElephantRBEvaluationSteadyState(comm, fe_problem),
    fe_problem(fe_problem)
{
  set_rb_theta_expansion(_rb_theta_expansion);
}
