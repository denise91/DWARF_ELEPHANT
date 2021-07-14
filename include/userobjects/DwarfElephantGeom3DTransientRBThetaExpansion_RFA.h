/**
  * The structures are defined for an elliptic PDE with the following restrictions:
  *  1. The number of thetas is equal to one (T1).
  *  2. The problem contains one load vector (F1) and one output (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTGEOM3DTRANSIENTRBTHETAEXPANSION_RFA_H
#define DWARFELEPHANTGEOM3DTRANSIENTRBTHETAEXPANSION_RFA_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"
#include "libmesh/transient_rb_theta_expansion.h"
#include "libmesh/transient_rb_assembly_expansion.h"

#include "DwarfElephantGeom3DRBTheta_RFA.h"
#include "DwarfElephantMeshSubdomainJacobians.h"
// Forward Declarations
namespace libMesh
{
  class TransientRBThetaExpansion;
}
///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */
/*
struct MTheta_qM1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return 3.82e6;
  }
};

struct MTheta_qM2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return 3.798e6;
  }
};

struct ATheta_qA0 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return 0.8;
  }
};

struct ATheta_qA1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return 1.9e5;
  }
};

struct ATheta_qA2 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return 0.52;
  }
};
*/
struct Geom3DTransientRBThetaExpansion : TransientRBThetaExpansion
{
  Geom3DTransientRBThetaExpansion()
  {
    /*
    attach_M_theta(&_m_theta_1);
    attach_M_theta(&_m_theta_2);
    attach_A_theta(&_a_theta_0);
    attach_A_theta(&_a_theta_1);
    attach_A_theta(&_a_theta_2);
    attach_A_theta(&_rb_theta);
    */

  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxZ1_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxZ2_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxZ3_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxZ4_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxZ5_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minX1_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minX2_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minX3_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minX4_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minX5_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxY1_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxY2_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxY3_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxY4_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxY5_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxX1_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxX2_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxX3_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxX4_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_maxX5_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minY1_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minY2_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minY3_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minY4_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minY5_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minZ1_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minZ2_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minZ3_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minZ4_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_minZ5_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_VesselCyl_0);
  attach_M_theta(&MTheta_subdomain_TimeDerivative_BoundingBox_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_maxX5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minY5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ1_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ2_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ3_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXZ_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYZ_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZX_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZY_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ4_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXY_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYX_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_minZ5_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_VesselCyl_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_VesselCyl_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_VesselCyl_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionXX_BoundingBox_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionYY_BoundingBox_0);
  attach_A_theta(&Geom3DRB_ATheta_DiffusionZZ_BoundingBox_0);
  attach_A_theta(&Geom3DRB_ATheta_Perfusion_VesselCyl_0);
  attach_A_theta(&_rb_theta); // Convection BC

  attach_F_theta(&_rb_theta); // Convection BC
  //attach_F_theta(&_rb_theta); // RF Heat Source from here on
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  //attach_F_theta(&_rb_theta);
  
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_1);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_2);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_3);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_4);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_5);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_6);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_7);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_8);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_9);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_10);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_11);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_12);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_13);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_14);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_15);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_16);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_17);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_18);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_19);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_20);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_21);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_22);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_23);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_24);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_25);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_26);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_27);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_28);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_29);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_30);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_31);
    subdomain_jac_rbthetas.push_back(&rbtheta_subdomain_32);
    num_subdomains = 32;
}
  /*
  MTheta_qM1 _m_theta_1;
  MTheta_qM2 _m_theta_2;
  ATheta_qA0 _a_theta_0;
  ATheta_qA1 _a_theta_1;
  ATheta_qA2 _a_theta_2;
  */

  MTheta_subdomain_1 MTheta_subdomain_TimeDerivative_maxZ1_0;
  MTheta_subdomain_2 MTheta_subdomain_TimeDerivative_maxZ2_0;
  MTheta_subdomain_3 MTheta_subdomain_TimeDerivative_maxZ3_0;
  MTheta_subdomain_4 MTheta_subdomain_TimeDerivative_maxZ4_0;
  MTheta_subdomain_5 MTheta_subdomain_TimeDerivative_maxZ5_0;
  MTheta_subdomain_6 MTheta_subdomain_TimeDerivative_minX1_0;
  MTheta_subdomain_7 MTheta_subdomain_TimeDerivative_minX2_0;
  MTheta_subdomain_8 MTheta_subdomain_TimeDerivative_minX3_0;
  MTheta_subdomain_9 MTheta_subdomain_TimeDerivative_minX4_0;
  MTheta_subdomain_10 MTheta_subdomain_TimeDerivative_minX5_0;
  MTheta_subdomain_11 MTheta_subdomain_TimeDerivative_maxY1_0;
  MTheta_subdomain_12 MTheta_subdomain_TimeDerivative_maxY2_0;
  MTheta_subdomain_13 MTheta_subdomain_TimeDerivative_maxY3_0;
  MTheta_subdomain_14 MTheta_subdomain_TimeDerivative_maxY4_0;
  MTheta_subdomain_15 MTheta_subdomain_TimeDerivative_maxY5_0;
  MTheta_subdomain_16 MTheta_subdomain_TimeDerivative_maxX1_0;
  MTheta_subdomain_17 MTheta_subdomain_TimeDerivative_maxX2_0;
  MTheta_subdomain_18 MTheta_subdomain_TimeDerivative_maxX3_0;
  MTheta_subdomain_19 MTheta_subdomain_TimeDerivative_maxX4_0;
  MTheta_subdomain_20 MTheta_subdomain_TimeDerivative_maxX5_0;
  MTheta_subdomain_21 MTheta_subdomain_TimeDerivative_minY1_0;
  MTheta_subdomain_22 MTheta_subdomain_TimeDerivative_minY2_0;
  MTheta_subdomain_23 MTheta_subdomain_TimeDerivative_minY3_0;
  MTheta_subdomain_24 MTheta_subdomain_TimeDerivative_minY4_0;
  MTheta_subdomain_25 MTheta_subdomain_TimeDerivative_minY5_0;
  MTheta_subdomain_26 MTheta_subdomain_TimeDerivative_minZ1_0;
  MTheta_subdomain_27 MTheta_subdomain_TimeDerivative_minZ2_0;
  MTheta_subdomain_28 MTheta_subdomain_TimeDerivative_minZ3_0;
  MTheta_subdomain_29 MTheta_subdomain_TimeDerivative_minZ4_0;
  MTheta_subdomain_30 MTheta_subdomain_TimeDerivative_minZ5_0;
  MTheta_subdomain_31 MTheta_subdomain_TimeDerivative_VesselCyl_0;
  MTheta_subdomain_32 MTheta_subdomain_TimeDerivative_BoundingBox_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ1 Geom3DRB_ATheta_DiffusionXX_maxZ1_0;
  Geom3DRB_ATheta_DiffusionXY_maxZ1 Geom3DRB_ATheta_DiffusionXY_maxZ1_0;
  Geom3DRB_ATheta_DiffusionXZ_maxZ1 Geom3DRB_ATheta_DiffusionXZ_maxZ1_0;
  Geom3DRB_ATheta_DiffusionYX_maxZ1 Geom3DRB_ATheta_DiffusionYX_maxZ1_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ1 Geom3DRB_ATheta_DiffusionYY_maxZ1_0;
  Geom3DRB_ATheta_DiffusionYZ_maxZ1 Geom3DRB_ATheta_DiffusionYZ_maxZ1_0;
  Geom3DRB_ATheta_DiffusionZX_maxZ1 Geom3DRB_ATheta_DiffusionZX_maxZ1_0;
  Geom3DRB_ATheta_DiffusionZY_maxZ1 Geom3DRB_ATheta_DiffusionZY_maxZ1_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ1 Geom3DRB_ATheta_DiffusionZZ_maxZ1_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ2 Geom3DRB_ATheta_DiffusionXX_maxZ2_0;
  Geom3DRB_ATheta_DiffusionXY_maxZ2 Geom3DRB_ATheta_DiffusionXY_maxZ2_0;
  Geom3DRB_ATheta_DiffusionXZ_maxZ2 Geom3DRB_ATheta_DiffusionXZ_maxZ2_0;
  Geom3DRB_ATheta_DiffusionYX_maxZ2 Geom3DRB_ATheta_DiffusionYX_maxZ2_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ2 Geom3DRB_ATheta_DiffusionYY_maxZ2_0;
  Geom3DRB_ATheta_DiffusionYZ_maxZ2 Geom3DRB_ATheta_DiffusionYZ_maxZ2_0;
  Geom3DRB_ATheta_DiffusionZX_maxZ2 Geom3DRB_ATheta_DiffusionZX_maxZ2_0;
  Geom3DRB_ATheta_DiffusionZY_maxZ2 Geom3DRB_ATheta_DiffusionZY_maxZ2_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ2 Geom3DRB_ATheta_DiffusionZZ_maxZ2_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ3 Geom3DRB_ATheta_DiffusionXX_maxZ3_0;
  Geom3DRB_ATheta_DiffusionXY_maxZ3 Geom3DRB_ATheta_DiffusionXY_maxZ3_0;
  Geom3DRB_ATheta_DiffusionXZ_maxZ3 Geom3DRB_ATheta_DiffusionXZ_maxZ3_0;
  Geom3DRB_ATheta_DiffusionYX_maxZ3 Geom3DRB_ATheta_DiffusionYX_maxZ3_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ3 Geom3DRB_ATheta_DiffusionYY_maxZ3_0;
  Geom3DRB_ATheta_DiffusionYZ_maxZ3 Geom3DRB_ATheta_DiffusionYZ_maxZ3_0;
  Geom3DRB_ATheta_DiffusionZX_maxZ3 Geom3DRB_ATheta_DiffusionZX_maxZ3_0;
  Geom3DRB_ATheta_DiffusionZY_maxZ3 Geom3DRB_ATheta_DiffusionZY_maxZ3_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ3 Geom3DRB_ATheta_DiffusionZZ_maxZ3_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ4 Geom3DRB_ATheta_DiffusionXX_maxZ4_0;
  Geom3DRB_ATheta_DiffusionXY_maxZ4 Geom3DRB_ATheta_DiffusionXY_maxZ4_0;
  Geom3DRB_ATheta_DiffusionXZ_maxZ4 Geom3DRB_ATheta_DiffusionXZ_maxZ4_0;
  Geom3DRB_ATheta_DiffusionYX_maxZ4 Geom3DRB_ATheta_DiffusionYX_maxZ4_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ4 Geom3DRB_ATheta_DiffusionYY_maxZ4_0;
  Geom3DRB_ATheta_DiffusionYZ_maxZ4 Geom3DRB_ATheta_DiffusionYZ_maxZ4_0;
  Geom3DRB_ATheta_DiffusionZX_maxZ4 Geom3DRB_ATheta_DiffusionZX_maxZ4_0;
  Geom3DRB_ATheta_DiffusionZY_maxZ4 Geom3DRB_ATheta_DiffusionZY_maxZ4_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ4 Geom3DRB_ATheta_DiffusionZZ_maxZ4_0;
  Geom3DRB_ATheta_DiffusionXX_maxZ5 Geom3DRB_ATheta_DiffusionXX_maxZ5_0;
  Geom3DRB_ATheta_DiffusionXY_maxZ5 Geom3DRB_ATheta_DiffusionXY_maxZ5_0;
  Geom3DRB_ATheta_DiffusionYX_maxZ5 Geom3DRB_ATheta_DiffusionYX_maxZ5_0;
  Geom3DRB_ATheta_DiffusionYY_maxZ5 Geom3DRB_ATheta_DiffusionYY_maxZ5_0;
  Geom3DRB_ATheta_DiffusionZZ_maxZ5 Geom3DRB_ATheta_DiffusionZZ_maxZ5_0;
  Geom3DRB_ATheta_DiffusionXX_minX1 Geom3DRB_ATheta_DiffusionXX_minX1_0;
  Geom3DRB_ATheta_DiffusionXY_minX1 Geom3DRB_ATheta_DiffusionXY_minX1_0;
  Geom3DRB_ATheta_DiffusionXZ_minX1 Geom3DRB_ATheta_DiffusionXZ_minX1_0;
  Geom3DRB_ATheta_DiffusionYX_minX1 Geom3DRB_ATheta_DiffusionYX_minX1_0;
  Geom3DRB_ATheta_DiffusionYY_minX1 Geom3DRB_ATheta_DiffusionYY_minX1_0;
  Geom3DRB_ATheta_DiffusionYZ_minX1 Geom3DRB_ATheta_DiffusionYZ_minX1_0;
  Geom3DRB_ATheta_DiffusionZX_minX1 Geom3DRB_ATheta_DiffusionZX_minX1_0;
  Geom3DRB_ATheta_DiffusionZY_minX1 Geom3DRB_ATheta_DiffusionZY_minX1_0;
  Geom3DRB_ATheta_DiffusionZZ_minX1 Geom3DRB_ATheta_DiffusionZZ_minX1_0;
  Geom3DRB_ATheta_DiffusionXX_minX2 Geom3DRB_ATheta_DiffusionXX_minX2_0;
  Geom3DRB_ATheta_DiffusionXY_minX2 Geom3DRB_ATheta_DiffusionXY_minX2_0;
  Geom3DRB_ATheta_DiffusionXZ_minX2 Geom3DRB_ATheta_DiffusionXZ_minX2_0;
  Geom3DRB_ATheta_DiffusionYX_minX2 Geom3DRB_ATheta_DiffusionYX_minX2_0;
  Geom3DRB_ATheta_DiffusionYY_minX2 Geom3DRB_ATheta_DiffusionYY_minX2_0;
  Geom3DRB_ATheta_DiffusionYZ_minX2 Geom3DRB_ATheta_DiffusionYZ_minX2_0;
  Geom3DRB_ATheta_DiffusionZX_minX2 Geom3DRB_ATheta_DiffusionZX_minX2_0;
  Geom3DRB_ATheta_DiffusionZY_minX2 Geom3DRB_ATheta_DiffusionZY_minX2_0;
  Geom3DRB_ATheta_DiffusionZZ_minX2 Geom3DRB_ATheta_DiffusionZZ_minX2_0;
  Geom3DRB_ATheta_DiffusionXX_minX3 Geom3DRB_ATheta_DiffusionXX_minX3_0;
  Geom3DRB_ATheta_DiffusionXY_minX3 Geom3DRB_ATheta_DiffusionXY_minX3_0;
  Geom3DRB_ATheta_DiffusionXZ_minX3 Geom3DRB_ATheta_DiffusionXZ_minX3_0;
  Geom3DRB_ATheta_DiffusionYX_minX3 Geom3DRB_ATheta_DiffusionYX_minX3_0;
  Geom3DRB_ATheta_DiffusionYY_minX3 Geom3DRB_ATheta_DiffusionYY_minX3_0;
  Geom3DRB_ATheta_DiffusionYZ_minX3 Geom3DRB_ATheta_DiffusionYZ_minX3_0;
  Geom3DRB_ATheta_DiffusionZX_minX3 Geom3DRB_ATheta_DiffusionZX_minX3_0;
  Geom3DRB_ATheta_DiffusionZY_minX3 Geom3DRB_ATheta_DiffusionZY_minX3_0;
  Geom3DRB_ATheta_DiffusionZZ_minX3 Geom3DRB_ATheta_DiffusionZZ_minX3_0;
  Geom3DRB_ATheta_DiffusionXX_minX4 Geom3DRB_ATheta_DiffusionXX_minX4_0;
  Geom3DRB_ATheta_DiffusionXY_minX4 Geom3DRB_ATheta_DiffusionXY_minX4_0;
  Geom3DRB_ATheta_DiffusionXZ_minX4 Geom3DRB_ATheta_DiffusionXZ_minX4_0;
  Geom3DRB_ATheta_DiffusionYX_minX4 Geom3DRB_ATheta_DiffusionYX_minX4_0;
  Geom3DRB_ATheta_DiffusionYY_minX4 Geom3DRB_ATheta_DiffusionYY_minX4_0;
  Geom3DRB_ATheta_DiffusionYZ_minX4 Geom3DRB_ATheta_DiffusionYZ_minX4_0;
  Geom3DRB_ATheta_DiffusionZX_minX4 Geom3DRB_ATheta_DiffusionZX_minX4_0;
  Geom3DRB_ATheta_DiffusionZY_minX4 Geom3DRB_ATheta_DiffusionZY_minX4_0;
  Geom3DRB_ATheta_DiffusionZZ_minX4 Geom3DRB_ATheta_DiffusionZZ_minX4_0;
  Geom3DRB_ATheta_DiffusionXX_minX5 Geom3DRB_ATheta_DiffusionXX_minX5_0;
  Geom3DRB_ATheta_DiffusionYY_minX5 Geom3DRB_ATheta_DiffusionYY_minX5_0;
  Geom3DRB_ATheta_DiffusionYZ_minX5 Geom3DRB_ATheta_DiffusionYZ_minX5_0;
  Geom3DRB_ATheta_DiffusionZY_minX5 Geom3DRB_ATheta_DiffusionZY_minX5_0;
  Geom3DRB_ATheta_DiffusionZZ_minX5 Geom3DRB_ATheta_DiffusionZZ_minX5_0;
  Geom3DRB_ATheta_DiffusionXX_maxY1 Geom3DRB_ATheta_DiffusionXX_maxY1_0;
  Geom3DRB_ATheta_DiffusionXY_maxY1 Geom3DRB_ATheta_DiffusionXY_maxY1_0;
  Geom3DRB_ATheta_DiffusionXZ_maxY1 Geom3DRB_ATheta_DiffusionXZ_maxY1_0;
  Geom3DRB_ATheta_DiffusionYX_maxY1 Geom3DRB_ATheta_DiffusionYX_maxY1_0;
  Geom3DRB_ATheta_DiffusionYY_maxY1 Geom3DRB_ATheta_DiffusionYY_maxY1_0;
  Geom3DRB_ATheta_DiffusionYZ_maxY1 Geom3DRB_ATheta_DiffusionYZ_maxY1_0;
  Geom3DRB_ATheta_DiffusionZX_maxY1 Geom3DRB_ATheta_DiffusionZX_maxY1_0;
  Geom3DRB_ATheta_DiffusionZY_maxY1 Geom3DRB_ATheta_DiffusionZY_maxY1_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY1 Geom3DRB_ATheta_DiffusionZZ_maxY1_0;
  Geom3DRB_ATheta_DiffusionXX_maxY2 Geom3DRB_ATheta_DiffusionXX_maxY2_0;
  Geom3DRB_ATheta_DiffusionXY_maxY2 Geom3DRB_ATheta_DiffusionXY_maxY2_0;
  Geom3DRB_ATheta_DiffusionXZ_maxY2 Geom3DRB_ATheta_DiffusionXZ_maxY2_0;
  Geom3DRB_ATheta_DiffusionYX_maxY2 Geom3DRB_ATheta_DiffusionYX_maxY2_0;
  Geom3DRB_ATheta_DiffusionYY_maxY2 Geom3DRB_ATheta_DiffusionYY_maxY2_0;
  Geom3DRB_ATheta_DiffusionYZ_maxY2 Geom3DRB_ATheta_DiffusionYZ_maxY2_0;
  Geom3DRB_ATheta_DiffusionZX_maxY2 Geom3DRB_ATheta_DiffusionZX_maxY2_0;
  Geom3DRB_ATheta_DiffusionZY_maxY2 Geom3DRB_ATheta_DiffusionZY_maxY2_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY2 Geom3DRB_ATheta_DiffusionZZ_maxY2_0;
  Geom3DRB_ATheta_DiffusionXX_maxY3 Geom3DRB_ATheta_DiffusionXX_maxY3_0;
  Geom3DRB_ATheta_DiffusionXY_maxY3 Geom3DRB_ATheta_DiffusionXY_maxY3_0;
  Geom3DRB_ATheta_DiffusionXZ_maxY3 Geom3DRB_ATheta_DiffusionXZ_maxY3_0;
  Geom3DRB_ATheta_DiffusionYX_maxY3 Geom3DRB_ATheta_DiffusionYX_maxY3_0;
  Geom3DRB_ATheta_DiffusionYY_maxY3 Geom3DRB_ATheta_DiffusionYY_maxY3_0;
  Geom3DRB_ATheta_DiffusionYZ_maxY3 Geom3DRB_ATheta_DiffusionYZ_maxY3_0;
  Geom3DRB_ATheta_DiffusionZX_maxY3 Geom3DRB_ATheta_DiffusionZX_maxY3_0;
  Geom3DRB_ATheta_DiffusionZY_maxY3 Geom3DRB_ATheta_DiffusionZY_maxY3_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY3 Geom3DRB_ATheta_DiffusionZZ_maxY3_0;
  Geom3DRB_ATheta_DiffusionXX_maxY4 Geom3DRB_ATheta_DiffusionXX_maxY4_0;
  Geom3DRB_ATheta_DiffusionXY_maxY4 Geom3DRB_ATheta_DiffusionXY_maxY4_0;
  Geom3DRB_ATheta_DiffusionXZ_maxY4 Geom3DRB_ATheta_DiffusionXZ_maxY4_0;
  Geom3DRB_ATheta_DiffusionYX_maxY4 Geom3DRB_ATheta_DiffusionYX_maxY4_0;
  Geom3DRB_ATheta_DiffusionYY_maxY4 Geom3DRB_ATheta_DiffusionYY_maxY4_0;
  Geom3DRB_ATheta_DiffusionYZ_maxY4 Geom3DRB_ATheta_DiffusionYZ_maxY4_0;
  Geom3DRB_ATheta_DiffusionZX_maxY4 Geom3DRB_ATheta_DiffusionZX_maxY4_0;
  Geom3DRB_ATheta_DiffusionZY_maxY4 Geom3DRB_ATheta_DiffusionZY_maxY4_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY4 Geom3DRB_ATheta_DiffusionZZ_maxY4_0;
  Geom3DRB_ATheta_DiffusionXX_maxY5 Geom3DRB_ATheta_DiffusionXX_maxY5_0;
  Geom3DRB_ATheta_DiffusionXZ_maxY5 Geom3DRB_ATheta_DiffusionXZ_maxY5_0;
  Geom3DRB_ATheta_DiffusionYY_maxY5 Geom3DRB_ATheta_DiffusionYY_maxY5_0;
  Geom3DRB_ATheta_DiffusionZX_maxY5 Geom3DRB_ATheta_DiffusionZX_maxY5_0;
  Geom3DRB_ATheta_DiffusionZZ_maxY5 Geom3DRB_ATheta_DiffusionZZ_maxY5_0;
  Geom3DRB_ATheta_DiffusionXX_maxX1 Geom3DRB_ATheta_DiffusionXX_maxX1_0;
  Geom3DRB_ATheta_DiffusionXY_maxX1 Geom3DRB_ATheta_DiffusionXY_maxX1_0;
  Geom3DRB_ATheta_DiffusionXZ_maxX1 Geom3DRB_ATheta_DiffusionXZ_maxX1_0;
  Geom3DRB_ATheta_DiffusionYX_maxX1 Geom3DRB_ATheta_DiffusionYX_maxX1_0;
  Geom3DRB_ATheta_DiffusionYY_maxX1 Geom3DRB_ATheta_DiffusionYY_maxX1_0;
  Geom3DRB_ATheta_DiffusionYZ_maxX1 Geom3DRB_ATheta_DiffusionYZ_maxX1_0;
  Geom3DRB_ATheta_DiffusionZX_maxX1 Geom3DRB_ATheta_DiffusionZX_maxX1_0;
  Geom3DRB_ATheta_DiffusionZY_maxX1 Geom3DRB_ATheta_DiffusionZY_maxX1_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX1 Geom3DRB_ATheta_DiffusionZZ_maxX1_0;
  Geom3DRB_ATheta_DiffusionXX_maxX2 Geom3DRB_ATheta_DiffusionXX_maxX2_0;
  Geom3DRB_ATheta_DiffusionXY_maxX2 Geom3DRB_ATheta_DiffusionXY_maxX2_0;
  Geom3DRB_ATheta_DiffusionXZ_maxX2 Geom3DRB_ATheta_DiffusionXZ_maxX2_0;
  Geom3DRB_ATheta_DiffusionYX_maxX2 Geom3DRB_ATheta_DiffusionYX_maxX2_0;
  Geom3DRB_ATheta_DiffusionYY_maxX2 Geom3DRB_ATheta_DiffusionYY_maxX2_0;
  Geom3DRB_ATheta_DiffusionYZ_maxX2 Geom3DRB_ATheta_DiffusionYZ_maxX2_0;
  Geom3DRB_ATheta_DiffusionZX_maxX2 Geom3DRB_ATheta_DiffusionZX_maxX2_0;
  Geom3DRB_ATheta_DiffusionZY_maxX2 Geom3DRB_ATheta_DiffusionZY_maxX2_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX2 Geom3DRB_ATheta_DiffusionZZ_maxX2_0;
  Geom3DRB_ATheta_DiffusionXX_maxX3 Geom3DRB_ATheta_DiffusionXX_maxX3_0;
  Geom3DRB_ATheta_DiffusionXY_maxX3 Geom3DRB_ATheta_DiffusionXY_maxX3_0;
  Geom3DRB_ATheta_DiffusionXZ_maxX3 Geom3DRB_ATheta_DiffusionXZ_maxX3_0;
  Geom3DRB_ATheta_DiffusionYX_maxX3 Geom3DRB_ATheta_DiffusionYX_maxX3_0;
  Geom3DRB_ATheta_DiffusionYY_maxX3 Geom3DRB_ATheta_DiffusionYY_maxX3_0;
  Geom3DRB_ATheta_DiffusionYZ_maxX3 Geom3DRB_ATheta_DiffusionYZ_maxX3_0;
  Geom3DRB_ATheta_DiffusionZX_maxX3 Geom3DRB_ATheta_DiffusionZX_maxX3_0;
  Geom3DRB_ATheta_DiffusionZY_maxX3 Geom3DRB_ATheta_DiffusionZY_maxX3_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX3 Geom3DRB_ATheta_DiffusionZZ_maxX3_0;
  Geom3DRB_ATheta_DiffusionXX_maxX4 Geom3DRB_ATheta_DiffusionXX_maxX4_0;
  Geom3DRB_ATheta_DiffusionXY_maxX4 Geom3DRB_ATheta_DiffusionXY_maxX4_0;
  Geom3DRB_ATheta_DiffusionXZ_maxX4 Geom3DRB_ATheta_DiffusionXZ_maxX4_0;
  Geom3DRB_ATheta_DiffusionYX_maxX4 Geom3DRB_ATheta_DiffusionYX_maxX4_0;
  Geom3DRB_ATheta_DiffusionYY_maxX4 Geom3DRB_ATheta_DiffusionYY_maxX4_0;
  Geom3DRB_ATheta_DiffusionYZ_maxX4 Geom3DRB_ATheta_DiffusionYZ_maxX4_0;
  Geom3DRB_ATheta_DiffusionZX_maxX4 Geom3DRB_ATheta_DiffusionZX_maxX4_0;
  Geom3DRB_ATheta_DiffusionZY_maxX4 Geom3DRB_ATheta_DiffusionZY_maxX4_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX4 Geom3DRB_ATheta_DiffusionZZ_maxX4_0;
  Geom3DRB_ATheta_DiffusionXX_maxX5 Geom3DRB_ATheta_DiffusionXX_maxX5_0;
  Geom3DRB_ATheta_DiffusionYY_maxX5 Geom3DRB_ATheta_DiffusionYY_maxX5_0;
  Geom3DRB_ATheta_DiffusionYZ_maxX5 Geom3DRB_ATheta_DiffusionYZ_maxX5_0;
  Geom3DRB_ATheta_DiffusionZY_maxX5 Geom3DRB_ATheta_DiffusionZY_maxX5_0;
  Geom3DRB_ATheta_DiffusionZZ_maxX5 Geom3DRB_ATheta_DiffusionZZ_maxX5_0;
  Geom3DRB_ATheta_DiffusionXX_minY1 Geom3DRB_ATheta_DiffusionXX_minY1_0;
  Geom3DRB_ATheta_DiffusionXY_minY1 Geom3DRB_ATheta_DiffusionXY_minY1_0;
  Geom3DRB_ATheta_DiffusionXZ_minY1 Geom3DRB_ATheta_DiffusionXZ_minY1_0;
  Geom3DRB_ATheta_DiffusionYX_minY1 Geom3DRB_ATheta_DiffusionYX_minY1_0;
  Geom3DRB_ATheta_DiffusionYY_minY1 Geom3DRB_ATheta_DiffusionYY_minY1_0;
  Geom3DRB_ATheta_DiffusionYZ_minY1 Geom3DRB_ATheta_DiffusionYZ_minY1_0;
  Geom3DRB_ATheta_DiffusionZX_minY1 Geom3DRB_ATheta_DiffusionZX_minY1_0;
  Geom3DRB_ATheta_DiffusionZY_minY1 Geom3DRB_ATheta_DiffusionZY_minY1_0;
  Geom3DRB_ATheta_DiffusionZZ_minY1 Geom3DRB_ATheta_DiffusionZZ_minY1_0;
  Geom3DRB_ATheta_DiffusionXX_minY2 Geom3DRB_ATheta_DiffusionXX_minY2_0;
  Geom3DRB_ATheta_DiffusionXY_minY2 Geom3DRB_ATheta_DiffusionXY_minY2_0;
  Geom3DRB_ATheta_DiffusionXZ_minY2 Geom3DRB_ATheta_DiffusionXZ_minY2_0;
  Geom3DRB_ATheta_DiffusionYX_minY2 Geom3DRB_ATheta_DiffusionYX_minY2_0;
  Geom3DRB_ATheta_DiffusionYY_minY2 Geom3DRB_ATheta_DiffusionYY_minY2_0;
  Geom3DRB_ATheta_DiffusionYZ_minY2 Geom3DRB_ATheta_DiffusionYZ_minY2_0;
  Geom3DRB_ATheta_DiffusionZX_minY2 Geom3DRB_ATheta_DiffusionZX_minY2_0;
  Geom3DRB_ATheta_DiffusionZY_minY2 Geom3DRB_ATheta_DiffusionZY_minY2_0;
  Geom3DRB_ATheta_DiffusionZZ_minY2 Geom3DRB_ATheta_DiffusionZZ_minY2_0;
  Geom3DRB_ATheta_DiffusionXX_minY3 Geom3DRB_ATheta_DiffusionXX_minY3_0;
  Geom3DRB_ATheta_DiffusionXY_minY3 Geom3DRB_ATheta_DiffusionXY_minY3_0;
  Geom3DRB_ATheta_DiffusionXZ_minY3 Geom3DRB_ATheta_DiffusionXZ_minY3_0;
  Geom3DRB_ATheta_DiffusionYX_minY3 Geom3DRB_ATheta_DiffusionYX_minY3_0;
  Geom3DRB_ATheta_DiffusionYY_minY3 Geom3DRB_ATheta_DiffusionYY_minY3_0;
  Geom3DRB_ATheta_DiffusionYZ_minY3 Geom3DRB_ATheta_DiffusionYZ_minY3_0;
  Geom3DRB_ATheta_DiffusionZX_minY3 Geom3DRB_ATheta_DiffusionZX_minY3_0;
  Geom3DRB_ATheta_DiffusionZY_minY3 Geom3DRB_ATheta_DiffusionZY_minY3_0;
  Geom3DRB_ATheta_DiffusionZZ_minY3 Geom3DRB_ATheta_DiffusionZZ_minY3_0;
  Geom3DRB_ATheta_DiffusionXX_minY4 Geom3DRB_ATheta_DiffusionXX_minY4_0;
  Geom3DRB_ATheta_DiffusionXY_minY4 Geom3DRB_ATheta_DiffusionXY_minY4_0;
  Geom3DRB_ATheta_DiffusionXZ_minY4 Geom3DRB_ATheta_DiffusionXZ_minY4_0;
  Geom3DRB_ATheta_DiffusionYX_minY4 Geom3DRB_ATheta_DiffusionYX_minY4_0;
  Geom3DRB_ATheta_DiffusionYY_minY4 Geom3DRB_ATheta_DiffusionYY_minY4_0;
  Geom3DRB_ATheta_DiffusionYZ_minY4 Geom3DRB_ATheta_DiffusionYZ_minY4_0;
  Geom3DRB_ATheta_DiffusionZX_minY4 Geom3DRB_ATheta_DiffusionZX_minY4_0;
  Geom3DRB_ATheta_DiffusionZY_minY4 Geom3DRB_ATheta_DiffusionZY_minY4_0;
  Geom3DRB_ATheta_DiffusionZZ_minY4 Geom3DRB_ATheta_DiffusionZZ_minY4_0;
  Geom3DRB_ATheta_DiffusionXX_minY5 Geom3DRB_ATheta_DiffusionXX_minY5_0;
  Geom3DRB_ATheta_DiffusionXZ_minY5 Geom3DRB_ATheta_DiffusionXZ_minY5_0;
  Geom3DRB_ATheta_DiffusionYY_minY5 Geom3DRB_ATheta_DiffusionYY_minY5_0;
  Geom3DRB_ATheta_DiffusionZX_minY5 Geom3DRB_ATheta_DiffusionZX_minY5_0;
  Geom3DRB_ATheta_DiffusionZZ_minY5 Geom3DRB_ATheta_DiffusionZZ_minY5_0;
  Geom3DRB_ATheta_DiffusionXX_minZ1 Geom3DRB_ATheta_DiffusionXX_minZ1_0;
  Geom3DRB_ATheta_DiffusionXY_minZ1 Geom3DRB_ATheta_DiffusionXY_minZ1_0;
  Geom3DRB_ATheta_DiffusionXZ_minZ1 Geom3DRB_ATheta_DiffusionXZ_minZ1_0;
  Geom3DRB_ATheta_DiffusionYX_minZ1 Geom3DRB_ATheta_DiffusionYX_minZ1_0;
  Geom3DRB_ATheta_DiffusionYY_minZ1 Geom3DRB_ATheta_DiffusionYY_minZ1_0;
  Geom3DRB_ATheta_DiffusionYZ_minZ1 Geom3DRB_ATheta_DiffusionYZ_minZ1_0;
  Geom3DRB_ATheta_DiffusionZX_minZ1 Geom3DRB_ATheta_DiffusionZX_minZ1_0;
  Geom3DRB_ATheta_DiffusionZY_minZ1 Geom3DRB_ATheta_DiffusionZY_minZ1_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ1 Geom3DRB_ATheta_DiffusionZZ_minZ1_0;
  Geom3DRB_ATheta_DiffusionXX_minZ2 Geom3DRB_ATheta_DiffusionXX_minZ2_0;
  Geom3DRB_ATheta_DiffusionXY_minZ2 Geom3DRB_ATheta_DiffusionXY_minZ2_0;
  Geom3DRB_ATheta_DiffusionXZ_minZ2 Geom3DRB_ATheta_DiffusionXZ_minZ2_0;
  Geom3DRB_ATheta_DiffusionYX_minZ2 Geom3DRB_ATheta_DiffusionYX_minZ2_0;
  Geom3DRB_ATheta_DiffusionYY_minZ2 Geom3DRB_ATheta_DiffusionYY_minZ2_0;
  Geom3DRB_ATheta_DiffusionYZ_minZ2 Geom3DRB_ATheta_DiffusionYZ_minZ2_0;
  Geom3DRB_ATheta_DiffusionZX_minZ2 Geom3DRB_ATheta_DiffusionZX_minZ2_0;
  Geom3DRB_ATheta_DiffusionZY_minZ2 Geom3DRB_ATheta_DiffusionZY_minZ2_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ2 Geom3DRB_ATheta_DiffusionZZ_minZ2_0;
  Geom3DRB_ATheta_DiffusionXX_minZ3 Geom3DRB_ATheta_DiffusionXX_minZ3_0;
  Geom3DRB_ATheta_DiffusionXY_minZ3 Geom3DRB_ATheta_DiffusionXY_minZ3_0;
  Geom3DRB_ATheta_DiffusionXZ_minZ3 Geom3DRB_ATheta_DiffusionXZ_minZ3_0;
  Geom3DRB_ATheta_DiffusionYX_minZ3 Geom3DRB_ATheta_DiffusionYX_minZ3_0;
  Geom3DRB_ATheta_DiffusionYY_minZ3 Geom3DRB_ATheta_DiffusionYY_minZ3_0;
  Geom3DRB_ATheta_DiffusionYZ_minZ3 Geom3DRB_ATheta_DiffusionYZ_minZ3_0;
  Geom3DRB_ATheta_DiffusionZX_minZ3 Geom3DRB_ATheta_DiffusionZX_minZ3_0;
  Geom3DRB_ATheta_DiffusionZY_minZ3 Geom3DRB_ATheta_DiffusionZY_minZ3_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ3 Geom3DRB_ATheta_DiffusionZZ_minZ3_0;
  Geom3DRB_ATheta_DiffusionXX_minZ4 Geom3DRB_ATheta_DiffusionXX_minZ4_0;
  Geom3DRB_ATheta_DiffusionXY_minZ4 Geom3DRB_ATheta_DiffusionXY_minZ4_0;
  Geom3DRB_ATheta_DiffusionXZ_minZ4 Geom3DRB_ATheta_DiffusionXZ_minZ4_0;
  Geom3DRB_ATheta_DiffusionYX_minZ4 Geom3DRB_ATheta_DiffusionYX_minZ4_0;
  Geom3DRB_ATheta_DiffusionYY_minZ4 Geom3DRB_ATheta_DiffusionYY_minZ4_0;
  Geom3DRB_ATheta_DiffusionYZ_minZ4 Geom3DRB_ATheta_DiffusionYZ_minZ4_0;
  Geom3DRB_ATheta_DiffusionZX_minZ4 Geom3DRB_ATheta_DiffusionZX_minZ4_0;
  Geom3DRB_ATheta_DiffusionZY_minZ4 Geom3DRB_ATheta_DiffusionZY_minZ4_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ4 Geom3DRB_ATheta_DiffusionZZ_minZ4_0;
  Geom3DRB_ATheta_DiffusionXX_minZ5 Geom3DRB_ATheta_DiffusionXX_minZ5_0;
  Geom3DRB_ATheta_DiffusionXY_minZ5 Geom3DRB_ATheta_DiffusionXY_minZ5_0;
  Geom3DRB_ATheta_DiffusionYX_minZ5 Geom3DRB_ATheta_DiffusionYX_minZ5_0;
  Geom3DRB_ATheta_DiffusionYY_minZ5 Geom3DRB_ATheta_DiffusionYY_minZ5_0;
  Geom3DRB_ATheta_DiffusionZZ_minZ5 Geom3DRB_ATheta_DiffusionZZ_minZ5_0;
  Geom3DRB_ATheta_DiffusionXX_VesselCyl Geom3DRB_ATheta_DiffusionXX_VesselCyl_0;
  Geom3DRB_ATheta_DiffusionYY_VesselCyl Geom3DRB_ATheta_DiffusionYY_VesselCyl_0;
  Geom3DRB_ATheta_DiffusionZZ_VesselCyl Geom3DRB_ATheta_DiffusionZZ_VesselCyl_0;
  Geom3DRB_ATheta_DiffusionXX_BoundingBox Geom3DRB_ATheta_DiffusionXX_BoundingBox_0;
  Geom3DRB_ATheta_DiffusionYY_BoundingBox Geom3DRB_ATheta_DiffusionYY_BoundingBox_0;
  Geom3DRB_ATheta_DiffusionZZ_BoundingBox Geom3DRB_ATheta_DiffusionZZ_BoundingBox_0;
  Geom3DRB_ATheta_Perfusion_VesselCyl Geom3DRB_ATheta_Perfusion_VesselCyl_0;
  RBTheta _rb_theta;
public:
    jacobian_subdomain_1 rbtheta_subdomain_1;
    jacobian_subdomain_2 rbtheta_subdomain_2;
    jacobian_subdomain_3 rbtheta_subdomain_3;
    jacobian_subdomain_4 rbtheta_subdomain_4;
    jacobian_subdomain_5 rbtheta_subdomain_5;
    jacobian_subdomain_6 rbtheta_subdomain_6;
    jacobian_subdomain_7 rbtheta_subdomain_7;
    jacobian_subdomain_8 rbtheta_subdomain_8;
    jacobian_subdomain_9 rbtheta_subdomain_9;
    jacobian_subdomain_10 rbtheta_subdomain_10;
    jacobian_subdomain_11 rbtheta_subdomain_11;
    jacobian_subdomain_12 rbtheta_subdomain_12;
    jacobian_subdomain_13 rbtheta_subdomain_13;
    jacobian_subdomain_14 rbtheta_subdomain_14;
    jacobian_subdomain_15 rbtheta_subdomain_15;
    jacobian_subdomain_16 rbtheta_subdomain_16;
    jacobian_subdomain_17 rbtheta_subdomain_17;
    jacobian_subdomain_18 rbtheta_subdomain_18;
    jacobian_subdomain_19 rbtheta_subdomain_19;
    jacobian_subdomain_20 rbtheta_subdomain_20;
    jacobian_subdomain_21 rbtheta_subdomain_21;
    jacobian_subdomain_22 rbtheta_subdomain_22;
    jacobian_subdomain_23 rbtheta_subdomain_23;
    jacobian_subdomain_24 rbtheta_subdomain_24;
    jacobian_subdomain_25 rbtheta_subdomain_25;
    jacobian_subdomain_26 rbtheta_subdomain_26;
    jacobian_subdomain_27 rbtheta_subdomain_27;
    jacobian_subdomain_28 rbtheta_subdomain_28;
    jacobian_subdomain_29 rbtheta_subdomain_29;
    jacobian_subdomain_30 rbtheta_subdomain_30;
    jacobian_subdomain_31 rbtheta_subdomain_31;
    jacobian_subdomain_32 rbtheta_subdomain_32;
    std::vector<RBTheta *> subdomain_jac_rbthetas;
    unsigned int num_subdomains;
};

struct DummyMAssembly : ElemAssembly
{
  virtual void interior_assembly(FEMContext & /*dummy*/)
  { }
};

struct DwarfElephantRBCustomTransientAssemblyExpansion : TransientRBAssemblyExpansion
{
  DwarfElephantRBCustomTransientAssemblyExpansion()
  {
    attach_M_assembly(&M0);
    attach_M_assembly(&M1);
    attach_M_assembly(&M2);
    attach_M_assembly(&M3);
    attach_M_assembly(&M4);
    attach_M_assembly(&M5);
    attach_M_assembly(&M6);
    attach_M_assembly(&M7);
    attach_M_assembly(&M8);
    attach_M_assembly(&M9);
    attach_M_assembly(&M10);
    attach_M_assembly(&M11);
    attach_M_assembly(&M12);
    attach_M_assembly(&M13);
    attach_M_assembly(&M14);
    attach_M_assembly(&M15);
    attach_M_assembly(&M16);
    attach_M_assembly(&M17);
    attach_M_assembly(&M18);
    attach_M_assembly(&M19);
    attach_M_assembly(&M20);
    attach_M_assembly(&M21);
    attach_M_assembly(&M22);
    attach_M_assembly(&M23);
    attach_M_assembly(&M24);
    attach_M_assembly(&M25);
    attach_M_assembly(&M26);
    attach_M_assembly(&M27);
    attach_M_assembly(&M28);
    attach_M_assembly(&M29);
    attach_M_assembly(&M30);
    attach_M_assembly(&M31);
    
    
  }
  DummyMAssembly M0;
  DummyMAssembly M1;
  DummyMAssembly M2;
  DummyMAssembly M3;
  DummyMAssembly M4;
  DummyMAssembly M5;
  DummyMAssembly M6;
  DummyMAssembly M7;
  DummyMAssembly M8;
  DummyMAssembly M9;
  DummyMAssembly M10;
  DummyMAssembly M11;
  DummyMAssembly M12;
  DummyMAssembly M13;
  DummyMAssembly M14;
  DummyMAssembly M15;
  DummyMAssembly M16;
  DummyMAssembly M17;
  DummyMAssembly M18;
  DummyMAssembly M19;
  DummyMAssembly M20;
  DummyMAssembly M21;
  DummyMAssembly M22;
  DummyMAssembly M23;
  DummyMAssembly M24;
  DummyMAssembly M25;
  DummyMAssembly M26;
  DummyMAssembly M27;
  DummyMAssembly M28;
  DummyMAssembly M29;
  DummyMAssembly M30;
  DummyMAssembly M31;
  
};

struct M_theta_10 : TransientRBThetaExpansion
{
  M_theta_10()
  {
    for (unsigned int i=0; i < 10; i++)
      attach_M_theta(&_rb_theta);

    for (unsigned int i=0; i < 32; i++)
     subdomain_jac_rbthetas.push_back(&_rb_theta);
    
    num_subdomains = 32;
}
  RBTheta _rb_theta;
public:
    
    std::vector<RBTheta *> subdomain_jac_rbthetas;
    unsigned int num_subdomains;
};

struct QM_10 : TransientRBAssemblyExpansion
{
  QM_10()
  {
    for (unsigned int i = 0; i < 10; i++)
      attach_M_assembly(&M0);    
  }
  DummyMAssembly M0;
};

struct A_theta_10 : TransientRBThetaExpansion
{
  A_theta_10()
  {
    for (unsigned int i=0; i < 10; i++)
      attach_A_theta(&_rb_theta);
    
    attach_F_theta(&_rb_theta);

    for (unsigned int i=0; i < 32; i++)
     subdomain_jac_rbthetas.push_back(&_rb_theta);
    
    num_subdomains = 32;
}
  RBTheta _rb_theta;
public:
    
    std::vector<RBTheta *> subdomain_jac_rbthetas;
    unsigned int num_subdomains;
};

struct QM_0 : TransientRBAssemblyExpansion
{
  QM_0()
  {  
  }
  DummyMAssembly M0;
};

struct BC_heat_source_thetas : TransientRBThetaExpansion
{
  BC_heat_source_thetas()
  {
    attach_A_theta(&_rb_theta);
    attach_F_theta(&_rb_theta);
    for (unsigned int i=0; i < 32; i++)
      attach_F_theta(&_rb_theta);

    for (unsigned int i=0; i < 32; i++)
     subdomain_jac_rbthetas.push_back(&_rb_theta);
    
    num_subdomains = 32;
}
  RBTheta _rb_theta;
public:
    
    std::vector<RBTheta *> subdomain_jac_rbthetas;
    unsigned int num_subdomains;
};
//------------------------------
#endif // DWARFELEPHANTGEOM3DTRANSIENTRBTHETAEXPANSION_RFA_H
