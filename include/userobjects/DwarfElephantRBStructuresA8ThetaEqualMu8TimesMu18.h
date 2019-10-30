///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESA8THETAEQUALMU8TIMESMU18_H
#define DWARFELEPHANTRBSTRUCTURESA8THETAEQUALMU8TIMESMU18_H

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

struct DwarfElephantThetaA8EqualMu8TimesMu18 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return (_mu.get_value("mu_8")*_mu.get_value("mu_18"));
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESA8THETAEQUALMU8TIMESMU18_H
