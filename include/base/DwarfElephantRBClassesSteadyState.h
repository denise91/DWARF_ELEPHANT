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
#include "libmesh/numeric_vector.h"

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
#include "DwarfElephantGeom2DRBThetaExpansion_RFA.h"
#include "DwarfElephantEIMStructures.h"
#include "libmesh/vtk_io.h"
#include "DwarfElephantNonAffineFunction.h"
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
		return 1;//_mu.get_value("mu_0");
	}
};

struct CustomRBThetaExpansion : RBThetaExpansion
{
  CustomRBThetaExpansion()
  {
    // Setting up the RBThetaExpansion object
    
    attach_A_theta(&_rb_theta);
    attach_A_theta(&_rb_theta);
    attach_F_theta(&_rb_theta);

    //attach_output_theta(&_rb_theta);

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
  
NumericVector<Number> * get_nonAffineF() // To test against EIM example from Martin's publication
  {
    return _nonAffineF.get();
  }
//  Real train_reduced_basis(const bool resize_rb_eval_data = true);

  void allocate_RB_error_structures() // To test against EIM example from Martin's publication
  {
    _nonAffineF = NumericVector<Number>::build(this->comm());
    _nonAffineF->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    _nonAffineF->zero();
  }

void compute_error_X_norm_vs_N(NumericVector<Number>* _EIMFEsolution, RBParameters _rb_online_mu, EquationSystems & _es)// Compute X inner product of the difference between full FE solution and EIM_FE solution
  {
    Number truthError_X_norm;
    std::unique_ptr<NumericVector<Number>> _RB_solution;
   _RB_solution = NumericVector<Number>::build(this->comm());
    _RB_solution->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    _RB_solution->zero();

    get_rb_evaluation().set_parameters(_rb_online_mu);
    for (int N = 1; N <= get_rb_evaluation().get_n_basis_functions(); N++)
    {
      get_rb_evaluation().rb_solve(N);
      this-> load_rb_solution();

      *_es.get_system("rb0").solution = *_es.get_system("RBSystem").solution;
      //_fe_problem.getNonlinearSystemBase().update();
      std::stringstream ss;
      std::string temp_string;
      ss << std::setw(2) << std::setfill('0') << N;
      temp_string = "out_" + ss.str();
      VTKIO(get_mesh()).write_equation_systems(temp_string+".pvtu", _es);
      // compute X norm of RB vs EIMFE error.
      for (int i = 0; i < N; i++)
      {
         _RB_solution->add(get_rb_evaluation().RB_solution(i),get_rb_evaluation().get_basis_function(i));     
      }
      *_RB_solution-=*_EIMFEsolution;
      get_non_dirichlet_inner_product_matrix_if_avail()->vector_mult(*inner_product_storage_vector,*(_RB_solution.get()));
    truthError_X_norm = std::sqrt(inner_product_storage_vector->dot(*(_RB_solution.get())));
      libMesh::out << "N = " << N << " Error = " << truthError_X_norm << "\n";
      _RB_solution->zero();
    }
    
    
  }

  void do_RB_vs_FE_Error_analysis(RBParameters mu, EquationSystems & _es)
  {
    // compute full FE solution
      std::unique_ptr<NumericVector<Number>> FullFEsolution;
      FullFEsolution = NumericVector<Number>::build(this->comm());
      FullFEsolution->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

      FullFEsolution -> zero();
      FullFEsolution -> close();


      this -> matrix -> zero();
      this -> rhs -> zero();
      
      this -> matrix -> close();
      this -> rhs -> close();

      
      for (int i = 0; i < get_rb_theta_expansion().get_n_A_terms(); i++)
        matrix -> add(get_rb_theta_expansion().eval_A_theta(i,mu),*get_Aq(i));

      for (int i = 0; i < get_rb_theta_expansion().get_n_F_terms(); i++)
        rhs -> add(get_rb_theta_expansion().eval_F_theta(i,mu),*get_Fq(i));//*_nonAffineF);
      
      this -> matrix -> close();
      this -> rhs -> close();
      if (extra_linear_solver)
    {
      // If extra_linear_solver has been initialized, then we use it for the
      // truth solves.
      solve_for_matrix_and_rhs(*extra_linear_solver, *matrix, *rhs);

      if (assert_convergence)
        check_convergence(*extra_linear_solver);
    }
  else
    {
      solve_for_matrix_and_rhs(*get_linear_solver(), *matrix, *rhs);

      if (assert_convergence)
        check_convergence(*get_linear_solver());
    }
    FullFEsolution -> add(*solution);
    ExodusII_IO(get_mesh()).write_equation_systems ("FullFEtruth.e",
this->get_equation_systems());
    compute_error_X_norm_vs_N(FullFEsolution.get(), mu, _es);
  }

  std::unique_ptr<NumericVector<Number>> _nonAffineF; 

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
  //CustomRBThetaExpansion RBExpansion;
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
      truth_solve(1);
      
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
