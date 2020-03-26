/**
 * This UserObject implements the Offline and Online stage of the RB method.
 */

//---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "TestDwarfElephantOfflineOnlineStageSteadyStateT3A4F1O1.h"

registerMooseObject("DwarfElephantApp", TestDwarfElephantOfflineOnlineStageSteadyStateT3A4F1O1);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageSteadyStateT3A4F1O1>()
{
    InputParameters params = validParams<DwarfElephantOfflineOnlineStageSteadyState>();
    return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
TestDwarfElephantOfflineOnlineStageSteadyStateT3A4F1O1::TestDwarfElephantOfflineOnlineStageSteadyStateT3A4F1O1(const InputParameters & params):
    DwarfElephantOfflineOnlineStageSteadyState(params)
{
  if(_online_stage==true & _online_mu_parameters.size()==0)
    mooseError("You have not defined the online parameters.");
}

void
TestDwarfElephantOfflineOnlineStageSteadyStateT3A4F1O1::execute()
{
    // Build the RBEvaluation object
    // Required for both the Offline and Online stage.
    TestDwarfElephantRBEvaluationSteadyStateT3A4F1O1 _rb_eval(comm() , _fe_problem);
    // Pass a pointer of the RBEvaluation object to the
    // RBConstruction object

    if(!_offline_stage && (_output_file || _store_basis_functions_sorted))
      _rb_con_ptr->init();


    if(_offline_stage || _output_file || _offline_error_bound || _online_N == 0 || _store_basis_functions_sorted)
      _rb_con_ptr->set_rb_evaluation(_rb_eval);

    if (_offline_stage)
    {
       // Transfer the affine vectors to the RB system.
       if(_skip_vector_assembly_in_rb_system)
        transferAffineVectors();

      // Transfer the affine matrices to the RB system.
      if(_skip_matrix_assembly_in_rb_system)
        setAffineMatrices();

      // Perform the offline stage.
      _console << std::endl;
      offlineStage();
      _console << std::endl;
    }

    if(_online_stage)
    {
      {
      TIME_SECTION(_online_stage_timer);
      // for older MOOSE versions that are using the PerfLog
      // Moose::perf_log.push("onlineStage()", "Execution");

      #if defined(LIBMESH_HAVE_CAPNPROTO)
        RBDataDeserialization::RBEvaluationDeserialization _rb_eval_reader(_rb_eval);
      #else
        _rb_eval.legacy_read_offline_data_from_files(_offline_data_name, true, true);
      #endif

      // _norm_factor = 1.0;//_rb_eval.get_error_bound_normalization();

      if(_online_N==0)
        _online_N = _rb_con_ptr->get_rb_evaluation().get_n_basis_functions();


      setOnlineParameters();
      _rb_eval.set_parameters(_rb_online_mu);

      _console << "---- Online Stage ----" << std::endl;
      _rb_eval.print_parameters();

      if(_offline_error_bound)
       _rb_con_ptr->get_rb_evaluation().evaluate_RB_error_bound = false;

      _rb_eval.rb_solve(_online_N);

      }
      {
      TIME_SECTION(_data_transfer_timer);
      // for older MOOSE versions that are using the PerfLog
      // Moose::perf_log.pop("onlineStage()", "Execution");
      // Back transfer of the data to use MOOSE Postprocessor and Output classes
      // Moose::perf_log.push("DataTransfer()", "Execution");

      if (_output_console)
        for (unsigned int i = 0; i != _n_outputs; i++)
          _console << "Output " << std::to_string(i) << ": value = " << _rb_eval.RB_outputs[i]
          << ", error bound = " << _rb_eval.RB_output_error_bounds[i] << std::endl;
          // << ", error bound = " << _rb_eval.RB_output_error_bounds[i]/_norm_factor << std::endl;


      if (_output_csv)
      {
        _RB_outputs.resize(_n_outputs);
        for (unsigned int i = 0; i != _n_outputs; i++)
        {
          _RB_outputs[i] = _rb_eval.RB_outputs[i];
        }
      }

      if(_output_file)
      {
        _rb_eval.read_in_basis_functions(*_rb_con_ptr, _offline_data_name, true);
        if(_load_basis_function)
          _rb_con_ptr->load_basis_function(_basis_function_number);
        else
        _rb_con_ptr->load_rb_solution();
         *_es.get_system(_system_name).solution = *_es.get_system("RBSystem").solution;
         _fe_problem.getNonlinearSystemBase().update();
      }

      if(_store_basis_functions_sorted)
      {
        if(!_output_file)
          _rb_eval.read_in_basis_functions(*_rb_con_ptr, _offline_data_name, true);

        std::ofstream basis_function_file;
        _n_bfs = _rb_con_ptr->get_rb_evaluation().get_n_basis_functions();
        for (unsigned int i = 0; i != _n_bfs; i++)
        {
          basis_function_file.open(_offline_data_name+"/basis_function"+std::to_string(i), std::ios::app | std::ios::binary);
          basis_function_file << _rb_con_ptr->get_rb_evaluation().get_basis_function(i);
          basis_function_file.close();
        }
      }
      // for older MOOSE versions that are using the PerfLog
      // Moose::perf_log.pop("DataTransfer()", "Execution");
    }
  }
}
