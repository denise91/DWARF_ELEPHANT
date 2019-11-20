 /**
  * The structures are defined for an elliptic PDE with the following restrictions:
  *  1. The number of thetas is equal to 10 (T10).
  *  2. The problem contains 9 load vectors (F9) and 1 outputs (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTUREST10F9O1M1TRANSIENT_H
#define DWARFELEPHANTRBSTRUCTUREST10F9O1M1TRANSIENT_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/transient_rb_theta_expansion.h"
#include "libmesh/transient_rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA0ThetaEqualMu0.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5.h"
#include "DwarfElephantRBStructuresA6ThetaEqualMu6.h"
#include "DwarfElephantRBStructuresA7ThetaEqualMu7.h"
#include "DwarfElephantRBStructuresA0ThetaEqualMu0TimesMu8.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1TimesMu8.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMu2TimesMu8.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3TimesMu8.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4TimesMu8.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5TimesMu8.h"


// Forward Declarations
namespace libMesh
{
  class RBTransientBThetaExpansion;
}

///The structures are defined for an elliptic PDE with the following restrictions: 1. The number of thetas is equal to 16 (T16). 2. The problem contains 16 load vectors (F16) and 80 outputs (O80).
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBT10F9O1M1TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBT10F9O1M1TransientExpansion()
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
  DwarfElephantThetaA0EqualMu0 _theta_a_0;
  DwarfElephantThetaA1EqualMu1 _theta_a_1;
  DwarfElephantThetaA2EqualMu2 _theta_a_2;
  DwarfElephantThetaA3EqualMu3 _theta_a_3;
  DwarfElephantThetaA4EqualMu4 _theta_a_4;
  DwarfElephantThetaA5EqualMu5 _theta_a_5;
  DwarfElephantThetaA0EqualMu0TimesMu8 _theta_f_0;
  DwarfElephantThetaA1EqualMu1TimesMu8 _theta_f_1;
  DwarfElephantThetaA2EqualMu2TimesMu8 _theta_f_2;
  DwarfElephantThetaA3EqualMu3TimesMu8 _theta_f_3;
  DwarfElephantThetaA4EqualMu4TimesMu8 _theta_f_4;
  DwarfElephantThetaA5EqualMu5TimesMu8 _theta_f_5;
  DwarfElephantThetaA6EqualMu6 _theta_a_6;
  DwarfElephantThetaA7EqualMu7 _theta_a_7;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTUREST8F9O1M1TRANSIENT_H
