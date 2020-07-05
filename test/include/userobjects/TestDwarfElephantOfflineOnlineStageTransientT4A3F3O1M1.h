/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the transient case.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageTransient.h"
#include "TestDwarfElephantRBEvaluationTransientT4A3F3O1M1.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageTransientT4A3F3O1M1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageTransientT4A3F3O1M1>();

///This UserObject implements the Offline and Online stage of the RB method for the transient case.
class TestDwarfElephantOfflineOnlineStageTransientT4A3F3O1M1 :
  public DwarfElephantOfflineOnlineStageTransient
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageTransientT4A3F3O1M1(const InputParameters & params);

    /* Methods */
    virtual void execute() override;
};