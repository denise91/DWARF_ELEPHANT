/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

 //-------------------------------------------------------------------------
 #include "TestDwarfElephantRBEvaluationSteadyStateT5A3F3O1.h"

TestDwarfElephantRBEvaluationSteadyStateT5A3F3O1::TestDwarfElephantRBEvaluationSteadyStateT5A3F3O1(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    DwarfElephantRBEvaluationSteadyState(comm, fe_problem),
    fe_problem(fe_problem)
{
  set_rb_theta_expansion(_rb_theta_expansion);
}
