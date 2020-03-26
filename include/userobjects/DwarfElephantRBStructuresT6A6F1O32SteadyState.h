/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to six (T6) and the number of Aq to six (A6).
 *  2. The problem contains one Fq (F1) and 32 outputs (O32).
 *
 * The structures defined are:
 * 1. Theta --> parameter-dependent part of the PDE
 * 2. RBThetaExpansion
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu0.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu1.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu2.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu3.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu4.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu5.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT6A6F1O32SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT6A6F1O32SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_A_theta(&_theta_a_4);
    attach_A_theta(&_theta_a_5);

    attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
  }
  // Member Variables
  DwarfElephantThetaEqualScalarDividedByMu0 _theta_a_0;
  DwarfElephantThetaEqualScalarDividedByMu1 _theta_a_1;
  DwarfElephantThetaEqualScalarDividedByMu2 _theta_a_2;
  DwarfElephantThetaEqualScalarDividedByMu3 _theta_a_3;
  DwarfElephantThetaEqualScalarDividedByMu4 _theta_a_4;
  DwarfElephantThetaEqualScalarDividedByMu5 _theta_a_5;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
