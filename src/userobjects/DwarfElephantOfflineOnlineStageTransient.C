/**
 * This UserObject implements the Offline and Online stage of the RB method.
 */

//---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantOfflineOnlineStageTransient.h"

registerMooseObject("DwarfElephantApp", DwarfElephantOfflineOnlineStageTransient);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantOfflineOnlineStageTransient>()
{
    InputParameters params = validParams<GeneralUserObject>();

    params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
    params.addParam<bool>("store_basis_functions", true, "Determines whether the basis functions are stored or not.");
    params.addParam<bool>("skip_matrix_assembly_in_rb_system", true, "Determines whether the matrix is assembled in the RB System or in the nl0 system.");
    params.addParam<bool>("skip_vector_assembly_in_rb_system", true, "Determines whether the vectors are assembled in the RB System or in the nl0 system.");
    params.addParam<bool>("offline_stage", true, "Determines whether the Offline stage will be calculated or not.");
    params.addParam<bool>("online_stage", true, "Determines whether the Online stage will be calculated or not.");
    params.addParam<bool>("offline_error_bound", false, "Determines which error bound is used.");
    params.addParam<bool>("output_file", true, "Determines whether an output file is generated or not.");
    params.addParam<bool>("store_basis_functions", true, "Determines whether the basis functions are stored for visualization purposes.");
    params.addParam<bool>("store_basis_functions_sorted", false, "Determines whether the basis functions are stored for visualization purposes.");
    params.addParam<bool>("output_console", false, "Determines whether an output of interest is computed or not.");
    params.addParam<bool>("output_csv", false, "Determines whether an output of interest is passed to the CSV file.");
    params.addParam<bool>("compliant", false, "Specifies if you have a compliant or non-compliant case.");
    params.addParam<bool>("norm_online_values", false, "Determines wether online parameters are normed.");
    params.addParam<unsigned int>("norm_id", 0, "Defines the id of the parameter that will be used for the normalization.");
    params.addParam<unsigned int>("online_N", 0, "Defines the dimension of the online stage.");
    params.addParam<std::string>("system","rb0","The name of the system that should be read in.");
    params.addParam<std::string>("offline_data_name","offline_data","Folder where the offline data should be stored.");
    params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system.");
    params.addParam<Real>("mu_bar", 1., "Value for mu-bar");
    params.addParam<unsigned int>("n_outputs", 1, "Defines the number of outputs.");
    params.addParam<std::vector<Real>>("online_mu", "Current values of the different layers for which the RB Method is solved.");

    return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantOfflineOnlineStageTransient::DwarfElephantOfflineOnlineStageTransient(const InputParameters & params):
    GeneralUserObject(params),
    _use_displaced(getParam<bool>("use_displaced")),
    _store_basis_functions(getParam<bool>("store_basis_functions")),
    _store_basis_functions_sorted(getParam<bool>("store_basis_functions_sorted")),
    _skip_matrix_assembly_in_rb_system(getParam<bool>("skip_matrix_assembly_in_rb_system")),
    _skip_vector_assembly_in_rb_system(getParam<bool>("skip_matrix_assembly_in_rb_system")),
    _offline_stage(getParam<bool>("offline_stage")),
    _online_stage(getParam<bool>("online_stage")),
    _offline_error_bound(getParam<bool>("offline_error_bound")),
    _output_file(getParam<bool>("output_file")),
    _output_console(getParam<bool>("output_console")),
    _output_csv(getParam<bool>("output_csv")),
    _compliant(getParam<bool>("compliant")),
    _norm_online_values(getParam<bool>("norm_online_values")),
    _norm_id(getParam<unsigned int>("norm_id")),
    _n_outputs(getParam<unsigned int>("n_outputs")),
    _system_name(getParam<std::string>("system")),
    _offline_data_name(getParam<std::string>("offline_data_name")),
    _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
    _sys(_es.get_system<TransientNonlinearImplicitSystem>(_system_name)),
    _initialize_rb_system(getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject")),
    _mesh_ptr(&_fe_problem.mesh()),
    _subdomain_ids(_mesh_ptr->meshSubdomains()),
    _mu_bar(getParam<Real>("mu_bar")),
    _online_N(getParam<unsigned int>("online_N")),
    _online_mu_parameters(getParam<std::vector<Real>>("online_mu")),
    _rb_problem(cast_ptr<DwarfElephantRBProblem *>(&_fe_problem)),
    _online_stage_timer(registerTimedSection("onlineStage", 1)),
    _data_transfer_timer(registerTimedSection("dataTransfer", 1))
{
  if(_online_stage==true & _online_mu_parameters.size()==0)
    mooseError("You have not defined the online parameters.");
}

void
DwarfElephantOfflineOnlineStageTransient::setAffineMatrices()
{
   _initialize_rb_system._inner_product_matrix -> close();
    for(unsigned int _q=0; _q<_initialize_rb_system._qa; _q++)
    {
      _rb_problem->rbAssembly(_q).setCachedJacobianContributions(*_initialize_rb_system._jacobian_subdomain[_q]);
      _initialize_rb_system._jacobian_subdomain[_q] ->close();
      _initialize_rb_system._inner_product_matrix->add(_mu_bar, *_initialize_rb_system._jacobian_subdomain[_q]);
    }

    _initialize_rb_system._L2_matrix -> close();
    for(unsigned int _q=0; _q<_initialize_rb_system._qm; _q++)
    {
      _rb_problem->rbAssembly(_q).setCachedMassMatrixContributions(*_initialize_rb_system._mass_matrix_subdomain[_q]);
      _initialize_rb_system._mass_matrix_subdomain[_q] ->close();
      _initialize_rb_system._L2_matrix->add(_mu_bar, *_initialize_rb_system._mass_matrix_subdomain[_q]);

    }

}

void
DwarfElephantOfflineOnlineStageTransient::transferAffineVectors()
{
  // Transfer the vectors
  // Transfer the data for the F vectors.
  for(unsigned int _q=0; _q<_initialize_rb_system._qf; _q++)
  {
    _rb_problem->rbAssembly(_q).setCachedResidual(*_initialize_rb_system._residuals[_q]);
    _initialize_rb_system._residuals[_q]->close();
  }

  if(_initialize_rb_system._parameter_dependent_IC)
    for(unsigned int _q=0; _q<_initialize_rb_system._q_ic; _q++)
      _initialize_rb_system._inital_conditions[_q]->close();


  // The RB code runs into problems for non-homogeneous boundary conditions
  // and the following lines are only needed in case of Nodal BCs
  // if(_compliant)
  // {
  //   // Transfer the data for the output vectors.
  //   for(unsigned int i=0; i < _initialize_rb_system._n_outputs; i++)
  //   {
  //     for(unsigned int _q=0; _q < _initialize_rb_system._ql[i]; _q++)
  //     {
  //       _rb_problem->rbAssembly(i).setCachedResidual(*_initialize_rb_system._outputs[i][_q]);
  //       _initialize_rb_system._outputs[i][_q]->close();
  //     }
  //   }
  // }
}

void
DwarfElephantOfflineOnlineStageTransient::offlineStage()
{
    _rb_con_ptr->train_reduced_basis();

   #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataSerialization::TransientRBEvaluationSerialization _rb_eval_writer(_rb_con_ptr->get_rb_evaluation());
     _rb_eval_writer.write_to_file("trans_rb_eval.bin");
    #else
      // Write the offline data to file (xdr format).
     _rb_con_ptr->get_rb_evaluation().legacy_write_offline_data_to_files(_offline_data_name, true);
    #endif

    // If desired, store the basis functions (xdr format).
    if (_store_basis_functions)
      _rb_con_ptr->get_rb_evaluation().write_out_basis_functions(*_rb_con_ptr, _offline_data_name, true);


//    _rb_con_ptr->print_basis_function_orthogonality();
}

void
DwarfElephantOfflineOnlineStageTransient::setOnlineParameters()
{
  for (unsigned int  _q = 0; _q < _online_mu_parameters.size(); _q++)
  {
      std::string  _mu_name = "mu_" + std::to_string(_q);
      _online_mu_parameters[_q] = _online_mu_parameters[_q];

      if (_norm_online_values)
        _rb_online_mu.set_value(_mu_name, _online_mu_parameters[_q]/_online_mu_parameters[_norm_id]);
      else
        _rb_online_mu.set_value(_mu_name, _online_mu_parameters[_q]);
  }
}

void
DwarfElephantOfflineOnlineStageTransient::initialize()
{
  _rb_con_ptr=_initialize_rb_system.get_rb_con_ptr();
}

void
DwarfElephantOfflineOnlineStageTransient::execute()
{
    // Build the RBEvaluation object
    // Required for both the Offline and Online stage.
    DwarfElephantRBEvaluationTransient _rb_eval(comm() , _fe_problem);

    if(_initialize_rb_system._parameter_dependent_IC)
    {
      DwarfElephantRBEvaluationTransient & _dwarf_elephant_trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(_rb_eval);
      _dwarf_elephant_trans_rb_eval.set_parameter_dependent_IC(_initialize_rb_system._parameter_dependent_IC);
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

     if(_initialize_rb_system._varying_timesteps)
     {
       DwarfElephantRBEvaluationTransient & _dwarf_elephant_trans_rb_eval = cast_ref<DwarfElephantRBEvaluationTransient &>(_rb_eval);
       _dwarf_elephant_trans_rb_eval.varying_timesteps = true;
       // _dwarf_elephant_trans_rb_eval.growth_rate = _initialize_rb_system._growth_rate;
     }

      Real _error_bound_final_time = _rb_eval.rb_solve(_online_N);

      _n_time_steps = _initialize_rb_system._n_time_steps;

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
//        // Plot the solution
//        Moose::perf_log.push("write_exodus()", "Output");
//
//        // Read in the basis functions
//        _rb_eval.read_in_basis_functions(*_rb_con_ptr);
//
//        std::string _systems_for_print[] = {"RBSystem"};
//        const std::set<std::string>  _system_names_for_print (_systems_for_print, _systems_for_print+sizeof(_systems_for_print)/sizeof(_systems_for_print[0]));
//
//        ExodusII_IO exo(_mesh_ptr->getMesh());
//        exo.write_equation_systems(getFileName(), _es, &_system_names_for_print);
//
//        for (unsigned int _time_step = 1; _time_step <= _rb_con_ptr->get_n_time_steps(); _time_step++)
//        {
//          exo.append(true);
//          _rb_con_ptr->pull_temporal_discretization_data(_rb_eval);
//          _rb_con_ptr->set_time_step(_time_step);
//          _rb_con_ptr->load_rb_solution();
//          exo.write_timestep(getFileName(), _es, _time_step, _time_step * _rb_con_ptr->get_delta_t());
//        }
    }
  }
}

std::string
DwarfElephantOfflineOnlineStageTransient::getFileName()
{
  std::string input_filename = _app.getFileName();
  size_t pos = input_filename.find_last_of('.');

  return input_filename.substr(0, pos) + ".e";
}

void
DwarfElephantOfflineOnlineStageTransient::finalize()
{
}

void
DwarfElephantOfflineOnlineStageTransient::endStep(Real input_time)
{
    Real _time = input_time;

    // Compute the Error Indicators and Markers
    _fe_problem.time()=_time;
    _fe_problem.computeIndicators();
    _fe_problem.computeMarkers();

    _fe_problem.execute(EXEC_CUSTOM);

    // Perform the output of the current time step
    _fe_problem.outputStep(EXEC_TIMESTEP_END);
    // _fe_problem.outputStep(EXEC_CUSTOM);

    // output
   // if (_time_interval && (_time + _timestep_tolerance >= _next_interval_output_time))
   //   _next_interval_output_time += _time_interval_output_interval;
}
