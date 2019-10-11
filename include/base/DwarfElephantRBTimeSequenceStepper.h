/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBTIMESEQUENCESTEPPER_H
#define DWARFELEPHANTRBTIMESEQUENCESTEPPER_H

#include "DwarfElephantRBTimeStepper.h"
#include "DwarfElephantRBProblem.h"

class DwarfElephantRBProblem;

class DwarfElephantRBTimeSequenceStepper: public DwarfElephantRBTimeStepper{

public:
  // Constructor
  DwarfElephantRBTimeSequenceStepper (FEProblemBase & fe_problem);

  // Destructor
  virtual ~DwarfElephantRBTimeSequenceStepper () { }

  virtual Real computeDT(Real & current_dt, unsigned int & time_level) override;

};

#endif
