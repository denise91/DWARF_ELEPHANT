/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBTIMESTEPPER_H
#define DWARFELEPHANTRBTIMESTEPPER_H

#include "FEProblemBase.h"
// #include "DwarfElephantRBClassesTransient.h"

class FEProblemBase;

class DwarfElephantRBTimeStepper{

public:
  // Constructor
  DwarfElephantRBTimeStepper (FEProblemBase & fe_problem);

  // Destructor
  virtual ~DwarfElephantRBTimeStepper () { }

  virtual Real computeDT(Real & current_dt, unsigned int & time_level);

  FEProblemBase & fe_problem;

};

#endif
