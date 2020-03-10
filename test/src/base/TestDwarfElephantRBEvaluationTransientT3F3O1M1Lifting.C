/**
 * In this class simplified subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS INHERITING FROM THE CORRECT RBSTRUCTURES.
 */

//-----------------------DWARFELEPHANTRBCONSTRUCTION-----------------------
#include "TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting.h"
#include "libmesh/xdr_cxx.h"

  TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting::TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    DwarfElephantRBEvaluationTransient(comm, fe_problem),
    fe_problem(fe_problem)
  {
    set_rb_theta_expansion(_rb_theta_expansion);
  }
