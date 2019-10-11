#include "DwarfElephantRBTimeSequenceStepper.h"


DwarfElephantRBTimeSequenceStepper::DwarfElephantRBTimeSequenceStepper(FEProblemBase & fe_problem):
DwarfElephantRBTimeStepper(fe_problem)
{}

Real
DwarfElephantRBTimeSequenceStepper::computeDT(Real & current_dt, unsigned int & time_level)
{
    DwarfElephantRBProblem & rb_problem = cast_ref<DwarfElephantRBProblem &>(fe_problem);

    std::vector<Real> time_sequence = rb_problem.getTimeSequence();
    return time_sequence[time_level];
}
