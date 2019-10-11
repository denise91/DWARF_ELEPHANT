 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBExecutionerTimeStepper.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBExecutionerTimeStepper);

template<>
InputParameters validParams<DwarfElephantRBExecutionerTimeStepper>()
{
  InputParameters params = validParams<Transient>();
  params.addParam<bool>("offline_stage", true, "Determines whether the Offline stage will be calculated or not.");
  return params;
}

DwarfElephantRBExecutionerTimeStepper::DwarfElephantRBExecutionerTimeStepper(const InputParameters & params):
  Transient(params),
  _offline_stage(getParam<bool>("offline_stage"))
{
}

void
DwarfElephantRBExecutionerTimeStepper::execute()
{
  if (_app.isRecovering())
    return;

  preExecute();

  _problem.advanceState();

  // first step in any steady state solve is always 1 (preserving backwards compatibility)
  // _time_step = 1;
  _time = _t_step;                 // need to keep _time in sync with _time_step to get correct output

// #ifdef LIBMESH_ENABLE_AMR
//
//   // Define the refinement loop
//   unsigned int steps = _problem.adaptivity().getSteps();
//   for (unsigned int r_step=0; r_step<=steps; r_step++)
//   {
// #endif //LIBMESH_ENABLE_AMR
    preSolve();
    _problem.timestepSetup();
    _problem.execute(EXEC_TIMESTEP_BEGIN);
    _problem.outputStep(EXEC_TIMESTEP_BEGIN);

    // Update warehouse active objects
    _problem.updateActiveObjects();

    if (_offline_stage)
      _problem.solve();
    postSolve();

    _problem.onTimestepEnd();
    // _problem.execute(EXEC_CUSTOM);
    _problem.execute(EXEC_TIMESTEP_END);
    // _problem.outputStep(EXEC_CUSTOM);

    // if(_simulation_type == "steady")
    // {
    //   // _problem.computeIndicators();
    //   // _problem.computeMarkers();
    //   //
    //   // _problem.execute(EXEC_CUSTOM);
    //   // _problem.outputStep(EXEC_TIMESTEP_END);
    //   // _problem.outputStep(EXEC_CUSTOM);
    // }

// #ifdef LIBMESH_ENABLE_AMR
//     if (r_step != steps)
//     {
//       _problem.adaptMesh();
//     }
//   }
// #endif

    {
      TIME_SECTION(_final_timer)
      _problem.execute(EXEC_FINAL);
      _problem.outputStep(EXEC_FINAL);
    }

  postExecute();
}
