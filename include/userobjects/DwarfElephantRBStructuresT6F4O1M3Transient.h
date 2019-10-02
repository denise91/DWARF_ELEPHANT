 /**
  * The structures are defined for an parabolic PDE with the following restrictions:
  *  1. The number of thetas is equal to six (T6).
  *  2. The problem contains four load vectors (F4) and one output (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */
///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTUREST6F4O1M3TRANSIENT_H
#define DWARFELEPHANTRBSTRUCTUREST6F4O1M3TRANSIENT_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/transient_rb_theta_expansion.h"
#include "libmesh/transient_rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA0ThetaEqualMu0DividedByMu2.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMu1DividedByMu2.h"
#include "DwarfElephantRBStructuresA2ThetaEqualScalarDividedByMu2.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMu3.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMu4.h"
#include "DwarfElephantRBStructuresA5ThetaEqualMu5.h"


// Forward Declarations
namespace libMesh
{
  class RBTransientBThetaExpansion;
}

///The structures are defined for an parabolic PDE with the following restrictions: 1. The number of thetas is equal to five (T5). 2. The problem contains one load vector (F1) and one output (O1).

/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBT6F4O1M3TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBT6F4O1M3TransientExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_M_theta(&_theta_m_0);
    attach_M_theta(&_theta_m_1);
    attach_M_theta(&_rb_theta);

    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);

    attach_F_theta(&_theta_a_0);
    attach_F_theta(&_theta_a_1);
    attach_F_theta(&_theta_a_2);
    attach_F_theta(&_theta_f_0);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaA0EqualMu0DividedByMu2 _theta_a_0;
  DwarfElephantThetaA1EqualMu1DividedByMu2 _theta_a_1;
  DwarfElephantThetaA2EqualScalarDividedByMu2 _theta_a_2;
  DwarfElephantThetaA3EqualMu3 _theta_m_0;
  DwarfElephantThetaA4EqualMu4 _theta_m_1;
  DwarfElephantThetaA5EqualMu5 _theta_f_0;

  // //DwarfElephantThetaA3EqualMu3 _theta_m_0;
  // DwarfElephantThetaA1EqualMu1 _theta_m_0;
  // //DwarfElephantThetaA4EqualMu4 _theta_m_1;
  // DwarfElephantThetaA3EqualMu3 _theta_f_0;
  // // //DwarfElephantThetaA5EqualMu5 _theta_f_0;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTUREST6F4O1M3Transient_H
