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
#ifndef DWARFELEPHANTRBCLASSESTRANSIENT_H
#define DWARFELEPHANTRBCLASSESTRANSIENT_H
///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

// libMesh includes
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"

// libMesh includes (RB package)
#include "libmesh/transient_rb_evaluation.h"
#include "libmesh/transient_rb_construction.h"
#include "libmesh/elem_assembly.h"
#include "libmesh/fem_context.h"
///-------------------------------------------------------------------------
#include "FEProblemBase.h"
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystemTransient.h"
#include "DwarfElephantOfflineOnlineStageTransient.h"
#include "DwarfElephantGeom3DTransientRBThetaExpansion_RFA.h"

/*
#include "DwarfElephantRBStructuresT1F1O1M1Transient.h"
#include "DwarfElephantRBStructuresT2F1O1M1Transient.h"
#include "DwarfElephantRBStructuresT2F2O1M2Transient.h"
#include "DwarfElephantRBStructuresT2F3O1M2Transient.h"
#include "DwarfElephantRBStructuresT2F3O3M2Transient.h"
#include "DwarfElephantRBStructuresT3F1O1M1Transient.h"
#include "DwarfElephantRBStructuresT3F1O3M1Transient.h"
#include "DwarfElephantRBStructuresT3F4O1M2Transient.h"
#include "DwarfElephantRBStructuresT3F4O3M2Transient.h"
#include "DwarfElephantRBStructuresT3F3O3M2IC1Transient.h"
#include "DwarfElephantRBStructuresT4F1O1M1Transient.h"
#include "DwarfElephantRBStructuresT4F1O1M1IC1Transient.h"
#include "DwarfElephantRBStructuresT5F1O1M1Transient.h"
#include "DwarfElephantRBStructuresT5F4O1M2Transient.h"
#include "DwarfElephantRBStructuresT6F1O1M1IC3Transient.h"
*/
#include "libmesh/transient_rb_theta_expansion.h"
#include "libmesh/transient_rb_assembly_expansion.h"
// Forward Declarations
namespace libMesh
{
  template <typename T> class SparseMatrix;
  template <typename T> class PetscMatrix;

  class EquationSystems;
  class TransientRBConstruction;
  class TransientRBEvaluation;
  class RBTheta;
  class RBThetaExpansion;
  class ElemAssembly;
  class FEMContext;
}

class DwarfElephantInitializeRBSystemSteadyState;

struct DwarfElephantCustomTransientTheta : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return _mu.get_value("mu_0");
  }
};

struct DwarfElephantRBCustomTransientThetaExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBCustomTransientThetaExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_M_theta(&_rb_theta);

    attach_A_theta(&_rb_theta);

    attach_A_theta(&_theta_a_0);

    //attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantCustomTransientTheta _theta_a_0;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

struct DummyMAssembly : ElemAssembly
{
  virtual void interior_assembly(FEMContext & dummy)
  { }
};

struct DwarfElephantRBCustomTransientAssemblyExpansion : TransientRBAssemblyExpansion
{
  DwarfElephantRBCustomTransientAssemblyExpansion()
  {
    attach_M_assembly(&M0);
    attach_M_assembly(&M1);
    attach_M_assembly(&M2);
    attach_M_assembly(&M3);
    attach_M_assembly(&M4);
    attach_M_assembly(&M5);
    attach_M_assembly(&M6);
    attach_M_assembly(&M7);
    attach_M_assembly(&M8);
    attach_M_assembly(&M9);
    attach_M_assembly(&M10);
    attach_M_assembly(&M11);
    attach_M_assembly(&M12);
    attach_M_assembly(&M13);
    attach_M_assembly(&M14);
    attach_M_assembly(&M15);
    attach_M_assembly(&M16);
    attach_M_assembly(&M17);
    attach_M_assembly(&M18);
    attach_M_assembly(&M19);
    attach_M_assembly(&M20);
    attach_M_assembly(&M21);
    attach_M_assembly(&M22);
    attach_M_assembly(&M23);
    attach_M_assembly(&M24);
    attach_M_assembly(&M25);
    attach_M_assembly(&M26);
    attach_M_assembly(&M27);
    attach_M_assembly(&M28);
    attach_M_assembly(&M29);
    attach_M_assembly(&M30);
    attach_M_assembly(&M31);
    
    
  }
  DummyMAssembly M0;
  DummyMAssembly M1;
  DummyMAssembly M2;
  DummyMAssembly M3;
  DummyMAssembly M4;
  DummyMAssembly M5;
  DummyMAssembly M6;
  DummyMAssembly M7;
  DummyMAssembly M8;
  DummyMAssembly M9;
  DummyMAssembly M10;
  DummyMAssembly M11;
  DummyMAssembly M12;
  DummyMAssembly M13;
  DummyMAssembly M14;
  DummyMAssembly M15;
  DummyMAssembly M16;
  DummyMAssembly M17;
  DummyMAssembly M18;
  DummyMAssembly M19;
  DummyMAssembly M20;
  DummyMAssembly M21;
  DummyMAssembly M22;
  DummyMAssembly M23;
  DummyMAssembly M24;
  DummyMAssembly M25;
  DummyMAssembly M26;
  DummyMAssembly M27;
  DummyMAssembly M28;
  DummyMAssembly M29;
  DummyMAssembly M30;
  DummyMAssembly M31;
  
};
///-----------------------DWARFELEPHANTRBCONSTRUCTION-----------------------
class DwarfElephantRBConstructionTransient : public TransientRBConstruction
{

//---------------------------------PUBLIC-----------------------------------
public:

  // Constructor
  DwarfElephantRBConstructionTransient (EquationSystems & es,
                        const std::string & name_in,
                        const unsigned int number_in);

  // Destructor
  virtual ~DwarfElephantRBConstructionTransient () { }

  // Type of the system
  typedef DwarfElephantRBConstructionTransient _sys_type;

  void FE_solve_debug(RBParameters mu, int write_interval)
  {
      const unsigned int Q_a = get_rb_theta_expansion().get_n_A_terms();
      const unsigned int Q_f = get_rb_theta_expansion().get_n_F_terms();
      unsigned int M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;
      const unsigned int n_time_steps = get_n_time_steps();
      const Real euler_theta = get_euler_theta();
      initialize_truth();
      set_time_step(0);
      std::unique_ptr<NumericVector<Number>> FullFEsolution;
      FullFEsolution = NumericVector<Number>::build(this->comm());
      FullFEsolution->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      Geom3DTransientRBThetaExpansion & rb_theta_exp = dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion());

      FullFEsolution -> zero();
      FullFEsolution -> close();


      this -> matrix -> zero();
      this -> rhs -> zero();
      
      this -> matrix -> close();
      this -> rhs -> close();
      
      Real dt = get_delta_t();
      // Prepare LHS matrix for full order FE solve
     
      
        for (unsigned int time_level=1; time_level<=n_time_steps; time_level++)
        {
            set_time_step(time_level);

            *old_local_solution = *current_local_solution;

      // We assume that the truth assembly has been attached to the system
            add_scaled_mass_matrix(1./dt,matrix);
            mass_matrix_scaled_matvec(1./dt, *rhs, *current_local_solution);
      
            std::unique_ptr<NumericVector<Number>> temp_vec = NumericVector<Number>::build(this->comm());
            temp_vec->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      
            for (unsigned int q_a=0; q_a<Q_a; q_a++)
            {
              matrix->add(euler_theta*get_rb_theta_expansion().eval_A_theta(q_a,mu), *get_Aq(q_a));

              get_Aq(q_a)->vector_mult(*temp_vec, *current_local_solution);
              temp_vec->scale( -(1.-euler_theta)*get_rb_theta_expansion().eval_A_theta(q_a,mu) );
              rhs->add(*temp_vec);
            }

            for (unsigned int q_f=0; q_f<Q_f; q_f++)
            {
              *temp_vec = *get_Fq(q_f);
              if (q_f == 0)
                  temp_vec->scale( get_control(get_time_step())*get_rb_theta_expansion().eval_F_theta(q_f, mu));
              else
                  temp_vec->scale( get_control(get_time_step())*get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu));
              rhs->add(*temp_vec);
            }
      
            this->matrix->close();
            this->rhs->close();

      // truth_assembly assembles into matrix and rhs, so use those for the solve
            solve_for_matrix_and_rhs(*get_linear_solver(), *matrix, *rhs);

      // The matrix doesn't change at each timestep, so we
      // can set reuse_preconditioner == true
            linear_solver->reuse_preconditioner(true);

            if (assert_convergence)
            {
                check_convergence(*get_linear_solver());
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
                std::ostringstream file_name2;
                file_name2 << "out_"
                        << std::setprecision(0)
                        << std::setfill('0')
                        << std::right
                        << time_level
                        << ".vtu";
                VTKIO(get_mesh()).write_equation_systems(file_name2.str(), this->get_equation_systems());
            }
        }

    // Set reuse_preconditioner back to false for subsequent solves.
      linear_solver->reuse_preconditioner(false);

      
      
  
  }
  // Type of the parent
  typedef TransientRBConstruction Parent;

  virtual void clear() override;

  virtual void allocate_data_structures() override;

  // Initialize data structure
  virtual void init_data() override;

  virtual void print_info() override;

  virtual void initialize_truth() override;
  
  virtual void truth_assembly() override;

  virtual Real get_RB_error_bound() override;

  NumericVector<Number> * get_IC_q(unsigned int q);

  NumericVector<Number> * get_non_dirichlet_IC_q(unsigned int q);

  NumericVector<Number> * get_non_dirichlet_IC_q_if_avail(unsigned int q);

  unsigned int get_parameter_dependent_IC() const {return parameter_dependent_IC;}

  virtual void set_parameter_dependent_IC(bool parameter_dependent_IC_in);

  void update_RB_initial_condition_all_N();

  void update_RB_parameterized_initial_condition_all_N();

  virtual void update_system() override;

  virtual Real train_reduced_basis(const bool resize_rb_eval_data=true) override;

  virtual Real train_reduced_basis_steady(const bool resize_rb_eval_data=true);

  void enrich_RB_space_for_initial_conditions();

  unsigned int u_var;

  bool parameter_dependent_IC;

  DwarfElephantRBCustomTransientAssemblyExpansion Dummy_TransientRBAssemblyExpansion;

private:
  /**
   * Vector storing the Q_ic vectors in the affine decomposition
   * of the initial conditions.
   */
  std::vector<std::unique_ptr<NumericVector<Number>>> IC_q_vector;
  std::vector<std::unique_ptr<NumericVector<Number>>> non_dirichlet_IC_q_vector;
};

///------------------------DWARFELEPHANTRBEVALUATION------------------------
class DwarfElephantRBEvaluationTransient : public TransientRBEvaluation
{

//---------------------------------PUBLIC-----------------------------------
public:
  DwarfElephantRBEvaluationTransient(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem);

  typedef TransientRBEvaluation Parent;

  virtual Real get_stability_lower_bound() override;

  virtual Real rb_solve(unsigned int N) override;
  
  void cache_online_residual_terms(const unsigned int N)
  {
    LOG_SCOPE("cache_online_residual_terms()", "TransientRBEvaluation");

    const RBParameters mu = get_parameters();
    unsigned int M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;

    TransientRBThetaExpansion & trans_theta_expansion =
    cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());
    const unsigned int Q_m = trans_theta_expansion.get_n_M_terms();
    const unsigned int Q_a = trans_theta_expansion.get_n_A_terms();
    const unsigned int Q_f = trans_theta_expansion.get_n_F_terms();

    cached_Fq_term = 0.;
    unsigned int q=0;
    for (unsigned int q_f1=0; q_f1<Q_f; q_f1++)
    {
      Number cached_theta_q_f1 = 0;
      if (q_f1 == 0)
          cached_theta_q_f1 = trans_theta_expansion.eval_F_theta(q_f1,mu);
      else
          cached_theta_q_f1 = get_rb_theta_expansion().eval_F_theta(((q_f1 -1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f1 -1)/M]->evaluate(mu);
      for (unsigned int q_f2=q_f1; q_f2<Q_f; q_f2++)
        {
          Real delta = (q_f1==q_f2) ? 1. : 2.;
          if (q_f2 == 0)
              cached_Fq_term += delta*cached_theta_q_f1*trans_theta_expansion.eval_F_theta(q_f2,mu) *
            Fq_representor_innerprods[q];
          else
              cached_Fq_term += delta*cached_theta_q_f1*get_rb_theta_expansion().eval_F_theta(((q_f2 -1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f2-1)/M]->evaluate(mu) * Fq_representor_innerprods[q];

          q++;
        }
    }

  cached_Fq_Aq_vector.resize(N);
  for (unsigned int q_f=0; q_f<Q_f; q_f++)
    {
      Number cached_theta_q_f = 0;
      if (q_f == 0)
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
      else
          cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu);
      for (unsigned int q_a=0; q_a<Q_a; q_a++)
        {
          Number cached_theta_q_a = trans_theta_expansion.eval_A_theta(q_a,mu);
          for (unsigned int i=0; i<N; i++)
            {
              cached_Fq_Aq_vector(i) += 2.*cached_theta_q_f*cached_theta_q_a*
                Fq_Aq_representor_innerprods[q_f][q_a][i];
            }
        }
    }

  cached_Aq_Aq_matrix.resize(N,N);
  q=0;
  for (unsigned int q_a1=0; q_a1<Q_a; q_a1++)
    {
      Number cached_theta_q_a1 = trans_theta_expansion.eval_A_theta(q_a1,mu);
      for (unsigned int q_a2=q_a1; q_a2<Q_a; q_a2++)
        {
          Number cached_theta_q_a2 = trans_theta_expansion.eval_A_theta(q_a2,mu);
          Real delta = (q_a1==q_a2) ? 1. : 2.;

          for (unsigned int i=0; i<N; i++)
            {
              for (unsigned int j=0; j<N; j++)
                {
                  cached_Aq_Aq_matrix(i,j) += delta*
                    cached_theta_q_a1*cached_theta_q_a2*
                    Aq_Aq_representor_innerprods[q][i][j];
                }
            }
          q++;
        }
    }

  cached_Fq_Mq_vector.resize(N);
  for (unsigned int q_f=0; q_f<Q_f; q_f++)
    {
      Number cached_theta_q_f = 0;
      if (q_f == 0)
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
      else
          cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu);
      for (unsigned int q_m=0; q_m<Q_m; q_m++)
        {
          Number cached_theta_q_m = trans_theta_expansion.eval_M_theta(q_m,mu);
          for (unsigned int i=0; i<N; i++)
            {
              cached_Fq_Mq_vector(i) += 2.*cached_theta_q_f * cached_theta_q_m * Fq_Mq_representor_innerprods[q_f][q_m][i];
            }
        }
    }

  cached_Aq_Mq_matrix.resize(N,N);
  for (unsigned int q_a=0; q_a<Q_a; q_a++)
    {
      Number cached_theta_q_a = trans_theta_expansion.eval_A_theta(q_a,mu);

      for (unsigned int q_m=0; q_m<Q_m; q_m++)
        {
          Number cached_theta_q_m = trans_theta_expansion.eval_M_theta(q_m,mu);

          for (unsigned int i=0; i<N; i++)
            {
              for (unsigned int j=0; j<N; j++)
                {
                    cached_Aq_Mq_matrix(i,j) += 2.*cached_theta_q_a*cached_theta_q_m*Aq_Mq_representor_innerprods[q_a][q_m][i][j];
                  }
              }
          }
      }

    cached_Mq_Mq_matrix.resize(N,N);
    q=0;
    for (unsigned int q_m1=0; q_m1<Q_m; q_m1++)
      {
        Number cached_theta_q_m1 = trans_theta_expansion.eval_M_theta(q_m1,mu);
        for (unsigned int q_m2=q_m1; q_m2<Q_m; q_m2++)
          {
            Number cached_theta_q_m2 = trans_theta_expansion.eval_M_theta(q_m2,mu);
            Real delta = (q_m1==q_m2) ? 1. : 2.;

            for (unsigned int i=0; i<N; i++)
              {
                for (unsigned int j=0; j<N; j++)
                  {
                     cached_Mq_Mq_matrix(i,j) += delta*
                      cached_theta_q_m1*cached_theta_q_m2*
                      Mq_Mq_representor_innerprods[q][i][j];
                  }
              }
            q++;
          }
      }
    }
  
  virtual Real uncached_compute_residual_dual_norm(const unsigned int N)
  {
        LOG_SCOPE("uncached_compute_residual_dual_norm()", "TransientRBEvaluation");

  // Use the stored representor inner product values
  // to evaluate the residual norm

  const RBParameters & mu = get_parameters();
  unsigned int M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;

  TransientRBThetaExpansion & trans_theta_expansion =
    cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());
  const unsigned int Q_m = trans_theta_expansion.get_n_M_terms();
  const unsigned int Q_a = trans_theta_expansion.get_n_A_terms();
  const unsigned int Q_f = trans_theta_expansion.get_n_F_terms();

  const Real dt          = get_delta_t();
  const Real euler_theta = get_euler_theta();

  std::vector<Number> RB_u_euler_theta(N);
  std::vector<Number> mass_coeffs(N);
  for (unsigned int i=0; i<N; i++)
    {
      RB_u_euler_theta[i]  = euler_theta*RB_solution(i) +
        (1.-euler_theta)*old_RB_solution(i);
      mass_coeffs[i] = -(RB_solution(i) - old_RB_solution(i))/dt;
    }

  Number residual_norm_sq = 0.;

  unsigned int q=0;
  for (unsigned int q_f1=0; q_f1<Q_f; q_f1++)
    {
      Number cached_theta_q_f1 = 0;
      if (q_f1 == 0)
          cached_theta_q_f1 = trans_theta_expansion.eval_F_theta(q_f1,mu);
      else
          cached_theta_q_f1 = get_rb_theta_expansion().eval_F_theta(((q_f1-1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f1-1)/M)]->evaluate(mu);
      for (unsigned int q_f2=q_f1; q_f2<Q_f; q_f2++)
        {
          Real delta = (q_f1==q_f2) ? 1. : 2.;
          if (q_f2 == 0)
              residual_norm_sq += delta*cached_theta_q_f1*trans_theta_expansion.eval_F_theta(q_f2,mu) * Fq_representor_innerprods[q];
          else
              residual_norm_sq += delta*cached_theta_q_f1*get_rb_theta_expansion().eval_F_theta(((q_f2 - 1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f2 - 1)/M)]->evaluate(mu) * Fq_representor_innerprods[q];

          q++;
        }
    }

  for (unsigned int q_f=0; q_f<Q_f; q_f++)
    {
      Number cached_theta_q_f = 0;
      if (q_f == 0)
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
      else
          cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f - 1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f - 1)/M)]->evaluate(mu);
      for (unsigned int q_a=0; q_a<Q_a; q_a++)
        {
          Number cached_theta_q_a = trans_theta_expansion.eval_A_theta(q_a,mu);
          for (unsigned int i=0; i<N; i++)
            {
              residual_norm_sq += 2.*RB_u_euler_theta[i]*cached_theta_q_f*cached_theta_q_a*
                Fq_Aq_representor_innerprods[q_f][q_a][i];
            }
        }
    }

  q=0;
  for (unsigned int q_a1=0; q_a1<Q_a; q_a1++)
    {
      Number cached_theta_q_a1 = trans_theta_expansion.eval_A_theta(q_a1,mu);
      for (unsigned int q_a2=q_a1; q_a2<Q_a; q_a2++)
        {
          Number cached_theta_q_a2 = trans_theta_expansion.eval_A_theta(q_a2,mu);
          Real delta = (q_a1==q_a2) ? 1. : 2.;

          for (unsigned int i=0; i<N; i++)
            {
              for (unsigned int j=0; j<N; j++)
                {
                  residual_norm_sq += delta*RB_u_euler_theta[i]*RB_u_euler_theta[j]*
                    cached_theta_q_a1*cached_theta_q_a2*
                    Aq_Aq_representor_innerprods[q][i][j];
                }
            }
          q++;
        }
    }

  // Now add the terms due to the time-derivative
  q=0;
  for (unsigned int q_m1=0; q_m1<Q_m; q_m1++)
    {
      Number cached_theta_q_m1 = trans_theta_expansion.eval_M_theta(q_m1,mu);
      for (unsigned int q_m2=q_m1; q_m2<Q_m; q_m2++)
        {
          Number cached_theta_q_m2 = trans_theta_expansion.eval_M_theta(q_m2,mu);
          Real delta = (q_m1==q_m2) ? 1. : 2.;

          for (unsigned int i=0; i<N; i++)
            {
              for (unsigned int j=0; j<N; j++)
                {
                  residual_norm_sq += delta*mass_coeffs[i]*mass_coeffs[j]*
                    cached_theta_q_m1*cached_theta_q_m2*
                    Mq_Mq_representor_innerprods[q][i][j];
                }
            }
          q++;
        }
    }

  for (unsigned int q_f=0; q_f<Q_f; q_f++)
    {
      Number cached_theta_q_f = 0;
      if (q_f == 0)
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
      else
          cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f - 1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f - 1)/M)]->evaluate(mu);
      for (unsigned int q_m=0; q_m<Q_m; q_m++)
        {
          Number cached_theta_q_m = trans_theta_expansion.eval_M_theta(q_m,mu);
          for (unsigned int i=0; i<N; i++)
            {
              residual_norm_sq += 2.*mass_coeffs[i]*cached_theta_q_f * cached_theta_q_m * Fq_Mq_representor_innerprods[q_f][q_m][i];
            }
        }
    }

  for (unsigned int q_a=0; q_a<Q_a; q_a++)
    {
      Number cached_theta_q_a = trans_theta_expansion.eval_A_theta(q_a,mu);

      for (unsigned int q_m=0; q_m<Q_m; q_m++)
        {
          Number cached_theta_q_m = trans_theta_expansion.eval_M_theta(q_m,mu);

          for (unsigned int i=0; i<N; i++)
            {
              for (unsigned int j=0; j<N; j++)
                {
                  residual_norm_sq += 2.*RB_u_euler_theta[i]*mass_coeffs[j]*
                    cached_theta_q_a*cached_theta_q_m*
                    Aq_Mq_representor_innerprods[q_a][q_m][i][j];
                }
            }
        }
    }

  if (libmesh_real(residual_norm_sq) < 0)
    {
      libMesh::out << "Warning: Square of residual norm is negative "
                   << "in TransientRBEvaluation::compute_residual_dual_norm()" << std::endl;

      // Sometimes this is negative due to rounding error,
      // but error is on the order of 1.e-10, so shouldn't
      // affect result
      residual_norm_sq = std::abs(residual_norm_sq);
    }

  //   libMesh::out << "slow residual_sq = " << slow_residual_norm_sq
  //                << ", fast residual_sq = " << residual_norm_sq << std::endl;

  return libmesh_real(std::sqrt( residual_norm_sq ));

  }
  

  FEProblemBase & get_fe_problem() {return fe_problem;}

  unsigned int get_parameter_dependent_IC() const {return parameter_dependent_IC;}

  virtual void set_parameter_dependent_IC(bool parameter_dependent_IC_in);

  virtual void resize_data_structures(const unsigned int Nmax,
                                      bool resize_error_bound_data=true) override;

  virtual void legacy_write_offline_data_to_files(const std::string & directory_name,
                                                  const bool write_binary_data) override;

  virtual void legacy_read_offline_data_from_files(const std::string & directory_name = "offline_data",
                                                   bool read_error_bound_data=true,
                                                   const bool read_binary_data=true) override;
  
  virtual Real compute_residual_dual_norm(const unsigned int N)
{
  LOG_SCOPE("compute_residual_dual_norm()", "TransientRBEvaluation");

  // This assembly assumes we have already called cache_online_residual_terms
  // and that the rb_solve parameter is constant in time

  const Real dt          = get_delta_t();
  const Real euler_theta = get_euler_theta();
  const Real current_control = get_control(get_time_step());

  DenseVector<Number> RB_u_euler_theta(N);
  DenseVector<Number> mass_coeffs(N);
  for (unsigned int i=0; i<N; i++)
    {
      RB_u_euler_theta(i)  = euler_theta*RB_solution(i) +
        (1.-euler_theta)*old_RB_solution(i);
      mass_coeffs(i) = -(RB_solution(i) - old_RB_solution(i))/dt;
    }

  Number residual_norm_sq = current_control*current_control*cached_Fq_term;

  residual_norm_sq += current_control*RB_u_euler_theta.dot(cached_Fq_Aq_vector);
  residual_norm_sq += current_control*mass_coeffs.dot(cached_Fq_Mq_vector);

  for (unsigned int i=0; i<N; i++)
    for (unsigned int j=0; j<N; j++)
      {
        residual_norm_sq += RB_u_euler_theta(i)*RB_u_euler_theta(j)*cached_Aq_Aq_matrix(i,j);
        residual_norm_sq += mass_coeffs(i)*mass_coeffs(j)*cached_Mq_Mq_matrix(i,j);
        residual_norm_sq += RB_u_euler_theta(i)*mass_coeffs(j)*cached_Aq_Mq_matrix(i,j);
      }


  if (libmesh_real(residual_norm_sq) < 0)
    {
      libMesh::out << "Warning: Square of residual norm is negative "
                   << "in TransientRBEvaluation::compute_residual_dual_norm()" << std::endl;
      if (std::abs(residual_norm_sq) > 1e-10) 
      {
          libMesh::out << "Negative residual norm squared = " << residual_norm_sq << std::endl;
      }
      // Sometimes this is negative due to rounding error,
      // but error is on the order of 1.e-10, so shouldn't
      // affect result
      residual_norm_sq = std::abs(residual_norm_sq);
    }

  return libmesh_real(std::sqrt( residual_norm_sq ));
}


  FEProblemBase & fe_problem;

  bool parameter_dependent_IC;

  //DwarfElephantRBCustomTransientThetaExpansion _rb_theta_expansion;
  
  Geom3DTransientRBThetaExpansion _rb_theta_expansion;

  std::vector<DenseVector<Number>> RB_IC_q_vector;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBCLASSESTRANSIENT_H
