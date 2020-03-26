/**
 * This UserObject implements the Offline and Online stage of the RB method.
 */

//---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "TestDwarfElephantOfflineOnlineStageTransientT4A3F4O1M1.h"

registerMooseObject("DwarfElephantApp", TestDwarfElephantOfflineOnlineStageTransientT4A3F4O1M1);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<TestDwarfElephantOfflineOnlineStageTransientT4A3F4O1M1>()
{
    InputParameters params = validParams<DwarfElephantOfflineOnlineStageTransient>();
    return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
TestDwarfElephantOfflineOnlineStageTransientT4A3F4O1M1::TestDwarfElephantOfflineOnlineStageTransientT4A3F4O1M1(const InputParameters & params):
    DwarfElephantOfflineOnlineStageTransient(params)
{
  if(_online_stage==true & _online_mu_parameters.size()==0)
    mooseError("You have not defined the online parameters.");
}


void
TestDwarfElephantOfflineOnlineStageTransientT4A3F4O1M1::execute()
{
    // Build the RBEvaluation object
    // Required for both the Offline and Online stage.
    TestDwarfElephantRBEvaluationTransientT4A3F4O1M1 _rb_eval(comm() , _fe_problem);

    if(_initialize_rb_system.get_parameter_dependent_IC())
    {
      DwarfElephantRBEvaluationTransient & _dwarf_elephant_trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(_rb_eval);
      _dwarf_elephant_trans_rb_eval.set_parameter_dependent_IC(_initialize_rb_system.get_parameter_dependent_IC());
    }

    if(!_offline_stage && (_output_file || _store_basis_functions_sorted))
      _rb_con_ptr->init();

    if(_offline_stage || _output_file || _offline_error_bound || _online_N == 0 || _store_basis_functions_sorted)
    {
      // Pass a pointer of the RBEvaluation object to the
      // RBConstruction object
      _rb_con_ptr->set_rb_evaluation(_rb_eval);

      TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(_rb_eval);
      trans_rb_eval.pull_temporal_discretization_data(*_rb_con_ptr);
    }

    if (_offline_stage)
    {
      TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(_rb_eval);
      trans_rb_eval.pull_temporal_discretization_data(*_rb_con_ptr);
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

      // for(unsigned int i =0; i < _n_outputs; i++)
      // {
      //   _rb_con_ptr->get_output_vector(i,0)->print_matlab("VectorClose" + std::to_string(i));
      // }
    }

    if(_online_stage)
    {
      {
      TIME_SECTION(_online_stage_timer);
      // for older MOOSE versions that are using the PerfLog
      // Moose::perf_log.push("onlineStage()", "Execution");

      #if defined(LIBMESH_HAVE_CAPNPROTO)
        RBDataDeserialization::TransientRBEvaluationDeserialization _rb_eval_reader(_rb_eval);
        _rb_eval_reader.read_from_file("trans_rb_eval.bin", /*read_error_bound_data*/ true);
      #else
        _rb_eval.legacy_read_offline_data_from_files(_offline_data_name, true, true);
      #endif

      setOnlineParameters();
      _rb_eval.set_parameters(_rb_online_mu);

      _console << "---- Online Stage ----" << std::endl;
      _rb_eval.print_parameters();

      if(_online_N==0)
        _online_N = _rb_con_ptr->get_rb_evaluation().get_n_basis_functions();

     if(_offline_error_bound)
      _rb_con_ptr->get_rb_evaluation().evaluate_RB_error_bound = false;

     if(_initialize_rb_system.get_varying_timesteps())
     {
       DwarfElephantRBEvaluationTransient & _dwarf_elephant_trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(_rb_eval);
       _dwarf_elephant_trans_rb_eval.varying_timesteps = true;
       // _dwarf_elephant_trans_rb_eval.growth_rate = _initialize_rb_system._growth_rate;
     }

      Real _error_bound_final_time = _rb_eval.rb_solve(_online_N);

      _n_time_steps = _rb_con_ptr->get_n_time_steps();

      _console << "Error bound at the final time is " << _error_bound_final_time << std::endl << std::endl;

      }
      {
      TIME_SECTION(_data_transfer_timer);
      // for older MOOSE versions that are using the PerfLog
      // Moose::perf_log.pop("onlineStage()", "Execution");
      // Back transfer of the data to use MOOSE Postprocessor and Output classes
      // Moose::perf_log.push("DataTransfer()", "Execution");

      if(_output_console)
      {
        TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(_rb_eval);
        for (unsigned int i = 0; i != _n_outputs; i++)
          for (unsigned int _time_step = 0; _time_step <= _n_time_steps; _time_step++)
            _console << "Output " << std::to_string(i) << " at timestep "
                     << std::to_string(_time_step) << ": value = "
                     << trans_rb_eval.RB_outputs_all_k[i][_time_step]
                     << ", error bound = "
                     << trans_rb_eval.RB_output_error_bounds_all_k[i][_time_step]
                     << std::endl;
      }

      if (_output_csv)
      {
        TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(_rb_eval);

        _RB_outputs_all_timesteps.resize(_n_time_steps+1);

        for (unsigned int _t = 0; _t <= _n_time_steps; _t++)
        {
          _RB_outputs_all_timesteps[_t].resize(_n_outputs);

          for (unsigned int i = 0; i != _n_outputs; i++)
          {
            _RB_outputs_all_timesteps[_t][i] = trans_rb_eval.RB_outputs_all_k[i][_t];
          }
        }

          _fe_problem.outputStep(EXEC_TIMESTEP_END);
          _fe_problem.outputStep(EXEC_CUSTOM);
      }

      if(_output_file)
      {
         _rb_eval.read_in_basis_functions(*_rb_con_ptr, _offline_data_name, true);

         for (unsigned int _time_step = 0; _time_step <= _n_time_steps; _time_step++)
        {
          _rb_con_ptr->set_time_step(_time_step);
          _rb_con_ptr->load_rb_solution();
          *_es.get_system(_system_name).solution = *_es.get_system("RBSystem").solution;
          _fe_problem.timeStep()=_time_step;
          // Perform the output of the current time step
          _fe_problem.time()=_time_step*_rb_con_ptr->get_delta_t();
          _fe_problem.getNonlinearSystemBase().update();
          endStep(_time_step*_rb_con_ptr->get_delta_t());
        }
      }

      if(_store_basis_functions_sorted)
      {
        if(!_output_file)
          _rb_eval.read_in_basis_functions(*_rb_con_ptr,_offline_data_name, true);

        std::ofstream basis_function_file;
        _n_bfs = _rb_con_ptr->get_rb_evaluation().get_n_basis_functions();
        for (unsigned int i = 0; i != _n_bfs; i++)
        {
          basis_function_file.open(_offline_data_name+"/basis_function"+std::to_string(i), std::ios::app | std::ios::binary);
          basis_function_file << _rb_con_ptr->get_rb_evaluation().get_basis_function(i);
          basis_function_file.close();
        }
      }
    }
  }
}
