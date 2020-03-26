/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to nine (T9) and the number of Aq to three (A3).
 *  2. The problem contains ten Fq (F10) and one output (O1).
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
#include "DwarfElephantRBStructuresThetaEqualMu0.h"
#include "DwarfElephantRBStructuresThetaEqualMu1.h"
#include "DwarfElephantRBStructuresThetaEqualMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu4.h"
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu4.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu4.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu4.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT9A3F10O1SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT9A3F10O1SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_f_0);
    attach_F_theta(&_theta_f_1);
    attach_F_theta(&_theta_f_2);
    attach_F_theta(&_theta_f_3);
    attach_F_theta(&_theta_f_4);
    attach_F_theta(&_theta_f_5);
    attach_F_theta(&_theta_f_3);
    attach_F_theta(&_theta_f_4);
    attach_F_theta(&_theta_f_5);

    attach_output_theta(&_rb_theta);
  }
  // Member Variables
  DwarfElephantThetaEqualMu0 _theta_a_0;
  DwarfElephantThetaEqualMu1 _theta_a_1;
  DwarfElephantThetaEqualMu2 _theta_a_2;
  DwarfElephantThetaEqualMu0TimesMu3 _theta_f_0;
  DwarfElephantThetaEqualMu1TimesMu3 _theta_f_1;
  DwarfElephantThetaEqualMu2TimesMu3 _theta_f_2;
  DwarfElephantThetaEqualMu0TimesMu4 _theta_f_3;
  DwarfElephantThetaEqualMu1TimesMu4 _theta_f_4;
  DwarfElephantThetaEqualMu2TimesMu4 _theta_f_5;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
