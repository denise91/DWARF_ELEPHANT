/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the steady state case.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageSteadyState.h"
#include "TestDwarfElephantRBEvaluationSteadyStateT3A3F1O21Inverse.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageSteadyStateT3A3F1O21Inverse;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageSteadyStateT3A3F1O21Inverse>();

///This UserObject implements the Offline and Online stage of the RB method for the steady state case.
class TestDwarfElephantOfflineOnlineStageSteadyStateT3A3F1O21Inverse :
  public DwarfElephantOfflineOnlineStageSteadyState
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageSteadyStateT3A3F1O21Inverse(const InputParameters & params);


    /* Methods */
    virtual void execute() override;
};
