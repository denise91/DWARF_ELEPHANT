 /**
  * The structures are defined for an elliptic PDE with the following restrictions:
  *  1. The number of thetas is equal to 16 (T16).
  *  2. The problem contains 17 load vectors (F17) and 1 outputs (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTUREST16F17O1STEADYSTATE_H
#define DWARFELEPHANTRBSTRUCTUREST16F17O1STEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA0ThetaEqualMu0.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5.h"
#include "DwarfElephantRBStructuresA6ThetaEqualMu6.h"
#include "DwarfElephantRBStructuresA7ThetaEqualMu7.h"
#include "DwarfElephantRBStructuresA8ThetaEqualMu8.h"
#include "DwarfElephantRBStructuresA9ThetaEqualMu9.h"
#include "DwarfElephantRBStructuresA10ThetaEqualMu10.h"
#include "DwarfElephantRBStructuresA11ThetaEqualMu11.h"
#include "DwarfElephantRBStructuresA12ThetaEqualMu12.h"
#include "DwarfElephantRBStructuresA13ThetaEqualMu13.h"
#include "DwarfElephantRBStructuresA14ThetaEqualMu14.h"
#include "DwarfElephantRBStructuresA15ThetaEqualMu15.h"


// Forward Declarations
namespace libMesh
{
 // class RBParameters;
 // class RBTheta;
  class RBThetaExpansion;
}

///The structures are defined for an elliptic PDE with the following restrictions: 1. The number of thetas is equal to 16 (T16). 2. The problem contains 16 load vectors (F16) and 80 outputs (O80).
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBT16F17O1SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT16F17O1SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_rb_theta);
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_A_theta(&_theta_a_4);
    attach_A_theta(&_theta_a_5);
    attach_A_theta(&_theta_a_6);
    attach_A_theta(&_theta_a_7);

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

    attach_output_theta(&_rb_theta);
  }
  // Member Variables
  DwarfElephantThetaA0EqualMu0 _theta_a_0;
  DwarfElephantThetaA1EqualMu1 _theta_a_1;
  DwarfElephantThetaA2EqualMu2 _theta_a_2;
  DwarfElephantThetaA3EqualMu3 _theta_a_3;
  DwarfElephantThetaA4EqualMu4 _theta_a_4;
  DwarfElephantThetaA5EqualMu5 _theta_a_5;
  DwarfElephantThetaA6EqualMu6 _theta_a_6;
  DwarfElephantThetaA7EqualMu7 _theta_a_7;
  DwarfElephantThetaA8EqualMu8 _theta_a_8;
  DwarfElephantThetaA9EqualMu9 _theta_a_9;
  DwarfElephantThetaA10EqualMu10 _theta_a_10;
  DwarfElephantThetaA11EqualMu11 _theta_a_11;
  DwarfElephantThetaA12EqualMu12 _theta_a_12;
  DwarfElephantThetaA13EqualMu13 _theta_a_13;
  DwarfElephantThetaA14EqualMu14 _theta_a_14;
  DwarfElephantThetaA15EqualMu15 _theta_a_15;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTUREST14F15O1STEADYSTATE_H
