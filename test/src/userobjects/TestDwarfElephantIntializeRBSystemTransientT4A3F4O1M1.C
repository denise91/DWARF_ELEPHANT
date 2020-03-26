 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "TestDwarfElephantInitializeRBSystemTransientT4A3F4O1M1.h"

registerMooseObject("DwarfElephantApp", TestDwarfElephantInitializeRBSystemTransientT4A3F4O1M1);

template<>
InputParameters validParams<TestDwarfElephantInitializeRBSystemTransientT4A3F4O1M1>()
{
  InputParameters params = validParams<DwarfElephantInitializeRBSystemTransient>();
    return params;
}

TestDwarfElephantInitializeRBSystemTransientT4A3F4O1M1::TestDwarfElephantInitializeRBSystemTransientT4A3F4O1M1(const InputParameters & params):
  DwarfElephantInitializeRBSystemTransient(params)
{
}

void
TestDwarfElephantInitializeRBSystemTransientT4A3F4O1M1::execute()
{
  if(!_initialized){
  // Define the parameter file for the libMesh functions.
  // GetPot infile (_parameters_filename);

  // Add a new equation system for the RB construction.
  _rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionTransient> ("RBSystem");

  if (_offline_stage){
    // Intialization of the added equation system
    _rb_con_ptr->init();
    _es.update();

    TestDwarfElephantRBEvaluationTransientT4A3F4O1M1 _rb_eval(_mesh_ptr->comm(), _fe_problem);
    // Pass a pointer of the RBEvaluation object to the
    // RBConstruction object
    _rb_con_ptr->set_rb_evaluation(_rb_eval);

    TransientRBThetaExpansion & _trans_theta_expansion = cast_ref<TransientRBThetaExpansion &>(_rb_con_ptr->get_rb_theta_expansion());

    // Get number of attached parameters.
    _n_outputs = _rb_con_ptr->get_rb_theta_expansion().get_n_outputs();
    _ql.resize(_n_outputs);
    _qa = _rb_con_ptr->get_rb_theta_expansion().get_n_A_terms();
    _qm = _trans_theta_expansion.get_n_M_terms();
    _qf = _rb_con_ptr->get_rb_theta_expansion().get_n_F_terms();

    if(_parameter_dependent_IC)
    {
      DwarfElephantRBTransientThetaExpansion & dwarf_elephant_trans_theta_expansion =
        cast_ref<DwarfElephantRBTransientThetaExpansion &>(_rb_con_ptr->get_rb_theta_expansion());

        _q_ic = dwarf_elephant_trans_theta_expansion.get_n_IC_terms();
    }

    for(unsigned int i=0; i < _n_outputs; i++)
    _ql[i] = _rb_con_ptr->get_rb_theta_expansion().get_n_output_terms(i);

    // Initialize required matrices and vectors.
      initializeOfflineStage();
  }
   _initialized = true;
  }
}
