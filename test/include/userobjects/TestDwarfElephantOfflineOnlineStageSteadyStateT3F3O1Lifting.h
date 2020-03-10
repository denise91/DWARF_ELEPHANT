/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef TestDwarfElephantOfflineOnlineStageSteadyStateT3F3O1Lifting_H
#define TestDwarfElephantOfflineOnlineStageSteadyStateT3F3O1Lifting_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageSteadyState.h"
#include "TestDwarfElephantRBEvaluationSteadyStateT3F3O1Lifting.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageSteadyStateT3F3O1Lifting;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageSteadyStateT3F3O1Lifting>();

///This UserObject implements the Offline and Online stage of the RB method for the steady state case.
class TestDwarfElephantOfflineOnlineStageSteadyStateT3F3O1Lifting :
  public DwarfElephantOfflineOnlineStageSteadyState
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageSteadyStateT3F3O1Lifting(const InputParameters & params);


    /* Methods */
    virtual void execute() override;
};
///-------------------------------------------------------------------------
#endif // TESTDwarfElephantOfflineOnlineStageSteadyStateT3F3O1Lifting_H
