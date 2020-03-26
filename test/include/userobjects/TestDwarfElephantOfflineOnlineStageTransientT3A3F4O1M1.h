/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the transient case.
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageTransient.h"
#include "TestDwarfElephantRBEvaluationTransientT3A3F4O1M1.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageTransientT3A3F4O1M1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageTransientT3A3F4O1M1>();

///This UserObject implements the Offline and Online stage of the RB method for the transient case.
class TestDwarfElephantOfflineOnlineStageTransientT3A3F4O1M1 :
  public DwarfElephantOfflineOnlineStageTransient
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageTransientT3A3F4O1M1(const InputParameters & params);

    /* Methods */
    virtual void execute() override;
};
