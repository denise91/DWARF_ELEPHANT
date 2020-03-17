/**
 * This UserObject implements the Offline and Online stage of the RB method.
 */

//---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantOfflineOnlineStageSteadyState.h"

registerMooseObject("DwarfElephantApp", DwarfElephantOfflineOnlineStageSteadyState);

//----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantOfflineOnlineStageSteadyState>()
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
    params.addParam<bool>("output_csv",false, "Determines whether an output of interest is passed to the CSV file.");
    params.addParam<bool>("compliant", false, "Specifies if you have a compliant or non-compliant case.");
    params.addParam<bool>("norm_online_values", false, "Determines wether online parameters are normed.");
    params.addParam<bool>("load_basis_function", false, "Set to true if you want to load a basis function.");
    params.addParam<bool>("write_output", true, "Stores the offline data.");
    params.addParam<unsigned int>("norm_id", 0, "Defines the id of the parameter that will be used for the normalization.");
    params.addParam<unsigned int>("n_outputs", 1, "Defines the number of outputs.");
    params.addParam<unsigned int>("online_N", 0, "Defines the dimension of the online stage.");
    params.addParam<unsigned int>("basis_function_number", 0, "The number of the basis function to retrieve.");
    params.addParam<std::string>("system","rb0","The name of the system that should be read in.");
    params.addParam<std::string>("offline_data_name","offline_data","Folder where the offline data should be stored.");
    params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system.");
    params.addParam<Real>("mu_bar", 1., "Value for mu-bar");
    params.addParam<std::vector<Real>>("online_mu", "Current values of the different layers for which the RB Method is solved.");

    return params;
}

//-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantOfflineOnlineStageSteadyState::DwarfElephantOfflineOnlineStageSteadyState(const InputParameters & params):
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
    _load_basis_function(getParam<bool>("load_basis_function")),
    _write_output(getParam<bool>("write_output")),
    _norm_id(getParam<unsigned int>("norm_id")),
    _n_outputs(getParam<unsigned int>("n_outputs")),
    _online_N(getParam<unsigned int>("online_N")),
    _basis_function_number(getParam<unsigned int>("basis_function_number")),
    _system_name(getParam<std::string>("system")),
    _offline_data_name(getParam<std::string>("offline_data_name")),
    _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
    _sys(_es.get_system<TransientNonlinearImplicitSystem>(_system_name)),
    _initialize_rb_system(getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject")),
    _mesh_ptr(&_fe_problem.mesh()),
    _subdomain_ids(_mesh_ptr->meshSubdomains()),
    _mu_bar(getParam<Real>("mu_bar")),
    _online_mu_parameters(getParam<std::vector<Real>>("online_mu")),
    _rb_problem(cast_ptr<DwarfElephantRBProblem *>(&_fe_problem)),
    // for MOOSE version that operate on the PerfLog comment out the following two lines
    _online_stage_timer(registerTimedSection("onlineStage", 1)),
    _data_transfer_timer(registerTimedSection("dataTransfer", 1))
{
  if(_online_stage==true & _online_mu_parameters.size()==0)
    mooseError("You have not defined the online parameters.");
}

void
DwarfElephantOfflineOnlineStageSteadyState::setAffineMatrices()
{
   _initialize_rb_system.getInnerProductMatrix() -> close();
    for(unsigned int _q=0; _q<_initialize_rb_system.getQa(); _q++)
    {
      _rb_problem->rbAssembly(_q).setCachedJacobianContributions(*_initialize_rb_system.getJacobianSubdomain()[_q]);
      _initialize_rb_system.getJacobianSubdomain()[_q] ->close();
      _initialize_rb_system.getInnerProductMatrix()->add(_mu_bar, *_initialize_rb_system.getJacobianSubdomain()[_q]);
    }
}

void
DwarfElephantOfflineOnlineStageSteadyState::transferAffineVectors()
{
    // Transfer the vectors
    // Transfer the data for the F vectors.
    for(unsigned int _q=0; _q<_initialize_rb_system.getQf(); _q++)
    {
      _rb_problem->rbAssembly(_q).setCachedResidual(*_initialize_rb_system.getResiduals()[_q]);
      _initialize_rb_system.getResiduals()[_q]->close();
    }

    // The RB code runs into problems for non-homogeneous boundary conditions
    // and the following lines are only needed in case of Nodal BCs
    // if(_compliant)
    // {
    //   // Transfer the data for the output vectors.
    //   for(unsigned int i=0; i < _initialize_rb_system._n_outputs; i++)
    //   {
    //     for(unsigned int _q=0; _q < _initialize_rb_system.getQl[i]; _q++)
    //     {
    //       _rb_problem->rbAssembly(i).setCachedResidual(*_initialize_rb_system._outputs[i][_q]);
    //       _initialize_rb_system._outputs[i][_q]->close();
    //     }
    //   }
    // }
}

void
DwarfElephantOfflineOnlineStageSteadyState::offlineStage()
{
      _rb_con_ptr->train_reduced_basis();
      if(_write_output){
        #if defined(LIBMESH_HAVE_CAPNPROTO)
        RBDataSerialization::RBEvaluationSerialization _rb_eval_writer(_rb_con_ptr->get_rb_evaluation());
        _rb_eval_writer.write_to_file("rb_eval.bin");
        #else
        _rb_con_ptr->get_rb_evaluation().legacy_write_offline_data_to_files(_offline_data_name, true);
        #endif
    }

    // If desired, store the basis functions (xdr format).
    if (_store_basis_functions)
      _rb_con_ptr->get_rb_evaluation().write_out_basis_functions(*_rb_con_ptr, _offline_data_name, true);

//    _rb_con_ptr->print_basis_function_orthogonality();
}

void
DwarfElephantOfflineOnlineStageSteadyState::setOnlineParameters()
{
    for (unsigned int  _q = 0; _q != _online_mu_parameters.size(); _q++)
    {
        std::string  _mu_name = "mu_" + std::to_string(_q);
        if (_norm_online_values)
          _online_mu_parameters[_q] = _online_mu_parameters[_q]/_online_mu_parameters[_norm_id];

        _rb_online_mu.set_value(_mu_name, _online_mu_parameters[_q]);
    }
}

void
DwarfElephantOfflineOnlineStageSteadyState::initialize()
{
  _rb_con_ptr=_initialize_rb_system.get_rb_con_ptr();
}

void
DwarfElephantOfflineOnlineStageSteadyState::execute()
{
    // Build the RBEvaluation object
    // Required for both the Offline and Online stage.
    DwarfElephantRBEvaluationSteadyState _rb_eval(comm() , _fe_problem);
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


    // TODO: add a function to extract matricies and vectors for further RB analyses
    //   SparseMatrix<Number> * _aq0 = _rb_con_ptr->get_Aq(0);
    //     _aq0->print_matlab("Aq0");
    //   SparseMatrix<Number> * _aq1 = _rb_con_ptr->get_Aq(1);
    //       _aq1->print_matlab("Aq1");
    //   SparseMatrix<Number> * _aq2 = _rb_con_ptr->get_Aq(2);
    //       _aq2->print_matlab("Aq2");
    //   SparseMatrix<Number> * _aq3 = _rb_con_ptr->get_Aq(3);
    //       _aq3->print_matlab("Aq3");
    //   SparseMatrix<Number> * _aq4 = _rb_con_ptr->get_Aq(4);
    //       _aq4->print_matlab("Aq4");
    //   SparseMatrix<Number> * _aq5 = _rb_con_ptr->get_Aq(5);
    //       _aq5->print_matlab("Aq5");
    //
    // SparseMatrix<Number> * _inner = _rb_con_ptr->get_inner_product_matrix();
    //             _inner->print_matlab("InnerProductMatrix");

      // NumericVector<Number> * _fq0 = _rb_con_ptr->get_Fq(0);
      //   _fq0->print_matlab("Fq0");

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
//        How to write own Exodus file  // not required anymore
//        Moose::perf_log.push("write_Exodus()", "Output");
//
//        std::string _systems_for_print[] = {"RBSystem"};
//        const std::set<std::string>  _system_names_for_print (_systems_for_print, _systems_for_print+sizeof(_systems_for_print)/sizeof(_systems_for_print[0]));
//
//        _rb_eval.read_in_basis_functions(*_rb_con_ptr);
//        _rb_con_ptr->load_rb_solution();
//
//        ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("TestDakotaRB.e", _es, &_system_names_for_print);
////
////      _rb_con_ptr->load_basis_function(0);
////      ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("bf0.e", _es);
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

void
DwarfElephantOfflineOnlineStageSteadyState::finalize()
{
  _fe_problem.computeIndicators();
  _fe_problem.computeMarkers();

  _fe_problem.execute(EXEC_CUSTOM);
  _fe_problem.outputStep(EXEC_TIMESTEP_END);
  _fe_problem.outputStep(EXEC_CUSTOM);
}

//std::string
//DwarfElephantOfflineOnlineStageSteadyState::getFileName()
//{
//  std::string input_filename = _app.getFileName();
//  size_t pos = input_filename.find_last_of('.');
//
//  return input_filename.substr(0, pos) + ".e";
//}
