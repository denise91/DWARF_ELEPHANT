/**
 * This Assembly class is required to cache the matrix and vector entries
 * introdued by the Dirichlet BCs with respect to the desired separation.
 */

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBAssembly.h"


DwarfElephantRBAssembly::DwarfElephantRBAssembly(SystemBase & sys, THREAD_ID tid)
  : //Assembly(sys, tid),
    _sys(sys),
    _tid(tid)
{
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBAssembly::~DwarfElephantRBAssembly()
{
}

///-------------------------------------------------------------------------
// The boundary entries of the residuals need to be cached to be set after
// multiplication of the parameter independent and dependent part are completed.
void
DwarfElephantRBAssembly::cacheResidual(numeric_index_type i, Real value)
{
  _cached_residual_contribution_rows.push_back(i);
  _cached_residual_contribution_vals.push_back(value);
}

// The boundary entries of the outputs need to be cached to be set after
// multiplication of the parameter independent and dependent part are completed.
void
DwarfElephantRBAssembly::cacheOutput(numeric_index_type i, Real value)
{
  _cached_output_contribution_rows.push_back(i);
  _cached_output_contribution_vals.push_back(value);
}

void
DwarfElephantRBAssembly::setCachedResidual(NumericVector<Number> & _residual)
{
  _residual.close();

  for (unsigned int i = 0; i < _cached_residual_contribution_vals.size(); ++i){
    _residual.set(_cached_residual_contribution_rows[i], _cached_residual_contribution_vals[i]);
  }
//  clearCachedResidualContributions(); Commented out for debugging purposes. This line causes the dirichlet BC to not be applied to all F vectors (in case there are multiple). This should also be the cause for the dirichlet BCs going haywire for multiple A matrices being affected by dirichlet BCs.
}

void
DwarfElephantRBAssembly::setCachedOutput(NumericVector<Number> & _output)
{
  _output.close();

  for (unsigned int i = 0; i < _cached_output_contribution_vals.size(); ++i)
    _output.set(_cached_output_contribution_rows[i], _cached_output_contribution_vals[i]);

  clearCachedOutputContributions();
}

// The boundary entries of the stiffness matrices need to be cached to be set
// after multiplication of the parameter independent and dependent part are
// completed.
void
DwarfElephantRBAssembly::cacheJacobianContribution(numeric_index_type i, numeric_index_type j, Real value)
{
  _cached_jacobian_contribution_rows.push_back(i);
  _cached_jacobian_contribution_cols.push_back(j);
  _cached_jacobian_contribution_vals.push_back(value);
}

// The boundary entries of the mass matrices need to be cached to be set
// after multiplication of the parameter independent and dependent part are
// completed.
void
DwarfElephantRBAssembly::cacheMassMatrixContribution(numeric_index_type i, numeric_index_type j, Real value)
{
  _cached_mass_contribution_rows.push_back(i);
  _cached_mass_contribution_cols.push_back(j);
  _cached_mass_contribution_vals.push_back(value);
}


void
DwarfElephantRBAssembly::setCachedJacobianContributions(SparseMatrix<Number> & _jacobian)
{
  _jacobian.close();
  _jacobian.zero_rows(_cached_jacobian_contribution_rows, 0.);

  for (unsigned int i = 0; i < _cached_jacobian_contribution_vals.size(); i++)
    _jacobian.set(_cached_jacobian_contribution_rows[i],
                  _cached_jacobian_contribution_cols[i],
                  _cached_jacobian_contribution_vals[i]);

  clearCachedJacobianContributions(); // Commented out for EIM example in Martin's publication
}

void
DwarfElephantRBAssembly::setCachedMassMatrixContributions(SparseMatrix<Number> & _mass)
{
  _mass.close();
  _mass.zero_rows(_cached_mass_contribution_rows);

  for (unsigned int i = 0; i < _cached_mass_contribution_vals.size(); ++i)
    _mass.set(_cached_mass_contribution_rows[i],
              _cached_mass_contribution_cols[i],
              _cached_mass_contribution_vals[i]);

  clearCachedMassMatrixContributions();
}

void
DwarfElephantRBAssembly::clearCachedJacobianContributions()
{
    unsigned int orig_size = _cached_jacobian_contribution_rows.size();

    _cached_jacobian_contribution_rows.clear();
    _cached_jacobian_contribution_cols.clear();
    _cached_jacobian_contribution_vals.clear();

    // It's possible (though massively unlikely) that clear() will
    // change the capacity of the vectors, so let's be paranoid and
    // explicitly reserve() the same amount of memory to avoid multiple
    // push_back() induced allocations.  We reserve 20% more than the
    // original size that was cached to account for variations in the
    // number of BCs assigned to each thread (for when the Jacobian
    // contributions are computed threaded).
    _cached_jacobian_contribution_rows.reserve(1.2 * orig_size);
    _cached_jacobian_contribution_cols.reserve(1.2 * orig_size);
    _cached_jacobian_contribution_vals.reserve(1.2 * orig_size);
}

void
DwarfElephantRBAssembly::clearCachedMassMatrixContributions()
{
    unsigned int orig_size = _cached_mass_contribution_rows.size();

    _cached_mass_contribution_rows.clear();
    _cached_mass_contribution_cols.clear();
    _cached_mass_contribution_vals.clear();

    // It's possible (though massively unlikely) that clear() will
    // change the capacity of the vectors, so let's be paranoid and
    // explicitly reserve() the same amount of memory to avoid multiple
    // push_back() induced allocations.  We reserve 20% more than the
    // original size that was cached to account for variations in the
    // number of BCs assigned to each thread (for when the Jacobian
    // contributions are computed threaded).
    _cached_mass_contribution_rows.reserve(1.2 * orig_size);
    _cached_mass_contribution_cols.reserve(1.2 * orig_size);
    _cached_mass_contribution_vals.reserve(1.2 * orig_size);
}

void
DwarfElephantRBAssembly::clearCachedResidualContributions()
{
    unsigned int orig_size = _cached_residual_contribution_rows.size();

    _cached_residual_contribution_rows.clear();
    _cached_residual_contribution_vals.clear();

    // It's possible (though massively unlikely) that clear() will
    // change the capacity of the vectors, so let's be paranoid and
    // explicitly reserve() the same amount of memory to avoid multiple
    // push_back() induced allocations.  We reserve 20% more than the
    // original size that was cached to account for variations in the
    // number of BCs assigned to each thread (for when the Jacobian
    // contributions are computed threaded).
    _cached_residual_contribution_rows.reserve(1.2 * orig_size);
    _cached_residual_contribution_vals.reserve(1.2 * orig_size);
}

void
DwarfElephantRBAssembly::clearCachedOutputContributions()
{
    unsigned int orig_size = _cached_output_contribution_rows.size();

    _cached_output_contribution_rows.clear();
    _cached_output_contribution_vals.clear();

    // It's possible (though massively unlikely) that clear() will
    // change the capacity of the vectors, so let's be paranoid and
    // explicitly reserve() the same amount of memory to avoid multiple
    // push_back() induced allocations.  We reserve 20% more than the
    // original size that was cached to account for variations in the
    // number of BCs assigned to each thread (for when the Jacobian
    // contributions are computed threaded).
    _cached_output_contribution_rows.reserve(1.2 * orig_size);
    _cached_output_contribution_vals.reserve(1.2 * orig_size);
}
