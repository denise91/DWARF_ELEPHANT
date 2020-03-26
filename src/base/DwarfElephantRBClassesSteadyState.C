/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

 //-------------------------------------------------------------------------
 #include "DwarfElephantRBClassesSteadyState.h"

DwarfElephantRBConstructionSteadyState::DwarfElephantRBConstructionSteadyState (EquationSystems & es,
                                                                                const std::string & name_in,
                                                                                const unsigned int number_in)
    : Parent(es, name_in, number_in)
  {}

void
DwarfElephantRBConstructionSteadyState::init_data()
{
  u_var = this->add_variable(get_equation_systems().get_system(0).variable_name(0) + "(RB)");
  Parent::init_data();
}

 Real
 DwarfElephantRBConstructionSteadyState::compute_residual_dual_norm(const unsigned int N)
{
   LOG_SCOPE("compute_residual_dual_norm()", "RBConstruction");

   // Put the residual in rhs in order to compute the norm of the Riesz representor
   // Note that this only works in serial since otherwise each processor will
   // have a different parameter value during the Greedy training.

   UniquePtr< NumericVector<Number> > RB_sol = NumericVector<Number>::build(this->comm());
   RB_sol->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

   UniquePtr< NumericVector<Number> > temp = NumericVector<Number>::build(this->comm());
   temp->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

   for(unsigned int i=0; i<N; i++)
   {
     RB_sol->add(get_rb_evaluation().RB_solution(i), get_rb_evaluation().get_basis_function(i));
   }

   this->truth_assembly();
   matrix->vector_mult(*temp, *RB_sol);
   rhs->add(-1., *temp);

   // Then solve to get the Reisz representor
   matrix->zero();
   matrix->add(1., *inner_product_matrix);
//   if(constrained_problem)
//     matrix->add(1., *constraint_matrix);

   solution->zero();
   solve();
   // Make sure we didn't max out the number of iterations
   if( (this->n_linear_iterations() >=
        this->get_equation_systems().parameters.get<unsigned int>("linear solver maximum iterations")) &&
       (this->final_linear_residual() >
        this->get_equation_systems().parameters.get<Real>("linear solver tolerance")) )
   {
     libmesh_error_msg("Warning: Linear solver may not have converged! Final linear residual = "
                       << this->final_linear_residual() << ", number of iterations = "
                       << this->n_linear_iterations());
   }

   inner_product_matrix->vector_mult(*inner_product_storage_vector, *solution);

   Real slow_residual_norm_sq = solution->dot(*inner_product_storage_vector);

   return std::sqrt( libmesh_real(slow_residual_norm_sq) );
}

DwarfElephantRBEvaluationSteadyState::DwarfElephantRBEvaluationSteadyState(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    RBEvaluation(comm),
    fe_problem(fe_problem)
{
  set_rb_theta_expansion(_rb_theta_expansion);
}

Real
DwarfElephantRBEvaluationSteadyState::get_stability_lower_bound()
{
  const RBParameters & mu = get_parameters();

  Real min_mu = mu.get_value("mu_0");

  for (unsigned int  i = 1; i != mu.n_parameters(); i++)
  {
    const std::string mu_name = "mu_" + std::to_string(i);
    Real min_mu_i = std::min(min_mu, mu.get_value(mu_name));

    if (min_mu_i < min_mu)
      min_mu = min_mu_i;
  }

  return min_mu;
}
