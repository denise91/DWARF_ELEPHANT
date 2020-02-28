/* This UserObject is required to initialitze the RB system structure
 * and transfer for the transient case.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTINITIALIZERBSYSTEMTRANSIENTT3F3O1M1_H
#define TESTDWARFELEPHANTINITIALIZERBSYSTEMTRANSIENTT3F3O1M1_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantInitializeRBSystemTransient.h"
#include "TestDwarfElephantRBEvaluationTransientT3F3O1M1.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantInitializeRBSystemTransient;
class TestDwarfElephantRBEvaluationTransientT3F3O1M1;
class TestDwarfElephantInitializeRBSystemTransientT3F3O1M1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantRBEvaluationTransientT3F3O1M1>();

///This UserObject is required to initialitze the RB system structure and transfer for the transient case.
class TestDwarfElephantInitializeRBSystemTransientT3F3O1M1 :
  public DwarfElephantInitializeRBSystemTransient
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantInitializeRBSystemTransientT3F3O1M1(const InputParameters & params);

    /* Methods */
    // Method not used in this UserObject.
    // virtual void execute() override;
    void execute();
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTINITIALIZERBSYSTEMTRANSIENTT3F3O1M1_H
