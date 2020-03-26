/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to 25 (T25) and the number of Aq to 12 (A12).
 *  2. The problem contains 13 Fq (F13) and 84 outputs (O84).
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
#include "DwarfElephantRBStructuresThetaEqualMu5.h"
#include "DwarfElephantRBStructuresThetaEqualMu6.h"
#include "DwarfElephantRBStructuresThetaEqualMu7.h"
#include "DwarfElephantRBStructuresThetaEqualMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu11.h"
#include "DwarfElephantRBStructuresThetaEqualMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu3TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu4TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu5TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu6TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu7TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu8TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu9TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu10TimesMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu11TimesMu12.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT25A12F13O84SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT25A12F13O84SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_A_theta(&_theta_a_4);
    attach_A_theta(&_theta_a_5);
    attach_A_theta(&_theta_a_6);
    attach_A_theta(&_theta_a_7);
    attach_A_theta(&_theta_a_8);
    attach_A_theta(&_theta_a_9);
    attach_A_theta(&_theta_a_10);
    attach_A_theta(&_theta_a_11);

    attach_F_theta(&_theta_a_12);
    attach_F_theta(&_theta_f_0);
    attach_F_theta(&_theta_f_1);
    attach_F_theta(&_theta_f_2);
    attach_F_theta(&_theta_f_3);
    attach_F_theta(&_theta_f_4);
    attach_F_theta(&_theta_f_5);
    attach_F_theta(&_theta_f_6);
    attach_F_theta(&_theta_f_7);
    attach_F_theta(&_theta_f_8);
    attach_F_theta(&_theta_f_9);
    attach_F_theta(&_theta_f_10);
    attach_F_theta(&_theta_f_11);

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
  DwarfElephantThetaEqualMu0 _theta_a_0;
  DwarfElephantThetaEqualMu1 _theta_a_1;
  DwarfElephantThetaEqualMu2 _theta_a_2;
  DwarfElephantThetaEqualMu3 _theta_a_3;
  DwarfElephantThetaEqualMu4 _theta_a_4;
  DwarfElephantThetaEqualMu5 _theta_a_5;
  DwarfElephantThetaEqualMu6 _theta_a_6;
  DwarfElephantThetaEqualMu7 _theta_a_7;
  DwarfElephantThetaEqualMu8 _theta_a_8;
  DwarfElephantThetaEqualMu9 _theta_a_9;
  DwarfElephantThetaEqualMu10 _theta_a_10;
  DwarfElephantThetaEqualMu11 _theta_a_11;
  DwarfElephantThetaEqualMu12 _theta_a_12;
  DwarfElephantThetaEqualMu0TimesMu12 _theta_f_0;
  DwarfElephantThetaEqualMu1TimesMu12 _theta_f_1;
  DwarfElephantThetaEqualMu2TimesMu12 _theta_f_2;
  DwarfElephantThetaEqualMu3TimesMu12 _theta_f_3;
  DwarfElephantThetaEqualMu4TimesMu12 _theta_f_4;
  DwarfElephantThetaEqualMu5TimesMu12 _theta_f_5;
  DwarfElephantThetaEqualMu6TimesMu12 _theta_f_6;
  DwarfElephantThetaEqualMu7TimesMu12 _theta_f_7;
  DwarfElephantThetaEqualMu8TimesMu12 _theta_f_8;
  DwarfElephantThetaEqualMu9TimesMu12 _theta_f_9;
  DwarfElephantThetaEqualMu10TimesMu12 _theta_f_10;
  DwarfElephantThetaEqualMu11TimesMu12 _theta_f_11;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
