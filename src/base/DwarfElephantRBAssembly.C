/**
 * This Assembly class is required to cache the matrix and vector entries
 * introdued by the Dirichlet BCs with respect to the desired separation.
 */

//---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBAssembly.h"


DwarfElephantRBAssembly::DwarfElephantRBAssembly(SystemBase & sys, THREAD_ID tid)
  : //Assembly(sys, tid),
    _sys(sys),
    _tid(tid)
{
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantRBAssembly::~DwarfElephantRBAssembly()
{
}

//-------------------------------------------------------------------------
// The boundary entries of the residuals need to be cached to be set after
// multiplication of the parameter independent and dependent part are completed.
void
DwarfElephantRBAssembly::cacheResidual(numeric_index_type i, Real value, unsigned int _id)
{
  _cached_residual_contribution_rows[_id].push_back(i);
  _cached_residual_contribution_vals[_id].push_back(value);
}

// The boundary entries of the outputs need to be cached to be set after
// multiplication of the parameter independent and dependent part are completed.
void
DwarfElephantRBAssembly::cacheOutput(numeric_index_type i, Real value, unsigned int _id)
{
  _cached_output_contribution_rows[_id].push_back(i);
  _cached_output_contribution_vals[_id].push_back(value);
}

void
DwarfElephantRBAssembly::setCachedResidual(NumericVector<Number> & _residual, unsigned int _id)
{
  _residual.close();

  for (unsigned int i = 0; i < _cached_residual_contribution_vals[_id].size(); ++i){
    _residual.set(_cached_residual_contribution_rows[_id][i], _cached_residual_contribution_vals[_id][i]);
  }

  // clearCachedResidualContributions();
}

void
DwarfElephantRBAssembly::setCachedOutput(NumericVector<Number> & _output, unsigned int _id)
{
  _output.close();

  for (unsigned int i = 0; i < _cached_output_contribution_vals.size(); ++i)
    _output.set(_cached_output_contribution_rows[_id][i], _cached_output_contribution_vals[_id][i]);

  // clearCachedOutputContributions();
}

// The boundary entries of the stiffness matrices need to be cached to be set
// after multiplication of the parameter independent and dependent part are
// completed.
void
DwarfElephantRBAssembly::cacheJacobianContribution(numeric_index_type i, numeric_index_type j, Real value, unsigned int _id)
{
  _cached_jacobian_contribution_rows[_id].push_back(i);
  _cached_jacobian_contribution_cols[_id].push_back(j);
  _cached_jacobian_contribution_vals[_id].push_back(value);
}

// The boundary entries of the mass matrices need to be cached to be set
// after multiplication of the parameter independent and dependent part are
// completed.
void
DwarfElephantRBAssembly::cacheMassMatrixContribution(numeric_index_type i, numeric_index_type j, Real value, unsigned int _id)
{
  _cached_mass_contribution_rows[_id].push_back(i);
  _cached_mass_contribution_cols[_id].push_back(j);
  _cached_mass_contribution_vals[_id].push_back(value);
}


void
DwarfElephantRBAssembly::setCachedJacobianContributions(SparseMatrix<Number> & _jacobian, unsigned int _id)
{
  _jacobian.close();
  _jacobian.zero_rows(_cached_jacobian_contribution_rows[_id], 0.0);

  for (unsigned int i = 0; i < _cached_jacobian_contribution_vals[_id].size(); i++)
    _jacobian.set(_cached_jacobian_contribution_rows[_id][i],
                  _cached_jacobian_contribution_cols[_id][i],
                  _cached_jacobian_contribution_vals[_id][i]);

  // clearCachedJacobianContributions();
}


void
DwarfElephantRBAssembly::setCachedMassMatrixContributions(SparseMatrix<Number> & _mass,unsigned int _id)
{
  _mass.close();
  _mass.zero_rows(_cached_mass_contribution_rows[_id],0.0);

  for (unsigned int i = 0; i < _cached_mass_contribution_vals[_id].size(); ++i)
    _mass.set(_cached_mass_contribution_rows[_id][i],
              _cached_mass_contribution_cols[_id][i],
              _cached_mass_contribution_vals[_id][i]);
  // clearCachedMassMatrixContributions();
}

// void
// DwarfElephantRBAssembly::clearCachedJacobianContributions()
// {
//     unsigned int orig_size = _cached_jacobian_contribution_rows.size();
//
//     _cached_jacobian_contribution_rows.clear();
//     _cached_jacobian_contribution_cols.clear();
//     _cached_jacobian_contribution_vals.clear();
//
//     // It's possible (though massively unlikely) that clear() will
//     // change the capacity of the vectors, so let's be paranoid and
//     // explicitly reserve() the same amount of memory to avoid multiple
//     // push_back() induced allocations.  We reserve 20% more than the
//     // original size that was cached to account for variations in the
//     // number of BCs assigned to each thread (for when the Jacobian
//     // contributions are computed threaded).
//     _cached_jacobian_contribution_rows.reserve(1.2 * orig_size);
//     _cached_jacobian_contribution_cols.reserve(1.2 * orig_size);
//     _cached_jacobian_contribution_vals.reserve(1.2 * orig_size);
// }
//
// void
// DwarfElephantRBAssembly::clearCachedMassMatrixContributions()
// {
//     unsigned int orig_size = _cached_mass_contribution_rows.size();
//
//     _cached_mass_contribution_rows.clear();
//     _cached_mass_contribution_cols.clear();
//     _cached_mass_contribution_vals.clear();
//
//     // It's possible (though massively unlikely) that clear() will
//     // change the capacity of the vectors, so let's be paranoid and
//     // explicitly reserve() the same amount of memory to avoid multiple
//     // push_back() induced allocations.  We reserve 20% more than the
//     // original size that was cached to account for variations in the
//     // number of BCs assigned to each thread (for when the Jacobian
//     // contributions are computed threaded).
//     _cached_mass_contribution_rows.reserve(1.2 * orig_size);
//     _cached_mass_contribution_cols.reserve(1.2 * orig_size);
//     _cached_mass_contribution_vals.reserve(1.2 * orig_size);
// }
//
// void
// DwarfElephantRBAssembly::clearCachedResidualContributions()
// {
//     unsigned int orig_size = _cached_residual_contribution_rows.size();
//
//     _cached_residual_contribution_rows.clear();
//     _cached_residual_contribution_vals.clear();
//
//     // It's possible (though massively unlikely) that clear() will
//     // change the capacity of the vectors, so let's be paranoid and
//     // explicitly reserve() the same amount of memory to avoid multiple
//     // push_back() induced allocations.  We reserve 20% more than the
//     // original size that was cached to account for variations in the
//     // number of BCs assigned to each thread (for when the Jacobian
//     // contributions are computed threaded).
//     _cached_residual_contribution_rows.reserve(1.2 * orig_size);
//     _cached_residual_contribution_vals.reserve(1.2 * orig_size);
// }
//
// void
// DwarfElephantRBAssembly::clearCachedOutputContributions()
// {
//     unsigned int orig_size = _cached_output_contribution_rows.size();
//
//     _cached_output_contribution_rows.clear();
//     _cached_output_contribution_vals.clear();
//
//     // It's possible (though massively unlikely) that clear() will
//     // change the capacity of the vectors, so let's be paranoid and
//     // explicitly reserve() the same amount of memory to avoid multiple
//     // push_back() induced allocations.  We reserve 20% more than the
//     // original size that was cached to account for variations in the
//     // number of BCs assigned to each thread (for when the Jacobian
//     // contributions are computed threaded).
//     _cached_output_contribution_rows.reserve(1.2 * orig_size);
//     _cached_output_contribution_vals.reserve(1.2 * orig_size);
// }

void
DwarfElephantRBAssembly::setCachedJacobianContributionSize(unsigned int _size)
{
  _cached_jacobian_contribution_rows.resize(_size);
  _cached_jacobian_contribution_cols.resize(_size);
  _cached_jacobian_contribution_vals.resize(_size);
}

void
DwarfElephantRBAssembly::setCachedMassContributionSize(unsigned int _size)
{
  _cached_mass_contribution_rows.resize(_size);
  _cached_mass_contribution_cols.resize(_size);
  _cached_mass_contribution_vals.resize(_size);
}

void
DwarfElephantRBAssembly::setCachedResidualContributionSize(unsigned int _size)
{
  _cached_residual_contribution_rows.resize(_size);
  _cached_residual_contribution_vals.resize(_size);
}

void
DwarfElephantRBAssembly::setCachedOutputContributionSize(unsigned int _size)
{
  _cached_output_contribution_rows.resize(_size);
  _cached_output_contribution_vals.resize(_size);
}
