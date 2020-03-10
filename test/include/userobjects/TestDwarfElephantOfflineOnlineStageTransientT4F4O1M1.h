/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the transient case.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT4F4O1M1_H
#define TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT4F4O1M1_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageTransient.h"
#include "TestDwarfElephantRBEvaluationTransientT4F4O1M1.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageTransientT4F4O1M1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageTransientT4F4O1M1>();

///This UserObject implements the Offline and Online stage of the RB method for the transient case.
class TestDwarfElephantOfflineOnlineStageTransientT4F4O1M1 :
  public DwarfElephantOfflineOnlineStageTransient
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageTransientT4F4O1M1(const InputParameters & params);

    /* Methods */
    virtual void execute() override;
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT4F4O1M1_H
