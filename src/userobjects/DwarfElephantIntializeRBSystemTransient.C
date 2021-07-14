 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystemTransient.h"

template<>
InputParameters validParams<DwarfElephantInitializeRBSystemTransient>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addRequiredParam<bool>("use_EIM","Enable / disable EIM");
  params.addParam<bool>("deterministic_training_EIM", false, "Determines whether the EIM training set is generated deterministically or randomly.");
  params.addParam<bool>("quiet_mode_EIM", true, "Determines the what is printed to the console during EIM computations.");
  params.addParam<bool>("normalize_EIM_bound_in_greedy", true, "Determines whether the normalized EIM bound is used in the Greedy or not.");
  params.addParam<unsigned int>("n_training_samples_EIM",-1, "Defines the number of training samples used in the EIM Greedy.");
  params.addParam<unsigned int>("training_parameters_random_seed_EIM", -1, "Defines the random seed for the generation of the EIM traning set.");
  params.addParam<unsigned int>("N_max_EIM", -1, "Defines the maximum number of EIM basis functions.");
  params.addParam<Real>("rel_training_tolerance_EIM", 1.0e-4, "Defines the relative training tolerance for the EIM Greedy.");
  params.addParam<Real>("abs_training_tolerance_EIM", 1.0e-12, "Defines the relative training tolerance for the EIM Greedy.");
  params.addRequiredParam<std::vector<std::string>>("parameter_names_EIM", "Parameter names for the EIM method.");
  params.addParam<std::vector<std::string>>("discrete_parameter_names_EIM", "Discrete parameter names for the EIM method.");
  params.addParam<std::vector<Real>>("discrete_parameter_values_EIM", "Defines the list of discrete EIM parameters.");
  params.addParam<std::string>("best_fit_type_EIM","projection","Best fit type for EIM.('projection' or 'eim')");
  params.addParam<std::vector<Real>>("parameter_min_values_EIM", "Defines the lower bound of the EIM parameter range.");
  params.addParam<std::vector<Real>>("parameter_max_values_EIM", "Defines the upper bound of the EIM parameter range.");
  params.addParam<std::vector<Real>>("discrete_parameter_values_EIM", "Defines the list of discrete EIM parameters.");
  params.addParam<std::vector<std::string>>("discrete_parameters_names_EIM","Names of the discrete parameters in EIM.");
  
  params.addParam<bool>("use_displaced_RB", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addParam<bool>("offline_stage_RB", true, "Determines whether the Offline stage will be calculated or not.");
  params.addParam<bool>("skip_matrix_assembly_in_rb_system", true, "Determines whether the matrix is assembled in the RB System or in the nl0 system.");
  params.addParam<bool>("skip_vector_assembly_in_rb_system", true, "Determines whether the vectors are assembled in the RB System or in the nl0 system.");
  params.addParam<bool>("deterministic_training_RB", false, "Determines whether the training set is generated deterministically or randomly.");
  params.addParam<bool>("quiet_mode_RB", true, "Determines the what is printed to the console.");
  params.addParam<bool>("normalize_rb_bound_in_greedy", true, "Determines whether the normalized RB bound is used in the Greedy or not.");
  params.addParam<bool>("nonzero_initialization_RB", false, "Determines whether zero is taken as initial condition or not.");
  params.addParam<bool>("parameter_dependent_IC_RB", false, "Determines whether the initial conditions are parameter dependent.");
  params.addParam<std::string>("system_RB","rb0","The name of the system that should be read in.");
//  params.addRequiredParam<std::string>("parameters_filename","Path to the input file. Required for the libMesh functions");
  params.addParam<std::string>("init_filename_RB", "", "Name of the file containing the inital conditions.");
  params.addRequiredParam<std::vector<std::string>>("parameter_names_RB", "Parameter names for the RB method.");
  params.addParam<std::vector<std::string>>("discrete_parameter_names_RB", "Discrete parameter names for the RB method.");
  params.addParam<int>("max_truth_solves_RB", -1, "Maximum number of truth solves within the POD.");
  params.addRequiredParam<unsigned int>("n_training_samples_RB", "Defines the number of training samples used in the Greedy.");
  params.addParam<unsigned int>("training_parameters_random_seed_RB", -1, "Defines the random seed for the generation of the traning set.");
  params.addRequiredParam<unsigned int>("N_max_RB", "Defines the maximum number of basis functions.");
  params.addRequiredParam<unsigned int>("n_time_steps_RB", "Defines the number of time steps.");
  params.addParam<unsigned int>("delta_N_RB",1,"Defines the number of basis functions that are added for each POD-Greedy step.");
  params.addParam<Real>("rel_training_tolerance_RB", 1.0e-4, "Defines the relative training tolerance for the Greedy.");
  params.addParam<Real>("abs_training_tolerance_RB", 1.0e-12, "Defines the relative training tolerance for the Greedy.");
  params.addRequiredParam<Real>("delta_t_RB", "Defines the size of the individual time step.");
  params.addParam<Real>("euler_theta_RB", 0., "Defines the Euler method (1 = backward Euler)");
  params.addParam<Real>("POD_tol_RB", -1., "Defines the tolerance of the POD.");
  params.addParam<std::vector<Real>>("parameter_min_values_RB", "Defines the lower bound of the parameter range.");
  params.addParam<std::vector<Real>>("parameter_max_values_RB", "Defines the upper bound of the parameter range.");
  params.addParam<std::vector<Real>>("discrete_parameter_values_RB", "Defines the list of parameters.");
  params.addRequiredParam<bool>("RB_RFA","Flag saying whether an RFA model is being used.");

  return params;
}

DwarfElephantInitializeRBSystemTransient::DwarfElephantInitializeRBSystemTransient(const InputParameters & params):
  GeneralUserObject(params),
  _use_displaced(getParam<bool>("use_displaced_RB")),
  _skip_matrix_assembly_in_rb_system(getParam<bool>("skip_matrix_assembly_in_rb_system")),
  _skip_vector_assembly_in_rb_system(getParam<bool>("skip_vector_assembly_in_rb_system")),
  _offline_stage(getParam<bool>("offline_stage_RB")),
  _deterministic_training(getParam<bool>("deterministic_training_RB")),
  _quiet_mode(getParam<bool>("quiet_mode_RB")),
  _normalize_rb_bound_in_greedy(getParam<bool>("normalize_rb_bound_in_greedy")),
  _nonzero_initialization(getParam<bool>("nonzero_initialization_RB")),
  _parameter_dependent_IC(getParam<bool>("parameter_dependent_IC_RB")),
  _use_EIM(getParam<bool>("use_EIM")),
  _deterministic_training_EIM(getParam<bool>("deterministic_training_EIM")),
  _quiet_mode_EIM(getParam<bool>("quiet_mode_EIM")), 
  _normalize_EIM_bound_in_greedy(getParam<bool>("normalize_EIM_bound_in_greedy")),
  _max_truth_solves(getParam<int>("max_truth_solves_RB")),
  _n_training_samples(getParam<unsigned int>("n_training_samples_RB")),
  _training_parameters_random_seed(getParam<unsigned int>("training_parameters_random_seed_RB")),
  _N_max(getParam<unsigned int>("N_max_RB")),
  _n_time_steps(getParam<unsigned int>("n_time_steps_RB")),
  _delta_N(getParam<unsigned int>("delta_N_RB")),
  _n_training_samples_EIM(getParam<unsigned int>("n_training_samples_EIM")),
  _training_parameters_random_seed_EIM(getParam<unsigned int>("training_parameters_random_seed_EIM")),
  _N_max_EIM(getParam<unsigned int>("N_max_EIM")),
  _rel_training_tolerance(getParam<Real>("rel_training_tolerance_RB")),
  _abs_training_tolerance(getParam<Real>("abs_training_tolerance_RB")),
  _delta_time(getParam<Real>("delta_t_RB")),
  _euler_theta(getParam<Real>("euler_theta_RB")),
  _POD_tol(getParam<Real>("POD_tol_RB")),
  _continuous_parameter_min_values(getParam<std::vector<Real>>("parameter_min_values_RB")),
  _continuous_parameter_max_values(getParam<std::vector<Real>>("parameter_max_values_RB")),
  _discrete_parameter_values_in(getParam<std::vector<Real>>("discrete_parameter_values_RB")),
  _rel_training_tolerance_EIM(getParam<Real>("rel_training_tolerance_EIM")),
  _abs_training_tolerance_EIM(getParam<Real>("abs_training_tolerance_EIM")),
  _continuous_parameter_min_values_EIM(getParam<std::vector<Real>>("parameter_min_values_EIM")),
  _continuous_parameter_max_values_EIM(getParam<std::vector<Real>>("parameter_max_values_EIM")),
  _discrete_parameter_values_in_EIM(getParam<std::vector<Real>>("discrete_parameter_values_EIM")),
  _system_name(getParam<std::string>("system_RB")),
  _best_fit_type_EIM(getParam<std::string>("best_fit_type_EIM")),
//  _parameters_filename(getParam<std::string>("parameters_filename")),
  _init_filename(getParam<std::string>("init_filename_RB")),
  _continuous_parameters(getParam<std::vector<std::string>>("parameter_names_RB")),
  _discrete_parameters(getParam<std::vector<std::string>>("discrete_parameter_names_RB")),
  _continuous_parameters_EIM(getParam<std::vector<std::string>>("parameter_names_EIM")),
  _discrete_parameters_EIM(getParam<std::vector<std::string>>("discrete_parameters_names_EIM")),
  _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
  _mesh_ptr(&_fe_problem.mesh()),
  _sys(&_es.get_system<TransientNonlinearImplicitSystem>(_system_name)),
  _RB_RFA(getParam<bool>("RB_RFA"))
{
    if (_use_EIM)
  {
    if ((_n_training_samples_EIM == 0)||(_N_max_EIM == 0))
      mooseError("UserObject DwarfElephantInitializeRBSystemSteadyState: Insufficient parameters provided for EIM. Look at file src/userobjects/DwarfElephantInitializeRBSystemSteadyState.C for details");
  }
  else if ((_n_training_samples_EIM != 0)||(_N_max_EIM != 0))
    mooseError("Check _use_EIM flag in input file");
    
    std::cout << "Created InitializeRBSystemTransient object " << DwarfElephantInitializeRBSystemTransient::name() << std::endl;
}

DwarfElephantInitializeRBSystemTransient::~DwarfElephantInitializeRBSystemTransient()
{
      // Delete statements added to prevent memory leaks
      if (_use_EIM) 
      { 
          delete _eim_eval_ptr;
      }
      delete _rb_eval_ptr;
          
}

void
DwarfElephantInitializeRBSystemTransient::processParameters() const
{ 
  /// Set the non-temporal data
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

  /// Set the temporal data
  _rb_con_ptr->set_n_time_steps(_n_time_steps);
  _rb_con_ptr->set_delta_t(_delta_time);
  _rb_con_ptr->set_euler_theta(_euler_theta);
  _rb_con_ptr->set_time_step(0);

  _rb_con_ptr->nonzero_initialization = _nonzero_initialization;
  _rb_con_ptr->init_filename = _init_filename;

  _rb_con_ptr->set_POD_tol(_POD_tol);
  _rb_con_ptr->set_max_truth_solves(_max_truth_solves);
  _rb_con_ptr->set_delta_N(_delta_N);

  TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(_rb_con_ptr->get_rb_evaluation());
  trans_rb_eval.pull_temporal_discretization_data(*_rb_con_ptr);

  _rb_con_ptr->set_parameter_dependent_IC(_parameter_dependent_IC);
}

void
DwarfElephantInitializeRBSystemTransient::processEIMParameters()
{
    // Setting paramter values for the EIM construction object
  // Set the random seed for the RNG. By default -1 is set, meaning that std::time is used as a seed for the RNG.
  _eim_con_ptr->set_training_random_seed(_training_parameters_random_seed_EIM);

  // Set quiet mode.
  _eim_con_ptr->set_quiet_mode(_quiet_mode_EIM);

  // Initialization of the RB parameters.
  _eim_con_ptr->set_Nmax(_N_max_EIM);

  _eim_con_ptr->set_rel_training_tolerance(_rel_training_tolerance_EIM);
  _eim_con_ptr->set_abs_training_tolerance(_abs_training_tolerance_EIM);

  _eim_con_ptr->set_normalize_rb_bound_in_greedy(_normalize_EIM_bound_in_greedy);

  RBParameters _mu_min_EIM;
  RBParameters _mu_max_EIM;

  for (unsigned int i=0; i<_continuous_parameters_EIM.size(); i++)
  {
    _mu_min_EIM.set_value(_continuous_parameters_EIM[i], _continuous_parameter_min_values_EIM[i]);
    _mu_max_EIM.set_value(_continuous_parameters_EIM[i], _continuous_parameter_max_values_EIM[i]);
  }

  for (unsigned int i=0; i<_discrete_parameters_EIM.size(); i++)
  {
    _discrete_parameter_values_EIM[_discrete_parameters_EIM[i]] = _discrete_parameter_values_in_EIM;
  }

  std::map<std::string,bool> _log_scaling;
  RBParameters::const_iterator it     = _mu_min_EIM.begin();
  RBParameters::const_iterator it_end = _mu_min_EIM.end();
  for ( ; it != it_end; ++it)
    {
      std::string _param_name = it->first;

      // For now, just set all entries to false.
      // TODO: Implement a decent way to specify log-scaling true/false
      // in the input text file
      _log_scaling[_param_name] = false;
    }

    _eim_con_ptr->initialize_parameters(_mu_min_EIM, _mu_max_EIM, _discrete_parameter_values_EIM);

   _eim_con_ptr->initialize_training_parameters(_eim_con_ptr->get_parameters_min(),
                                               _eim_con_ptr->get_parameters_max(),
                                               _n_training_samples_EIM,
                                               _log_scaling,
                                               _deterministic_training_EIM);
   _eim_con_ptr->set_best_fit_type_flag(_best_fit_type_EIM);
  // End setting parameter values for the EIM construction object
}

void
DwarfElephantInitializeRBSystemTransient::initializeOfflineStage()
{
      using std::cout;
  using std::endl;
  //double vm, rss;
  // Get and process the necessary input parameters for the
  // offline stage
  //  _rb_con_ptr->process_parameters_file(_parameters_filename);
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
  _mass_matrix_subdomain.resize(_qm);
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

  // Eliminates error message for the initialization of new non-zero entries
  // For the future: change SparseMatrix pattern (increases efficency)
  _L2_matrix = _rb_con_ptr->L2_matrix.get();
  PetscMatrix<Number> * _petsc_L2_matrix = dynamic_cast<PetscMatrix<Number>* > (_L2_matrix);
  MatSetOption(_petsc_L2_matrix->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);

  for (unsigned int _q=0; _q < _qa; _q++)
  {
    _jacobian_subdomain[_q] = _rb_con_ptr->get_Aq(_q);

    // Eliminates error message for the initialization of new non-zero entries
    // For the future: change SparseMatrix pattern (increases efficency)
    PetscMatrix<Number> * _petsc_matrix = dynamic_cast<PetscMatrix<Number>* > (_jacobian_subdomain[_q]);
    MatSetOption(_petsc_matrix->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
  }

  for (unsigned int _q=0; _q < _qm; _q++)
  {
    // in case you are using a libMesh version older than Dec 6, 2017 use the following
    // line
    // _mass_matrix_subdomain[_q] = _rb_con_ptr->M_q_vector[_q];
    _mass_matrix_subdomain[_q] = _rb_con_ptr->get_M_q(_q);

    // Eliminates error message for the initialization of new non-zero entries
    // For the future: change SparseMatrix pattern (increases efficency)
    PetscMatrix<Number> * _petsc_matrix = dynamic_cast<PetscMatrix<Number>* > (_mass_matrix_subdomain[_q]);
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
DwarfElephantInitializeRBSystemTransient::initializeEIM()
{


        _eim_con_ptr = &_es.add_system<DwarfElephantEIMConstructionSteadyState>("EIMSystem");
  _rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionTransient> ("RBSystem");


  // Intialization of the added equation system
  _eim_con_ptr->init();
  _eim_con_ptr->get_explicit_system().init();
  _rb_con_ptr->init();
  _es.update();

  _rb_eval_ptr = new DwarfElephantRBEvaluationTransient(_mesh_ptr->comm(), _fe_problem, _RB_RFA);
  _eim_eval_ptr = new DwarfElephantEIMEvaluationSteadyState(_mesh_ptr->comm());
  
  // Pass a pointer of the RBEvaluation object to the
  // RBConstruction object
  _eim_con_ptr->set_rb_evaluation(*_eim_eval_ptr);
  _rb_con_ptr->set_rb_evaluation(*_rb_eval_ptr);
}
void
DwarfElephantInitializeRBSystemTransient::initializeOfflineStageEIM()
{

  processEIMParameters();
  _eim_con_ptr->print_info();
  _eim_con_ptr->initialize_rb_construction(_skip_matrix_assembly_in_rb_system,_skip_vector_assembly_in_rb_system);
  //_eim_con_ptr->train_reduced_basis();

  // The following lines need to be changed at a future time
  _inner_product_matrix_eim = _eim_con_ptr->get_inner_product_matrix();
  PetscMatrix<Number> * _petsc_inner_matrix_eim = dynamic_cast<PetscMatrix<Number>* > (_inner_product_matrix_eim);
   MatSetOption(_petsc_inner_matrix_eim->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
   

  // Print the system informations for the RBConstruction system.
  _eim_con_ptr->print_info(); 
}
void
DwarfElephantInitializeRBSystemTransient::initialize()
{
}

void
DwarfElephantInitializeRBSystemTransient::execute()
{
  // Define the parameter file for the libMesh functions.
  // GetPot infile (_parameters_filename);

  // Add a new equation system for the RB construction.
  using std::cout;
  using std::endl;
  double vm, rss;
  std::ofstream outfile;

  if (!_use_EIM) { _rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionTransient> ("RBSystem");}
  else
      initializeEIM();
  process_mem_usage(vm, rss);
  cout << "InitializeRBSystem Execute; rb_con object created VM: " << vm << "; RSS: " << rss << endl;
  //outfile.open("Memory_usage_trace_2.csv",std::ofstream::app);
  //outfile << vm << ", " << rss << endl;
  //outfile.close();
  if (_offline_stage){
    if (!_use_EIM)
    {
        // Intialization of the added equation system
    _rb_con_ptr->init();
    _es.update();

    _rb_eval_ptr = new DwarfElephantRBEvaluationTransient(_mesh_ptr->comm(), _fe_problem, _RB_RFA);
    // Pass a pointer of the RBEvaluation object to the
    // RBConstruction object
    _rb_con_ptr->set_rb_evaluation(*_rb_eval_ptr);

    TransientRBThetaExpansion & _trans_theta_expansion = cast_ref<TransientRBThetaExpansion &>(_rb_con_ptr->get_rb_theta_expansion());

    // Get number of attached parameters.
    _n_outputs = _rb_con_ptr->get_rb_theta_expansion().get_n_outputs();
    _ql.resize(_n_outputs);
    _qa = _rb_con_ptr->get_rb_theta_expansion().get_n_A_terms();
    _qm = _trans_theta_expansion.get_n_M_terms();
    _qf = _rb_con_ptr->get_rb_theta_expansion().get_n_F_terms();

    for(unsigned int i=0; i < _n_outputs; i++)
    _ql[i] = _rb_con_ptr->get_rb_theta_expansion().get_n_output_terms(i);

    // Initialize required matrices and vectors.
      initializeOfflineStage();
    }
    else 
    {
        initializeOfflineStageEIM();
    }    
  }
  else
      if (!_use_EIM)
    {
        // Intialization of the added equation system
    _rb_con_ptr->init();
    _es.update();

    _rb_eval_ptr = new DwarfElephantRBEvaluationTransient(_mesh_ptr->comm(), _fe_problem, _RB_RFA);
    // Pass a pointer of the RBEvaluation object to the
    // RBConstruction object
    _rb_con_ptr->set_rb_evaluation(*_rb_eval_ptr);}
  process_mem_usage(vm, rss);
  cout << "InitializeRBSystem Execute; rb_eval object created; offline stage initialized VM: " << vm << "; RSS: " << rss << endl;
  //outfile.open("Memory_usage_trace_2.csv",std::ofstream::app);
  //outfile << vm << ", " << rss << endl;
  //outfile.close();
}

void
DwarfElephantInitializeRBSystemTransient::finalize()
{
}

std::vector<std::vector<NumericVector <Number> *> >
DwarfElephantInitializeRBSystemTransient::getOutputs() const
{
  return _outputs;
}

void
DwarfElephantInitializeRBSystemTransient::AssignAffineMatricesAndVectors() const
{
    _n_outputs = _rb_con_ptr->get_rb_theta_expansion().get_n_outputs();
    _ql.resize(_n_outputs);
    _qa = _rb_con_ptr->get_rb_theta_expansion().get_n_A_terms();
    _qm = cast_ref<TransientRBThetaExpansion &>(_rb_con_ptr->get_rb_theta_expansion()).get_n_M_terms();
    _qf = _rb_con_ptr->get_rb_theta_expansion().get_n_F_terms();

    for(unsigned int i=0; i < _n_outputs; i++)
    _ql[i] = _rb_con_ptr->get_rb_theta_expansion().get_n_output_terms(i);
    
    // Get and process the necessary input parameters for the
    // offline stage
    //  _rb_con_ptr->process_parameters_file(_parameters_filename);
    //processParameters();

    // Print the system informations for the RBConstruction system.
    _rb_con_ptr->print_info();

    // Initialize the RB construction. Note, we skip the matrix and vector
    // assembly, since this is already done by MOOSE.
    //_rb_con_ptr->initialize_rb_construction(_skip_matrix_assembly_in_rb_system, _skip_vector_assembly_in_rb_system);

    // Save the A's, F's and output vectors from the RBConstruction class in pointers.
    // This additional saving of the pointers is required because otherwise a the RBEvaluation object has
    // to be set again in the RBKernel.

    // Define size of all new parameters.
    _jacobian_subdomain.resize(_qa);
    _mass_matrix_subdomain.resize(_qm);
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

    // Eliminates error message for the initialization of new non-zero entries
    // For the future: change SparseMatrix pattern (increases efficency)
    _L2_matrix = _rb_con_ptr->L2_matrix.get();
    PetscMatrix<Number> * _petsc_L2_matrix = dynamic_cast<PetscMatrix<Number>* > (_L2_matrix);
    MatSetOption(_petsc_L2_matrix->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);

    for (unsigned int _q=0; _q < _qa; _q++)
    {
      _jacobian_subdomain[_q] = _rb_con_ptr->get_Aq(_q);

      // Eliminates error message for the initialization of new non-zero entries
      // For the future: change SparseMatrix pattern (increases efficency)
      PetscMatrix<Number> * _petsc_matrix = dynamic_cast<PetscMatrix<Number>* > (_jacobian_subdomain[_q]);
      MatSetOption(_petsc_matrix->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
    }

    for (unsigned int _q=0; _q < _qm; _q++)
    {
      // in case you are using a libMesh version older than Dec 6, 2017 use the following
      // line
      // _mass_matrix_subdomain[_q] = _rb_con_ptr->M_q_vector[_q];
      _mass_matrix_subdomain[_q] = _rb_con_ptr->get_M_q(_q);

      // Eliminates error message for the initialization of new non-zero entries
      // For the future: change SparseMatrix pattern (increases efficency)
      PetscMatrix<Number> * _petsc_matrix = dynamic_cast<PetscMatrix<Number>* > (_mass_matrix_subdomain[_q]);
      MatSetOption(_petsc_matrix->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
    }

    // Get the correct vectors from the RB System.
    for (unsigned int _q=0; _q < _qf; _q++)
      _residuals[_q] = _rb_con_ptr->get_Fq(_q);

    for (unsigned int i=0; i < _n_outputs; i++)
      for (unsigned int _q=0; _q < _ql[i]; _q++)
        _outputs[i][_q] = _rb_con_ptr->get_output_vector(i,_q);
    
    _fullFEnonAffineF = _rb_con_ptr->get_nonAffineF();
}

void 
DwarfElephantInitializeRBSystemTransient::process_mem_usage(double& vm_usage, double& resident_set)
{
   //////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0
   using std::ios_base;
   using std::ifstream;
   using std::string;

   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);

   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / 1024.0;
   resident_set = rss * page_size_kb;
}
