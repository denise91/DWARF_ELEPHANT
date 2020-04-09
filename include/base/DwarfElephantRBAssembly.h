/**
 * This Assembly class is required to cache the matrix and vector entries
 * introdued by the Dirichlet BCs with respect to the desired separation.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// libMesh includes
#include "libmesh/sparse_matrix.h"
#include "libmesh/numeric_vector.h"

// MOOSE includes
#include "MooseTypes.h"

///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  template <typename T> class SparseMatrix;
  template <typename T> class NumericVector;
}

class SystemBase;

///This Assembly class is required to cache the matrix and vector entries introdued by the Dirichlet BCs with respect to the desired separation.
class DwarfElephantRBAssembly
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBAssembly(SystemBase & sys, THREAD_ID tid);
  virtual ~DwarfElephantRBAssembly();

  /* Methods */
  void cacheJacobianContribution(numeric_index_type i, numeric_index_type j, Real value, unsigned int _id);
  void cacheMassMatrixContribution(numeric_index_type i, numeric_index_type j, Real value, unsigned int _id);
  void cacheResidual(numeric_index_type i, Real value, unsigned int _id);
  void cacheOutput(numeric_index_type i, Real value, unsigned int _id);

  void setCachedResidual(NumericVector<Number> & _residual, unsigned int _id);
  void setCachedOutput(NumericVector<Number> & _output, unsigned int _id);
  void setCachedJacobianContributions(SparseMatrix<Number> & _jacobian, unsigned int _id);
  void setCachedMassMatrixContributions(SparseMatrix<Number> & _mass, unsigned int _id);

  void setCachedJacobianContributionSize(unsigned int _size);
  void setCachedMassContributionSize(unsigned int _size);
  void setCachedResidualContributionSize(unsigned int _size);
  void setCachedOutputContributionSize(unsigned int _size);

  // void clearCachedJacobianContributions();
  // void clearCachedMassMatrixContributions();
  // void clearCachedResidualContributions();
  // void clearCachedOutputContributions();

//--------------------------------PROTECTED---------------------------------
protected:
  /* Attributes */
  SystemBase & _sys;
  THREAD_ID _tid;

  std::vector<std::vector<numeric_index_type>> _cached_jacobian_contribution_rows;
  std::vector<std::vector<numeric_index_type>> _cached_jacobian_contribution_cols;
  std::vector<std::vector<Real>> _cached_jacobian_contribution_vals;

  std::vector<std::vector<numeric_index_type>> _cached_mass_contribution_rows;
  std::vector<std::vector<numeric_index_type>> _cached_mass_contribution_cols;
  std::vector<std::vector<Real>> _cached_mass_contribution_vals;

  std::vector<std::vector<numeric_index_type>> _cached_residual_contribution_rows;
  std::vector<std::vector<Real>> _cached_residual_contribution_vals;

  std::vector<std::vector<numeric_index_type>> _cached_output_contribution_rows;
  std::vector<std::vector<Real>> _cached_output_contribution_vals;
};
