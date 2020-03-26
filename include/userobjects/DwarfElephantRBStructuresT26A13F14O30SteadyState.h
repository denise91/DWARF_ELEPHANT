/*
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to 26 (T26) and the number of Aq to 13 (A13).
 *  2. The problem contains 14 Fq (F14) and 30 outputs (O30).
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
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu3TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu4TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu5TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu6TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu7TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu8TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu9TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu10TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu11TimesMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu12TimesMu13.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT26A13F14O30SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT26A13F14O30SteadyStateExpansion()
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
    attach_A_theta(&_theta_a_12);

    attach_F_theta(&_rb_theta);
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
    attach_F_theta(&_theta_f_12);

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
  DwarfElephantThetaEqualMu0TimesMu13 _theta_f_0;
  DwarfElephantThetaEqualMu1TimesMu13 _theta_f_1;
  DwarfElephantThetaEqualMu2TimesMu13 _theta_f_2;
  DwarfElephantThetaEqualMu3TimesMu13 _theta_f_3;
  DwarfElephantThetaEqualMu4TimesMu13 _theta_f_4;
  DwarfElephantThetaEqualMu5TimesMu13 _theta_f_5;
  DwarfElephantThetaEqualMu6TimesMu13 _theta_f_6;
  DwarfElephantThetaEqualMu7TimesMu13 _theta_f_7;
  DwarfElephantThetaEqualMu8TimesMu13 _theta_f_8;
  DwarfElephantThetaEqualMu9TimesMu13 _theta_f_9;
  DwarfElephantThetaEqualMu10TimesMu13 _theta_f_10;
  DwarfElephantThetaEqualMu11TimesMu13 _theta_f_11;
  DwarfElephantThetaEqualMu12TimesMu13 _theta_f_12;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
