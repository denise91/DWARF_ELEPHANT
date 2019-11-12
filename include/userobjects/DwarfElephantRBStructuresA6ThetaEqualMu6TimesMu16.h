///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESA6THETAEQUALMU6TIMESMU16_H
#define DWARFELEPHANTRBSTRUCTURESA6THETAEQUALMU6TIMESMU16_H

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

struct DwarfElephantThetaA6EqualMu6TimesMu16 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return (_mu.get_value("mu_6")*_mu.get_value("mu_16"));
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESA6THETAEQUALMU6TIMESMU16_H
