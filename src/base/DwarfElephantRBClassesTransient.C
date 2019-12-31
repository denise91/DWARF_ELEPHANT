/**
 * In this class simplified subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * RBSimpleEvaluation: requires only the definition of the lower coercivity
 * constant. The value is here specified for a Conduction problem.
 *
 * RBSimpleConstruction: In order to construct the RB System with the
 * RBSimpleEvaluation subclass the method build_rb_evaluation needs to be
 * overriden.
 *
 * NOTE: ENSURE THAT THE CLASS IS INHERITING FROM THE CORRECT RBSTRUCTURES.
 */

///-----------------------DWARFELEPHANTRBCONSTRUCTION-----------------------
#include "DwarfElephantRBClassesTransient.h"

DwarfElephantRBConstructionTransient::DwarfElephantRBConstructionTransient (EquationSystems & es,
                      const std::string & name_in,
                      const unsigned int number_in)
  : Parent(es, name_in, number_in),
  parameter_dependent_IC(false)
{}

void
DwarfElephantRBConstructionTransient::clear()
{
  Parent::clear();
/*
  if(parameter_dependent_IC)
  {
    // clear the initial conditions
    IC_q_vector.clear();

    if (store_non_dirichlet_operators)
      {
        non_dirichlet_IC_q_vector.clear();
      }
  }*/

}

void
DwarfElephantRBConstructionTransient::allocate_data_structures()
{
  Parent::allocate_data_structures();
/*
  if(parameter_dependent_IC)
  {
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

      IC_q_vector.resize(dwarf_elephant_trans_theta_expansion.get_n_IC_terms());

      // Initialize the intial conditions
      for (unsigned int q=0; q<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q++)
      {
        // Initialize the memory for the vectors
        IC_q_vector[q] = NumericVector<Number>::build(this->comm());
        IC_q_vector[q]->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      }

      // We also need to initialize a second set of non-Dirichlet operators
      if (store_non_dirichlet_operators)
        {
          non_dirichlet_IC_q_vector.resize(dwarf_elephant_trans_theta_expansion.get_n_IC_terms());
          for (unsigned int q=0; q<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q++)
          {
            // Initialize the memory for the vectors
            non_dirichlet_IC_q_vector[q] = NumericVector<Number>::build(this->comm());
            non_dirichlet_IC_q_vector[q]->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
          }
        }
      }*/

}

void
DwarfElephantRBConstructionTransient::init_data()
  {
    u_var = this->add_variable (get_equation_systems().get_system(0).variable_name(0) + "(RB)", libMesh::FIRST);

    Parent::init_data();

    set_rb_assembly_expansion(Dummy_TransientRBAssemblyExpansion);
  }

  void
  DwarfElephantRBConstructionTransient::print_info()
  {
    RBConstruction::print_info();

    libMesh::out << std::endl << "TransientRBConstruction parameters:" << std::endl;

    if (is_rb_eval_initialized())
      {
        // Print out info that describes the current setup
        //TransientRBThetaExpansion & trans_theta_expansion =
        //  cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());
        //libMesh::out << "Q_m: " << trans_theta_expansion.get_n_M_terms() << std::endl;
      }
    else
      {
        libMesh::out << "RBThetaExpansion member is not set yet" << std::endl;
      }
    libMesh::out << "Number of time-steps: " << get_n_time_steps() << std::endl;
    libMesh::out << "dt: " << get_delta_t() << std::endl;
    libMesh::out << "euler_theta (time discretization parameter): " << get_euler_theta() << std::endl;
    if (get_POD_tol() > 0.)
      libMesh::out << "POD_tol: " << get_POD_tol() << std::endl;
    if (max_truth_solves > 0)
      libMesh::out << "Maximum number of truth solves: " << max_truth_solves << std::endl;
    libMesh::out << "delta_N (number of basis functions to add each POD-Greedy step): " << get_delta_N() << std::endl;
    if (nonzero_initialization)
      {
        libMesh::out << "Using initial conditions provided by MOOSE." << std::endl;
      }
    else
      {
        libMesh::out << "Using zero initial condition" << std::endl;
      }
    libMesh::out << std::endl;
  }

  void
  DwarfElephantRBConstructionTransient::initialize_truth()
  {
    if (nonzero_initialization)
      {
        const RBParameters & mu = get_parameters();
/*
        DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
          cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion()); */

        if (!parameter_dependent_IC){
          DwarfElephantRBEvaluationTransient & trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(get_rb_evaluation());
          *this->solution.get() = *trans_rb_eval.get_fe_problem().es().get_system("rb0").solution.get();
        }
        /*else
        {
          this->solution->zero();

          for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
            this->solution.get()->add(dwarf_elephant_trans_theta_expansion.eval_IC_theta(q_ic, mu), *get_IC_q(q_ic));
        }*/
      }
    else
      {
        // Otherwise zero out the solution as a default
        this->solution->zero();
      }
    this->solution->close();
    this->update();
  }

  void DwarfElephantRBConstructionTransient::truth_assembly()
  {
      LOG_SCOPE("truth_assembly()", "TransientRBConstruction");
      unsigned int M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;

  this->matrix->close();

  this->matrix->zero();
  this->rhs->zero();

  const RBParameters & mu = get_parameters();

  TransientRBThetaExpansion & trans_theta_expansion =
    cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());

  const unsigned int Q_a = trans_theta_expansion.get_n_A_terms();
  const unsigned int Q_f = trans_theta_expansion.get_n_F_terms();

  const Real dt          = get_delta_t();
  const Real euler_theta = get_euler_theta();

  {
    // We should have already assembled the matrices
    // and vectors in the affine expansion, so
    // just use them

    add_scaled_mass_matrix(1./dt, matrix);
    mass_matrix_scaled_matvec(1./dt, *rhs, *current_local_solution);

    std::unique_ptr<NumericVector<Number>> temp_vec = NumericVector<Number>::build(this->comm());
    temp_vec->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

    for (unsigned int q_a=0; q_a<Q_a; q_a++)
      {
        matrix->add(euler_theta*trans_theta_expansion.eval_A_theta(q_a,mu), *get_Aq(q_a));

        get_Aq(q_a)->vector_mult(*temp_vec, *current_local_solution);
        temp_vec->scale( -(1.-euler_theta)*trans_theta_expansion.eval_A_theta(q_a,mu) );
        rhs->add(*temp_vec);
      }

    for (unsigned int q_f=0; q_f<Q_f; q_f++)
      {
        *temp_vec = *get_Fq(q_f);
        if (q_f == 0)
            temp_vec->scale( get_control(get_time_step())*trans_theta_expansion.eval_F_theta(q_f,mu) );
        else
            temp_vec->scale( get_control(get_time_step())*get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu));
        rhs->add(*temp_vec);
      }

  }

  this->matrix->close();
  this->rhs->close();
  }
  
  Real DwarfElephantRBConstructionTransient::get_RB_error_bound()
  {
    get_rb_evaluation().set_parameters( get_parameters() );

    Real error_bound = get_rb_evaluation().rb_solve(get_rb_evaluation().get_n_basis_functions());

    if (get_normalize_rb_bound_in_greedy())
      {
        Real error_bound_normalization = get_rb_evaluation().rb_solve(0);

        if ((error_bound < get_abs_training_tolerance ()) ||
            (error_bound_normalization < get_abs_training_tolerance ()))
          {
            // We don't want to normalize this error bound if the bound or the
            // normalization value are below the absolute tolerance. Hence do nothing
            // in this case.
          }
        else
          error_bound /= error_bound_normalization;
      }

    return error_bound;
  }

  NumericVector<Number> *
  DwarfElephantRBConstructionTransient::get_IC_q(unsigned int q)
  {/*
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

    if (q >= dwarf_elephant_trans_theta_expansion.get_n_IC_terms())
      libmesh_error_msg("Error: We must have q < Q_ic in get_IC_q.");
*/
    return IC_q_vector[q].get();
  }

  NumericVector<Number> *
  DwarfElephantRBConstructionTransient::get_non_dirichlet_IC_q(unsigned int q)
  {
    if (!store_non_dirichlet_operators)
      libmesh_error_msg("Error: Must have store_non_dirichlet_operators==true to access non_dirichlet_IC_q.");
/*
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion()); 

    if (q >= dwarf_elephant_trans_theta_expansion.get_n_IC_terms())
      libmesh_error_msg("Error: We must have q < Q_f in get_Fq."); */

    return non_dirichlet_IC_q_vector[q].get();
  }

  NumericVector<Number> *
  DwarfElephantRBConstructionTransient::get_non_dirichlet_IC_q_if_avail(unsigned int q)
  {
    if (store_non_dirichlet_operators)
      {
        return get_non_dirichlet_IC_q(q);
      }

    return get_IC_q(q);
  }

  void
  DwarfElephantRBConstructionTransient::set_parameter_dependent_IC(bool parameter_dependent_IC_in)
  {
    this->parameter_dependent_IC = parameter_dependent_IC_in;
  }

  void
  DwarfElephantRBConstructionTransient::update_system()
  {
    // If delta_N is set to zero, there is nothing to update
    if (get_delta_N() == 0)
      return;

    RBConstruction::update_system();

    libMesh::out << "Updating RB initial conditions" << std::endl;
    if (!parameter_dependent_IC)
      update_RB_initial_condition_all_N();
    else
      update_RB_parameterized_initial_condition_all_N();
  }

  void
  DwarfElephantRBConstructionTransient::update_RB_initial_condition_all_N()
  {
    LOG_SCOPE("update_RB_initial_condition_all_N()", "TransientRBConstruction");

    TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(get_rb_evaluation());

    // Load the initial condition into the solution vector
    initialize_truth();

    std::unique_ptr<NumericVector<Number>> temp1 = NumericVector<Number>::build(this->comm());
    temp1->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

    std::unique_ptr<NumericVector<Number>> temp2 = NumericVector<Number>::build(this->comm());
    temp2->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);


    unsigned int RB_size = get_rb_evaluation().get_n_basis_functions();

    // First compute the right-hand side vector for the L2 projection
    L2_matrix->vector_mult(*temp1, *solution);

    for (unsigned int i=(RB_size-delta_N); i<RB_size; i++)
      {
        RB_ic_proj_rhs_all_N(i) = temp1->dot(get_rb_evaluation().get_basis_function(i));
      }

    // Now compute the projection for each N
    DenseMatrix<Number> RB_L2_matrix_N;
    DenseVector<Number> RB_rhs_N;
    for (unsigned int N=(RB_size-delta_N); N<RB_size; N++)
      {
        // We have to index here by N+1 since the loop index is zero-based.
        trans_rb_eval.RB_L2_matrix.get_principal_submatrix(N+1, RB_L2_matrix_N);

        RB_ic_proj_rhs_all_N.get_principal_subvector(N+1, RB_rhs_N);

        DenseVector<Number> RB_ic_N(N+1);

        // Now solve the linear system
        RB_L2_matrix_N.lu_solve(RB_rhs_N, RB_ic_N);

        // Load RB_ic_N into RB_initial_condition_all_N
        trans_rb_eval.RB_initial_condition_all_N[N] = RB_ic_N;

        // Compute the L2 error for the RB initial condition
        // This part is dependent on the truth space.

        // load the RB solution into temp1
        temp1->zero();
        for (unsigned int i=0; i<N+1; i++)
          {
            temp1->add(RB_ic_N(i), get_rb_evaluation().get_basis_function(i));
          }

        // subtract truth initial condition from RB_ic_N
        temp1->add(-1., *solution);

        // Compute L2 norm error, i.e. sqrt(M(solution,solution))
        temp2->zero();
        L2_matrix->vector_mult(*temp2, *temp1);

        trans_rb_eval.initial_L2_error_all_N[N] = libmesh_real(std::sqrt(temp2->dot(*temp1)));
      }
  }

  void
  DwarfElephantRBConstructionTransient::update_RB_parameterized_initial_condition_all_N()
  {

    TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(get_rb_evaluation());
/*
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion()); 

    DwarfElephantRBEvaluationTransient & dwarf_elephant_trans_rb_eval =
      cast_ref<DwarfElephantRBEvaluationTransient &>(get_rb_evaluation());

    std::unique_ptr<NumericVector<Number>> temp1 = NumericVector<Number>::build(this->comm());
    temp1->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

    std::unique_ptr<NumericVector<Number>> temp2 = NumericVector<Number>::build(this->comm());
    temp2->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

    std::vector<std::unique_ptr<NumericVector<Number>>> temp3;
    temp3.resize(dwarf_elephant_trans_theta_expansion.get_n_IC_terms());

    for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
    {
      temp3[q_ic]= NumericVector<Number>::build(this->comm());
      temp3[q_ic]->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    }

    unsigned int RB_size = get_rb_evaluation().get_n_basis_functions();

    // First compute the right-hand side vector for the L2 projection
    for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
    {
      L2_matrix->vector_mult(*temp3[q_ic], *get_IC_q(q_ic));
    }

    for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
    {
      for (unsigned int i=(RB_size-delta_N); i<RB_size; i++)
      {
      // RB_ic_proj_rhs_all_N(i) = temp1->dot(get_rb_evaluation().get_basis_function(i));
        dwarf_elephant_trans_rb_eval.RB_IC_q_vector[q_ic](i) = temp3[q_ic]->dot(get_rb_evaluation().get_basis_function(i));
      }
    }

    // Now compute the projection for each N
    DenseMatrix<Number> RB_L2_matrix_N;
    DenseVector<Number> RB_rhs_N;
    DenseVector<Number> RB_IC_q_f;

    const RBParameters & mu = get_parameters();

    for (unsigned int N=(RB_size-delta_N); N<RB_size; N++)
      {
        RB_rhs_N.resize(N+1);
        // We have to index here by N+1 since the loop index is zero-based.
        trans_rb_eval.RB_L2_matrix.get_principal_submatrix(N+1, RB_L2_matrix_N);
        // RB_ic_proj_rhs_all_N.get_principal_subvector(N+1, RB_rhs_N);

        for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
        {
          dwarf_elephant_trans_rb_eval.RB_IC_q_vector[q_ic].get_principal_subvector(N+1, RB_IC_q_f);
          RB_rhs_N.add(dwarf_elephant_trans_theta_expansion.eval_IC_theta(q_ic, mu), RB_IC_q_f);
        }

        DenseVector<Number> RB_ic_N(N+1);

        // Now solve the linear systems
        RB_L2_matrix_N.lu_solve(RB_rhs_N, RB_ic_N);

        // Compute the L2 error for the RB initial condition
        // This part is dependent on the truth space.

        // load the RB solution into temp1
        temp1->zero();

        for (unsigned int i=0; i<N+1; i++)
        {
          temp1->add(RB_ic_N(i), get_rb_evaluation().get_basis_function(i));
        }

        initialize_truth();
        // subtract truth initial condition from RB_ic_N
        temp1->add(-1., *solution);

        // Compute L2 norm error, i.e. sqrt(M(solution,solution))
        temp2->zero();
        L2_matrix->vector_mult(*temp2, *temp1);

        trans_rb_eval.initial_L2_error_all_N[N] = libmesh_real(std::sqrt(temp2->dot(*temp1)));
      } */
  }

  Real
  DwarfElephantRBConstructionTransient::train_reduced_basis(const bool resize_rb_eval_data)
  {
    compute_truth_projection_error = true;

    Real value = train_reduced_basis_steady(resize_rb_eval_data);

    compute_truth_projection_error = false;

    return value;
  }

  Real
  DwarfElephantRBConstructionTransient::train_reduced_basis_steady(const bool resize_rb_eval_data)
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

        // Update the list of Greedily selected parameters
        this->update_greedy_param_list();

        // Perform an Offline truth solve for the current parameter
        truth_solve(-1);

        // Add orthogonal part of the snapshot to the RB space
        libMesh::out << "Enriching the RB space" << std::endl;

        if (parameter_dependent_IC && get_rb_evaluation().get_n_basis_functions() == 0)
          enrich_RB_space_for_initial_conditions();
        else
          enrich_RB_space();

        update_system();

        // Increment counter
        count++;
      }
    this->update_greedy_param_list();

    return training_greedy_error;
  }

  void
  DwarfElephantRBConstructionTransient::enrich_RB_space_for_initial_conditions() {/*
    LOG_SCOPE("enrich_RB_space()", "RBConstruction");

    // DwarfElephantRBEvaluationTransient & trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(get_rb_evaluation());
    auto new_bf = NumericVector<Number>::build(this->comm());
    new_bf->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion()); 

    for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
    {
      new_bf->add(1., *get_IC_q(q_ic));
    }

    for (unsigned int index=0; index<get_rb_evaluation().get_n_basis_functions(); index++)
      {
        get_non_dirichlet_inner_product_matrix_if_avail()->vector_mult(*inner_product_storage_vector, *new_bf);

        Number scalar =
          inner_product_storage_vector->dot(get_rb_evaluation().get_basis_function(index));
        new_bf->add(-scalar, get_rb_evaluation().get_basis_function(index));
      }

    // Normalize new_bf
    get_non_dirichlet_inner_product_matrix_if_avail()->vector_mult(*inner_product_storage_vector, *new_bf);
    Number new_bf_norm = std::sqrt( inner_product_storage_vector->dot(*new_bf) );

    if (new_bf_norm == 0.)
      {
        new_bf->zero(); // avoid potential nan's
      }
    else
      {
        new_bf->scale(1./new_bf_norm);
      }

    // load the new basis function into the basis_functions vector.
    get_rb_evaluation().basis_functions.emplace_back( std::move(new_bf) ); */
  }


///------------------------DWARFELEPHANTRBEVALUATION------------------------
#include "libmesh/xdr_cxx.h"

  DwarfElephantRBEvaluationTransient::DwarfElephantRBEvaluationTransient(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    TransientRBEvaluation(comm),
    fe_problem(fe_problem),
    parameter_dependent_IC(false)
  {
    set_rb_theta_expansion(_rb_theta_expansion);
  }

  Real
  DwarfElephantRBEvaluationTransient::get_stability_lower_bound()
  {
    /*
      const RBParameters & mu = get_parameters();
    bool norm_values = fe_problem.getUserObject<DwarfElephantOfflineOnlineStageTransient>("performRBSystem")._norm_online_values;
    unsigned int norm_id = fe_problem.getUserObject<DwarfElephantOfflineOnlineStageTransient>("performRBSystem")._norm_id;

    Real min_mu;
    Real min_mu_i;

    min_mu = mu.get_value("mu_0");

    if(norm_values)
      min_mu = min_mu/mu.get_value("mu_"+ std::to_string(norm_id));

    for (unsigned int  i = 1; i != mu.n_parameters(); i++)
    {
      const std::string mu_name = "mu_" + std::to_string(i);
      if(norm_values)
        min_mu_i = std::min(min_mu, mu.get_value(mu_name)/mu.get_value(mu_name));
      else
        min_mu_i = std::min(min_mu, mu.get_value(mu_name));

      if (min_mu_i < min_mu)
        min_mu = min_mu_i;
    }*/

    return 0.0418;//min_mu;
  }

  void
  DwarfElephantRBEvaluationTransient::set_parameter_dependent_IC(bool parameter_dependent_IC_in)
  {
    this->parameter_dependent_IC = parameter_dependent_IC_in;
  }

  Real
  DwarfElephantRBEvaluationTransient::rb_solve(unsigned int N)
  {
    LOG_SCOPE("rb_solve()", "TransientRBEvaluation");

    if (N > get_n_basis_functions())
      libmesh_error_msg("ERROR: N cannot be larger than the number of basis functions in rb_solve");

    const RBParameters & mu = get_parameters();
    unsigned int M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;

    TransientRBThetaExpansion & trans_theta_expansion =
      cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());

    const unsigned int Q_m = trans_theta_expansion.get_n_M_terms();
    const unsigned int Q_a = trans_theta_expansion.get_n_A_terms();
    const unsigned int Q_f = trans_theta_expansion.get_n_F_terms();

    const unsigned int n_time_steps = get_n_time_steps();
    const Real dt                   = get_delta_t();
    const Real euler_theta          = get_euler_theta();

    // Resize the RB and error bound vectors
    error_bound_all_k.resize(n_time_steps+1);
    RB_outputs_all_k.resize(trans_theta_expansion.get_n_outputs());
    RB_output_error_bounds_all_k.resize(trans_theta_expansion.get_n_outputs());
    for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
      {
        RB_outputs_all_k[n].resize(n_time_steps+1, 0.);
        RB_output_error_bounds_all_k[n].resize(n_time_steps+1, 0.);
      }

    // First assemble the mass matrix
    DenseMatrix<Number> RB_mass_matrix_N(N,N);
    RB_mass_matrix_N.zero();
    DenseMatrix<Number> RB_M_q_m;
    for (unsigned int q_m=0; q_m<Q_m; q_m++)
      {
        RB_M_q_vector[q_m].get_principal_submatrix(N, RB_M_q_m);
        RB_mass_matrix_N.add(trans_theta_expansion.eval_M_theta(q_m, mu), RB_M_q_m);
      }

    RB_LHS_matrix.resize(N,N);
    RB_LHS_matrix.zero();

    RB_RHS_matrix.resize(N,N);
    RB_RHS_matrix.zero();

    RB_LHS_matrix.add(1./dt, RB_mass_matrix_N);
    RB_RHS_matrix.add(1./dt, RB_mass_matrix_N);

    DenseMatrix<Number> RB_Aq_a;
    for (unsigned int q_a=0; q_a<Q_a; q_a++)
      {
        RB_Aq_vector[q_a].get_principal_submatrix(N, RB_Aq_a);

        RB_LHS_matrix.add(       euler_theta*trans_theta_expansion.eval_A_theta(q_a,mu), RB_Aq_a);
        RB_RHS_matrix.add( -(1.-euler_theta)*trans_theta_expansion.eval_A_theta(q_a,mu), RB_Aq_a);
      }

    // Add forcing terms
    DenseVector<Number> RB_Fq_f;
    RB_RHS_save.resize(N);
    RB_RHS_save.zero();
    for (unsigned int q_f=0; q_f<Q_f; q_f++)
      {
        RB_Fq_vector[q_f].get_principal_subvector(N, RB_Fq_f);
        if (q_f == 0)
            RB_RHS_save.add(trans_theta_expansion.eval_F_theta(q_f,mu), RB_Fq_f);
        else
            RB_RHS_save.add(get_rb_theta_expansion().eval_F_theta(((q_f-1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f-1)/M)]->evaluate(mu), RB_Fq_f);
      }


    // Set system time level to 0
    set_time_step(0);

    // Resize/clear the solution vector
    RB_solution.resize(N);

    // Load the initial condition into RB_solution
    if (N > 0)
      {
        if (parameter_dependent_IC)
        {/*
          DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
            cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

          DenseVector<Number> RB_rhs_N(N);
          DenseMatrix<Number> RB_L2_matrix_N;

          DenseVector<Number> RB_IC_q_f;
          for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
          {
            RB_IC_q_vector[q_ic].get_principal_subvector(N, RB_IC_q_f);
            RB_rhs_N.add(dwarf_elephant_trans_theta_expansion.eval_IC_theta(q_ic,mu),RB_IC_q_f);
          }

          RB_L2_matrix.get_principal_submatrix(N, RB_L2_matrix_N);

          // DenseVector<Number> RB_ic_N(N+1);

          // Now solve the linear systems
          RB_L2_matrix_N.lu_solve(RB_rhs_N, RB_solution);*/
        }
        else
          RB_solution = RB_initial_condition_all_N[N-1];
      }

    // Resize/clear the old solution vector
    old_RB_solution.resize(N);

    // Initialize the RB rhs
    DenseVector<Number> RB_rhs(N);
    RB_rhs.zero();

    // Initialize the vectors storing solution data
    RB_temporal_solution_data.resize(n_time_steps+1);
    for (unsigned int time_level=0; time_level<=n_time_steps; time_level++)
      {
        RB_temporal_solution_data[time_level].resize(N);
      }
    // and load the initial data
    RB_temporal_solution_data[0] = RB_solution;

    // Set outputs at initial time
    {
      DenseVector<Number> RB_output_vector_N;
      for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
        {
          RB_outputs_all_k[n][0] = 0.;
          for (unsigned int q_l=0; q_l<trans_theta_expansion.get_n_output_terms(n); q_l++)
            {
              RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
              RB_outputs_all_k[n][0] += trans_theta_expansion.eval_output_theta(n,q_l,mu)*RB_output_vector_N.dot(RB_solution);
            }
        }
    }
    // Initialize error bounds, if necessary
    Real error_bound_sum = 0.;
    Real alpha_LB = 0.;
    if (evaluate_RB_error_bound)
      {
        if (N > 0)
          {
            error_bound_sum += pow( initial_L2_error_all_N[N-1], 2.);
          }

        // Set error bound at the initial time
        error_bound_all_k[get_time_step()] = std::sqrt(error_bound_sum);

        // Compute the outputs and associated error bounds at the initial time
        DenseVector<Number> RB_output_vector_N;
        for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
          {
            RB_outputs_all_k[n][0] = 0.;
            for (unsigned int q_l=0; q_l<trans_theta_expansion.get_n_output_terms(n); q_l++)
              {
                RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
                RB_outputs_all_k[n][0] += trans_theta_expansion.eval_output_theta(n,q_l,mu)*RB_output_vector_N.dot(RB_solution);
              }

            RB_output_error_bounds_all_k[n][0] = error_bound_all_k[0] * eval_output_dual_norm(n,mu);
          }

        alpha_LB = get_stability_lower_bound();

        // Precompute time-invariant parts of the dual norm of the residual.
        cache_online_residual_terms(N);
      }

    for (unsigned int time_level=1; time_level<=n_time_steps; time_level++)
      {
        set_time_step(time_level);
        old_RB_solution = RB_solution;

        // Compute RB_rhs, as RB_LHS_matrix x old_RB_solution
        RB_RHS_matrix.vector_mult(RB_rhs, old_RB_solution);

        // Add forcing terms
        RB_rhs.add(get_control(time_level), RB_RHS_save);

        if (N > 0)
          {
            RB_LHS_matrix.lu_solve(RB_rhs, RB_solution);
          }

        // Save RB_solution for current time level
        RB_temporal_solution_data[time_level] = RB_solution;

        // Evaluate outputs
        DenseVector<Number> RB_output_vector_N;
        for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
          {
            RB_outputs_all_k[n][time_level] = 0.;
            for (unsigned int q_l=0; q_l<trans_theta_expansion.get_n_output_terms(n); q_l++)
              {
                RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
                RB_outputs_all_k[n][time_level] += trans_theta_expansion.eval_output_theta(n,q_l,mu)*
                  RB_output_vector_N.dot(RB_solution);
              }
          }

        // Calculate RB error bounds
        if (evaluate_RB_error_bound)
          {
            // Evaluate the dual norm of the residual for RB_solution_vector
            // Real epsilon_N = uncached_compute_residual_dual_norm(N);
            Real epsilon_N = compute_residual_dual_norm(N);

            error_bound_sum += residual_scaling_numer(alpha_LB) * pow(epsilon_N, 2.);

            // store error bound at time-level _k
            error_bound_all_k[time_level] = std::sqrt(error_bound_sum/residual_scaling_denom(alpha_LB));

            // Now evaluated output error bounds
            for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
              {
                RB_output_error_bounds_all_k[n][time_level] = error_bound_all_k[time_level] *
                  eval_output_dual_norm(n,mu);
              }
          }
      }

    _rb_solve_data_cached = true ;

    if (evaluate_RB_error_bound) // Calculate the error bounds
      {
        return error_bound_all_k[n_time_steps];
      }
    else // Don't calculate the error bounds
      {
        // Just return -1. if we did not compute the error bound
        return -1.;
      }
  }

void
DwarfElephantRBEvaluationTransient::resize_data_structures(const unsigned int Nmax,
                                                     bool resize_error_bound_data)
{
  Parent::resize_data_structures(Nmax,resize_error_bound_data);

  if(parameter_dependent_IC)
  {/*
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

    RB_IC_q_vector.resize(dwarf_elephant_trans_theta_expansion.get_n_IC_terms());

    for (unsigned int q=0; q<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q++)
    {
      // Initialize the memory for the RB vectors
      RB_IC_q_vector[q].resize(Nmax);
    }*/
  }
}

void
DwarfElephantRBEvaluationTransient::legacy_write_offline_data_to_files(const std::string & directory_name,
                                                                       const bool write_binary_data)
{
  Parent::legacy_write_offline_data_to_files(directory_name, write_binary_data);

  if(parameter_dependent_IC)
  {/*
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

    // The writing mode: ENCODE for binary, WRITE for ASCII
    XdrMODE mode = write_binary_data ? ENCODE : WRITE;

    // The suffix to use for all the files that are written out
    const std::string suffix = write_binary_data ? ".xdr" : ".dat";

    if (this->processor_id() == 0)
    {
      // Next write out the IC_q vectors
      std::ostringstream file_name;
      unsigned int n_bfs = this->get_n_basis_functions();

      for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
        {
          file_name.str("");
          file_name << directory_name << "/RB_IC_";
          file_name << std::setw(3)
                    << std::setprecision(0)
                    << std::setfill('0')
                    << std::right
                    << q_ic;
          file_name << suffix;
          Xdr RB_IC_q_f_out(file_name.str(), mode);

          for (unsigned int i=0; i<n_bfs; i++)
            {
              RB_IC_q_f_out << RB_IC_q_vector[q_ic](i);
            }
          RB_IC_q_f_out.close();
        }
    }*/
  }
}

void
DwarfElephantRBEvaluationTransient::legacy_read_offline_data_from_files(const std::string & directory_name,
                                                                        bool read_error_bound_data,
                                                                        const bool read_binary_data)
{
  Parent::legacy_read_offline_data_from_files(directory_name, read_error_bound_data, read_binary_data);

  if(parameter_dependent_IC)
  {/*
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

    // This was set in RBSystem::read_offline_data_from_files
    unsigned int n_bfs = this->get_n_basis_functions();

    // The reading mode: DECODE for binary, READ for ASCII
    XdrMODE mode = read_binary_data ? DECODE : READ;

    // The suffix to use for all the files that are written out
    const std::string suffix = read_binary_data ? ".xdr" : ".dat";

    // The string stream we'll use to make the file names
    std::ostringstream file_name;

    // Next read in the IC_q vectors
    for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
      {
        file_name.str("");
        file_name << directory_name << "/RB_IC_";
        file_name << std::setw(3)
                  << std::setprecision(0)
                  << std::setfill('0')
                  << std::right
                  << q_ic;
        file_name << suffix;
        assert_file_exists(file_name.str());

        Xdr RB_IC_q_f_in(file_name.str(), mode);

        for (unsigned int i=0; i<n_bfs; i++)
          {
            Number value;
            RB_IC_q_f_in >> value;
            RB_IC_q_vector[q_ic](i) = value;
          }
        RB_IC_q_f_in.close();
      }*/
  }
}
