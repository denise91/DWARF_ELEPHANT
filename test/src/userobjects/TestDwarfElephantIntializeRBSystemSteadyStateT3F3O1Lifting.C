 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "TestDwarfElephantInitializeRBSystemSteadyStateT3F3O1Lifting.h"

registerMooseObject("DwarfElephantApp", TestDwarfElephantInitializeRBSystemSteadyStateT3F3O1Lifting);

template<>
InputParameters validParams<TestDwarfElephantInitializeRBSystemSteadyStateT3F3O1Lifting>()
{
  InputParameters params = validParams<DwarfElephantInitializeRBSystemSteadyState>();
  return params;
}

TestDwarfElephantInitializeRBSystemSteadyStateT3F3O1Lifting::TestDwarfElephantInitializeRBSystemSteadyStateT3F3O1Lifting(const InputParameters & params):
  DwarfElephantInitializeRBSystemSteadyState(params)
{
}

void
TestDwarfElephantInitializeRBSystemSteadyStateT3F3O1Lifting::execute()
{
  // Define the parameter file for the libMesh functions.
  // In our case not required, because the read-in is done via the MOOSE inputfile.
  // GetPot infile (_parameters_filename);

  // Add a new equation system for the RB construction.
  _rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionSteadyState> ("RBSystem");

  // Intialization of the added equation system
  if(_offline_stage)
  {
    _rb_con_ptr->init();
    _es.update();

    TestDwarfElephantRBEvaluationSteadyStateT3F3O1Lifting _rb_eval(_mesh_ptr->comm(), _fe_problem);
    // Pass a pointer of the RBEvaluation object to the
    // RBConstruction object
    _rb_con_ptr->set_rb_evaluation(_rb_eval);

    // Get number of attached parameters.
    _n_outputs = _rb_con_ptr->get_rb_theta_expansion().get_n_outputs();
    _ql.resize(_n_outputs);
    _qa = _rb_con_ptr->get_rb_theta_expansion().get_n_A_terms();
    _qf = _rb_con_ptr->get_rb_theta_expansion().get_n_F_terms();

    for(unsigned int i=0; i < _n_outputs; i++)
      _ql[i] = _rb_con_ptr->get_rb_theta_expansion().get_n_output_terms(i);

    initializeOfflineStage();
  }
}
