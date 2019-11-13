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

// First commit of branch
 ///-------------------------------------------------------------------------
 #include "DwarfElephantRBClassesSteadyState.h"
#include "libmesh/timestamp.h"


DwarfElephantRBConstructionSteadyState::DwarfElephantRBConstructionSteadyState (EquationSystems & es,
                                                                                const std::string & name_in,
                                                                                const unsigned int number_in)
    : Parent(es, name_in, number_in)
  { }

void
DwarfElephantRBConstructionSteadyState::init_data()
{
  u_var = this->add_variable(get_equation_systems().get_system(0).variable_name(0) + "(RB)");
  Parent::init_data();
}

Real
DwarfElephantRBConstructionSteadyState::train_reduced_basis(const bool resize_rb_eval_data)
{
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
//
//
//  // If we are continuing from a previous training run,
//  // we might already be at the max number of basis functions.
//  // If so, we can just return.
  if (get_rb_evaluation().get_n_basis_functions() >= get_Nmax())
    {
      libMesh::out << "Maximum number of basis functions reached: Nmax = "
                   << get_Nmax() << std::endl;
      return 0.;
    }
//
//
  // Compute the dual norms of the outputs if we haven't already done so
  compute_output_dual_innerprods();

//  // Compute the Fq Riesz representor dual norms if we haven't already done so
  compute_Fq_representor_innerprods();
//
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
//
//          // Break out of training phase if we have reached Nmax
//          // or if the training_tolerance is satisfied.
          if (greedy_termination_test(training_greedy_error, initial_greedy_error, count))
            break;
        }
//
      libMesh::out << "Performing truth solve at parameter:" << std::endl;
      print_parameters();
      //GreedyOutputFile << get_parameters().get_value("mu_0") << ", " << get_parameters().get_value("mu_1") << ", " << training_greedy_error << std::endl;
//      // Update the list of Greedily selected parameters
      this->update_greedy_param_list();
//
//      // Perform an Offline truth solve for the current parameter
      //if (count == 10)
      //  {
      //     libMesh::out << "Printing truth solution." << std::endl;
      //     print_parameters();
      //     Real truth_X_norm = truth_solve(1);
      //  }
      
      //else
        Real truth_X_norm = truth_solve(-1);
//
//      // Add orthogonal part of the snapshot to the RB space
      libMesh::out << "Enriching the RB space" << std::endl;
      enrich_RB_space();
//
      update_system();
//
//      // Increment counter
      count++;
    }
  this->update_greedy_param_list();
//
  return training_greedy_error;
}

void DwarfElephantRBConstructionSteadyState::compute_Fq_representor_innerprods(bool compute_inner_products)
{

  // Skip calculations if we've already computed the Fq_representors
  if (!Fq_representor_innerprods_computed)
    {
      // Only log if we get to here
      LOG_SCOPE("compute_Fq_representor_innerprods()", "RBConstruction");

      for (unsigned int q_f=0; q_f<get_rb_theta_expansion().get_n_F_terms(); q_f++)
        {
          if (!Fq_representor[q_f])
            {
              Fq_representor[q_f] = NumericVector<Number>::build(this->comm());
              Fq_representor[q_f]->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
            }

          libmesh_assert(Fq_representor[q_f]->size()       == this->n_dofs()       &&
                         Fq_representor[q_f]->local_size() == this->n_local_dofs() );

          rhs->zero();
          rhs->add(1., *get_Fq(q_f));

          if (!is_quiet())
            libMesh::out << "Starting solve q_f=" << q_f
                         << " in RBConstruction::update_residual_terms() at "
                         << Utility::get_timestamp() << std::endl;

          rhs->print_matlab("rhs_debug.m");
          solve_for_matrix_and_rhs(*inner_product_solver, *inner_product_matrix, *rhs);
          
          if (assert_convergence)
            check_convergence(*inner_product_solver);

          if (!is_quiet())
            {
              libMesh::out << "Finished solve q_f=" << q_f
                           << " in RBConstruction::update_residual_terms() at "
                           << Utility::get_timestamp() << std::endl;

              libMesh::out << this->n_linear_iterations()
                           << " iterations, final residual "
                           << this->final_linear_residual() << std::endl;
            }

          *Fq_representor[q_f] = *solution;
        }

      if (compute_inner_products)
        {
          unsigned int q=0;

          for (unsigned int q_f1=0; q_f1<get_rb_theta_expansion().get_n_F_terms(); q_f1++)
            {
              get_non_dirichlet_inner_product_matrix_if_avail()->vector_mult(*inner_product_storage_vector, *Fq_representor[q_f1]);

              for (unsigned int q_f2=q_f1; q_f2<get_rb_theta_expansion().get_n_F_terms(); q_f2++)
                {
                  Fq_representor_innerprods[q] = inner_product_storage_vector->dot(*Fq_representor[q_f2]);

                  q++;
                }
            }
        } // end if (compute_inner_products)

      Fq_representor_innerprods_computed = true;
    }

  get_rb_evaluation().Fq_representor_innerprods = Fq_representor_innerprods;
}

 
DwarfElephantRBEvaluationSteadyState::DwarfElephantRBEvaluationSteadyState(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    RBEvaluation(comm),
    fe_problem(fe_problem)
{
  //set_rb_theta_expansion(_eim_test_rb_theta_expansion);
  //set_rb_theta_expansion(_goem_2D_rb_theta_expansion);
  //set_rb_theta_expansion(RBExpansion);
  set_rb_theta_expansion(_geom_3D_rb_theta_expansion);
}

Real
DwarfElephantRBEvaluationSteadyState::get_stability_lower_bound()
{
  /*
  const RBParameters & mu = get_parameters();

  Real min_mu = mu.get_value("mu_0");

  for (unsigned int  i = 1; i != mu.n_parameters(); i++)
  {
    const std::string mu_name = "mu_" + std::to_string(i);
    Real min_mu_i = std::min(min_mu, mu.get_value(mu_name));

    if (min_mu_i < min_mu)
      min_mu = min_mu_i;
  }

  return min_mu; */
  // rb_scm_eval->set_parameters(get_parameters());
  // return rb_scm_eval->get_SCM_LB();
  return 0.0418;
}

DwarfElephantEIMEvaluationSteadyState::DwarfElephantEIMEvaluationSteadyState(const libMesh::Parallel::Communicator & comm) :
    RBEIMEvaluation(comm)
  {
    attach_parametrized_function(&sg);
  }

  /**
   * Constructor.
   */
  DwarfElephantEIMConstructionSteadyState::DwarfElephantEIMConstructionSteadyState (EquationSystems & es,
                         const std::string & name_in,
                         const unsigned int number_in)
    : Parent(es, name_in, number_in)
  {
  }

  void DwarfElephantEIMConstructionSteadyState::init_data()
  {
    Parent::init_data();
  }
  
  std::unique_ptr<ElemAssembly> DwarfElephantEIMConstructionSteadyState::build_eim_assembly(unsigned int index)
  {
    DwarfElephantEIMConstructionSteadyState::_rb_eim_assembly_objects_new.push_back(libmesh_make_unique<DwarfElephantEIMFAssembly>(*this, index));
    return libmesh_make_unique<DwarfElephantEIMFAssembly>(*this, index);
  }
  /**
   * Initialize the implicit system that is used to perform L2 projections.
   */
  void DwarfElephantEIMConstructionSteadyState::init_implicit_system()
  {
    this->add_variable ("L2_proj_var"); // variable name should be the same as the one defined in the MOOSE input file for compatibility with EIM
  }

  /**
   * Initialize the explicit system that is used to store the basis functions.
   */
  void DwarfElephantEIMConstructionSteadyState::init_explicit_system()
  {
    u_var = get_explicit_system().add_variable ("f_EIM");//, libMesh::FIRST);
  }
