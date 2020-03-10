/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTRBEVALUATIONTRANSIENTT4F4O1M1_H
#define TESTDWARFELEPHANTRBEVALUATIONTRANSIENTT4F4O1M1_H

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

#include "DwarfElephantRBClassesTransient.h"
#include "TestDwarfElephantRBStructuresT4F4O1M1Transient.h"

///In this class the subclasse of TransientRBEvaluation class is introduced. NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
class TestDwarfElephantRBEvaluationTransientT4F4O1M1 : public DwarfElephantRBEvaluationTransient
{

//---------------------------------PUBLIC-----------------------------------
public:
  TestDwarfElephantRBEvaluationTransientT4F4O1M1(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

  typedef DwarfElephantRBEvaluationTransient Parent;

  FEProblemBase & fe_problem;
  TestDwarfElephantRBT4F4O1M1TransientExpansion _rb_theta_expansion;
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTRBEVALUATIONTRANSIENTT4F4O1M1_H
