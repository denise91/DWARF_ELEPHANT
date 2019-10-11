#include "DwarfElephantRBTimeStepper.h"


DwarfElephantRBTimeStepper::DwarfElephantRBTimeStepper(FEProblemBase & fe_problem):
fe_problem(fe_problem)
{}

Real
DwarfElephantRBTimeStepper::computeDT(Real & current_dt, unsigned int & time_level){
    return current_dt;
}
