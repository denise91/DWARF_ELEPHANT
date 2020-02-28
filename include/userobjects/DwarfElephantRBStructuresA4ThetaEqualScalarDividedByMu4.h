///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESA4THETAEQUALSCALARDIVIDEDBYMU4_H
#define DWARFELEPHANTRBSTRUCTURESA4THETAEQUALSCALARDIVIDEDBYMU4_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"


// Forward Declarations
namespace libMesh
{
  class RBParameters;
  class RBTheta;
}

/**
 * Please take the name convention of this package for the mu object into
 * account to ensure a gernal useability of your class.
 */

struct DwarfElephantThetaA4EqualScalarDividedByMu4 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return (1.0/_mu.get_value("mu_4"));
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESA4THETAEQUALSCALARDIVIDEDBYMU4_H
