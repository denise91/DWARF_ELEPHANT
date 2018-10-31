/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * DwarfElephantRBEvaluation: requires only the definition of the lower
 * coercivity constant. The value is here specified for a three layer
 * problem.
 *
 * DwarfElephantRBConstruction: In order to construct the RB System with the
 * DwarfElephantRBEvaluation subclass the method build_rb_evaluation needs to be
 * overriden.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBCLASSESSTEADYSTATE_H
#define DWARFELEPHANTRBCLASSESSTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

#include <fstream>
// libMesh includes
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"

// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"
#include "libmesh/rb_evaluation.h"
#include "libmesh/rb_construction.h"
#include "libmesh/rb_eim_construction.h"
#include "libmesh/rb_eim_evaluation.h"
#include "libmesh/rb_eim_assembly.h"
#include "libmesh/auto_ptr.h" // libmesh_make_unique

// MOOSE includes
#include "FEProblemBase.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBStructuresT3F1O1SteadyState.h"
#include "DwarfElephantGeom2DRBThetaExpansion.h"
#include "DwarfElephantEIMStructures.h"
///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  template <typename T> class SparseMatrix;
  template <typename T> class NumericVector;
  template <typename T> class PetscMatrix;

  class EquationSystems;
  class RBConstruction;
  class RBEvaluation;
  class RBEIMConstruction;
  class RBEIMEvaluation;
  class RBEIMAssembly;
  class RBParameters;
}

class DwarfElephantInitializeRBSystemSteadyState;


struct CustomRBTheta : RBTheta
{
	virtual Number evaluate(const RBParameters &_mu)
	{
		return _mu.get_value("mu_0");
	}
};

struct CustomRBThetaExpansion : RBThetaExpansion
{
  CustomRBThetaExpansion()
  {
    // Setting up the RBThetaExpansion object
    
    attach_A_theta(&_rb_theta);
attach_A_theta(&_theta_a_1);
    attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  CustomRBTheta _theta_a_1;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-----------------------DWARFELEPHANTRBCONSTRUCTION-----------------------
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

  virtual Real compute_residual_dual_norm(const unsigned int N);
 
  virtual Real train_reduced_basis(const bool resize_rb_eval_data=true) override;
  
  virtual void compute_Fq_representor_innerprods(bool compute_inner_products=true) override;
  
  unsigned int u_var;
  std::ofstream GreedyOutputFile;
};

///------------------------DWARFELEPHANTRBEVALUATION------------------------
class DwarfElephantRBEvaluationSteadyState : public RBEvaluation
{

//---------------------------------PUBLIC-----------------------------------
public:
  DwarfElephantRBEvaluationSteadyState(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

  virtual ~DwarfElephantRBEvaluationSteadyState() {}
    virtual Real get_stability_lower_bound();

  FEProblemBase & get_fe_problem(){return fe_problem;}

  FEProblemBase & fe_problem;
  //DwarfElephantEIMTestRBThetaExpansion _eim_test_rb_theta_expansion;
  Geom2DRBThetaExpansion _goem_2D_rb_theta_expansion;
  CustomRBThetaExpansion RBExpansion;
};


class DwarfElephantEIMEvaluationSteadyState : public RBEIMEvaluation
{
public:

  DwarfElephantEIMEvaluationSteadyState(const libMesh::Parallel::Communicator & comm);
  
  virtual ~DwarfElephantEIMEvaluationSteadyState() {}

  ShiftedGaussian sg;
};

// A simple subclass of RBEIMConstruction.
class DwarfElephantEIMConstructionSteadyState : public RBEIMConstruction
{
public:

  /**
   * Constructor.
   */
  DwarfElephantEIMConstructionSteadyState (EquationSystems & es,
                         const std::string & name_in,
                         const unsigned int number_in);

  
  virtual ~DwarfElephantEIMConstructionSteadyState() {}
  /**
   * The type of the parent.
   */
  typedef RBEIMConstruction Parent;

  virtual std::unique_ptr<ElemAssembly> build_eim_assembly(unsigned int index);
  
  virtual void init_data();
  
  /**
   * Initialize the implicit system that is used to perform L2 projections.
   */
  virtual void init_implicit_system();

  /**
   * Initialize the explicit system that is used to store the basis functions.
   */
  virtual void init_explicit_system();

  virtual Real train_reduced_basis(const bool resize_rb_eval_data=true)
{
  // precompute all the parametrized functions that we'll use in the greedy
  initialize_parametrized_functions_in_training_set();

  LOG_SCOPE("train_reduced_basis()", "RBConstruction");

  int count = 0;

  // initialize rb_eval's parameters
  get_rb_evaluation().initialize_parameters(*this);

  // possibly resize data structures according to Nmax
  if (resize_rb_eval_data)
    {
      get_rb_evaluation().resize_data_structures(get_Nmax());
    }

  // Clear the Greedy param list
  for (std::size_t i=0; i<get_rb_evaluation().greedy_param_list.size(); i++)
    get_rb_evaluation().greedy_param_list[i].clear();

  get_rb_evaluation().greedy_param_list.clear();

  Real training_greedy_error;


  // If we are continuing from a previous training run,
  // we might already be at the max number of basis functions.
  // If so, we can just return.
  if (get_rb_evaluation().get_n_basis_functions() >= get_Nmax())
    {
      libMesh::out << "Maximum number of basis functions reached: Nmax = "
                   << get_Nmax() << std::endl;
      return 0.;
    }


  // Compute the dual norms of the outputs if we haven't already done so
  compute_output_dual_innerprods();

  // Compute the Fq Riesz representor dual norms if we haven't already done so
  compute_Fq_representor_innerprods();

  libMesh::out << std::endl << "---- Performing Greedy basis enrichment ----" << std::endl;
  Real initial_greedy_error = 0.;
  bool initial_greedy_error_initialized = false;
  while (true)
    {
      libMesh::out << std::endl << "---- Basis dimension: "
                   << get_rb_evaluation().get_n_basis_functions() << " ----" << std::endl;

      if (count > 0 || (count==0 && use_empty_rb_solve_in_greedy))
        {
          libMesh::out << "Performing RB solves on training set" << std::endl;
          training_greedy_error = compute_max_error_bound();
          
          
          libMesh::out << "Maximum error bound is " << training_greedy_error << std::endl << std::endl;

          // record the initial error
          if (!initial_greedy_error_initialized)
            {
              initial_greedy_error = training_greedy_error;
              initial_greedy_error_initialized = true;
            }

          // Break out of training phase if we have reached Nmax
          // or if the training_tolerance is satisfied.
          if (greedy_termination_test(training_greedy_error, initial_greedy_error, count))
            break;
        }

      libMesh::out << "Performing truth solve at parameter:" << std::endl;
      print_parameters();
      GreedyOutputFile << get_parameters().get_value("mu_0") << ", " << get_parameters().get_value("mu_1") << ", " << training_greedy_error << std::endl; 
      
      // Update the list of Greedily selected parameters
      this->update_greedy_param_list();

      // Perform an Offline truth solve for the current parameter
      truth_solve(-1);
      
      // Add orthogonal part of the snapshot to the RB space
      libMesh::out << "Enriching the RB space" << std::endl;
      enrich_RB_space();
      
      update_system();

      // Increment counter
      count++;
    }
  this->update_greedy_param_list();

  return training_greedy_error;

} 
  /**
   * Variable number for u.
   */
  unsigned int u_var;

  std::vector<std::unique_ptr<DwarfElephantEIMFAssembly>> _rb_eim_assembly_objects_new;
  std::ofstream GreedyOutputFile;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBCLASSESSTEADYSTATE_H
