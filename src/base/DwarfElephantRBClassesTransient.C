/**
 * In this class simplified subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS INHERITING FROM THE CORRECT RBSTRUCTURES.
 */

//-----------------------DWARFELEPHANTRBCONSTRUCTION-----------------------
#include "DwarfElephantRBClassesTransient.h"

DwarfElephantRBConstructionTransient::DwarfElephantRBConstructionTransient (EquationSystems & es,
                      const std::string & name_in,
                      const unsigned int number_in)
  : Parent(es, name_in, number_in),
  parameter_dependent_IC(false),
  varying_timesteps(false),
  growth_rate(1.0),
  delta_t_init(1.0),
  time_dependent_parameter(false),
  time_dependent_boundary(false),
  _IDs_time_dependent_boundary(0)
{}

void
DwarfElephantRBConstructionTransient::clear()
{
  Parent::clear();

  if(parameter_dependent_IC)
  {
    // clear the initial conditions
    IC_q_vector.clear();

    if (store_non_dirichlet_operators)
      {
        non_dirichlet_IC_q_vector.clear();
      }
  }

}

void
DwarfElephantRBConstructionTransient::allocate_data_structures()
{
  Parent::allocate_data_structures();

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
      }

}

void
DwarfElephantRBConstructionTransient::init_data()
  {
    u_var = this->add_variable (get_equation_systems().get_system(0).variable_name(0) + "(RB)", libMesh::FIRST);

    Parent::init_data();
  }

  void
  DwarfElephantRBConstructionTransient::print_info()
  {
    RBConstruction::print_info();

    libMesh::out << std::endl << "TransientRBConstruction parameters:" << std::endl;

    if (is_rb_eval_initialized())
      {
        // Print out info that describes the current setup
        TransientRBThetaExpansion & trans_theta_expansion =
          cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());
        libMesh::out << "Q_m: " << trans_theta_expansion.get_n_M_terms() << std::endl;
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

        // RBParameters mu_time;
        //
        // if(time_dependent_parameter)
        //   mu_time = calculate_time_dependent_mu(mu, time, ID_param);

        DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
          cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

        // DwarfElephantRBProblem * _rb_problem = cast_ptr<DwarfElephantRBProblem *>(&trans_rb_eval.get_fe_problem());

        if (!parameter_dependent_IC){
          DwarfElephantRBEvaluationTransient & trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(get_rb_evaluation());
          *this->solution.get() = *trans_rb_eval.get_fe_problem().es().get_system("rb0").solution.get();
        }
        else
        {
          this->solution->zero();

          for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
          {
            // if(time_dependent_parameter)
            //   this->solution.get()->add(dwarf_elephant_trans_theta_expansion.eval_IC_theta(q_ic, mu_time), *get_IC_q(q_ic));
            // else
              this->solution.get()->add(dwarf_elephant_trans_theta_expansion.eval_IC_theta(q_ic, mu), *get_IC_q(q_ic));
          }
        }
      }
    else
      {
        // Otherwise zero out the solution as a default
        this->solution->zero();
      }
    this->solution->close();
    this->update();
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
  {
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

    if (q >= dwarf_elephant_trans_theta_expansion.get_n_IC_terms())
      libmesh_error_msg("Error: We must have q < Q_ic in get_IC_q.");

    return IC_q_vector[q].get();
  }

  NumericVector<Number> *
  DwarfElephantRBConstructionTransient::get_non_dirichlet_IC_q(unsigned int q)
  {
    if (!store_non_dirichlet_operators)
      libmesh_error_msg("Error: Must have store_non_dirichlet_operators==true to access non_dirichlet_IC_q.");

    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

    if (q >= dwarf_elephant_trans_theta_expansion.get_n_IC_terms())
      libmesh_error_msg("Error: We must have q < Q_f in get_Fq.");

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
    if (parameter_dependent_IC)
      update_RB_parameterized_initial_condition_all_N();
    else
      update_RB_initial_condition_all_N();
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
      }
  }

  Real
  DwarfElephantRBConstructionTransient::train_reduced_basis(const bool resize_rb_eval_data)
  {
    compute_truth_projection_error = true;

    Real value = 0;
    // TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(get_rb_evaluation());
    // DwarfElephantRBEvaluationTransient & _dwarf_elephant_trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(trans_rb_eval);

    // adaptive_timestepping = false;
    if (parameter_dependent_IC || varying_timesteps || time_dependent_parameter)
      value = train_reduced_basis_steady(resize_rb_eval_data);
    else
      value = Parent::train_reduced_basis(resize_rb_eval_data);

    compute_truth_projection_error = false;

    return value;
  }

  Real
  DwarfElephantRBConstructionTransient::train_reduced_basis_steady(const bool resize_rb_eval_data)
  {
  LOG_SCOPE("train_reduced_basis()", "RBConstruction");

  int count = 0;
  if(varying_timesteps)
  {
    delta_t_init = get_delta_t();
    DwarfElephantRBEvaluationTransient & _dwarf_elephant_trans_rb_eval =
      cast_ref<DwarfElephantRBEvaluationTransient &>(get_rb_evaluation());

    _dwarf_elephant_trans_rb_eval.varying_timesteps = varying_timesteps;
    _dwarf_elephant_trans_rb_eval.delta_t_init = delta_t_init;
    _dwarf_elephant_trans_rb_eval.growth_rate = growth_rate;
    _dwarf_elephant_trans_rb_eval.threshold = threshold;
  }

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

  Real training_greedy_error = 0.;


  // If we are continuing from a previous training run,
  // we might already be at the max number of basis functions.
  // If so, we can just return.
  if (get_rb_evaluation().get_n_basis_functions() >= get_Nmax())
    {
      libMesh::out << "Maximum number of basis functions reached: Nmax = "
                   << get_Nmax() << std::endl;
      return 0.;
    }


  if(!skip_residual_in_train_reduced_basis)
    {
      // Compute the dual norms of the outputs if we haven't already done so.
      compute_output_dual_innerprods();

      // Compute the Fq Riesz representor dual norms if we haven't already done so.
      compute_Fq_representor_innerprods();
    }

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
      if(varying_timesteps || time_dependent_parameter || time_dependent_boundary)
        truth_solve_mod(-1);
      else
        truth_solve(-1);

      // Add orthogonal part of the snapshot to the RB space
      libMesh::out << "Enriching the RB space" << std::endl;
      if (parameter_dependent_IC && get_rb_evaluation().get_n_basis_functions() == 0)
        enrich_RB_space_for_initial_conditions();
      else
        enrich_RB_space();

      update_system();

      // Check if we've reached Nmax now. We do this before calling
      // update_residual_terms() since we can skip that step if we've
      // already reached Nmax.
      if (get_rb_evaluation().get_n_basis_functions() >= this->get_Nmax())
      {
        libMesh::out << "Maximum number of basis functions reached: Nmax = "
                     << get_Nmax() << std::endl;
        break;
      }

      if(!skip_residual_in_train_reduced_basis)
        {
          Parent::update_residual_terms(compute_RB_inner_product);
        }

      // Increment counter
      count++;
    }
  this->update_greedy_param_list();

  return training_greedy_error;
}

  void
  DwarfElephantRBConstructionTransient::enrich_RB_space_for_initial_conditions() {
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
    get_rb_evaluation().basis_functions.emplace_back( std::move(new_bf) );
  }

  Real DwarfElephantRBConstructionTransient::truth_solve_mod(int write_interval)
  {
    LOG_SCOPE("truth_solve()", "TransientRBConstruction");

    const RBParameters & mu = get_parameters();

    RBParameters mu_time;
    RBParameters mu_init;

    if(time_dependent_parameter || time_dependent_boundary)
      time = 0;

    if(time_dependent_parameter)
      {
      mu_time = calculate_time_dependent_mu(mu, time, ID_param);
      for(unsigned int i = 0; i< mu.n_parameters(); i++)
      {
        const std::string mu_name = "mu_" + std::to_string(i);
        mu_init.set_value(mu_name, mu.get_value(mu_name));
      }
      set_parameters(mu_time);
    }

    DwarfElephantRBEvaluationTransient & trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(get_rb_evaluation());
    DwarfElephantRBProblem * _rb_problem = cast_ptr<DwarfElephantRBProblem *>(&trans_rb_eval.get_fe_problem());

    const unsigned int n_time_steps = get_n_time_steps();

    //   // NumericVector for computing true L2 error
    //   std::unique_ptr<NumericVector<Number>> temp = NumericVector<Number>::build();
    //   temp->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

    // Apply initial condition again.
    initialize_truth();
    set_time_step(0);

    // Now compute the truth outputs
    if(time_dependent_parameter){
      for (unsigned int n=0; n<get_rb_theta_expansion().get_n_outputs(); n++)
      {
        truth_outputs_all_k[n][0] = 0.;
        for (unsigned int q_l=0; q_l<get_rb_theta_expansion().get_n_output_terms(n); q_l++)
          {
            truth_outputs_all_k[n][0] += get_rb_theta_expansion().eval_output_theta(n,q_l,mu_time)*
              get_output_vector(n,q_l)->dot(*solution);
          }
      }
    }
    else{
      for (unsigned int n=0; n<get_rb_theta_expansion().get_n_outputs(); n++)
      {
        truth_outputs_all_k[n][0] = 0.;
        for (unsigned int q_l=0; q_l<get_rb_theta_expansion().get_n_output_terms(n); q_l++)
          {
            truth_outputs_all_k[n][0] += get_rb_theta_expansion().eval_output_theta(n,q_l,mu)*
              get_output_vector(n,q_l)->dot(*solution);
          }
      }
    }

    // Load initial projection error into temporal_data dense matrix
    if (compute_truth_projection_error)
      set_error_temporal_data();

    Real dt;
    if(varying_timesteps)
      dt = delta_t_init;
    else
      dt = get_delta_t();

    if(time_dependent_parameter)
      set_parameters(mu_init);

    for (unsigned int time_level=1; time_level<n_time_steps; time_level++)
      {
        set_time_step(time_level);

        *old_local_solution = *current_local_solution;

        RBParameters mu_time;

        if(time_dependent_parameter || time_dependent_boundary)
          time += dt;

        if(time_dependent_parameter)
        {
          mu_time = calculate_time_dependent_mu(mu_init, time, ID_param);
          set_parameters(mu_time);
        }

        if(time_dependent_boundary) // important: the moose system needs the correct time
        {
          _rb_problem->time()=time;
          _rb_problem->computeResidualSys(_rb_problem->getNonlinearSystem().sys(), *solution, *_rb_problem->getNonlinearSystem().sys().rhs);

          for(unsigned int i = 0; i<_IDs_time_dependent_boundary.size(); i++)
            _rb_problem->rbAssembly(i).setCachedResidual(*get_Fq(i));
        }

        // We assume that the truth assembly has been attached to the system
        truth_assembly();

        // truth_assembly assembles into matrix and rhs, so use those for the solve
        solve_for_matrix_and_rhs(*get_linear_solver(), *matrix, *rhs);

        // The matrix doesn't change at each timestep, so we
        // can set reuse_preconditioner == true
        if(!varying_timesteps || !time_dependent_parameter)
          linear_solver->reuse_preconditioner(true);

        if (assert_convergence)
          {
            check_convergence(*get_linear_solver());
          }

        // Now compute the truth outputs
        if(time_dependent_parameter){
          for (unsigned int n=0; n<get_rb_theta_expansion().get_n_outputs(); n++)
          {
            truth_outputs_all_k[n][time_level] = 0.;
            for (unsigned int q_l=0; q_l<get_rb_theta_expansion().get_n_output_terms(n); q_l++)
              {
                truth_outputs_all_k[n][time_level] +=
                  get_rb_theta_expansion().eval_output_theta(n,q_l,mu_time)*get_output_vector(n,q_l)->dot(*solution);
              }
          }
        }else{
          for (unsigned int n=0; n<get_rb_theta_expansion().get_n_outputs(); n++)
          {
            truth_outputs_all_k[n][time_level] = 0.;
            for (unsigned int q_l=0; q_l<get_rb_theta_expansion().get_n_output_terms(n); q_l++)
              {
                truth_outputs_all_k[n][time_level] +=
                  get_rb_theta_expansion().eval_output_theta(n,q_l,mu)*get_output_vector(n,q_l)->dot(*solution);
              }
          }
        }

        // load projection error into column _k of temporal_data matrix
        if (compute_truth_projection_error)
          set_error_temporal_data();

        if ((write_interval > 0) && (time_level%write_interval == 0))
          {
            libMesh::out << std::endl << "Truth solve, plotting time step " << time_level << std::endl;

            std::ostringstream file_name;

            file_name << "truth.e.";
            file_name << std::setw(3)
                      << std::setprecision(0)
                      << std::setfill('0')
                      << std::right
                      << time_level;

  #ifdef LIBMESH_HAVE_EXODUS_API
            ExodusII_IO(get_mesh()).write_equation_systems (file_name.str(),
                                                            this->get_equation_systems());
  #endif
          }

          // std::ostringstream file_name;
          // file_name << "truth"
          // << get_rb_evaluation().get_n_basis_functions()
          // << "."
          // << std::setprecision(0)
          // << std::setfill('0')
          // << std::right
          // << time_level
          // <<".e";
          //
          // ExodusII_IO(get_mesh()).write_equation_systems (file_name.str(),
          //                                                 this->get_equation_systems());

          if(varying_timesteps)
          {
            if(dt < threshold){
              dt*=growth_rate;
              set_delta_t(dt);
            }
          }

          if(time_dependent_parameter)
            set_parameters(mu_init);
      }

    // Set reuse_preconditioner back to false for subsequent solves.
    if(!varying_timesteps || !time_dependent_parameter)
      linear_solver->reuse_preconditioner(true);

    // Get the L2 norm of the truth solution at time-level _K
    // Useful for normalizing our true error data
    L2_matrix->vector_mult(*inner_product_storage_vector, *solution);
    Real final_truth_L2_norm = libmesh_real(std::sqrt(inner_product_storage_vector->dot(*solution)));

    return final_truth_L2_norm;
  }

  RBParameters
  DwarfElephantRBConstructionTransient::calculate_time_dependent_mu(const RBParameters mu, Real time, std::vector<unsigned int> ID_param)
  {
    RBParameters & mu_time = const_cast<RBParameters&>(mu);
    Real dt = get_delta_t();

    Real pre_factor = 1.0;

    if (time < start_time || time - dt >= end_time)
      pre_factor = 0.0;
    else if (time - dt < start_time)
    {
      if (time <= end_time)
        pre_factor *= (time - start_time) / dt;
      else
        pre_factor *= (end_time - start_time) / dt;
    }
    else if (time > end_time)
      pre_factor *= (end_time - (time - dt)) / dt;

    for(unsigned int i = 0; i < ID_param.size(); i++)
    {
      const std::string mu_name = "mu_" + std::to_string(ID_param[i]);
      Real _time_dependency = pre_factor * mu_time.get_value(mu_name);
      mu_time.set_value(mu_name, _time_dependency);
    }

    return mu_time;
  }

  Real DwarfElephantRBConstructionTransient::uncached_compute_residual_dual_norm(const unsigned int N)
  {
    LOG_SCOPE("uncached_compute_residual_dual_norm()", "TransientRBConstruction");

    // This is the "slow" way of computing the residual, but it is useful
    // for validating the "fast" way.
    // Note that this only works in serial since otherwise each processor will
    // have a different parameter value during the Greedy training.

    // Assemble the right-hand side to find the Reisz representor
    // of the residual in the X norm
    std::unique_ptr<NumericVector<Number>> RB_sol = NumericVector<Number>::build(this->comm());
    RB_sol->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    RB_sol->zero();

    std::unique_ptr<NumericVector<Number>> ghosted_temp = NumericVector<Number>::build(this->comm());
    ghosted_temp->init (this->n_dofs(), this->n_local_dofs(),
                        this->get_dof_map().get_send_list(), false,
                        GHOSTED);

    std::unique_ptr<NumericVector<Number>> parallel_temp = NumericVector<Number>::build(this->comm());
    parallel_temp->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

    // Store current_local_solution, since we don't want to corrupt it
    *ghosted_temp = *current_local_solution;

    DwarfElephantRBEvaluationTransient & trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(get_rb_evaluation());

    for (unsigned int i=0; i<N; i++)
    {
      RB_sol->add(trans_rb_eval.RB_solution(i), get_rb_evaluation().get_basis_function(i));
      parallel_temp->add( trans_rb_eval.old_RB_solution(i), get_rb_evaluation().get_basis_function(i));
    }

    // Load parallel_temp into current_local_solution in order to do assembly
    const std::vector<unsigned int> & send_list = this->get_dof_map().get_send_list();
    parallel_temp->localize (*current_local_solution, send_list);

    // Load the system_matrix
    this->truth_assembly();

    // Restore current_local_solution
    *current_local_solution = *ghosted_temp;

    matrix->vector_mult(*parallel_temp, *RB_sol);
    rhs->add(-1., *parallel_temp);
    rhs->close();

    // zero_dirichlet_dofs_on_rhs();

    // Then solve the system to get the Reisz representor
    matrix->zero();
    {
      matrix->add(1., *inner_product_matrix);
      // if (constrained_problem)
        // matrix->add(1., *constraint_matrix);
    }


    solution->zero();
    solve();
    // Make sure we didn't max out the number of iterations
    if ((this->n_linear_iterations() >=
         this->get_equation_systems().parameters.get<unsigned int>("linear solver maximum iterations")) &&
        (this->final_linear_residual() >
         this->get_equation_systems().parameters.get<Real>("linear solver tolerance")))
    {
      libmesh_error_msg("Warning: Linear solver may not have converged! Final linear residual = "
                   << this->final_linear_residual() << ", number of iterations = "
                   << this->n_linear_iterations());
    }

   get_non_dirichlet_inner_product_matrix_if_avail()->vector_mult(*inner_product_storage_vector, *solution);

   Real slow_residual_norm_sq = solution->dot(*inner_product_storage_vector);

   return libmesh_real(std::sqrt( slow_residual_norm_sq ));
  }


//------------------------DWARFELEPHANTRBEVALUATION------------------------
#include "libmesh/xdr_cxx.h"

  DwarfElephantRBEvaluationTransient::DwarfElephantRBEvaluationTransient(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    TransientRBEvaluation(comm),
    fe_problem(fe_problem),
    varying_timesteps(false),
    parameter_dependent_IC(false)
  {
    set_rb_theta_expansion(_rb_theta_expansion);
  }

  Real
  DwarfElephantRBEvaluationTransient::get_stability_lower_bound()
  {
    // const RBParameters & mu = get_parameters();

    // bool norm_values = fe_problem.getUserObject<DwarfElephantOfflineOnlineStageTransient>("performRBSystem")._norm_online_values;
    // unsigned int norm_id = fe_problem.getUserObject<DwarfElephantOfflineOnlineStageTransient>("performRBSystem")._norm_id;
    //
    // Real min_mu;
    // Real min_mu_i;
    //
    // min_mu = mu.get_value("mu_0");
    //
    // if(norm_values)
    //   min_mu = min_mu/mu.get_value("mu_"+ std::to_string(norm_id));
    //
    // for (unsigned int  i = 1; i != mu.n_parameters(); i++)
    // {
    //   const std::string mu_name = "mu_" + std::to_string(i);
    //   if(norm_values)
    //     min_mu_i = std::min(min_mu, mu.get_value(mu_name)/mu.get_value(mu_name));
    //   else
    //     min_mu_i = std::min(min_mu, mu.get_value(mu_name));
    //
    //   if (min_mu_i < min_mu)
    //     min_mu = min_mu_i;
    // }

    // return min_mu;

    const RBParameters & mu = get_parameters();
    TransientRBThetaExpansion & trans_theta_expansion =
      cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());

    // Real min_mu;
    Real min_mu_a;
    // Real min_mu_m;
    Real min_mu_a_i;
    // Real min_mu_m_i;

    // const unsigned int Q_m = trans_theta_expansion.get_n_M_terms();
    const unsigned int Q_a = trans_theta_expansion.get_n_A_terms();

    min_mu_a = trans_theta_expansion.eval_A_theta(0,mu);
    for (unsigned int q_a=1; q_a<Q_a; q_a++){
      min_mu_a_i = trans_theta_expansion.eval_A_theta(q_a,mu);

      if(min_mu_a_i < min_mu_a)
        min_mu_a = min_mu_a_i;
    }
    //
    // min_mu_m = trans_theta_expansion.eval_M_theta(0,mu);
    // for (unsigned int q_m=1; q_m<Q_m; q_m++){
    //   min_mu_m_i = trans_theta_expansion.eval_M_theta(q_m,mu);
    //
    //   if(min_mu_m_i < min_mu_m)
    //     min_mu_m = min_mu_m_i;
    // }

    // min_mu = std::min(min_mu_a, min_mu_m);
    return min_mu_a;
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

    // Allow time dependent parameters
    DwarfElephantRBProblem & problem = cast_ref<DwarfElephantRBProblem &>(fe_problem);

    DwarfElephantInitializeRBSystemTransient & initialize_rb_system =
      problem.getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(problem._initial_rb_userobject);


    // Calculate the time dependency of the parameters
    RBParameters mu_time;
    RBParameters mu_init;

    if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
    {
      time = 0;
      mu_time = calculate_time_dependent_mu(mu, time, ID_param);
      for(unsigned int i = 0; i< mu.n_parameters(); i++)
      {
        const std::string mu_name = "mu_" + std::to_string(i);
        mu_init.set_value(mu_name, mu.get_value(mu_name));
      }
      set_parameters(mu_time);
    }

    TransientRBThetaExpansion & trans_theta_expansion =
      cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());

    const unsigned int Q_m = trans_theta_expansion.get_n_M_terms();
    const unsigned int Q_a = trans_theta_expansion.get_n_A_terms();
    const unsigned int Q_f = trans_theta_expansion.get_n_F_terms();

    // Enable varying time steps
    const unsigned int n_time_steps = get_n_time_steps();
    Real dt;
    if(varying_timesteps)
      dt = delta_t_init;
    else
      dt = get_delta_t();
    const Real euler_theta          = get_euler_theta();

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
    if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
    {
      for (unsigned int q_m=0; q_m<Q_m; q_m++)
      {
        RB_M_q_vector[q_m].get_principal_submatrix(N, RB_M_q_m);
        RB_mass_matrix_N.add(trans_theta_expansion.eval_M_theta(q_m, mu_time), RB_M_q_m);
      }
    }else{
      for (unsigned int q_m=0; q_m<Q_m; q_m++)
      {
        RB_M_q_vector[q_m].get_principal_submatrix(N, RB_M_q_m);
        RB_mass_matrix_N.add(trans_theta_expansion.eval_M_theta(q_m, mu), RB_M_q_m);
      }
    }

    RB_LHS_matrix.resize(N,N);
    RB_LHS_matrix.zero();

    RB_RHS_matrix.resize(N,N);
    RB_RHS_matrix.zero();

    RB_LHS_matrix.add(1./dt, RB_mass_matrix_N);
    RB_RHS_matrix.add(1./dt, RB_mass_matrix_N);

    DenseMatrix<Number> RB_Aq_a;
    if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
    {
      for (unsigned int q_a=0; q_a<Q_a; q_a++)
      {
        RB_Aq_vector[q_a].get_principal_submatrix(N, RB_Aq_a);

        RB_LHS_matrix.add(       euler_theta*trans_theta_expansion.eval_A_theta(q_a,mu_time), RB_Aq_a);
        RB_RHS_matrix.add( -(1.-euler_theta)*trans_theta_expansion.eval_A_theta(q_a,mu_time), RB_Aq_a);
      }
    }else{
      for (unsigned int q_a=0; q_a<Q_a; q_a++)
      {
        RB_Aq_vector[q_a].get_principal_submatrix(N, RB_Aq_a);

        RB_LHS_matrix.add(       euler_theta*trans_theta_expansion.eval_A_theta(q_a,mu), RB_Aq_a);
        RB_RHS_matrix.add( -(1.-euler_theta)*trans_theta_expansion.eval_A_theta(q_a,mu), RB_Aq_a);
      }
    }

    // Add forcing terms
    DenseVector<Number> RB_Fq_f;
    RB_RHS_save.resize(N);
    RB_RHS_save.zero();
    if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
    {
      for (unsigned int q_f=0; q_f<Q_f; q_f++)
      {
        RB_Fq_vector[q_f].get_principal_subvector(N, RB_Fq_f);
        RB_RHS_save.add(trans_theta_expansion.eval_F_theta(q_f,mu_time), RB_Fq_f);
      }
    }else{
      for (unsigned int q_f=0; q_f<Q_f; q_f++)
      {
        RB_Fq_vector[q_f].get_principal_subvector(N, RB_Fq_f);
        RB_RHS_save.add(trans_theta_expansion.eval_F_theta(q_f,mu), RB_Fq_f);
      }
    }

    // Set system time level to 0
    set_time_step(0);
    set_delta_t(dt);

    // Resize/clear the solution vector
    RB_solution.resize(N);

    // Load the initial condition into RB_solution
    if (N > 0)
      {
        if (parameter_dependent_IC)
        {
          DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
            cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

          DenseVector<Number> RB_rhs_N(N);
          DenseMatrix<Number> RB_L2_matrix_N;

          DenseVector<Number> RB_IC_q_f;
          if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
          {
            for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
            {
              RB_IC_q_vector[q_ic].get_principal_subvector(N, RB_IC_q_f);
              RB_rhs_N.add(dwarf_elephant_trans_theta_expansion.eval_IC_theta(q_ic,mu_time),RB_IC_q_f);
            }
          }else{
            for (unsigned int q_ic=0; q_ic<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q_ic++)
            {
              RB_IC_q_vector[q_ic].get_principal_subvector(N, RB_IC_q_f);
              RB_rhs_N.add(dwarf_elephant_trans_theta_expansion.eval_IC_theta(q_ic,mu),RB_IC_q_f);
            }
          }

          RB_L2_matrix.get_principal_submatrix(N, RB_L2_matrix_N);

          // DenseVector<Number> RB_ic_N(N+1);

          // Now solve the linear systems
          RB_L2_matrix_N.lu_solve(RB_rhs_N, RB_solution);
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
      if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
      {
        for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
        {
            RB_outputs_all_k[n][0] = 0.;
          for (unsigned int q_l=0; q_l<trans_theta_expansion.get_n_output_terms(n); q_l++)
            {
              RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
              RB_outputs_all_k[n][0] += trans_theta_expansion.eval_output_theta(n,q_l,mu_time)*RB_output_vector_N.dot(RB_solution);
            }
        }
      }else{
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
        DenseVector<Number> RB_output_vector_N;
        if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
        {
          for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
          {
              RB_outputs_all_k[n][0] = 0.;
            for (unsigned int q_l=0; q_l<trans_theta_expansion.get_n_output_terms(n); q_l++)
              {
                RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
                RB_outputs_all_k[n][0] += trans_theta_expansion.eval_output_theta(n,q_l,mu_time)*RB_output_vector_N.dot(RB_solution);
              }
              RB_output_error_bounds_all_k[n][0] = error_bound_all_k[0] * eval_output_dual_norm(n,mu_time);
          }
        }else{
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
        }

        if(!initialize_rb_system._rb_con_ptr->time_dependent_parameter)
        {
          alpha_LB = get_stability_lower_bound();

          // Precompute time-invariant parts of the dual norm of the residual.
          cache_online_residual_terms(N);
        }
      }

    if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
      set_parameters(mu_init);

    for (unsigned int time_level=1; time_level<=n_time_steps; time_level++)
      {
        if(varying_timesteps && !initialize_rb_system._rb_con_ptr->time_dependent_parameter)
        {
          RB_LHS_matrix.zero();
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
        }else if((!varying_timesteps && initialize_rb_system._rb_con_ptr->time_dependent_parameter)||(varying_timesteps && initialize_rb_system._rb_con_ptr->time_dependent_parameter))
        {
          // Set time dependency for the parameter
          time += dt;
          ID_param = initialize_rb_system._rb_con_ptr->ID_param;

          RBParameters mu_time = calculate_time_dependent_mu(mu_init, time, ID_param);
          set_parameters(mu_time);

          // Update the mass matrix
          RB_mass_matrix_N.zero();
          DenseMatrix<Number> RB_M_q_m;
          for (unsigned int q_m=0; q_m<Q_m; q_m++)
          {
            RB_M_q_vector[q_m].get_principal_submatrix(N, RB_M_q_m);
            RB_mass_matrix_N.add(trans_theta_expansion.eval_M_theta(q_m, mu_time), RB_M_q_m);
          }

          RB_LHS_matrix.zero();
          RB_RHS_matrix.zero();

          RB_LHS_matrix.add(1./dt, RB_mass_matrix_N);
          RB_RHS_matrix.add(1./dt, RB_mass_matrix_N);

          DenseMatrix<Number> RB_Aq_a;
          for (unsigned int q_a=0; q_a<Q_a; q_a++)
          {
            RB_Aq_vector[q_a].get_principal_submatrix(N, RB_Aq_a);
            RB_LHS_matrix.add(       euler_theta*trans_theta_expansion.eval_A_theta(q_a,mu_time), RB_Aq_a);
            RB_RHS_matrix.add( -(1.-euler_theta)*trans_theta_expansion.eval_A_theta(q_a,mu_time), RB_Aq_a);
          }

          DenseVector<Number> RB_Fq_f;
          RB_RHS_save.zero();
          for (unsigned int q_f=0; q_f<Q_f; q_f++)
          {
            RB_Fq_vector[q_f].get_principal_subvector(N, RB_Fq_f);
            RB_RHS_save.add(trans_theta_expansion.eval_F_theta(q_f,mu_time), RB_Fq_f);
          }
        }

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
        if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
        {
          for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
          {
              RB_outputs_all_k[n][time_level] = 0.;
            for (unsigned int q_l=0; q_l<trans_theta_expansion.get_n_output_terms(n); q_l++)
              {
                RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
                RB_outputs_all_k[n][time_level] += trans_theta_expansion.eval_output_theta(n,q_l,mu_time)*
                  RB_output_vector_N.dot(RB_solution);
              }
          }
        }else{
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
        }
        // Calculate RB error bounds
        if (evaluate_RB_error_bound)
          {
            // Evaluate the dual norm of the residual for RB_solution_vector
            // Real epsilon_N = initialize_rb_system._rb_con_ptr->uncached_compute_residual_dual_norm(N);

            alpha_LB = get_stability_lower_bound();
            cache_online_residual_terms(N);

            Real epsilon_N = compute_residual_dual_norm(N);

            // if(varying_timesteps)
            //   error_bound_sum += delta_t_init * pow(epsilon_N, 2.);
            // else
              error_bound_sum += residual_scaling_numer(alpha_LB) * pow(epsilon_N, 2.);

            // store error bound at time-level _k
              error_bound_all_k[time_level] = std::sqrt(error_bound_sum/residual_scaling_denom(alpha_LB));

            // Now evaluated output error bounds
            if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
            {
              for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
              {
                  RB_output_error_bounds_all_k[n][time_level] = error_bound_all_k[time_level] *
                  eval_output_dual_norm(n,mu_time);
              }
            }else{
              for (unsigned int n=0; n<trans_theta_expansion.get_n_outputs(); n++)
              {
                  RB_output_error_bounds_all_k[n][time_level] = error_bound_all_k[time_level] *
                  eval_output_dual_norm(n,mu);
              }
            }
          }

          if(varying_timesteps)
          {
            if(dt < threshold){
              dt*=growth_rate;
              set_delta_t(dt);
            }
          }

          if(initialize_rb_system._rb_con_ptr->time_dependent_parameter)
            set_parameters(mu_init);

      }

    _rb_solve_data_cached = true ;

    if (evaluate_RB_error_bound) // Calculate the error bounds
      {
        // libMesh::out << "Mu: " << mu.get_value("mu_0") << ", error: " << error_bound_all_k[n_time_steps] << std::endl;
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
  {
    DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
      cast_ref<DwarfElephantRBTransientThetaExpansion &>(get_rb_theta_expansion());

    RB_IC_q_vector.resize(dwarf_elephant_trans_theta_expansion.get_n_IC_terms());

    for (unsigned int q=0; q<dwarf_elephant_trans_theta_expansion.get_n_IC_terms(); q++)
    {
      // Initialize the memory for the RB vectors
      RB_IC_q_vector[q].resize(Nmax);
    }
  }
}

void
DwarfElephantRBEvaluationTransient::legacy_write_offline_data_to_files(const std::string & directory_name,
                                                                       const bool write_binary_data)
{
  Parent::legacy_write_offline_data_to_files(directory_name, write_binary_data);

  if(parameter_dependent_IC)
  {
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
    }
  }
  if(varying_timesteps)
  {
    // // The writing mode: ENCODE for binary, WRITE for ASCII
    // XdrMODE mode = write_binary_data ? ENCODE : WRITE;
    //
    // // The suffix to use for all the files that are written out
    // const std::string suffix = write_binary_data ? ".xdr" : ".dat";
    //
    // if (this->processor_id() == 0)
    // {
    //   // Next write out the IC_q vectors
    //   std::ostringstream file_name;
    //
    //   file_name.str("");
    //   file_name << directory_name << "/dt_steps";
    //   file_name << suffix;
    //
    //   Xdr dt_steps_out(file_name.str(), mode);
    //   dt_steps_out << dt_steps;
    //   dt_steps_out.close();
    // }
  }
}

void
DwarfElephantRBEvaluationTransient::legacy_read_offline_data_from_files(const std::string & directory_name,
                                                                        bool read_error_bound_data,
                                                                        const bool read_binary_data)
{
  Parent::legacy_read_offline_data_from_files(directory_name, read_error_bound_data, read_binary_data);

  if(parameter_dependent_IC)
  {
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
      }
  }
}

RBParameters
DwarfElephantRBEvaluationTransient::calculate_time_dependent_mu(const RBParameters mu, Real time, std::vector<unsigned int> ID_param) const
{
  RBParameters & mu_time = const_cast<RBParameters&>(mu);
  DwarfElephantRBProblem & problem = cast_ref<DwarfElephantRBProblem &>(fe_problem);
  DwarfElephantInitializeRBSystemTransient & initialize_rb_system =
    problem.getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(problem._initial_rb_userobject);

  Real dt = get_delta_t();
  Real start_time = initialize_rb_system._rb_con_ptr->start_time;
  Real end_time = initialize_rb_system._rb_con_ptr->end_time;

  Real pre_factor = 1.0;

  if (time < start_time || time - dt >= end_time)
    pre_factor = 0.0;
  else if (time - dt < start_time)
  {
    if (time <= end_time)
      pre_factor *= (time - start_time) / dt;
    else
      pre_factor *= (end_time - start_time) / dt;
  }
  else if (time > end_time)
    pre_factor *= (end_time - (time - dt)) / dt;

  for(unsigned int i = 0; i < ID_param.size(); i++)
  {
    const std::string mu_name = "mu_" + std::to_string(ID_param[i]);
    Real _time_dependency = pre_factor * mu_time.get_value(mu_name);
    mu_time.set_value(mu_name, _time_dependency);
  }

  return mu_time;
}
