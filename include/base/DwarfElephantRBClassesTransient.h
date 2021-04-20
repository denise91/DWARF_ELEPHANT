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


#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
// libMesh includes
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/enum_io_package.h"
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

// for memory logging function
#include <unistd.h>
#include <ios>
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
  virtual Number evaluate (const RBParameters & /*_mu*/)
  {
    return 0.05;//0*_mu.get_value("mu_0");
  }
};

struct AdvX : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return 0*_mu.get_value("mu_0");
  }
};

struct AdvY : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return _mu.get_value("mu_1");
  }
};

struct DwarfElephantRBCustomTransientThetaExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBCustomTransientThetaExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_rb_theta);
    //attach_A_theta(&adv_x);
    attach_F_theta(&_rb_theta);
   // attach_A_theta(&adv_y);


    //attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantCustomTransientTheta _theta_a_0;
  AdvX adv_x;
  AdvY adv_y;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

struct debugAssemblyExpansion : TransientRBAssemblyExpansion
{
    debugAssemblyExpansion()
    {
        attach_M_assembly(&M0);
    }
    DummyMAssembly M0;
};


///------------------------DWARFELEPHANTRBEVALUATION------------------------
class DwarfElephantRBEvaluationTransient : public TransientRBEvaluation
{

//---------------------------------PUBLIC-----------------------------------
public:
  DwarfElephantRBEvaluationTransient(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem, bool _RB_RFA_in);

  typedef TransientRBEvaluation Parent;

  virtual Real get_stability_lower_bound() override;

  virtual Real rb_solve(unsigned int N) override;
  
  void cache_online_residual_terms(const unsigned int N)
  {
    LOG_SCOPE("cache_online_residual_terms()", "TransientRBEvaluation");

    const RBParameters mu = get_parameters();
    unsigned int M = 1;
    if (_RB_RFA)
        M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;

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
      
      if (_RB_RFA)
      {
          if (q_f1 == 0)
              cached_theta_q_f1 = trans_theta_expansion.eval_F_theta(q_f1,mu);
          else
              cached_theta_q_f1 = get_rb_theta_expansion().eval_F_theta(((q_f1 -1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f1 -1)/M]->evaluate(mu);
      }
      else
          cached_theta_q_f1 = trans_theta_expansion.eval_F_theta(q_f1,mu);
      
      for (unsigned int q_f2=q_f1; q_f2<Q_f; q_f2++)
        {
          Real delta = (q_f1==q_f2) ? 1. : 2.;
          if (_RB_RFA)
          {
              if (q_f2 == 0)
                  cached_Fq_term += delta*cached_theta_q_f1*trans_theta_expansion.eval_F_theta(q_f2,mu) *
                  Fq_representor_innerprods[q];
              else
                  cached_Fq_term += delta*cached_theta_q_f1*get_rb_theta_expansion().eval_F_theta(((q_f2 -1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f2-1)/M]->evaluate(mu) * Fq_representor_innerprods[q];
          }
          else
              cached_Fq_term += delta*cached_theta_q_f1*trans_theta_expansion.eval_F_theta(q_f2,mu) *
                  Fq_representor_innerprods[q];

          q++;
        }
    }

  cached_Fq_Aq_vector.resize(N);
  for (unsigned int q_f=0; q_f<Q_f; q_f++)
    {
      Number cached_theta_q_f = 0;
      if (_RB_RFA)
      {
          if (q_f == 0)
              cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
          else
              cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu);
      }
      else
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
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
      if (_RB_RFA)
      {
          if (q_f == 0)
              cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
          else
              cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu);
      }
      else
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
      
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
  
  virtual Real uncached_compute_residual_dual_norm(const unsigned int N) override
  {
        LOG_SCOPE("uncached_compute_residual_dual_norm()", "TransientRBEvaluation");

  // Use the stored representor inner product values
  // to evaluate the residual norm

  const RBParameters & mu = get_parameters();
  unsigned int M = 1;
  if (_RB_RFA)
      M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;

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
      if (_RB_RFA)
      {
          if (q_f1 == 0)
              cached_theta_q_f1 = trans_theta_expansion.eval_F_theta(q_f1,mu);
          else
              cached_theta_q_f1 = get_rb_theta_expansion().eval_F_theta(((q_f1-1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f1-1)/M)]->evaluate(mu);
      }
      else
          cached_theta_q_f1 = trans_theta_expansion.eval_F_theta(q_f1,mu);
      
      for (unsigned int q_f2=q_f1; q_f2<Q_f; q_f2++)
        {
          Real delta = (q_f1==q_f2) ? 1. : 2.;
          if (_RB_RFA)
          {
              if (q_f2 == 0)
                  residual_norm_sq += delta*cached_theta_q_f1*trans_theta_expansion.eval_F_theta(q_f2,mu) * Fq_representor_innerprods[q];
              else
                  residual_norm_sq += delta*cached_theta_q_f1*get_rb_theta_expansion().eval_F_theta(((q_f2 - 1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f2 - 1)/M)]->evaluate(mu) * Fq_representor_innerprods[q];
          }
          else
              residual_norm_sq += delta*cached_theta_q_f1*trans_theta_expansion.eval_F_theta(q_f2,mu) * Fq_representor_innerprods[q];

          q++;
        }
    }

  for (unsigned int q_f=0; q_f<Q_f; q_f++)
    {
      Number cached_theta_q_f = 0;
      if (_RB_RFA)
      {
          if (q_f == 0)
              cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
          else
              cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f - 1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f - 1)/M)]->evaluate(mu);
      }
      else
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
      
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
      if (_RB_RFA)
      {
          if (q_f == 0)
              cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
          else
              cached_theta_q_f = get_rb_theta_expansion().eval_F_theta(((q_f - 1)%M + 1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[((q_f - 1)/M)]->evaluate(mu);
      }
      else
          cached_theta_q_f = trans_theta_expansion.eval_F_theta(q_f,mu);
      
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
  
  virtual Real compute_residual_dual_norm(const unsigned int N) override
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
  
  //Geom3DTransientRBThetaExpansion _rb_theta_expansion;
  //M_theta_10 _rb_theta_expansion;
  A_theta_10 _rb_theta_expansion;
  //BC_heat_source_thetas _rb_theta_expansion;
  //DwarfElephantRBCustomTransientThetaExpansion _rb_theta_expansion;
  //DwarfElephantRBCustomTransientThetaExpansion _rb_theta_expansion;

  std::vector<DenseVector<Number>> RB_IC_q_vector;
  
  bool _RB_RFA;
};
///-------------------------------------------------------------------------


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

  std::string execute_command(const char *     cmd);
  
  void write_mesh_node_coords_and_elem_connectivities(std::string mesh_name);

  void print_matrix(SparseMatrix<Number> * mat_in, std::string filename);

  void print_vector(NumericVector<Number> * vec_in, std::string filename);

  void set_up_error_norm_v_N_vec()
  {
      error_norm_sum_v_N.resize(get_rb_evaluation().get_n_basis_functions());
      online_error_bound_v_N.resize(get_rb_evaluation().get_n_basis_functions());
      for (unsigned int i = 0; i < get_rb_evaluation().get_n_basis_functions(); i++)
          error_norm_sum_v_N[i] = 0;
  }
  
  void print_error_norm_v_N_vec(RBParameters mu)
  {
      std::ostringstream outfiletext;
      std::ostringstream outfilename;
      std::ofstream outfile;
      outfile << "#N, Energy norm error, Energy norm error bound" ;
      for (int i = 0; i < get_rb_evaluation().get_n_basis_functions(); i++)
      {
          libMesh::out << "N = " << i+1 << " Error = " << error_norm_sum_v_N[i]  << " Error bound = " << online_error_bound_v_N[i] << "\n";
          outfiletext << i+1 << ", " << error_norm_sum_v_N[i] << ", " << online_error_bound_v_N[i] << std::endl;
          if (error_norm_sum_v_N[i] > online_error_bound_v_N[i]) {libMesh::out << "                  ^^^^^^^^^              Error is larger than error bound!" << "\n";}
      }
      outfilename << "./RB_Error_ErrorBound_Plots/mu_"; 
      outfilename << std::fixed << mu.get_value("mu_0");
      outfilename << "_" ;
      outfilename << std::fixed << mu.get_value("mu_1");
      outfilename <<"_" ;
      outfilename << std::fixed << mu.get_value("mu_2");
      outfilename << "_";
      outfilename << std::fixed << mu.get_value("mu_3");
      outfilename << "_";
      outfilename << std::fixed << mu.get_value("mu_4");
      outfilename << ".txt";
      outfile.open(outfilename.str());
      outfile << outfiletext.str();
      outfile.close();
      
  }

  void FE_solve_debug(RBParameters mu, int write_interval, int /*num_param_values*/, int mesh_index, std::vector<unsigned int> _temp_averaging_node_ids)
  { // computes the full FE solution and returns it as a vector of numeric vectors
      const unsigned int Q_a = get_rb_theta_expansion().get_n_A_terms();
      const unsigned int Q_f = get_rb_theta_expansion().get_n_F_terms();
      unsigned int M = 1;
      if (dynamic_cast<DwarfElephantRBEvaluationTransient&>(get_rb_evaluation())._RB_RFA)
          M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;
      const unsigned int n_time_steps = get_n_time_steps();
      const Real euler_theta = get_euler_theta();
      std::ofstream file_theta_objects;
      TransientRBThetaExpansion & trans_theta_expansion =
      cast_ref<TransientRBThetaExpansion &>(get_rb_theta_expansion());
      Real A_freq_factor = 3.1e98;
      Real E_act = 6.28e5;
      Real R_ideal_gas = 8.314;
      //Real _needle_neighbourhood_RMS_temp_final = 0; //holds the Root Mean Squared temperature at the final time in a 2cm ball around the needle center.
      
      std::unique_ptr<NumericVector<Number>> _needle_neighbourhood_temp = NumericVector<Number>::build(this->comm());
      _needle_neighbourhood_temp->init(this->n_dofs(),this->n_local_dofs(),false,PARALLEL);
      _needle_neighbourhood_temp->zero();
      
      std::unique_ptr<NumericVector<Number>> _arrhenius_integral = NumericVector<Number>::build(this->comm());
      _arrhenius_integral->init(this->n_dofs(),this->n_local_dofs(),false,PARALLEL);
      _arrhenius_integral->zero();
      
      std::unique_ptr<NumericVector<Number>> _tissue_damage = NumericVector<Number>::build(this->comm());
      _tissue_damage->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      _tissue_damage->zero();
      _tissue_damage->add(1.0);

      std::unique_ptr<NumericVector<Number>> temp_vec_L2_norm = NumericVector<Number>::build(this->comm());
      temp_vec_L2_norm->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      temp_vec_L2_norm->zero();
      
      const unsigned int Q_m = trans_theta_expansion.get_n_M_terms();
      initialize_truth();
      set_time_step(0);
      std::vector<std::unique_ptr<NumericVector<Number>>> FullFEsolution;
      FullFEsolution.resize(n_time_steps);
      std::vector<std::unique_ptr<NumericVector<Number>>> _RB_solution;
      _RB_solution.resize(n_time_steps);
      
      std::unique_ptr<SparseMatrix<Number>> M_mu;
      std::unique_ptr<SparseMatrix<Number>> A_mu;
      
      A_mu = SparseMatrix<Number>::build(this->comm());
      this->get_dof_map().attach_matrix(*A_mu);
      A_mu->init();
      A_mu->zero();
      A_mu->close();
      
      M_mu = SparseMatrix<Number>::build(this->comm());
      this->get_dof_map().attach_matrix(*M_mu);
      M_mu->init();
      M_mu->zero();
      M_mu->close();
      
      //Geom3DTransientRBThetaExpansion & rb_theta_exp = dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion());


      
      Real dt = get_delta_t();
      Real temperature_L2_norm_sq = 0;
      Real temperature_L2_norm_time_integral = 0;
      // Prepare LHS matrix for full order FE solve
     
      
        for (unsigned int time_level=1; time_level<=n_time_steps; time_level++)
        {
            FullFEsolution[time_level-1] = NumericVector<Number>::build(this->comm());
            FullFEsolution[time_level-1]->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
            FullFEsolution[time_level-1] -> zero();
            FullFEsolution[time_level-1] -> close();
            
            _RB_solution[time_level-1] = NumericVector<Number>::build(this->comm());
            _RB_solution[time_level-1]->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
            _RB_solution[time_level-1] -> zero();
            _RB_solution[time_level-1] -> close();
            set_time_step(time_level);

            *old_local_solution = *current_local_solution;
            
            this->matrix->close();
            this -> matrix -> zero();
            this -> rhs -> zero();
            {
      // We assume that the truth assembly has been attached to the system
                
                if (time_level==1)
                {
                   file_theta_objects.open("M_theta_A_theta_param_min.m");
                   file_theta_objects << "thetas_param_min = [" << std::endl;
                }
                for (unsigned int q=0; q<Q_m; q++)
                {
                        matrix->add(1./dt * trans_theta_expansion.eval_M_theta(q,mu), *get_M_q(q));
                }
            //add_scaled_mass_matrix(1./dt,matrix);
                std::unique_ptr<NumericVector<Number>> temp_vec2 = NumericVector<Number>::build(this->comm());
                temp_vec2->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);

                for (unsigned int q=0; q<Q_m; q++)
                {
                    get_M_q(q)->vector_mult(*temp_vec2, *current_local_solution);
                    rhs->add(1./dt * trans_theta_expansion.eval_M_theta(q,mu), *temp_vec2);
                    if (time_level==1)
                      file_theta_objects << trans_theta_expansion.eval_M_theta(q,mu) << std::endl;
                    if (time_level == 1)
                        M_mu->add(trans_theta_expansion.eval_M_theta(q,mu),*get_M_q(q));
                    //if (trans_theta_expansion.eval_M_theta(q,mu) != 1.0)
                      //  libMesh::out << "q_m = " << q << " M_theta diff = "<< trans_theta_expansion.eval_M_theta(q,mu) - 1.0 << std::endl;
                }
            //mass_matrix_scaled_matvec(1./dt, *rhs, *current_local_solution);
      
            std::unique_ptr<NumericVector<Number>> temp_vec = NumericVector<Number>::build(this->comm());
            temp_vec->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      
            for (unsigned int q_a=0; q_a<Q_a; q_a++)
            {
              matrix->add(euler_theta*get_rb_theta_expansion().eval_A_theta(q_a,mu), *get_Aq(q_a));
                
              if (time_level==1)
                file_theta_objects << get_rb_theta_expansion().eval_A_theta(q_a,mu) << std::endl;
              get_Aq(q_a)->vector_mult(*temp_vec, *current_local_solution);
              temp_vec->scale( -(1.-euler_theta)*get_rb_theta_expansion().eval_A_theta(q_a,mu) );
              
              rhs->add(*temp_vec);
              if (time_level == 1)
                  A_mu -> add(get_rb_theta_expansion().eval_A_theta(q_a,mu),*get_Aq(q_a));
              //if (get_rb_theta_expansion().eval_A_theta(q_a,mu) != 1.0)
                //        libMesh::out << "q_a = " << q_a << " A_theta diff = "<< get_rb_theta_expansion().eval_A_theta(q_a,mu)- 1.0 << std::endl;
            }
            if (time_level==1)
            {
              file_theta_objects << "];";
              file_theta_objects.close();
            }
            if (time_level==1) matrix->print_matlab("matrix_mu_debug_2020_09_21.m");

            for (unsigned int q_f=0; q_f<Q_f; q_f++)
            {
              *temp_vec = *get_Fq(q_f);
              if (dynamic_cast<DwarfElephantRBEvaluationTransient&>(get_rb_evaluation())._RB_RFA)
              {
                  if (q_f == 0)
                      temp_vec->scale( get_control(get_time_step())*get_rb_theta_expansion().eval_F_theta(q_f, mu));
                  else // To use EIM approximation of the heat source
                      {
                        temp_vec->scale( get_control(get_time_step())*get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu));
                        //temp_vec->scale( get_control(get_time_step()));
                        //Real F_theta_value = get_control(get_time_step())*get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu);
                        //int test = 0;
                      }
                  //else if (q_f == 1)
                  //{   
                  //    _nonAffineF->close();
                  //    *temp_vec=*_nonAffineF;
                  //} 
                  //else
                  //    break;
              }
              else
                  temp_vec->scale( get_control(get_time_step())*get_rb_theta_expansion().eval_F_theta(q_f, mu));
              
              rhs->add(*temp_vec);
              std::ostringstream rhs_name;
              //rhs_name << "rhs_" << q_f << ".m";
              //if (time_level == 1) rhs->print_matlab(rhs_name.str());
              
              //if (get_rb_theta_expansion().eval_F_theta(q_f,mu) != 1.0)
                //        libMesh::out << "q_f = " << q_f << " F_theta diff = "<< get_rb_theta_expansion().eval_F_theta(q_f,mu) - 1.0 << std::endl;
            }

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
            FullFEsolution[time_level-1]->add(*solution);
            // load projection error into column _k of temporal_data matrix
            //solution->print_matlab("FE_solution_"+ std::to_string(time_level)+".m");
            if (compute_truth_projection_error)
                set_error_temporal_data();
            
            if ((write_interval > 0) && (time_level%write_interval == 0))
            {
                libMesh::out << std::endl << "Truth solve, plotting time step " << time_level << std::endl;

                std::ostringstream file_name;

                //file_name << "temp_r0_" << mu.get_value("mu_0") << "_l0_"<< mu.get_value("mu_1") << "_mesh_" << mesh_index << "_";
                //file_name << std::setw(3)
                //    << std::setprecision(0)
                //    << std::setfill('0')
                //    << std::right
                //    << time_level << ".e";
                file_name << "FullFEtruth.e"; 
                #ifdef LIBMESH_HAVE_EXODUS_API
                ExodusII_IO(get_mesh()).write_equation_systems (file_name.str(),
                                                          this->get_equation_systems());
                #endif 
                /*std::ostringstream file_name2;
                file_name2 << "out_"
                        << std::setprecision(0)
                        << std::setfill('0')
                        << std::right
                        << time_level
                        << ".vtu";
                VTKIO(get_mesh()).write_equation_systems(file_name2.str(), this->get_equation_systems()); */
            }
            inner_product_matrix->vector_mult(*temp_vec_L2_norm,*solution);
            temperature_L2_norm_sq = temp_vec_L2_norm->dot(*solution);
            temperature_L2_norm_time_integral += sqrt(temperature_L2_norm_sq)*dt;
            temp_vec_L2_norm->zero();
            
           
            //*(this->solution) = *_temperature_soln[time_step-1];
            //VTKIO(get_mesh()).write_equation_systems("test_temp_" + std::to_string(time_step) + ".vtu", this->get_equation_systems());
            for (unsigned int node = 0; node < this->n_local_dofs(); node++) // could be parallelized
            {
                Real integral_prev_step[] = {0};
                std::vector<unsigned int> index = {_arrhenius_integral->first_local_index() + node};
                _arrhenius_integral->get(index,integral_prev_step);
                if (time_level == 1)
                    _arrhenius_integral->set(_arrhenius_integral->first_local_index() + node,integral_prev_step[0] - 0.5*dt*A_freq_factor*exp(-E_act/(R_ideal_gas * ((*solution)(_arrhenius_integral->first_local_index() + node) + 310.15) )));
                else if (time_level < n_time_steps)
                    _arrhenius_integral->set(_arrhenius_integral->first_local_index() + node,integral_prev_step[0] - dt*A_freq_factor*exp(-E_act/(R_ideal_gas * ((*solution)(_arrhenius_integral->first_local_index() + node) + 310.15))));
                else
                    _arrhenius_integral->set(_arrhenius_integral->first_local_index() + node,integral_prev_step[0] - 0.5*dt*A_freq_factor*exp(-E_act/(R_ideal_gas * ((*solution)(_arrhenius_integral->first_local_index() + node) + 310.15))));
            }
        }

    // Set reuse_preconditioner back to false for subsequent solves.
      linear_solver->reuse_preconditioner(false);
      for (unsigned int node = 0; node < this->n_local_dofs(); node++) // could be parallelized
          {
              if ((*_tissue_damage)(_tissue_damage->first_local_index() + node))
                  if (exp((*_arrhenius_integral)(_tissue_damage->first_local_index() + node)) >= exp(-1.0))
                      _tissue_damage->set(_tissue_damage->first_local_index() + node,0.0);
          }
      _tissue_damage->close();
      this->get_equation_systems().get_system("aux0").solution->close();
      *(this->get_equation_systems().get_system("aux0").solution) = *_tissue_damage;
      std::ostringstream tissue_dmg_file_name;
      tissue_dmg_file_name  << "tissue_damage_r0_" << mu.get_value("mu_0") << "_l0_" << mu.get_value("mu_1") << "_mesh_" << mesh_index << ".vtu"; 
      //VTKIO(get_mesh()).write_equation_systems(tissue_dmg_file_name.str(), this->get_equation_systems());
      //if (this->processor_id() == 0)
      //{
      //  std::ostringstream outfilename;
      //  outfilename << "Temperature_L2_norm_time_integral_r0_" << mu.get_value("mu_0") << "_l0_" << mu.get_value("mu_1") << "_mesh_" << mesh_index << ".txt"; 
      //  std::ofstream outfile;
      //  outfile.open(outfilename.str());
      //  outfile << temperature_L2_norm_time_integral;
      //  outfile.close();
      //}
      
      for (unsigned int avg_node_id = 0; avg_node_id < _temp_averaging_node_ids.size(); avg_node_id++)
      {
          if (solution->first_local_index() <= _temp_averaging_node_ids[avg_node_id] && _temp_averaging_node_ids[avg_node_id] <= solution->first_local_index() + this->n_local_dofs())
              _needle_neighbourhood_temp->set(solution->first_local_index() + avg_node_id,(*solution)(solution->first_local_index() + avg_node_id));
      }
      inner_product_matrix->vector_mult(*temp_vec_L2_norm,*_needle_neighbourhood_temp);
      temperature_L2_norm_sq = temp_vec_L2_norm->dot(*_needle_neighbourhood_temp);
      temperature_L2_norm_time_integral = sqrt(temperature_L2_norm_sq);
      //if (this->processor_id() == 0)
      //{
      //  std::ostringstream outfilename;
      //  outfilename << "Temperature_RMS_aroundNeedle_r0_" << mu.get_value("mu_0") << "_l0_" << mu.get_value("mu_1") << "_mesh_" << mesh_index << ".txt"; 
      //  std::ofstream outfile;
      //  outfile.open(outfilename.str());
      //  outfile << temperature_L2_norm_time_integral;
      //  outfile.close();
      //}
      // Compute RB solution and RB_v_FE error in energy norm here
      // Create sparse matrices to hold assembled mass matrix and A matrix
      /*
      DwarfElephantRBEvaluationTransient & trans_rb_eval = dynamic_cast<DwarfElephantRBEvaluationTransient&>(get_rb_evaluation());
      Number error_energy_norm;
      get_rb_evaluation().set_parameters(mu);
      std::unique_ptr<NumericVector<Number>> temp_vec_error = NumericVector<Number>::build(this->comm());
      temp_vec_error->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      temp_vec_error->zero();
      for (int N = 1; N <= get_rb_evaluation().get_n_basis_functions(); N++)
      {
          

          online_error_bound_v_N[N-1] = get_rb_evaluation().rb_solve(N);
          //this->load_rb_solution();
          error_energy_norm = 0;
          for (unsigned int time_level=1; time_level<=n_time_steps; time_level++)
          {
              temp_vec_error->zero();
              _RB_solution[time_level-1]->zero();
              for (int i = 0; i < N; i++)
              {
                  _RB_solution[time_level-1]->add((trans_rb_eval.RB_temporal_solution_data[time_level])(i),get_rb_evaluation().get_basis_function(i));     
              }
              //  *_RB_solution[time_level-1]-=*FullFEsolution[time_level-1];
              _RB_solution[time_level-1]->add(-1.,*(FullFEsolution[time_level-1].get()));
              A_mu->vector_mult(*temp_vec_error,*(_RB_solution[time_level-1].get()));
              error_energy_norm += temp_vec_error -> dot(*(_RB_solution[time_level-1].get()));
          }
          error_energy_norm = error_energy_norm*dt;
          temp_vec_error -> zero();
          M_mu -> vector_mult(*temp_vec_error,*(_RB_solution[n_time_steps-1].get()));
          error_energy_norm += temp_vec_error -> dot(*(_RB_solution[n_time_steps-1].get()));
          error_energy_norm = std::sqrt(error_energy_norm);
          error_norm_sum_v_N[N-1] = error_energy_norm/static_cast<double>(num_param_values);
          // Write out the error energy norm for the particular value of N to file
      }*/
  
  }

  void FE_solve_steady(RBParameters mu)
  {
      std::string exec_string = "parallel";
      const unsigned int Q_a = get_rb_theta_expansion().get_n_A_terms();
      const unsigned int Q_f = get_rb_theta_expansion().get_n_F_terms();
      unsigned int M = 1;
      if (dynamic_cast<DwarfElephantRBEvaluationTransient&>(get_rb_evaluation())._RB_RFA)
          M = get_rb_theta_expansion().get_n_F_terms()/dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).num_subdomains;
      
      std::unique_ptr<SparseMatrix<Number>> A_mu;
      
      A_mu = SparseMatrix<Number>::build(this->comm());
      this->get_dof_map().attach_matrix(*A_mu);
      A_mu->init();
      A_mu->zero();
      A_mu->close();

      std::unique_ptr<NumericVector<Number>> FullFEsolution = NumericVector<Number>::build(this->comm());
      FullFEsolution->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      FullFEsolution->zero();
      FullFEsolution->close();

      this->matrix->close();
      this -> matrix -> zero();
      this -> rhs -> zero();
      libMesh::out << std::endl;
      for (unsigned int q_a=0; q_a<Q_a; q_a++)
      {
          matrix->add(get_rb_theta_expansion().eval_A_theta(q_a,mu), *get_Aq(q_a));
          A_mu -> add(get_rb_theta_expansion().eval_A_theta(q_a,mu),*get_Aq(q_a));
          libMesh::out << "ATheta " << q_a << " = " << get_rb_theta_expansion().eval_A_theta(q_a,mu) << std::endl;
      }
      matrix->print_matlab("A_mu_" + exec_string + ".m");
      std::unique_ptr<NumericVector<Number>> temp_vec = NumericVector<Number>::build(this->comm());
      temp_vec->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      temp_vec->zero();
      for (unsigned int q_f=0; q_f<Q_f; q_f++)
      {
          *temp_vec = *get_Fq(q_f);/*
          if (q_f == 0)
          {
              temp_vec->scale( get_rb_theta_expansion().eval_F_theta(q_f, mu));
              libMesh::out << "FTheta " << q_f << " = " << get_rb_theta_expansion().eval_F_theta(q_f,mu) << std::endl;
          }
          else 
          {
              temp_vec->scale(get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu) * dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu));
              Real F_theta_value = get_rb_theta_expansion().eval_F_theta(((q_f-1)%M+1), mu)*dynamic_cast<Geom3DTransientRBThetaExpansion&>(get_rb_theta_expansion()).subdomain_jac_rbthetas[(q_f-1)/M]->evaluate(mu);
              int test = 0;
              libMesh::out << "FTheta " << q_f << " = " << F_theta_value << std::endl;
          }*/
          temp_vec->scale( get_rb_theta_expansion().eval_F_theta(q_f, mu));
          rhs->add(*temp_vec);
          libMesh::out << "FTheta " << q_f << " = " << get_rb_theta_expansion().eval_F_theta(q_f,mu) << std::endl;
      }
      
//      rhs->print_matlab("rhs_matlab_script_" + exec_string + ".m");
      print_matrix(matrix, "test_A_matrix.txt");

      print_vector(rhs, "test_f_vector.txt");
/*
      std::ofstream outfile;
      outfile.open("/home/2014-0004_focal_therapy/PhDs/AdapTT/Nikhil/DwarfElephant/rhs_parallel_node_id_" + std::to_string(this->comm().rank()) + ".txt");
      for (unsigned int i = rhs->first_local_index(); i < rhs->last_local_index(); i++)
      {
          outfile << i << " " << (*rhs)(i) << endl;
      }
      outfile.close();*/
      this->matrix->close();
      this->rhs->close();
      this->matrix->print_matlab("steady_solve_stiffness_matrix.m");  
      // truth_assembly assembles into matrix and rhs, so use those for the solve
      solve_for_matrix_and_rhs(*get_linear_solver(), *matrix, *rhs);
      // The matrix doesn't change at each timestep, so we
      // can set reuse_preconditioner == true
      linear_solver->reuse_preconditioner(true);

      if (assert_convergence)
      {
          check_convergence(*get_linear_solver());
      }
      FullFEsolution->add(*solution);
      solution->print_matlab("steady_soln.m");
            
      libMesh::out << std::endl << "Plot Steady State Solution" << std::endl;

      std::ostringstream file_name;

      file_name << "temp_r0_" << mu.get_value("mu_0") << "_l0_"<< mu.get_value("mu_1") << "_steady.e";
 
      #ifdef LIBMESH_HAVE_EXODUS_API
      ExodusII_IO(get_mesh()).write_equation_systems (file_name.str(),
                                                          this->get_equation_systems());
      #endif
      VTKIO(get_mesh()).write_equation_systems(file_name.str(), this->get_equation_systems());
  }

  void computeTissueDamage(unsigned int _num_online_solves, std::vector<std::vector<Real>> _online_mu_vec)
  {
    
      RBParameters _rb_online_mu;
      DwarfElephantRBEvaluationTransient & trans_rb_eval = dynamic_cast<DwarfElephantRBEvaluationTransient&>(get_rb_evaluation());
      unsigned int _online_N = 0;
      const unsigned int n_time_steps = get_n_time_steps();
      const Real euler_theta = get_euler_theta();
      Real dt = get_delta_t();
      Real A_freq_factor = 3.1e98;
      Real E_act = 6.28e5;
      Real R_ideal_gas = 8.314;
      
      std::unique_ptr<NumericVector<Number>> _arrhenius_integral = NumericVector<Number>::build(this->comm());
      _arrhenius_integral->init(this->n_dofs(),this->n_local_dofs(),false,PARALLEL);
      _arrhenius_integral->zero();
      
      _tissue_damage = NumericVector<Number>::build(this->comm());
      _tissue_damage->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
      _tissue_damage->zero();
      _tissue_damage->add(1.0);
      
      _temperature_soln.resize(n_time_steps);
      
      for (unsigned int _i_online_solve = 0; _i_online_solve < _num_online_solves; _i_online_solve++)
      {
          for (unsigned int  _q = 0; _q < _online_mu_vec[_i_online_solve].size(); _q++)
          {
              std::string  _mu_name = "mu_" + std::to_string(_q);
              _rb_online_mu.set_value(_mu_name, _online_mu_vec[_i_online_solve][_q]);
      
              this->set_n_time_steps(n_time_steps);
              this->set_delta_t(dt);
              this->set_euler_theta(euler_theta);
              this->set_time_step(0);
          }
          
          trans_rb_eval.set_parameters(_rb_online_mu);
          trans_rb_eval.print_parameters();
  
          if(_online_N==0)
              _online_N = this->get_rb_evaluation().get_n_basis_functions();
          
          std::cout << "Number of basis functions: " << _online_N;
          //Real _error_bound_final_time = trans_rb_eval.rb_solve(_online_N); 
          //this->load_rb_solution();
          for (unsigned int time_step = 1; time_step <= n_time_steps; time_step++)
          {
            if (_i_online_solve == 0)
            {
                _temperature_soln[time_step - 1] = NumericVector<Number>::build(this->comm());
                _temperature_soln[time_step - 1]->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
            }
            _temperature_soln[time_step - 1]->zero();
            for (int i = 0; i < _online_N; i++)
            {
                _temperature_soln[time_step-1]->add((trans_rb_eval.RB_temporal_solution_data[time_step])(i),get_rb_evaluation().get_basis_function(i));     
            }
            _temperature_soln[time_step-1]->add(310.15); // Add the body core temperature to the solution
            //*(this->solution) = *_temperature_soln[time_step-1];
            //VTKIO(get_mesh()).write_equation_systems("test_temp_" + std::to_string(time_step) + ".vtu", this->get_equation_systems());
            for (unsigned int node = 0; node < this->n_local_dofs(); node++) // could be parallelized
            {
                Real integral_prev_step[] = {0};
                std::vector<unsigned int> index = {_arrhenius_integral->first_local_index() + node};
                _arrhenius_integral->get(index,integral_prev_step);
                if (time_step == 1)
                    _arrhenius_integral->set(_arrhenius_integral->first_local_index() + node,integral_prev_step[0] - 0.5*dt*A_freq_factor*exp(-E_act/(R_ideal_gas * (*_temperature_soln[time_step - 1])(_arrhenius_integral->first_local_index() + node))));
                else if (time_step < n_time_steps)
                    _arrhenius_integral->set(_arrhenius_integral->first_local_index() + node,integral_prev_step[0] - dt*A_freq_factor*exp(-E_act/(R_ideal_gas * (*_temperature_soln[time_step - 1])(_arrhenius_integral->first_local_index() + node))));
                else
                    _arrhenius_integral->set(_arrhenius_integral->first_local_index() + node,integral_prev_step[0] - 0.5*dt*A_freq_factor*exp(-E_act/(R_ideal_gas * (*_temperature_soln[time_step - 1])(_arrhenius_integral->first_local_index() + node))));
            }
              
          }
          this->solution->zero();
          for (unsigned int node = 0; node < this->n_local_dofs(); node++) // could be parallelized
          {
              if ((*_tissue_damage)(_tissue_damage->first_local_index() + node))
                  //_tissue_damage->set(node,(*_arrhenius_integral)(node));
                  if (exp((*_arrhenius_integral)(_tissue_damage->first_local_index() + node)) >= exp(-1.0))
                      _tissue_damage->set(_tissue_damage->first_local_index() + node,0.0);
          }
      }
      this->solution->close();
      _tissue_damage->close();
      *(this->solution) = *_tissue_damage;
      VTKIO(get_mesh()).write_equation_systems("tissuedamage.vtu", this->get_equation_systems());
  }
  
  NumericVector<Number> * get_nonAffineF() // To test error caused by EIM in the RB solution
  {
    return _nonAffineF.get();
  }
  
    void allocate_RB_error_structures() // To test against EIM example from Martin's publication
  {
    _nonAffineF = NumericVector<Number>::build(this->comm());
    _nonAffineF->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
    _nonAffineF->zero();
  }
  
  // Type of the parent
  typedef TransientRBConstruction Parent;

  virtual void clear() override;

  virtual void allocate_data_structures() override;

  // Initialize data structure
  virtual void init_data() override;
  void write_num_subdomains()
  {
    
    std::ofstream num_subdomains_file("EIM_num_subdomains.txt",std::ofstream::out);
    num_subdomains_file << this->get_mesh().n_subdomains() << std::endl;
    num_subdomains_file.close();
  }

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
  
  virtual void compute_Fq_representor_innerprods(bool compute_inner_products=true) override;
  
  void process_mem_usage(double& vm_usage, double& resident_set);

  unsigned int u_var;

  bool parameter_dependent_IC;
  
  std::vector<Number> error_norm_sum_v_N;
  std::vector<Real> online_error_bound_v_N;
  DwarfElephantRBCustomTransientAssemblyExpansion Dummy_TransientRBAssemblyExpansion;
  //QM_10 Dummy_TransientRBAssemblyExpansion;
  //QM_0 Dummy_TransientRBAssemblyExpansion;
  //debugAssemblyExpansion Dummy_TransientRBAssemblyExpansion;
  std::unique_ptr<NumericVector<Number>> _nonAffineF;
  std::vector<std::unique_ptr<NumericVector<Number>>> _temperature_soln;
  std::unique_ptr<NumericVector<Number>> _tissue_damage;
  //debugAssemblyExpansion Dummy_TransientRBAssemblyExpansion;
private:
  /**
   * Vector storing the Q_ic vectors in the affine decomposition
   * of the initial conditions.
   */
  std::vector<std::unique_ptr<NumericVector<Number>>> IC_q_vector;
  std::vector<std::unique_ptr<NumericVector<Number>>> non_dirichlet_IC_q_vector;
};


#endif // DWARFELEPHANTRBCLASSESTRANSIENT_H
