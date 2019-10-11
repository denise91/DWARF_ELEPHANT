#include "DwarfElephantRBGrowthRateTimeStepper.h"


DwarfElephantRBGrowthRateTimeStepper::DwarfElephantRBGrowthRateTimeStepper(FEProblemBase & fe_problem):
DwarfElephantRBTimeStepper(fe_problem)
{}

Real
DwarfElephantRBGrowthRateTimeStepper::computeDT(Real & current_dt, unsigned int & time_level)
{
    DwarfElephantRBProblem & rb_problem = cast_ref<DwarfElephantRBProblem &>(fe_problem);

    if(current_dt < rb_problem.getThreshold())
      current_dt *= rb_problem.getGrowthRate();
    return current_dt;
}
