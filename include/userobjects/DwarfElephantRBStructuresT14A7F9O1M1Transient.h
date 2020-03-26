/*
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to 14 (T14) and the number of Aq to seven (A7).
 *  2. The problem contains nine Fq (F9) and one output (O1).
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

#include "DwarfElephantRBStructuresThetaEqualMu0.h"
#include "DwarfElephantRBStructuresThetaEqualMu1.h"
#include "DwarfElephantRBStructuresThetaEqualMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu4.h"
#include "DwarfElephantRBStructuresThetaEqualMu5.h"
#include "DwarfElephantRBStructuresThetaEqualMu6.h"
#include "DwarfElephantRBStructuresThetaEqualMu7.h"
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu3TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu4TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu5TimesMu8.h"


// Forward Declarations
namespace libMesh
{
  class RBTransientBThetaExpansion;
}

struct DwarfElephantRBT14A7F9O1M1TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBT14A7F9O1M1TransientExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_M_theta(&_rb_theta);

    attach_A_theta(&_rb_theta);
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_A_theta(&_theta_a_4);
    attach_A_theta(&_theta_a_5);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_f_0);
    attach_F_theta(&_theta_f_1);
    attach_F_theta(&_theta_f_2);
    attach_F_theta(&_theta_f_3);
    attach_F_theta(&_theta_f_4);
    attach_F_theta(&_theta_f_5);
    attach_F_theta(&_theta_a_6);
    attach_F_theta(&_theta_a_7);

    attach_output_theta(&_rb_theta);
  }
  // Member Variables
  DwarfElephantThetaEqualMu0 _theta_a_0;
  DwarfElephantThetaEqualMu1 _theta_a_1;
  DwarfElephantThetaEqualMu2 _theta_a_2;
  DwarfElephantThetaEqualMu3 _theta_a_3;
  DwarfElephantThetaEqualMu4 _theta_a_4;
  DwarfElephantThetaEqualMu5 _theta_a_5;
  DwarfElephantThetaEqualMu0TimesMu8 _theta_f_0;
  DwarfElephantThetaEqualMu1TimesMu8 _theta_f_1;
  DwarfElephantThetaEqualMu2TimesMu8 _theta_f_2;
  DwarfElephantThetaEqualMu3TimesMu8 _theta_f_3;
  DwarfElephantThetaEqualMu4TimesMu8 _theta_f_4;
  DwarfElephantThetaEqualMu5TimesMu8 _theta_f_5;
  DwarfElephantThetaEqualMu6 _theta_a_6;
  DwarfElephantThetaEqualMu7 _theta_a_7;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
