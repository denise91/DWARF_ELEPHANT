/**
 * This UserObject implements the Offline and Online stage of the RB method
 * for the transient case.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT3F3O1M1LIFTING_H
#define TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT3F3O1M1LIFTING_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantOfflineOnlineStageTransient.h"
#include "TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting.h"


///-------------------------------------------------------------------------
// Forward Declarations
class TestDwarfElephantOfflineOnlineStageTransientT3F3O1M1Lifting;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageTransientT3F3O1M1Lifting>();

///This UserObject implements the Offline and Online stage of the RB method for the transient case.
class TestDwarfElephantOfflineOnlineStageTransientT3F3O1M1Lifting :
  public DwarfElephantOfflineOnlineStageTransient
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantOfflineOnlineStageTransientT3F3O1M1Lifting(const InputParameters & params);

    /* Methods */
    virtual void execute() override;
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTOFFLINEONLINESTAGETRANSIENTT3F3O1M1Lifting_H
