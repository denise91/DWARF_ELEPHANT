/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

// libMesh includes
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"

// libMesh includes (RB package)
#include "libmesh/rb_evaluation.h"
#include "libmesh/rb_construction.h"

// MOOSE includes
#include "FEProblemBase.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantOfflineOnlineStageSteadyState.h"

#include "DwarfElephantRBStructuresT1A1F1O1SteadyState.h"
#include "DwarfElephantRBStructuresT2A2F1O1SteadyState.h"
#include "DwarfElephantRBStructuresT2A2F1O3SteadyState.h"
#include "DwarfElephantRBStructuresT2A2F1O5SteadyState.h"
#include "DwarfElephantRBStructuresT2A2F3O1SteadyState.h"
#include "DwarfElephantRBStructuresT2A2F2O10SteadyState.h"
#include "DwarfElephantRBStructuresT2A2F3O10SteadyState.h"
#include "DwarfElephantRBStructuresT3A1F4O10SteadyState.h"
#include "DwarfElephantRBStructuresT3A2F4O10SteadyState.h"
#include "DwarfElephantRBStructuresT3A3F1O1SteadyState.h"
#include "DwarfElephantRBStructuresT3A3F1O81SteadyState.h"
#include "DwarfElephantRBStructuresT3A3F2O1SteadyState.h"
#include "DwarfElephantRBStructuresT3A3F4O1SteadyState.h"
#include "DwarfElephantRBStructuresT3A3F1O3SteadyState.h"
#include "DwarfElephantRBStructuresT4A3F5O2347SteadyState.h"
#include "DwarfElephantRBStructuresT4A4F1O1SteadyState.h"
#include "DwarfElephantRBStructuresT4A4F1O32SteadyState.h"
#include "DwarfElephantRBStructuresT4A4F2O1SteadyState.h"
#include "DwarfElephantRBStructuresT5A3F3O1SteadyState.h"
#include "DwarfElephantRBStructuresT5A5F1O1SteadyState.h"
#include "DwarfElephantRBStructuresT5A5F3O1SteadyState.h"
#include "DwarfElephantRBStructuresT5A6F1O40SteadyState.h"
#include "DwarfElephantRBStructuresT5A6F1O81SteadyState.h"
#include "DwarfElephantRBStructuresT6A3F4O1SteadyState.h"
#include "DwarfElephantRBStructuresT6A6F1O1SteadyState.h"
#include "DwarfElephantRBStructuresT6A6F1O32SteadyState.h"
#include "DwarfElephantRBStructuresT6A6F1O81SteadyState.h"
#include "DwarfElephantRBStructuresT7A1F8O80SteadyState.h"
#include "DwarfElephantRBStructuresT7A1F8O2400SteadyState.h"
#include "DwarfElephantRBStructuresT7A1F8O4747SteadyState.h"
#include "DwarfElephantRBStructuresT7A8F8O2385SteadyState.h"
#include "DwarfElephantRBStructuresT8A2F9O1SteadyState.h"
#include "DwarfElephantRBStructuresT8A2F9O10SteadyState.h"
#include "DwarfElephantRBStructuresT8A2F9O20SteadyState.h"
#include "DwarfElephantRBStructuresT8A2F9O2347SteadyState.h"
#include "DwarfElephantRBStructuresT8A8F9O980SteadyState.h"
#include "DwarfElephantRBStructuresT8A8F9O2385SteadyState.h"
#include "DwarfElephantRBStructuresT9A3F7O1SteadyState.h"
#include "DwarfElephantRBStructuresT9A3F10O1SteadyState.h"
#include "DwarfElephantRBStructuresT9A9F2O80SteadyState.h"
#include "DwarfElephantRBStructuresT9A9F10O80SteadyState.h"
#include "DwarfElephantRBStructuresT9A9F10O900SteadyState.h"
#include "DwarfElephantRBStructuresT9A9F10O980SteadyState.h"
#include "DwarfElephantRBStructuresT12A3F10O1SteadyState.h"
#include "DwarfElephantRBStructuresT12A12F13O1SteadyState.h"
#include "DwarfElephantRBStructuresT12A12F13O20SteadyState.h"
#include "DwarfElephantRBStructuresT12A12F13O80SteadyState.h"
#include "DwarfElephantRBStructuresT12A12F13O84SteadyState.h"
#include "DwarfElephantRBStructuresT12A12F13O984SteadyState.h"
#include "DwarfElephantRBStructuresT12A12F13O2347SteadyState.h"
#include "DwarfElephantRBStructuresT14A8F15O1SteadyState.h"
#include "DwarfElephantRBStructuresT15A8F16O2385SteadyState.h"
#include "DwarfElephantRBStructuresT15A9F8O80SteadyState.h"
#include "DwarfElephantRBStructuresT15A9F16O80SteadyState.h"
#include "DwarfElephantRBStructuresT16A7F16O1205SteadyState.h"
#include "DwarfElephantRBStructuresT16A9F16O1SteadyState.h"
#include "DwarfElephantRBStructuresT16A9F16O80SteadyState.h"
#include "DwarfElephantRBStructuresT16A9F17O1SteadyState.h"
#include "DwarfElephantRBStructuresT18A10F19O1SteadyState.h"
#include "DwarfElephantRBStructuresT19A9F19O2385SteadyState.h"
#include "DwarfElephantRBStructuresT23A7F16O1205SteadyState.h"
#include "DwarfElephantRBStructuresT25A12F13O84SteadyState.h"
#include "DwarfElephantRBStructuresT26A13F14O30SteadyState.h"
#include "DwarfElephantRBStructuresT27A13F14O84SteadyState.h"
#include "DwarfElephantRBStructuresT27A13F14O983SteadyState.h"
#include "DwarfElephantRBStructuresT32A8F25O80SteadyState.h"
#include "DwarfElephantRBStructuresT32A8F25O980SteadyState.h"
#include "DwarfElephantRBStructuresT36A9F28O980SteadyState.h"

///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  template <typename T> class SparseMatrix;
  template <typename T> class PetscMatrix;

  class EquationSystems;
  class RBConstruction;
  class RBEvaluation;
}

class DwarfElephantInitializeRBSystemSteadyState;

///In this class the subclasse of RBConstruction class is introduced.
class DwarfElephantRBConstructionSteadyState : public RBConstruction
{

//---------------------------------PUBLIC-----------------------------------
public:

  // Constructor
  DwarfElephantRBConstructionSteadyState (EquationSystems & es,
                        const std::string & name_in,
                        const unsigned int number_in);

  // Destructor
  virtual ~DwarfElephantRBConstructionSteadyState () { }

  // Type of the system
  typedef DwarfElephantRBConstructionSteadyState _sys_type;

  // Type of the parent
  typedef RBConstruction Parent;

  // Initialize data structure
  virtual void init_data() override;

  Real compute_residual_dual_norm(const unsigned int N);

  unsigned int u_var;

};

///In this class the subclasse of RBEvaluation class is introduced. NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
class DwarfElephantRBEvaluationSteadyState : public RBEvaluation
{

//---------------------------------PUBLIC-----------------------------------
public:
  DwarfElephantRBEvaluationSteadyState(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

  virtual Real get_stability_lower_bound();

  FEProblemBase & get_fe_problem(){return fe_problem;}

  FEProblemBase & fe_problem;
  DwarfElephantRBT3A3F1O1SteadyStateExpansion _rb_theta_expansion;
  // DwarfElephantRBT14F14O84SteadyStateExpansion _rb_theta_expansion;
    // DwarfElephantRBT18F19O1SteadyStateExpansion _rb_theta_expansion;
    // DwarfElephantRBT14F15O1SteadyStateExpansion _rb_theta_expansion;
  // DwarfElephantRBT16F17O1SteadyStateExpansion _rb_theta_expansion;
};
