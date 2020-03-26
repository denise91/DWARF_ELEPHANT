/*
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to 18 (T18) and the number of Aq to ten (A10).
 *  2. The problem contains 19 Fq (F19) and one output (O1).
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
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu3TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu4.h"
#include "DwarfElephantRBStructuresThetaEqualMu4TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu5.h"
#include "DwarfElephantRBStructuresThetaEqualMu5TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu6.h"
#include "DwarfElephantRBStructuresThetaEqualMu6TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu7.h"
#include "DwarfElephantRBStructuresThetaEqualMu7TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu8TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu9TimesMu18.h"
#include "DwarfElephantRBStructuresThetaEqualMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu11.h"
#include "DwarfElephantRBStructuresThetaEqualMu12.h"
#include "DwarfElephantRBStructuresThetaEqualMu13.h"
#include "DwarfElephantRBStructuresThetaEqualMu14.h"
#include "DwarfElephantRBStructuresThetaEqualMu15.h"
#include "DwarfElephantRBStructuresThetaEqualMu16.h"
#include "DwarfElephantRBStructuresThetaEqualMu17.h"


// Forward Declarations
namespace libMesh
{
  class RBTransientBThetaExpansion;
}

struct DwarfElephantRBT18A10F19O1M1TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBT18A10F19O1M1TransientExpansion()
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
    attach_A_theta(&_theta_a_6);
    attach_A_theta(&_theta_a_7);
    attach_A_theta(&_theta_a_8);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_a_0);
    attach_F_theta(&_theta_a_1);
    attach_F_theta(&_theta_a_2);
    attach_F_theta(&_theta_a_3);
    attach_F_theta(&_theta_a_4);
    attach_F_theta(&_theta_a_5);
    attach_F_theta(&_theta_a_6);
    attach_F_theta(&_theta_a_7);
    attach_F_theta(&_theta_a_8);
    attach_F_theta(&_theta_a_9);
    attach_F_theta(&_theta_a_10);
    attach_F_theta(&_theta_a_11);
    attach_F_theta(&_theta_a_12);
    attach_F_theta(&_theta_a_13);
    attach_F_theta(&_theta_a_14);
    attach_F_theta(&_theta_a_15);
    attach_F_theta(&_theta_a_16);
    attach_F_theta(&_theta_a_17);

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
  DwarfElephantThetaEqualMu13 _theta_a_13;
  DwarfElephantThetaEqualMu14 _theta_a_14;
  DwarfElephantThetaEqualMu15 _theta_a_15;
  DwarfElephantThetaEqualMu16 _theta_a_16;
  DwarfElephantThetaEqualMu17 _theta_a_17;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
