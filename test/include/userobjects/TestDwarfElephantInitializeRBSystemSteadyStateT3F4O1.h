/* This UserObject is required to initialitze the RB system structure
 * and transfer for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef TESTDWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATET3F4O1_H
#define TESTDWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATET3F4O1_H

///---------------------------------INCLUDES--------------------------------
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "TestDwarfElephantRBEvaluationSteadyStateT3F4O1.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantInitializeRBSystemSteadyState;
class TestDwarfElephantRBEvaluationSteadyStateT3F4O1;
class TestDwarfElephantInitializeRBSystemSteadyStateT3F4O1;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantInitializeRBSystemSteadyStateT3F4O1>();

///This UserObject is required to initialitze the RB system structure and transfer for the steady state case.
class TestDwarfElephantInitializeRBSystemSteadyStateT3F4O1 :
  public DwarfElephantInitializeRBSystemSteadyState
{

//----------------------------------PUBLIC----------------------------------
  public:
    TestDwarfElephantInitializeRBSystemSteadyStateT3F4O1(const InputParameters & params);

    virtual void execute() override;

    friend class TestDwarfElephantRBEvaluationSteadyStateT3F4O1;
};
///-------------------------------------------------------------------------
#endif // TESTDWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATET3F4O1_H
