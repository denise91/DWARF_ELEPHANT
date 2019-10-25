///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESA00THETACONSTANT_H
#define DWARFELEPHANTRBSTRUCTURESA00THETACONSTANT_H

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

struct DwarfElephantThetaA00Constant : RBTheta
{
  virtual Number evaluate (const RBParameters & )
  {
    return 0;
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESA00THETACONSTANT_H
