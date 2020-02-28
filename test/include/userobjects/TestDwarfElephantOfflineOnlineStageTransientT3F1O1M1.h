/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the transient case.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT3F1O1M1_H
#define TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT3F1O1M1_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageTransient.h"
#include "TestDwarfElephantRBEvaluationTransientT3F1O1M1.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageTransientT3F1O1M1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageTransientT3F1O1M1>();

///This UserObject implements the Offline and Online stage of the RB method for the transient case.
class TestDwarfElephantOfflineOnlineStageTransientT3F1O1M1 :
  public DwarfElephantOfflineOnlineStageTransient
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageTransientT3F1O1M1(const InputParameters & params);

    /* Methods */
    virtual void execute() override;
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT3F1O1M1_H
