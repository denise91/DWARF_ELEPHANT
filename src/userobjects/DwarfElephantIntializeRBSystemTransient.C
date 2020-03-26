 ///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantInitializeRBSystemTransient.h"

registerMooseObject("DwarfElephantApp", DwarfElephantInitializeRBSystemTransient);

template<>
InputParameters validParams<DwarfElephantInitializeRBSystemTransient>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
  params.addParam<bool>("offline_stage", true, "Determines whether the Offline stage will be calculated or not.");
  params.addParam<bool>("skip_matrix_assembly_in_rb_system", true, "Determines whether the matrix is assembled in the RB System or in the nl0 system.");
  params.addParam<bool>("skip_vector_assembly_in_rb_system", true, "Determines whether the vectors are assembled in the RB System or in the nl0 system.");
  params.addParam<bool>("deterministic_training", false, "Determines whether the training set is generated deterministically or randomly.");
  params.addParam<bool>("quiet_mode", true, "Determines the what is printed to the console.");
  params.addParam<bool>("normalize_rb_bound_in_greedy", false, "Determines whether the normalized RB bound is used in the Greedy or not.");
  params.addParam<bool>("nonzero_initialization", false, "Determines whether zero is taken as initial condition or not.");
  params.addParam<bool>("parameter_dependent_IC", false, "Determines whether the initial conditions are parameter dependent.");
  params.addParam<std::string>("system","rb0","The name of the system that should be read in.");
//  params.addRequiredParam<std::string>("parameters_filename","Path to the input file. Required for the libMesh functions");
  params.addParam<std::string>("init_filename", "", "Name of the file containing the inital conditions.");
  params.addRequiredParam<std::vector<std::string>>("parameter_names", "Parameter names for the RB method.");
  params.addParam<std::vector<std::string>>("discrete_parameter_names", "Discrete parameter names for the RB method.");
  params.addParam<int>("max_truth_solves", -1, "Maximum number of truth solves within the POD.");
  params.addRequiredParam<unsigned int>("n_training_samples", "Defines the number of training samples used in the Greedy.");
  params.addParam<unsigned int>("training_parameters_random_seed", -1, "Defines the random seed for the generation of the traning set.");
  params.addRequiredParam<unsigned int>("N_max", "Defines the maximum number of basis functions.");
  params.addRequiredParam<unsigned int>("n_time_steps", "Defines the number of time steps.");
  params.addParam<unsigned int>("delta_N",1,"Defines the number of basis functions that are added for each POD-Greedy step.");
  params.addParam<Real>("rel_training_tolerance", 1.0e-4, "Defines the relative training tolerance for the Greedy.");
  params.addParam<Real>("abs_training_tolerance", 1.0e-12, "Defines the relative training tolerance for the Greedy.");
  params.addRequiredParam<Real>("delta_t", "Defines the size of the individual time step.");
  params.addParam<Real>("euler_theta", 0., "Defines the Euler method (1 = backward Euler)");
  params.addParam<Real>("POD_tol", -1., "Defines the tolerance of the POD.");
  params.addParam<std::vector<Real>>("parameter_min_values", "Defines the lower bound of the parameter range.");
  params.addParam<std::vector<Real>>("parameter_max_values", "Defines the upper bound of the parameter range.");
  params.addParam<std::vector<Real>>("discrete_parameter_values", "Defines the list of parameters.");
  params.addParam<bool>("varying_timesteps", false, "Determines whether the time steps vary.");
  params.addParam<bool>("time_dependent_parameter", false, "Determines whether some training parameters are time depedent.");
  params.addParam<bool>("time_dependent_lifting_function", false, "Determines whether the boundary condition is time depedent.");
  // params.addParam<Real>("growth_rate", 1.0,"The growth rate for the timesteps.");
  // params.addParam<Real>("threshold", 1.0e30,"Threshold for the growth of dt.");
  params.addParam<std::vector<unsigned int>>("ID_time_dependent_param", std::vector<unsigned int> {0}, "The IDs of the time dependent paramters.");
  params.addParam<Real>("start_time", 0.0,"The start time for the time dependent parameter.");
  params.addParam<Real>("end_time", 0.0,"The end time for the time dependent parameter.");

  return params;
}

DwarfElephantInitializeRBSystemTransient::DwarfElephantInitializeRBSystemTransient(const InputParameters & params):
  GeneralUserObject(params),
  _use_displaced(getParam<bool>("use_displaced")),
  _offline_stage(getParam<bool>("offline_stage")),
  _parameter_dependent_IC(getParam<bool>("parameter_dependent_IC")),
  _initialized(false),
  _delta_time(getParam<Real>("delta_t")),
  _continuous_parameter_min_values(getParam<std::vector<Real>>("parameter_min_values")),
  _continuous_parameter_max_values(getParam<std::vector<Real>>("parameter_max_values")),
  _discrete_parameter_values_in(getParam<std::vector<Real>>("discrete_parameter_values")),
  _system_name(getParam<std::string>("system")),
  _continuous_parameters(getParam<std::vector<std::string>>("parameter_names")),
  _discrete_parameters(getParam<std::vector<std::string>>("discrete_parameter_names")),
  _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
  _mesh_ptr(&_fe_problem.mesh()),
  _sys(&_es.get_system<TransientNonlinearImplicitSystem>(_system_name)),
  _varying_timesteps(getParam<bool>("varying_timesteps")),
  _time_dependent_parameter(getParam<bool>("time_dependent_parameter")),
  _ID_time_dependent_param(getParam<std::vector<unsigned int>>("ID_time_dependent_param")),
  _start_time(getParam<Real>("start_time")),
  _end_time(getParam<Real>("end_time"))
{
}

void
DwarfElephantInitializeRBSystemTransient::processParameters()
{
  /// Set the non-temporal data
  // Set the random seed for the RNG. By default -1 is set, meaning that std::time is used as a seed for the RNG.
  _rb_con_ptr->set_training_random_seed(getParam<unsigned int>("training_parameters_random_seed"));
  // Set quiet mode.
  _rb_con_ptr->set_quiet_mode(getParam<bool>("quiet_mode"));

  // Initialization of the RB parameters.
  _rb_con_ptr->set_Nmax(getParam<unsigned int>("N_max"));

  _rb_con_ptr->set_rel_training_tolerance(getParam<Real>("rel_training_tolerance"));
  _rb_con_ptr->set_abs_training_tolerance(getParam<Real>("abs_training_tolerance"));

  _rb_con_ptr->set_normalize_rb_bound_in_greedy(getParam<bool>("normalize_rb_bound_in_greedy"));

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
                                               getParam<unsigned int>("n_training_samples"),
                                               _log_scaling,
                                               getParam<bool>("deterministic_training"));

  /// Set the temporal data
  _rb_con_ptr->set_n_time_steps(getParam<unsigned int>("n_time_steps"));
  _rb_con_ptr->set_delta_t(_delta_time);
  _rb_con_ptr->set_euler_theta(getParam<Real>("euler_theta"));
  _rb_con_ptr->set_time_step(0);

  _rb_con_ptr->nonzero_initialization = getParam<bool>("nonzero_initialization");
  _rb_con_ptr->init_filename = getParam<std::string>("init_filename");

  _rb_con_ptr->set_POD_tol(getParam<Real>("POD_tol"));
  _rb_con_ptr->set_max_truth_solves(getParam<int>("max_truth_solves"));
  _rb_con_ptr->set_delta_N(getParam<unsigned int>("delta_N"));

  TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(_rb_con_ptr->get_rb_evaluation());
  trans_rb_eval.pull_temporal_discretization_data(*_rb_con_ptr);

  if(_varying_timesteps)
  {
    DwarfElephantRBConstructionTransient * _dwarf_elephant_rb_con_ptr = dynamic_cast<DwarfElephantRBConstructionTransient * > (_rb_con_ptr);
    _dwarf_elephant_rb_con_ptr->varying_timesteps = _varying_timesteps;
    // _dwarf_elephant_rb_con_ptr->growth_rate = _growth_rate;
    // _dwarf_elephant_rb_con_ptr->threshold = _threshold;
  }

  if(_parameter_dependent_IC)
  {
    DwarfElephantRBConstructionTransient * _dwarf_elephant_rb_con_ptr = dynamic_cast<DwarfElephantRBConstructionTransient * > (_rb_con_ptr);
    _dwarf_elephant_rb_con_ptr->set_parameter_dependent_IC(_parameter_dependent_IC);
  }

  if(_time_dependent_parameter)
  {
    DwarfElephantRBConstructionTransient * _dwarf_elephant_rb_con_ptr = dynamic_cast<DwarfElephantRBConstructionTransient * > (_rb_con_ptr);
    _dwarf_elephant_rb_con_ptr->time_dependent_parameter = _time_dependent_parameter;
    _dwarf_elephant_rb_con_ptr->ID_param = _ID_time_dependent_param;
    _dwarf_elephant_rb_con_ptr->start_time = _start_time;
    _dwarf_elephant_rb_con_ptr->end_time = _end_time;
  }
}

void
DwarfElephantInitializeRBSystemTransient::initializeOfflineStage()
{
  // Get and process the necessary input parameters for the
  // offline stage
  //  _rb_con_ptr->process_parameters_file(_parameters_filename);
  processParameters();

  // Print the system informations for the RBConstruction system.
  _rb_con_ptr->print_info();

  // Initialize the RB construction. Note, we skip the matrix and vector
  // assembly, since this is already done by MOOSE.
  _rb_con_ptr->initialize_rb_construction(getParam<bool>("skip_matrix_assembly_in_rb_system"), getParam<bool>("skip_vector_assembly_in_rb_system"));

  // Save the A's, F's and output vectors from the RBConstruction class in pointers.
  // This additional saving of the pointers is required because otherwise a the RBEvaluation object has
  // to be set again in the RBKernel.

  // Define size of all new parameters.
  _jacobian_subdomain.resize(_qa);
  _mass_matrix_subdomain.resize(_qm);
  _residuals.resize(_qf);
  _outputs.resize(_n_outputs);

  if(_parameter_dependent_IC)
    _inital_conditions.resize(_q_ic);

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

  if(_parameter_dependent_IC)
  {
    DwarfElephantRBConstructionTransient * _dwarf_elephant_rb_con_ptr = dynamic_cast<DwarfElephantRBConstructionTransient * > (_rb_con_ptr);
    for (unsigned int _q=0; _q < _q_ic; _q++)
      _inital_conditions[_q] = _dwarf_elephant_rb_con_ptr->get_IC_q(_q);
  }

   for (unsigned int i=0; i < _n_outputs; i++)
     for (unsigned int _q=0; _q < _ql[i]; _q++)
       _outputs[i][_q] = _rb_con_ptr->get_output_vector(i,_q);
}

void
DwarfElephantInitializeRBSystemTransient::initialize()
{
}

void
DwarfElephantInitializeRBSystemTransient::execute()
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

    DwarfElephantRBEvaluationTransient _rb_eval(_mesh_ptr->comm(), _fe_problem);
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

void
DwarfElephantInitializeRBSystemTransient::finalize()
{
}
