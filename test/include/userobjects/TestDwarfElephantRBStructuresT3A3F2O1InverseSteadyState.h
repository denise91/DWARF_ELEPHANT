/**
 * The structures are defined for an parabolic PDE with the following restrictions:
 *  1. The number of thetas is equal to three (T3) and the number of Aq to three (A3).
 *  2. The problem contains one load vector (F1) and one output (O1).
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

#include "DwarfElephantRBStructuresThetaConstant.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu0.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu1.h"
#include "DwarfElephantRBStructuresThetaEqualScalarDividedByMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu3.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct TestDwarfElephantRBT3A3F2O1InverseSteadyStateExpansion : RBThetaExpansion
{
  TestDwarfElephantRBT3A3F2O1InverseSteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_f_0);

    attach_output_theta(&_rb_theta);
  }
  // Member Variables
  DwarfElephantThetaConstant _theta_a_00;
  DwarfElephantThetaEqualScalarDividedByMu0 _theta_a_0;
  DwarfElephantThetaEqualScalarDividedByMu1 _theta_a_1;
  DwarfElephantThetaEqualScalarDividedByMu2 _theta_a_2;
  DwarfElephantThetaEqualMu3 _theta_f_0;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};