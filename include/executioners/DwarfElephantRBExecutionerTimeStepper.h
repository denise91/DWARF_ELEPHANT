/**
 * This Executioner class is required to execute the RB method directly over
 * the libMesh system. It is for both the steady state and transient case.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBEXECUTIONERTIMESTEPPER_H
#define DWARFELEPHANTRBEXECUTIONERTIMESTEPPER_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "Transient.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantRBExecutionerTimeStepper;

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBExecutionerTimeStepper>();

///This Executioner class is required to execute the RB method directly over the libMesh system. It is for both the steady state and transient case.
class DwarfElephantRBExecutionerTimeStepper :
  public Transient
{
//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantRBExecutionerTimeStepper(const InputParameters & params);

    /*Methods*/
    void execute() override;

//--------------------------------PROTECTED---------------------------------
  protected:
    /*Attributes*/
    bool _offline_stage;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBEXECUTIONERTIMESTEPPER_H
