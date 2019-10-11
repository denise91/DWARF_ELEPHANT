/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBGROWTHRATETIMESTEPPER_H
#define DWARFELEPHANTRBGROWTHRATETIMESTEPPER_H

#include "DwarfElephantRBTimeStepper.h"
#include "DwarfElephantRBProblem.h"

class DwarfElephantRBProblem;

class DwarfElephantRBGrowthRateTimeStepper: public DwarfElephantRBTimeStepper{

public:
  // Constructor
  DwarfElephantRBGrowthRateTimeStepper (FEProblemBase & fe_problem);

  // Destructor
  virtual ~DwarfElephantRBGrowthRateTimeStepper () { }

  virtual Real computeDT(Real & current_dt, unsigned int & time_level) override;

};

#endif
