/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTRBEVALUATIONTRANSIENTT3F3O1M1LIFTING_H
#define TESTDWARFELEPHANTRBEVALUATIONTRANSIENTT3F3O1M1LIFTING_H

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

#include "DwarfElephantRBClassesTransient.h"
#include "TestDwarfElephantRBStructuresT3F3O1M1LiftingTransient.h"

///In this class the subclasse of TransientRBEvaluation class is introduced. NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
class TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting : public DwarfElephantRBEvaluationTransient
{

//---------------------------------PUBLIC-----------------------------------
public:
  TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

  typedef DwarfElephantRBEvaluationTransient Parent;

  FEProblemBase & fe_problem;
  TestDwarfElephantRBT3F3O1M1LiftingTransientExpansion _rb_theta_expansion;
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTRBEVALUATIONTRANSIENTT3F3O1M1Lifting_H
