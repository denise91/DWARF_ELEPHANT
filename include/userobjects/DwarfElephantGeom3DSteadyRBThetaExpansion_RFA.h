///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTGEOM3DSTEADYRBTHETAEXPANSION_RFA_H
#define DWARFELEPHANTGEOM3DSTEADYRBTHETAEXPANSION_RFA_H

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
  class SteadyRBThetaExpansion;
}
///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */
struct TissueDiff_theta : RBTheta
{
    virtual Number evaluate(const RBParameters &_mu)
    {
        return 0.8;
    }
};

struct BloodDiff_theta : RBTheta
{
    virtual Number evaluate(const RBParameters &_mu)
    {
        return 0.52;
    }
};

struct Perf_theta : RBTheta
{
    virtual Number evaluate(const RBParameters &_mu)
    {
        return 1.9e5;//0;//
    }
};
struct Geom3DSteadyRBThetaExpansion : RBThetaExpansion
{
  Geom3DSteadyRBThetaExpansion()
  {
    attach_A_theta(&_rb_theta);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_F_theta(&_rb_theta);


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
public:
    TissueDiff_theta _theta_a_1;
    BloodDiff_theta _theta_a_2;
    Perf_theta _theta_a_3;
    RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
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

//------------------------------
#endif // DWARFELEPHANTGEOM3DSTEADYRBTHETAEXPANSION_RFA_H
