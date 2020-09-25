/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to six (T6) and the number of Aq to three (A3).
 *  2. The problem contains four Fq (F4) and one output (O1).
 *
 * The structures defined are:
 * 1. Theta --> parameter-dependent part of the PDE
 * 2. RBThetaExpansion
 */
///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/transient_rb_theta_expansion.h"
#include "libmesh/transient_rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresThetaEqualMu0DividedByMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu1DividedByMu2.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu4.h"
#include "DwarfElephantRBStructuresThetaEqualMu5.h"


// Forward Declarations
namespace libMesh
{
  class RBTransientBThetaExpansion;
}

struct DwarfElephantRBT6A3F2O1M3TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBT6A3F2O1M3TransientExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_M_theta(&_theta_m_0);
    attach_M_theta(&_theta_m_1);
    attach_M_theta(&_rb_theta);

    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_f_0);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaEqualMu0DividedByMu2 _theta_a_0;
  DwarfElephantThetaEqualMu1DividedByMu2 _theta_a_1;
  DwarfElephantThetaEqualScalarDividedByMu2 _theta_a_2;
  DwarfElephantThetaEqualMu3 _theta_m_0;
  DwarfElephantThetaEqualMu4 _theta_m_1;
  DwarfElephantThetaEqualMu5 _theta_f_0;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
