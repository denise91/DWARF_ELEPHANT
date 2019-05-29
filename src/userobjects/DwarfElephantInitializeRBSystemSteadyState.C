 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include <chrono>
template<>
InputParameters validParams<DwarfElephantInitializeRBSystemSteadyState>()
{
  InputParameters params = validParams<GeneralUserObject>();

  params.addParam<bool>("use_EIM",false,"Flag for whether on not to use EIM in current simulation");
  params.addParam<bool>("use_hp_EIM",false,"Flag for whether on not to use hp-EIM in current simulation");
  params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addParam<bool>("offline_stage", true, "Determines whether the Offline stage will be calculated or not.");
  //params.addParam<bool>("compliant", true, "Determines whether F is equal to the output vector or not.");
  params.addParam<bool>("skip_matrix_assembly_in_rb_system", true, "Determines whether the matrix is assembled in the RB System or in the nl0 system.");
  params.addParam<bool>("skip_vector_assembly_in_rb_system", true, "Determines whether the vectors are assembled in the RB System or in the nl0 system.");
  
  params.addParam<unsigned int>("n_training_samples_EIM",-1, "Defines the number of training samples used in the EIM Greedy."); // Do not make this a required parameter
  params.addParam<bool>("deterministic_training_EIM", false, "Determines whether the EIM training set is generated deterministically or randomly.");
  params.addParam<unsigned int>("training_parameters_random_seed_EIM", -1, "Defines the random seed for the generation of the EIM traning set.");
  params.addParam<bool>("quiet_mode_EIM", true, "Determines the what is printed to the console.");
  params.addParam<unsigned int>("N_max_EIM",-1, "Defines the maximum number of EIM basis functions."); // Do not make this a required parameter
  params.addParam<Real>("rel_training_tolerance_EIM", 1.0e-4, "Defines the relative training tolerance for the EIM Greedy.");
  params.addParam<Real>("abs_training_tolerance_EIM", 1.0e-12, "Defines the relative training tolerance for the EIM Greedy.");
  params.addParam<bool>("normalize_EIM_bound_in_greedy", false, "Determines whether the normalized EIM bound is used in the Greedy or not.");
  params.addParam<std::vector<std::string>>("parameter_names_EIM","Parameter names for the EIM."); // do not make this a required parameter
  params.addParam<std::vector<Real>>("parameter_min_values_EIM", "Defines the lower bound of the EIM parameter range.");
  params.addParam<std::vector<Real>>("parameter_max_values_EIM", "Defines the upper bound of the EIM parameter range.");
  params.addParam<std::vector<std::string>>("discrete_parameter_names_EIM","Discrete parameter names for the EIM method.");
  params.addParam<std::vector<Real>>("discrete_parameter_values_EIM", "Defines the list of discrete EIM parameter values.");
  params.addParam<std::string>("system","EIM0","The name of the system that should be read in.");
  params.addParam<std::string>("best_fit_type_EIM","projection","The algorithm to be used in the EIM greedy ('projection' or 'eim').");

  params.addParam<bool>("compliant",true,"Determines whether F is equal to the output vector or not.");
  params.addRequiredParam<unsigned int>("n_training_samples_RB", "Defines the number of training samples used in the RB Greedy.");
  params.addParam<bool>("deterministic_training_RB", false, "Determines whether the RB training set is generated deterministically or randomly.");
  params.addParam<unsigned int>("training_parameters_random_seed_RB", -1, "Defines the random seed for the generation of the RB traning set.");
  params.addParam<bool>("quiet_mode_RB", true, "Determines the what is printed to the console.");
  params.addRequiredParam<unsigned int>("N_max_RB", "Defines the maximum number of RB basis functions.");
  params.addParam<Real>("rel_training_tolerance_RB", 1.0e-4, "Defines the relative training tolerance for the RB Greedy.");
  params.addParam<Real>("abs_training_tolerance_RB", 1.0e-12, "Defines the relative training tolerance for the RB Greedy.");
  params.addParam<bool>("normalize_rb_bound_in_greedy", false, "Determines whether the normalized RB bound is used in the Greedy or not.");
  params.addRequiredParam<std::vector<std::string>>("parameter_names_RB", "Parameter names for the RB method.");
  params.addParam<std::vector<Real>>("parameter_min_values_RB", "Defines the lower bound of the RB parameter range.");
  params.addParam<std::vector<Real>>("parameter_max_values_RB", "Defines the upper bound of the RB parameter range.");
  params.addParam<std::vector<std::string>>("discrete_parameter_names_RB", "Discrete parameter names for the RB method.");
  params.addParam<std::vector<Real>>("discrete_parameter_values_RB", "Defines the list of discrete RB parameter values.");
  params.addParam<std::string>("system","rb0","The name of the system that should be read in.");
  
  //params.addParam<unsigned int>("training_parameters_random_seed_SCM",-1,"Defines the random seed for the generation of the RB training set.");
  //params.addParam<Real>("training_tolerance_SCM",1e-5,"Determines the training tolerance for the SCM greedy");
  //params.addRequiredParam<std::vector<std::string>>("parameter_names_SCM","Parameter names for SCM");
  //params.addRequiredParam<std::vector<Real>>("parameter_min_values_SCM","Parameter minimum values for SCM");
  //params.addRequiredParam<std::vector<Real>>("parameter_max_values_SCM","Parameter maximum values for SCM");
  //params.addParam<std::vector<std::string>>("discrete_parameters_names_SCM","Names of discrete parameters for SCM.");
  //params.addParam<std::vector<Real>>("discrete_parameter_values_SCM","Discrete parameter values for SCM.");

  return params;
}

DwarfElephantInitializeRBSystemSteadyState::DwarfElephantInitializeRBSystemSteadyState(const InputParameters & params):
  GeneralUserObject(params),
  _use_EIM(getParam<bool>("use_EIM")),
  _use_hp_EIM(getParam<bool>("use_hp_EIM")),
  _use_displaced(getParam<bool>("use_displaced")),
  _skip_matrix_assembly_in_rb_system(getParam<bool>("skip_matrix_assembly_in_rb_system")),
  _skip_vector_assembly_in_rb_system(getParam<bool>("skip_vector_assembly_in_rb_system")),
  _offline_stage(getParam<bool>("offline_stage")),
  _deterministic_training_EIM(getParam<bool>("deterministic_training_EIM")),
  _quiet_mode_EIM(getParam<bool>("quiet_mode_EIM")),
  _normalize_EIM_bound_in_greedy(getParam<bool>("normalize_EIM_bound_in_greedy")),
  _n_training_samples_EIM(getParam<unsigned int>("n_training_samples_EIM")),
  _training_parameters_random_seed_EIM(getParam<unsigned int>("training_parameters_random_seed_EIM")),
  _N_max_EIM(getParam<unsigned int>("N_max_EIM")),
  _rel_training_tolerance_EIM(getParam<Real>("rel_training_tolerance_EIM")),
  _abs_training_tolerance_EIM(getParam<Real>("abs_training_tolerance_EIM")),
  _continuous_parameter_min_values_EIM(getParam<std::vector<Real>>("parameter_min_values_EIM")),
  _continuous_parameter_max_values_EIM(getParam<std::vector<Real>>("parameter_max_values_EIM")),
  _discrete_parameter_values_in_EIM(getParam<std::vector<Real>>("discrete_parameter_values_EIM")),
  _continuous_parameters_EIM(getParam<std::vector<std::string>>("parameter_names_EIM")),
  _discrete_parameters_EIM(getParam<std::vector<std::string>>("discrete_parameter_names_EIM")),
  _best_fit_type_EIM(getParam<std::string>("best_fit_type_EIM")),
//  _parameters_filename(getParam<std::string>("parameters_filename")),
  _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
  _mesh_ptr(&_fe_problem.mesh()),
  _compliant(getParam<bool>("compliant")),
  _deterministic_training_RB(getParam<bool>("deterministic_training_RB")),
  _quiet_mode_RB(getParam<bool>("quiet_mode_RB")),
  _normalize_RB_bound_in_greedy(getParam<bool>("normalize_rb_bound_in_greedy")),
  _n_training_samples_RB(getParam<unsigned int>("n_training_samples_RB")),
  _training_parameters_random_seed_RB(getParam<unsigned int>("training_parameters_random_seed_RB")),
  _N_max_RB(getParam<unsigned int>("N_max_RB")),
  _system_name(getParam<std::string>("system")),
  _continuous_parameters_RB(getParam<std::vector<std::string>>("parameter_names_RB")),
  _discrete_parameters_RB(getParam<std::vector<std::string>>("discrete_parameter_names_RB")),
  _rel_training_tolerance_RB(getParam<Real>("rel_training_tolerance_RB")),
  _abs_training_tolerance_RB(getParam<Real>("abs_training_tolerance_RB")),
  _continuous_parameter_min_values_RB(getParam<std::vector<Real>>("parameter_min_values_RB")),
  _continuous_parameter_max_values_RB(getParam<std::vector<Real>>("parameter_max_values_RB"))//,
  //_training_parameters_random_seed_SCM(getParam<unsigned int>("training_parameters_random_seed_SCM")),
  //_training_tolerance_SCM(getParam<Real>("training_tolerance_SCM")),
  //_continuous_parameters_SCM(getParam<std::vector<std::string>>("parameter_names_SCM")),
  //_continuous_parameter_min_values_SCM(getParam<std::vector<Real>>("parameter_min_values_SCM")),
 // _continuous_parameter_max_values_SCM(getParam<std::vector<Real>>("parameter_max_values_SCM"))
{
  if (_use_EIM != _use_hp_EIM)
  {
    if ((_n_training_samples_EIM == -1)||(_N_max_EIM == -1))
      mooseError("UserObject DwarfElephantInitializeRBSystemSteadyState: Insufficient parameters provided for EIM. Look at file src/userobjects/DwarfElephantInitializeRBSystemSteadyState.C for details");
  }
  else if ((_n_training_samples_EIM != -1)||(_N_max_EIM != -1))
    mooseError("UserObject DwarfElephantInitializeRBSystemSteadyState: (_use_EIM xor _use_hp_EIM) flag must be set to true in input file");

  std::cout << "Created initialize_rb_system object " << DwarfElephantInitializeRBSystemSteadyState::name() << std::endl;

  if (_use_hp_EIM)
  {
      _eim_data_in._N_max = _N_max_EIM;
      _eim_data_in._abs_tol = _rel_training_tolerance_EIM;
      _eim_data_in._best_fit_type = _best_fit_type_EIM;
      _eim_data_in._cont_param = _continuous_parameters_EIM;
      _eim_data_in._cont_param_max = _continuous_parameter_max_values_EIM;
      _eim_data_in._cont_param_min = _continuous_parameter_min_values_EIM;
      _eim_data_in._deterministic_training = _deterministic_training_EIM;
      _eim_data_in._n_training_samples = _n_training_samples_EIM;
      _eim_data_in._normalize_bound = _normalize_EIM_bound_in_greedy;
      _eim_data_in._quiet_mode = _quiet_mode_EIM;
      _eim_data_in._rel_tol = _rel_training_tolerance_EIM;
      _eim_data_in._training_random_seed = _training_parameters_random_seed_EIM;
  
  _rb_data_in._N_max = _N_max_RB;
  _rb_data_in._abs_tol = _rel_training_tolerance_RB;
  _rb_data_in._cont_param = _continuous_parameters_RB;
  _rb_data_in._cont_param_max = _continuous_parameter_max_values_RB;
  _rb_data_in._cont_param_min = _continuous_parameter_min_values_RB;
  _rb_data_in._deterministic_training_RB = _deterministic_training_RB;
  _rb_data_in._n_training_samples = _n_training_samples_RB;
  _rb_data_in._normalize_RB_bound_in_greedy = _normalize_RB_bound_in_greedy;
  _rb_data_in._quiet_mode_RB = _quiet_mode_RB;
  _rb_data_in._rel_tol = _rel_training_tolerance_RB;
  _rb_data_in._training_random_seed = _training_parameters_random_seed_RB;
  }
}

void
DwarfElephantInitializeRBSystemSteadyState::processEIMParameters()
{
  // Setting paramter values for the EIM construction object
  // Set the random seed for the RNG. By default -1 is set, meaning that std::time is used as a seed for the RNG.
  _eim_con_ptr->set_training_random_seed(_training_parameters_random_seed_EIM);

  // Set quiet mode.
  _eim_con_ptr->set_quiet_mode(_quiet_mode_EIM);

  // Initialization of the RB parameters.
  _eim_con_ptr->set_Nmax(_N_max_EIM);

  _eim_con_ptr->set_rel_training_tolerance(_rel_training_tolerance_EIM);
  //_eim_con_ptr->set_abs_training_tolerance(_abs_training_tolerance);

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
DwarfElephantInitializeRBSystemSteadyState::processRBParameters() const
{

  // End setting parameter values for the RB construction object
  // Set the random seed for the RNG. By default -1 is set, meaning that std::time is used as a seed for the RNG.
  _rb_con_ptr->set_training_random_seed(_training_parameters_random_seed_RB);

  // Set quiet mode.
  _rb_con_ptr->set_quiet_mode(_quiet_mode_RB);

  // Initialization of the RB parameters.
  _rb_con_ptr->set_Nmax(_N_max_RB);

  _rb_con_ptr->set_rel_training_tolerance(_rel_training_tolerance_RB);
  _rb_con_ptr->set_abs_training_tolerance(_abs_training_tolerance_RB);

  _rb_con_ptr->set_normalize_rb_bound_in_greedy(_normalize_RB_bound_in_greedy);

  RBParameters _mu_min_RB;
  RBParameters _mu_max_RB;

  for (unsigned int i=0; i<_continuous_parameters_RB.size(); i++)
  {
    _mu_min_RB.set_value(_continuous_parameters_RB[i], _continuous_parameter_min_values_RB[i]);
    _mu_max_RB.set_value(_continuous_parameters_RB[i], _continuous_parameter_max_values_RB[i]);
  }

  for (unsigned int i=0; i<_discrete_parameters_RB.size(); i++)
  {
    _discrete_parameter_values_RB[_discrete_parameters_RB[i]] = _discrete_parameter_values_in_RB;
  }

  std::map<std::string,bool> _log_scaling;
  RBParameters::const_iterator it     = _mu_min_RB.begin();
  RBParameters::const_iterator it_end = _mu_min_RB.end();
  for ( ; it != it_end; ++it)
    {
      std::string _param_name = it->first;

      // For now, just set all entries to false.
      // TODO: Implement a decent way to specify log-scaling true/false
      // in the input text file
      _log_scaling[_param_name] = false;
    }

    _rb_con_ptr->initialize_parameters(_mu_min_RB, _mu_max_RB, _discrete_parameter_values_RB);

   _rb_con_ptr->initialize_training_parameters(_rb_con_ptr->get_parameters_min(),
                                               _rb_con_ptr->get_parameters_max(),
                                               _n_training_samples_RB,
                                               _log_scaling,
                                               _deterministic_training_RB);
 
}
/*
void
DwarfElephantInitializeRBSystemSteadyState::processSCMParameters()
{

  // End setting parameter values for the RB construction object
  // Set the random seed for the RNG. By default -1 is set, meaning that std::time is used as a seed for the RNG.
  _rb_scm_con_ptr->set_training_random_seed(_training_parameters_random_seed_SCM);


  // Initialization of the SCM parameters.

  _rb_scm_con_ptr->set_SCM_training_tolerance(_training_tolerance_SCM);

  RBParameters _mu_min_SCM;
  RBParameters _mu_max_SCM;

  for (unsigned int i=0; i<_continuous_parameters_SCM.size(); i++)
  {
    _mu_min_SCM.set_value(_continuous_parameters_SCM[i], _continuous_parameter_min_values_SCM[i]);
    _mu_max_SCM.set_value(_continuous_parameters_SCM[i], _continuous_parameter_max_values_SCM[i]);
  }

  for (unsigned int i=0; i<_discrete_parameters_SCM.size(); i++)
  {
    _discrete_parameter_values_SCM[_discrete_parameters_SCM[i]] = _discrete_parameter_values_in_SCM;
  }
/*
  std::map<std::string,bool> _log_scaling;
  RBParameters::const_iterator it     = _mu_min_RB.begin();
  RBParameters::const_iterator it_end = _mu_min_RB.end();
  for ( ; it != it_end; ++it)
    {
      std::string _param_name = it->first;

      // For now, just set all entries to false.
      // TODO: Implement a decent way to specify log-scaling true/false
      // in the input text file
      _log_scaling[_param_name] = false;
    }
*/ /*
   _rb_scm_con_ptr->initialize_parameters(_mu_min_SCM, _mu_max_SCM, _discrete_parameter_values_SCM);

   std::map<std::string,bool> log_scaling;
   const RBParameters & mu = _rb_scm_con_ptr->get_parameters();
   unsigned int i = 0;
   for (const auto & pr : mu)
     {
       const std::string & param_name = pr.first;
       log_scaling[param_name] = false;
     }

   _rb_scm_con_ptr->initialize_training_parameters(_rb_scm_con_ptr->get_parameters_min(),
                                               _rb_scm_con_ptr->get_parameters_max(),
                                               _n_training_samples_SCM,
                                               _log_scaling_SCM,
                                               _deterministic_training_SCM);
 
}*/

void DwarfElephantInitializeRBSystemSteadyState::initializeOfflineStageEIM()
{
// Get and process the necessary input parameters for the
  // offline stage

  //libMesh way: //  _rb_con_ptr->process_parameters_file(_parameters_filename);
  processEIMParameters(); // sets parameter values for the EIM construction object
  _eim_con_ptr->print_info();
  _eim_con_ptr->initialize_rb_construction(_skip_matrix_assembly_in_rb_system,_skip_vector_assembly_in_rb_system);
  //_eim_con_ptr->train_reduced_basis();

// The following lines need to be changed at a future time
  _inner_product_matrix_eim = _eim_con_ptr->get_inner_product_matrix();
  PetscMatrix<Number> * _petsc_inner_matrix_eim = dynamic_cast<PetscMatrix<Number>* > (_inner_product_matrix_eim);
   MatSetOption(_petsc_inner_matrix_eim->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
   

  // Print the system informations for the RBConstruction system.
  _eim_con_ptr->print_info();
  //_hp_eim_bt_ptr = new DwarfElephanthpEIMBinaryTree(0,0,1.0,0.4);
  
}

void DwarfElephantInitializeRBSystemSteadyState::initializeOfflineStageRBOnly()
{
// Get and process the necessary input parameters for the
  // offline stage

  //libMesh way: //  _rb_con_ptr->process_parameters_file(_parameters_filename);
  processRBParameters(); // sets parameter values for the RB construction object
  // processEIMParameters(); // sets parameter values for the SCM construction object
  //processSCMParameters();

  _rb_con_ptr->print_info();
  //_rb_scm_con_ptr->print_info();

  _rb_con_ptr->initialize_rb_construction(_skip_matrix_assembly_in_rb_system,_skip_vector_assembly_in_rb_system);
  

  AssignAffineMatricesAndVectors();
   

  // Print the system informations for the RBConstruction system.
  _rb_con_ptr->print_info(); 
  //_rb_scm_con_ptr->perform_SCM_greedy();
}

void DwarfElephantInitializeRBSystemSteadyState::initializeEIM()
{
    // Define the parameter file for the libMesh functions.
  // In our case not required, because the read-in is done via the MOOSE inputfile.
  // GetPot infile (_parameters_filename);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Starting InitializeEIM eim and rb con creation" << std::endl;
  // Add a new equation system for the RB construction.
  _eim_con_ptr = &_es.add_system<DwarfElephantEIMConstructionSteadyState>("EIMSystem");
  _rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionSteadyState> ("RBSystem");


  // Intialization of the added equation system
  _eim_con_ptr->init();
  _eim_con_ptr->get_explicit_system().init();
  _rb_con_ptr->init();
  _es.update();
std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Time spent in eim and rb con creation" << duration << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Starting eval objects allocation" << std::endl;
  _rb_eval_ptr = new DwarfElephantRBEvaluationSteadyState(_mesh_ptr->comm(), _fe_problem);
  _eim_eval_ptr = new DwarfElephantEIMEvaluationSteadyState(_mesh_ptr->comm());
  
  // Pass a pointer of the RBEvaluation object to the
  // RBConstruction object
  _eim_con_ptr->set_rb_evaluation(*_eim_eval_ptr);
  _rb_con_ptr->set_rb_evaluation(*_rb_eval_ptr);
t2 = std::chrono::high_resolution_clock::now();
duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  std::cout << "Time spent in eval objects creation" << duration << std::endl;
}

void DwarfElephantInitializeRBSystemSteadyState::initializeRBOnly()
{
    // Define the parameter file for the libMesh functions.
  // In our case not required, because the read-in is done via the MOOSE inputfile.
  // GetPot infile (_parameters_filename);
  std::cout << "Starting InitializeRB::initialize()" << std::endl;
  // Add a new equation system for the RB construction.
  _rb_con_ptr = &_es.add_system<DwarfElephantRBConstructionSteadyState> ("RBSystem");
  //_rb_scm_con_ptr = &_es.add_system<RBSCMConstruction>("RBConvectionDiffusion");
  //_rb_scm_con_ptr->set_RB_system_name("RBConvectionDiffusion");
  //_rb_scm_con_ptr->add_variable("p",FIRST);

  // Intialization of the added equation system
  _rb_con_ptr->init();
  _es.update();

  //_es.parameters.set<unsigned int>("eigenpairs") = 1;
  //_es.parameters.set<unsigned int>("basis vectors") = 1;
  //_es.parameters.set<unsigned int>("linear solver maximum iterations") = 1000;

  _rb_eval_ptr = new DwarfElephantRBEvaluationSteadyState(_mesh_ptr->comm(), _fe_problem);

  _rb_con_ptr->set_rb_evaluation(*_rb_eval_ptr);

  //_rb_scm_eval_ptr = new RBSCMEvaluation(_mesh_ptr->comm());
  //_rb_scm_eval_ptr->set_rb_theta_expansion(_rb_eval_ptr->get_rb_theta_expansion());

  //_rb_eval_ptr->rb_scm_eval = &(*_rb_scm_eval_ptr);
  //_rb_scm_con_ptr->set_rb_scm_evaluation(rb_scm_eval);
}

void
DwarfElephantInitializeRBSystemSteadyState::initializeOfflineStage_hp_EIM()
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    _hp_eim_tree_ptr= new DwarfElephanthpEIMM_aryTree(_es, _mesh_ptr, _eim_data_in, "offline");
      std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << "Time spent in hp eim tree initialization " << duration << std::endl;
    
    _inner_product_matrix_eim = _hp_eim_tree_ptr->root->_eim_con_ptr->get_inner_product_matrix();
    PetscMatrix<Number> * _petsc_inner_matrix_eim = dynamic_cast<PetscMatrix<Number>* > (_inner_product_matrix_eim);
    MatSetOption(_petsc_inner_matrix_eim->mat(), MAT_NEW_NONZERO_ALLOCATION_ERR, PETSC_FALSE);
}

void
DwarfElephantInitializeRBSystemSteadyState::initializeOfflineStage() // make new initializeOfflineStageEIM() and initializeOfflineStageRB() functions and use them with if conditions
{
  if (_use_EIM)
  {
      std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
      initializeOfflineStageEIM();
      std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
      std::cout << "Time spent in standard EIM construction initialization " << duration << std::endl;
  }
  else if (_use_hp_EIM)
  {
      initializeOfflineStage_hp_EIM();
  }
  
  else
    initializeOfflineStageRBOnly();
}

void
DwarfElephantInitializeRBSystemSteadyState::initialize() // Make new initializeEIM() initializeRB() functions that can be called depending on whether we need EIM or not.
{
  if (_use_EIM)
  {    
      //std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
      initializeEIM();
      //std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
      //auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
      //std::cout << "Time spent in standard EIM construction allocation " << duration << std::endl;
  }
  else
     initializeRBOnly();

  if (_offline_stage) // location of _offline_stage if statement changed for compatibility with EIM.
  {
    initializeOfflineStage();
  }
  std::cout << "Initialized initialize_rb_system object" << std::endl;
}

void
DwarfElephantInitializeRBSystemSteadyState::execute()
{

}

void
DwarfElephantInitializeRBSystemSteadyState::finalize()
{
}


std::vector<std::vector<NumericVector <Number> *> >
DwarfElephantInitializeRBSystemSteadyState::getOutputs() const
{
  return _outputs;
}

void
DwarfElephantInitializeRBSystemSteadyState::AssignAffineMatricesAndVectors() const
{
	// Get number of attached parameters.
    _n_outputs = _rb_con_ptr->get_rb_theta_expansion().get_n_outputs();
    _ql.resize(_n_outputs);
    _qa = _rb_con_ptr->get_rb_theta_expansion().get_n_A_terms();
    _qf = _rb_con_ptr->get_rb_theta_expansion().get_n_F_terms();

    for(unsigned int i=0; i < _n_outputs; i++)
      _ql[i] = _rb_con_ptr->get_rb_theta_expansion().get_n_output_terms(i);

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

    _fullFEnonAffineF = _rb_con_ptr->get_nonAffineF();
}