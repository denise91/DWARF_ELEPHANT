/* This UserObject is required to initialitze the RB system structure
 * and transfer for the transient case.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTINITIALIZERBSYSTEMTRANSIENTT3F3O1M1LIFTING_H
#define TESTDWARFELEPHANTINITIALIZERBSYSTEMTRANSIENTT3F3O1M1LIFTING_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantInitializeRBSystemTransient.h"
#include "TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantInitializeRBSystemTransient;
class TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting;
class TestDwarfElephantInitializeRBSystemTransientT3F3O1M1Lifting;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantRBEvaluationTransientT3F3O1M1Lifting>();

///This UserObject is required to initialitze the RB system structure and transfer for the transient case.
class TestDwarfElephantInitializeRBSystemTransientT3F3O1M1Lifting :
  public DwarfElephantInitializeRBSystemTransient
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantInitializeRBSystemTransientT3F3O1M1Lifting(const InputParameters & params);

    /* Methods */
    // Method not used in this UserObject.
    // virtual void execute() override;
    void execute();
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTINITIALIZERBSYSTEMTRANSIENTT3F3O1M1Lifting_H
