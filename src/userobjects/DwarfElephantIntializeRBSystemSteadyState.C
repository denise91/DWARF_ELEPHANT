 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystemSteadyState.h"

registerMooseObject("DwarfElephantApp", DwarfElephantInitializeRBSystemSteadyState);

template<>
InputParameters validParams<DwarfElephantInitializeRBSystemSteadyState>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addParam<bool>("offline_stage", true, "Determines whether the Offline stage will be calculated or not.");
  params.addParam<bool>("skip_matrix_assembly_in_rb_system", true, "Determines whether the matrix is assembled in the RB System or in the nl0 system.");
  params.addParam<bool>("skip_vector_assembly_in_rb_system", true, "Determines whether the vectors are assembled in the RB System or in the nl0 system.");
  params.addParam<bool>("deterministic_training", false, "Determines whether the training set is generated deterministically or randomly.");
  params.addParam<bool>("quiet_mode", true, "Determines the what is printed to the console.");
  params.addParam<bool>("normalize_rb_bound_in_greedy", false, "Determines whether the normalized RB bound is used in the Greedy or not.");
  params.addParam<std::string>("system","rb0","The name of the system that should be read in.");
//  params.addRequiredParam<std::string>("parameters_filename","Path to the input file. Required for the libMesh functions");
  params.addRequiredParam<std::vector<std::string>>("parameter_names", "Parameter names for the RB method.");
  params.addParam<std::vector<std::string>>("discrete_parameter_names", "Discrete parameter names for the RB method.");
  params.addRequiredParam<unsigned int>("n_training_samples", "Defines the number of training samples used in the Greedy.");
  params.addParam<unsigned int>("training_parameters_random_seed", -1, "Defines the random seed for the generation of the traning set.");
  params.addRequiredParam<unsigned int>("N_max", "Defines the maximum number of basis functions.");
  params.addParam<Real>("rel_training_tolerance", 1.0e-4, "Defines the relative training tolerance for the Greedy.");
  params.addParam<Real>("abs_training_tolerance", 1.0e-12, "Defines the relative training tolerance for the Greedy.");
  params.addParam<std::vector<Real>>("parameter_min_values", "Defines the lower bound of the parameter range.");
  params.addParam<std::vector<Real>>("parameter_max_values", "Defines the upper bound of the parameter range.");
  params.addParam<std::vector<Real>>("discrete_parameter_values", "Defines the list of parameters.");

  return params;
}

DwarfElephantInitializeRBSystemSteadyState::DwarfElephantInitializeRBSystemSteadyState(const InputParameters & params):
  GeneralUserObject(params),
  _use_displaced(getParam<bool>("use_displaced")),
  _skip_matrix_assembly_in_rb_system(getParam<bool>("skip_matrix_assembly_in_rb_system")),
  _skip_vector_assembly_in_rb_system(getParam<bool>("skip_vector_assembly_in_rb_system")),
  _offline_stage(getParam<bool>("offline_stage")),
  _deterministic_training(getParam<bool>("deterministic_training")),
  _quiet_mode(getParam<bool>("quiet_mode")),
  _normalize_rb_bound_in_greedy(getParam<bool>("normalize_rb_bound_in_greedy")),
  _n_training_samples(getParam<unsigned int>("n_training_samples")),
  _training_parameters_random_seed(getParam<unsigned int>("training_parameters_random_seed")),
  _N_max(getParam<unsigned int>("N_max")),
  _rel_training_tolerance(getParam<Real>("rel_training_tolerance")),
  _abs_training_tolerance(getParam<Real>("abs_training_tolerance")),
  _continuous_parameter_min_values(getParam<std::vector<Real>>("parameter_min_values")),
  _continuous_parameter_max_values(getParam<std::vector<Real>>("parameter_max_values")),
  _discrete_parameter_values_in(getParam<std::vector<Real>>("discrete_parameter_values")),
  _system_name(getParam<std::string>("system")),
//  _parameters_filename(getParam<std::string>("parameters_filename")),
  _continuous_parameters(getParam<std::vector<std::string>>("parameter_names")),
  _discrete_parameters(getParam<std::vector<std::string>>("discrete_parameter_names")),
  _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
  _mesh_ptr(&_fe_problem.mesh()),
  _sys(&_es.get_system<TransientNonlinearImplicitSystem>(_system_name))
{
}

void
DwarfElephantInitializeRBSystemSteadyState::processParameters()
{
  // Set the random seed for the RNG. By default -1 is set, meaning that std::time is used as a seed for the RNG.
  _rb_con_ptr->set_training_random_seed(_training_parameters_random_seed);

  // Set quiet mode.
  _rb_con_ptr->set_quiet_mode(_quiet_mode);

  // Initialization of the RB parameters.
  _rb_con_ptr->set_Nmax(_N_max);

  _rb_con_ptr->set_rel_training_tolerance(_rel_training_tolerance);
  _rb_con_ptr->set_abs_training_tolerance(_abs_training_tolerance);

  _rb_con_ptr->set_normalize_rb_bound_in_greedy(_normalize_rb_bound_in_greedy);

  RBParameters _mu_min;
  RBParameters _mu_max;

  for (unsigned int i=0; i<_continuous_parameters.size(); i++)
  {
    _mu_min.set_value(_continuous_parameters[i], _continuous_parameter_min_values[i]);
    _mu_max.set_value(_continuous_parameters[i], _continuous_parameter_max_values[i]);
  }

  for (unsigned int i=0; i<_discrete_parameters.size(); i++)
  {
    _discrete_parameter_values[_discrete_parameters[i]] = _discrete_parameter_values_in;
  }

  std::map<std::string,bool> _log_scaling;
  RBParameters::const_iterator it     = _mu_min.begin();
  RBParameters::const_iterator it_end = _mu_min.end();
  for ( ; it != it_end; ++it)
    {
      std::string _param_name = it->first;

      // For now, just set all entries to false.
      // TODO: Implement a decent way to specify log-scaling true/false
      // in the input text file
      _log_scaling[_param_name] = false;
    }

    _rb_con_ptr->initialize_parameters(_mu_min, _mu_max, _discrete_parameter_values);

   _rb_con_ptr->initialize_training_parameters(_rb_con_ptr->get_parameters_min(),
                                               _rb_con_ptr->get_parameters_max(),
                                               _n_training_samples,
                                               _log_scaling,
                                               _deterministic_training);
}


void
DwarfElephantInitializeRBSystemSteadyState::initializeOfflineStage()
{
  // Get and process the necessary input parameters for the
  // offline stage

  //libMesh way: //  _rb_con_ptr->process_parameters_file(_parameters_filename);
  processParameters();

  // Print the system informations for the RBConstruction system.
  _rb_con_ptr->print_info();

  // Initialize the RB construction. Note, we skip the matrix and vector
  // assembly, since this is already done by MOOSE.
  _rb_con_ptr->initialize_rb_construction(_skip_matrix_assembly_in_rb_system, _skip_vector_assembly_in_rb_system);

   // Save the A's, F's and output vectors from the RBConstruction class in pointers.
   // This additional saving of the pointers is required because otherwise a the RBEvaluation object has
   // to be set again in the RBKernel.

   // Define size of all new parameters.
   _jacobian_subdomain.resize(_qa);
   _residuals.resize(_qf);
   _outputs.resize(_n_outputs);

   for (unsigned int i=0; i < _n_outputs; i++)
     _outputs[i].resize(_ql[i]);

    // Get the correct matrices from the RB System.

   // Eliminates error message for the initialization of new non-zero entries
   // For the future: change SparseMatrix pattern (increases efficency)
   _inner_product_matrix = _rb_con_ptr->get_inner_product_matrix();
   PetscMatrix<Number> * _petsc_inner_matrix = dynamic_cast<PetscMatrix<Number>* > (_inner_product_matrix);
   MatSetOption(_petsc_inner_matrix->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);

   for (unsigned int _q=0; _q < _qa; _q++)
   {
     _jacobian_subdomain[_q] = _rb_con_ptr->get_Aq(_q);

     // Eliminates error message for the initialization of new non-zero entries
     // For the future: change SparseMatrix pattern (increases efficency)
     PetscMatrix<Number> * _petsc_matrix = dynamic_cast<PetscMatrix<Number>* > (_jacobian_subdomain[_q]);
     MatSetOption(_petsc_matrix->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
    }

    // Get the correct vectors from the RB System.
    for (unsigned int _q=0; _q < _qf; _q++)
      _residuals[_q] = _rb_con_ptr->get_Fq(_q);

    for (unsigned int i=0; i < _n_outputs; i++)
      for (unsigned int _q=0; _q < _ql[i]; _q++)
        _outputs[i][_q] = _rb_con_ptr->get_output_vector(i,_q);
}

void
DwarfElephantInitializeRBSystemSteadyState::initialize()
{
}

void
DwarfElephantInitializeRBSystemSteadyState::execute()
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

    DwarfElephantRBEvaluationSteadyState _rb_eval(_mesh_ptr->comm(), _fe_problem);
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

void
DwarfElephantInitializeRBSystemSteadyState::finalize()
{
}
