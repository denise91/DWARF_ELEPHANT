/* This UserObject is required to initialitze the RB system structure
 * and transfer for the steady state case.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "TestDwarfElephantRBEvaluationSteadyStateT3A3F1O1.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantInitializeRBSystemSteadyState;
class TestDwarfElephantRBEvaluationSteadyStateT3A3F1O1;
class TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O1>();

///This UserObject is required to initialitze the RB system structure and transfer for the steady state case.
class TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O1 :
  public DwarfElephantInitializeRBSystemSteadyState
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantInitializeRBSystemSteadyStateT3A3F1O1(const InputParameters & params);

    virtual void execute() override;
};
