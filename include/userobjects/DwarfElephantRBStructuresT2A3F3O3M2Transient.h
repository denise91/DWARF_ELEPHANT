/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to two (T2) and the number of Aq to three (A3).
 *  2. The problem contains three Fq (F3) and three outputs (O3).
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

#include "DwarfElephantRBStructuresThetaConstant.h"
#include "DwarfElephantRBStructuresThetaEqualMu0.h"
#include "DwarfElephantRBStructuresThetaEqualMu1.h"
#include "DwarfElephantRBStructuresThetaEqualMu2.h"


// Forward Declarations
namespace libMesh
{
  class RBTransientBThetaExpansion;
}

struct DwarfElephantRBT2A3F3O3M2TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBT2A3F3O3M2TransientExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_M_theta(&_theta_a_00);
    attach_M_theta(&_rb_theta);

    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_rb_theta);
    attach_A_theta(&_theta_a_1);

    attach_F_theta(&_theta_a_0);
    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_a_1);

    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaConstant _theta_a_00;
  DwarfElephantThetaEqualMu0 _theta_a_0;
  DwarfElephantThetaEqualMu1 _theta_a_1;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
