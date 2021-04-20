/**
 * This UserObject implements the Offline and Online stage of the RB method.
 */

///---------------------------------INCLUDES--------------------------------
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantOfflineOnlineStageTransient.h"

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantOfflineOnlineStageTransient>()
{
    std::vector<Real> _zero_vect{0,0,0,0,0};
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
    params.addParam<bool>("output_console", false, "Determines whether an output of interest is computed or not.");
    params.addParam<bool>("output_csv", false, "Determines whether an output of interest is passed to the CSV file.");
    params.addParam<bool>("compliant", false, "Specifies if you have a compliant or non-compliant case.");
    params.addParam<bool>("norm_online_values", false, "Determines wether online parameters are normed.");
    params.addParam<unsigned int>("norm_id", 0, "Defines the id of the parameter that will be used for the normalization.");
    params.addParam<unsigned int>("online_N", 0, "Defines the dimension of the online stage.");
    params.addParam<std::string>("system","rb0","The name of the system that should be read in.");
    params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system.");
    params.addParam<Real>("mu_bar", 1., "Value for mu-bar");
    params.addParam<unsigned int>("n_outputs", 1, "Defines the number of outputs.");
    params.addRequiredParam<std::vector<Real>>("online_mu", "Current values of the different layers for which the RB Method is solved.");
    params.addRequiredParam<std::vector<Real>>("mu_ref", "The reference parameter values to be used to compute the RB inner product matrix.");
    params.addRequiredParam<unsigned int>("num_online_solves","Number of online solves to perform");
    params.addParam<std::vector<Real>>("online_mu_0",_zero_vect,"Online param value 0");
    params.addParam<std::vector<Real>>("online_mu_1",_zero_vect,"Online param value 1");
    params.addParam<std::vector<Real>>("online_mu_2",_zero_vect,"Online param value 2");
    params.addParam<std::vector<Real>>("online_mu_3",_zero_vect,"Online param value 3");
    params.addParam<std::vector<Real>>("online_mu_4",_zero_vect,"Online param value 4");
    params.addParam<std::vector<Real>>("online_mu_5",_zero_vect,"Online param value 5");
    params.addParam<std::vector<Real>>("online_mu_6",_zero_vect,"Online param value 6");
    params.addParam<std::vector<Real>>("online_mu_7",_zero_vect,"Online param value 7");
    params.addParam<std::vector<Real>>("online_mu_8",_zero_vect,"Online param value 8");
    params.addParam<std::vector<Real>>("online_mu_9",_zero_vect,"Online param value 9");
    params.addParam<std::vector<Real>>("online_mu_10",_zero_vect,"Online param value 10");
    params.addParam<std::vector<Real>>("online_mu_11",_zero_vect,"Online param value 11");
    params.addParam<std::vector<Real>>("online_mu_12",_zero_vect,"Online param value 12");
    params.addParam<std::vector<Real>>("online_mu_13",_zero_vect,"Online param value 13");
    params.addParam<std::vector<Real>>("online_mu_14",_zero_vect,"Online param value 14");
    params.addParam<std::vector<Real>>("online_mu_15",_zero_vect,"Online param value 15");
    params.addParam<std::vector<Real>>("online_mu_16",_zero_vect,"Online param value 16");
    params.addParam<std::vector<Real>>("online_mu_17",_zero_vect,"Online param value 17");
    params.addParam<std::vector<Real>>("online_mu_18",_zero_vect,"Online param value 18");
    params.addParam<std::vector<Real>>("online_mu_19",_zero_vect,"Online param value 19");
    params.addParam<std::vector<Real>>("online_mu_20",_zero_vect,"Online param value 20");
    params.addParam<std::vector<Real>>("online_mu_21",_zero_vect,"Online param value 21");
    params.addParam<std::vector<Real>>("online_mu_22",_zero_vect,"Online param value 22");
    params.addParam<std::vector<Real>>("online_mu_23",_zero_vect,"Online param value 23");
    params.addParam<std::vector<Real>>("online_mu_24",_zero_vect,"Online param value 24");
    params.addParam<std::vector<Real>>("online_mu_25",_zero_vect,"Online param value 25");
    params.addParam<std::vector<Real>>("online_mu_26",_zero_vect,"Online param value 26");
    params.addParam<std::vector<Real>>("online_mu_27",_zero_vect,"Online param value 27");
    params.addParam<std::vector<Real>>("online_mu_28",_zero_vect,"Online param value 28");
    params.addParam<std::vector<Real>>("online_mu_29",_zero_vect,"Online param value 29");
    params.addParam<std::vector<Real>>("online_mu_30",_zero_vect,"Online param value 30");
    params.addParam<std::vector<Real>>("online_mu_31",_zero_vect,"Online param value 31");
    params.addParam<std::vector<Real>>("online_mu_32",_zero_vect,"Online param value 32");
    params.addParam<std::vector<Real>>("online_mu_33",_zero_vect,"Online param value 33");
    params.addParam<std::vector<Real>>("online_mu_34",_zero_vect,"Online param value 34");
    params.addParam<std::vector<Real>>("online_mu_35",_zero_vect,"Online param value 35");
    params.addParam<std::vector<Real>>("online_mu_36",_zero_vect,"Online param value 36");
    params.addParam<std::vector<Real>>("online_mu_37",_zero_vect,"Online param value 37");
    params.addParam<std::vector<Real>>("online_mu_38",_zero_vect,"Online param value 38");
    params.addParam<std::vector<Real>>("online_mu_39",_zero_vect,"Online param value 39");
    params.addParam<std::vector<Real>>("online_mu_40",_zero_vect,"Online param value 40");
    params.addParam<std::vector<Real>>("online_mu_41",_zero_vect,"Online param value 41");
    params.addParam<std::vector<Real>>("online_mu_42",_zero_vect,"Online param value 42");
    params.addParam<std::vector<Real>>("online_mu_43",_zero_vect,"Online param value 43");
    params.addParam<std::vector<Real>>("online_mu_44",_zero_vect,"Online param value 44");
    params.addParam<std::vector<Real>>("online_mu_45",_zero_vect,"Online param value 45");
    params.addParam<std::vector<Real>>("online_mu_46",_zero_vect,"Online param value 46");
    params.addParam<std::vector<Real>>("online_mu_47",_zero_vect,"Online param value 47");
    params.addParam<std::vector<Real>>("online_mu_48",_zero_vect,"Online param value 48");
    params.addParam<std::vector<Real>>("online_mu_49",_zero_vect,"Online param value 49");
    params.addRequiredParam<unsigned int>("Aq_mat_offset","Starting index of the Aq matrices to be assembled in this run.");
    params.addRequiredParam<unsigned int>("Mq_mat_offset","Starting index of the Mq matrices to be assembled in this run.");
    params.addRequiredParam<unsigned int>("mesh_num","The mesh refinement index starting at 0");
    params.addRequiredParam<std::string>("param_str","param_min, param_ref or param_max");
    params.addParam<std::string>("mesh_file_location","","location where mesh data should be written");
    params.addParam<std::string>("mat_file_location","","location where sparse-matrix files (Aq (non-bc) and Mq) should be written");
    params.addParam<std::string>("vec_file_location","","locatoin where BC (Aq and Fq) and heat source (Fq) files should be written");
    return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantOfflineOnlineStageTransient::DwarfElephantOfflineOnlineStageTransient(const InputParameters & params):
    GeneralUserObject(params),
    _use_displaced(getParam<bool>("use_displaced")),
    _store_basis_functions(getParam<bool>("store_basis_functions")),
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
    _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
    _sys(_es.get_system<TransientNonlinearImplicitSystem>(_system_name)),
    _initialize_rb_system(getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject")),
    _mesh_ptr(&_fe_problem.mesh()),
    _subdomain_ids(_mesh_ptr->meshSubdomains()),
    _mu_bar(getParam<Real>("mu_bar")),
    _online_N(getParam<unsigned int>("online_N")),
    _online_mu_parameters(getParam<std::vector<Real>>("online_mu")),
    _rb_problem(cast_ptr<DwarfElephantRBProblem *>(&_fe_problem)),
    _ref_mu_parameters(getParam<std::vector<Real>>("mu_ref")),
    _num_online_solves(getParam<unsigned int>("num_online_solves")),
    _Aq_mat_offset(getParam<unsigned int>("Aq_mat_offset")),
    _Mq_mat_offset(getParam<unsigned int>("Mq_mat_offset")),
    _mesh_num(getParam<unsigned int>("mesh_num")),
    _param_str(getParam<std::string>("param_str")),
    _mesh_file_location(getParam<std::string>("mesh_file_location")),
    _mat_file_location(getParam<std::string>("mat_file_location")),
    _vec_file_location(getParam<std::string>("vec_file_location"))

{
    
    for (unsigned int i = 0; i < _num_online_solves; i++)
        _online_mu_vec.push_back(getParam<std::vector<Real>>("online_mu_"+std::to_string(i)));
}

void
DwarfElephantOfflineOnlineStageTransient::setAffineMatrices()
{
   _initialize_rb_system._inner_product_matrix -> close();
   for(unsigned int _p = 0; _p < _ref_mu_parameters.size(); _p++)
       _mu_ref.set_value("mu_"+std::to_string(_p),_ref_mu_parameters[_p]);
   
    for(unsigned int _q=0; _q<_initialize_rb_system._qa; _q++)
    {
      //_rb_problem->rbAssembly(_q).setCachedJacobianContributions(*_initialize_rb_system._jacobian_subdomain[_q]); // For testing against EIM example in Martin's publication
      _initialize_rb_system._jacobian_subdomain[_q] ->close();
      //_initialize_rb_system._jacobian_subdomain[_q]->print_matlab(_mat_file_location + "mesh" + std::to_string(_mesh_num) + "/Aq_"+std::to_string(_q+_Aq_mat_offset)+".m"); //CHECK IF TESTCASE

      //_initialize_rb_system._inner_product_matrix->add(_initialize_rb_system._rb_eval_ptr->get_rb_theta_expansion().eval_A_theta(_q,_mu_ref), *_initialize_rb_system._jacobian_subdomain[_q]);
      //_initialize_rb_system._inner_product_matrix -> print_matlab("./3DRBRFAMatrices/RBRFA3DPerf_InnerProdMat.m");
    }
   //_initialize_rb_system._inner_product_matrix->add(1., *_initialize_rb_system._jacobian_subdomain[0]); // for debugging

    _initialize_rb_system._L2_matrix -> close();
    for(unsigned int _q=0; _q<_initialize_rb_system._qm; _q++)
    {
      // _initialize_rb_system._mass_matrix_subdomain[_q] ->close();
      // _initialize_rb_system._L2_matrix->add(_mu_bar, *_initialize_rb_system._mass_matrix_subdomain[_q]);
     // _rb_problem->rbAssembly(_q).setCachedMassMatrixContributions(*_initialize_rb_system._mass_matrix_subdomain[_q]);
      _initialize_rb_system._mass_matrix_subdomain[_q] ->close();
      //_initialize_rb_system._L2_matrix->add(dynamic_cast<TransientRBThetaExpansion&>(_initialize_rb_system._rb_eval_ptr->get_rb_theta_expansion()).eval_M_theta(_q,_mu_ref), *_initialize_rb_system._mass_matrix_subdomain[_q]);
      //_initialize_rb_system._mass_matrix_subdomain[_q]->print_matlab(_mat_file_location + "mesh" + std::to_string(_mesh_num) + "/Mq_"+std::to_string(_q+_Mq_mat_offset)+".m"); //CHECK IF TESTCASE
    }
}

void
DwarfElephantOfflineOnlineStageTransient::transferAffineVectors()
{
  // Transfer the vectors
  // Transfer the data for the F vectors.
 for(unsigned int _q=0; _q<_initialize_rb_system._qf; _q++)
  {
    //_rb_problem->rbAssembly(_q).setCachedResidual(*_initialize_rb_system._residuals[_q]);
    _initialize_rb_system._residuals[_q]->close();
    _initialize_rb_system._residuals[_q]->print_matlab(_vec_file_location + "F_vectors/" + _param_str + "/mesh" + std::to_string(_mesh_num) + "/Fq_"+std::to_string(_q)+".m"); //CHECK TESTCASE OR ACTUAL CASE
  }

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
    
    //setOnlineParameters();
    //_initialize_rb_system._rb_eval_ptr ->set_parameters(_rb_online_mu); // always keep commented
    
    //_initialize_rb_system._rb_con_ptr->FE_solve_debug(_rb_online_mu, 1/*write_interval*/,1/*num_param_values*/, _mesh_index, _initialize_rb_system._temp_averaging_node_ids);
//    _initialize_rb_system._rb_con_ptr->FE_solve_steady(_rb_online_mu);
   //_initialize_rb_system._rb_con_ptr->write_mesh_node_coords_and_elem_connectivities(_mesh_file_location + "mesh_"+std::to_string(_mesh_num)); //CHECK TEST SUFFIX: _test (argument 2)
/*    std::cout << endl << "this is a processor" << endl;

    _initialize_rb_system._rb_con_ptr->train_reduced_basis();
   #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataSerialization::TransientRBEvaluationSerialization _rb_eval_writer(_initialize_rb_system._rb_con_ptr->get_rb_evaluation());
     _rb_eval_writer.write_to_file("trans_rb_eval.bin");
    #else
      // Write the offline data to file (xdr format).
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().legacy_write_offline_data_to_files();
    #endif

    // If desired, store the basis functions (xdr format).
    if (_store_basis_functions)
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().write_out_basis_functions(*_initialize_rb_system._rb_con_ptr);


//    _initialize_rb_system._rb_con_ptr->print_basis_function_orthogonality(); */
}

void DwarfElephantOfflineOnlineStageTransient::offlineStageEIM()
{

    setOnlineParameters();
    //_initialize_rb_system._rb_eval_ptr ->set_parameters(_rb_online_mu);
    _initialize_rb_system._eim_con_ptr -> load_rb_solution();
    *_es.get_system("aux0").solution = *_es.get_system("EIMSystem_explicit_sys").solution;
    VTKIO(_mesh_ptr->getMesh()).write_equation_systems("EIMSoln.pvtu", _es);
    std::vector<unsigned int> _temp_avg_node_ids = {2};
    _initialize_rb_system._rb_con_ptr->FE_solve_debug(_rb_online_mu, 1, 1, _mesh_num, _temp_avg_node_ids);
    //_initialize_rb_system._rb_con_ptr->train_reduced_basis();
    /*
    std::cout << "After RB training" << std::endl;
    std::srand( static_cast<unsigned>( std::time(0)));
    for (unsigned int counter = 0; counter < 20; counter++)
    {
        //setOnlineParameters();
        std::cout << "Error Analysis" << std::endl;
        Real random_number = ((double)std::rand())/RAND_MAX; // in range [0,1]
        _rb_online_mu.set_value("mu_0",1e-3 + 4e-3*random_number);
        random_number = ((double)std::rand())/RAND_MAX; // in range [0,1]
        _rb_online_mu.set_value("mu_1",3e-2 + 4e-2 * random_number);
        random_number = ((double)std::rand())/RAND_MAX; // in range [0,1]
        _rb_online_mu.set_value("mu_2",-1e-2 + 2e-2 * random_number);
        random_number = ((double)std::rand())/RAND_MAX; // in range [0,1]
        _rb_online_mu.set_value("mu_3",-1e-2 + 2e-2 * random_number);
        random_number = ((double)std::rand())/RAND_MAX; // in range [0,1]
        _rb_online_mu.set_value("mu_4",-1e-2 + 2e-2 * random_number);
        _initialize_rb_system._rb_con_ptr->set_up_error_norm_v_N_vec();
        _initialize_rb_system._rb_con_ptr->FE_solve_debug(_rb_online_mu, 1);
        _initialize_rb_system._rb_con_ptr->print_error_norm_v_N_vec(_rb_online_mu);
    } */
    //setOnlineParameters();
    //_initialize_rb_system._rb_con_ptr->set_up_error_norm_v_N_vec();
    //_initialize_rb_system._rb_con_ptr->FE_solve_debug(_rb_online_mu, 1);
    //_initialize_rb_system._rb_con_ptr->print_error_norm_v_N_vec(_rb_online_mu);
    // Do Error Analysis here

    
    #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataSerialization::RBEvaluationSerialization _rb_eval_writer(_initialize_rb_system._rb_con_ptr->get_rb_evaluation());
      _rb_eval_writer.write_to_file("rb_eval.bin");
    #else
      // Write the offline data to file (xdr format).
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().legacy_write_offline_data_to_files("offline_data");
    #endif

    // If desired, store the basis functions (xdr format).
    if (_store_basis_functions)
    {
      _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().write_out_basis_functions(_initialize_rb_system._eim_con_ptr->get_explicit_system(),"eim_data");  
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().write_out_basis_functions(*_initialize_rb_system._rb_con_ptr,"offline_data");
    }

//    _initialize_rbeim_system._rb_con_ptr->print_basis_function_orthogonality();
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
      
      _initialize_rb_system._rb_con_ptr->set_n_time_steps(_initialize_rb_system._n_time_steps);
      _initialize_rb_system._rb_con_ptr->set_delta_t(_initialize_rb_system._delta_time);
      _initialize_rb_system._rb_con_ptr->set_euler_theta(_initialize_rb_system._euler_theta);
      _initialize_rb_system._rb_con_ptr->set_time_step(0);
  }
}

void DwarfElephantOfflineOnlineStageTransient::onlineStageEIM()
{
    {
      Moose::perf_log.push("onlineStage()", "Execution");
      
        #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataDeserialization::RBEIMEvaluationDeserialization _rb_eim_eval_reader(_initialize_rb_system._eim_con_ptr -> get_rb_evaluation());
      rb_eim_eval_reader.read_from_file("rb_eim_eval.bin");
      #else
      _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("eim_data");
      #endif
      _initialize_rb_system._eim_eval_ptr -> initialize_eim_theta_objects();
      for (unsigned int _i = 0; _i < _fe_problem.mesh().meshSubdomains().size() ; _i++) // add conditional statement later to handle multiple cases
          _initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
      //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
      
            #if defined(LIBMESH_HAVE_CAPNPROTO)
        RBDataDeserialization::TrasientRBEvaluationDeserialization _rb_eval_reader(_rb_eval);
        _rb_eval_reader.read_from_file("trans_rb_eval.bin", /*read_error_bound_data*/ true);
      #else
        _initialize_rb_system._rb_eval_ptr->legacy_read_offline_data_from_files();
      #endif
      setOnlineParameters();// Input parameter values from file
      _initialize_rb_system._rb_eval_ptr ->set_parameters(_rb_online_mu);

      _console << "---- Online Stage ----" << std::endl;
      _initialize_rb_system._rb_eval_ptr ->print_parameters();

      if(_online_N==0)
        _online_N = _initialize_rb_system._rb_con_ptr->get_rb_evaluation().get_n_basis_functions();

     if(_offline_error_bound)
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().evaluate_RB_error_bound = false;

      Real _error_bound_final_time = _initialize_rb_system._rb_con_ptr->get_rb_evaluation().rb_solve(_online_N); // run loop for multiple online solves. Collect full order solution vectors for each of the online sovles.
      // call function to compute the Arrhenius tissue damage.

      _n_time_steps = _initialize_rb_system._n_time_steps;

      _console << "Error bound at the final time is " << _error_bound_final_time << std::endl << std::endl;

      if(_output_console)
      {
        TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(*_initialize_rb_system._rb_eval_ptr);
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
        TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(*_initialize_rb_system._rb_eval_ptr);

        _RB_outputs_all_timesteps.resize(_n_time_steps+1);

        for (unsigned int _t = 0; _t <= _n_time_steps; _t++)
        {
          _RB_outputs_all_timesteps[_t].resize(_n_outputs);

          for (unsigned int i = 0; i != _n_outputs; i++)
            _RB_outputs_all_timesteps[_t][i] = trans_rb_eval.RB_outputs_all_k[i][_t];
        }

          _fe_problem.outputStep(EXEC_TIMESTEP_END);
      }

      Moose::perf_log.pop("onlineStage()", "Execution");

      Moose::perf_log.push("DataTransfer()", "Execution");
      if(_output_file)
      {
         _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().read_in_basis_functions(_initialize_rb_system._eim_con_ptr->get_explicit_system(),"eim_data");
          _initialize_rb_system._rb_eval_ptr->read_in_basis_functions(*_initialize_rb_system._rb_con_ptr);
          _initialize_rb_system._eim_con_ptr -> load_rb_solution();
         *_es.get_system("aux0").solution = *_es.get_system("EIMSystem_explicit_sys").solution;
          _fe_problem.getNonlinearSystemBase().update();
         for (unsigned int _time_step = 1; _time_step <= _n_time_steps; _time_step++)
        {
          _initialize_rb_system._rb_con_ptr->set_time_step(_time_step);
          _initialize_rb_system._rb_con_ptr->load_rb_solution();
          *_es.get_system(_system_name).solution = *_es.get_system("RBSystem").solution;
          *_es.get_system("aux0").solution = *_es.get_system("EIMSystem_explicit_sys").solution;
          _fe_problem.getNonlinearSystemBase().update();
          _fe_problem.timeStep()=_time_step;
          endStep(0);
        }

          //ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("TransientRBSoln.e",_es);
          //VTKIO(_mesh_ptr->getMesh()).write_equation_systems("out.pvtu", _es);
      }
      Moose::perf_log.pop("DataTransfer()", "Execution");
    }
}
void
DwarfElephantOfflineOnlineStageTransient::initialize()
{
}

void
DwarfElephantOfflineOnlineStageTransient::execute()
{
    using std::cout;
    using std::endl;
    
    // Build the RBEvaluation object
    // Required for both the Offline and Online stage.
    //DwarfElephantRBEvaluationTransient _rb_eval(comm() , _fe_problem, _initialize_rb_system._RB_RFA);

//    _initialize_rb_system._rb_con_ptr->process_parameters_file(_initialize_rb_system._parameters_filename);

    //if (!_offline_stage && _output_file && !_initialize_rb_system._use_EIM)
    //  _initialize_rb_system._rb_con_ptr->init();
    
    if (_offline_stage || _output_file || _offline_error_bound || _online_N == 0)
    {
      // Pass a pointer of the RBEvaluation object to the
      // RBConstruction object
      if (!_initialize_rb_system._use_EIM) {/*_initialize_rb_system._rb_con_ptr->set_rb_evaluation(_rb_eval);*/}

      TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(*_initialize_rb_system._rb_eval_ptr);
      trans_rb_eval.pull_temporal_discretization_data(*_initialize_rb_system._rb_con_ptr);
    }
    
    if (_offline_stage)
    {
      
        TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(*_initialize_rb_system._rb_eval_ptr);
      trans_rb_eval.pull_temporal_discretization_data(*_initialize_rb_system._rb_con_ptr);
      // Transfer the affine vectors to the RB system.
      if(_skip_vector_assembly_in_rb_system)
        transferAffineVectors();

      // Transfer the affine matrices to the RB system.
      if(_skip_matrix_assembly_in_rb_system)
        setAffineMatrices();

      // Perform the offline stage.
      _console << std::endl;

      if (_initialize_rb_system._use_EIM) { offlineStageEIM();}
      else
          offlineStage(); // Commenting out because the matrices are to be written out in matlab format to be used in a matlab script.

      _console << std::endl;
    }

    if(_online_stage)
    {
      if (!_initialize_rb_system._use_EIM) {  
      #if defined(LIBMESH_HAVE_CAPNPROTO)
        RBDataDeserialization::TrasientRBEvaluationDeserialization _rb_eval_reader(_rb_eval);
        _rb_eval_reader.read_from_file("trans_rb_eval.bin", /*read_error_bound_data*/ true); 
      #else
        _initialize_rb_system._rb_eval_ptr->legacy_read_offline_data_from_files();
      #endif
      _initialize_rb_system._rb_eval_ptr->read_in_basis_functions(*_initialize_rb_system._rb_con_ptr);
      std::cout << "\n Number of basis functions: " << _initialize_rb_system._rb_eval_ptr->get_n_basis_functions() << std::endl;
      setOnlineParameters();
      _initialize_rb_system._rb_con_ptr->computeTissueDamage(_num_online_solves, _online_mu_vec); }
        /*
        if (!_initialize_rb_system._use_EIM) {
            
        
        Moose::perf_log.push("onlineStage()", "Execution");

      #if defined(LIBMESH_HAVE_CAPNPROTO)
        RBDataDeserialization::TrasientRBEvaluationDeserialization _rb_eval_reader(_rb_eval);
        _rb_eval_reader.read_from_file("trans_rb_eval.bin", / *read_error_bound_data* / / * true); * /
 / *     #else
        _initialize_rb_system._rb_eval_ptr->legacy_read_offline_data_from_files();
      #endif

      setOnlineParameters();
      _initialize_rb_system._rb_eval_ptr->set_parameters(_rb_online_mu);

      _console << "---- Online Stage ----" << std::endl;
      _initialize_rb_system._rb_eval_ptr->print_parameters();

      
      if(_online_N==0)
        _online_N = _initialize_rb_system._rb_con_ptr->get_rb_evaluation().get_n_basis_functions();

     if(_offline_error_bound)
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().evaluate_RB_error_bound = false;

      Real _error_bound_final_time = _initialize_rb_system._rb_eval_ptr->rb_solve(_online_N);

      _n_time_steps = _initialize_rb_system._n_time_steps;

      _console << "Error bound at the final time is " << _error_bound_final_time << std::endl << std::endl;

      if(_output_console)
      {
        TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(*_initialize_rb_system._rb_eval_ptr);
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
        TransientRBEvaluation & trans_rb_eval = cast_ref<TransientRBEvaluation &>(*_initialize_rb_system._rb_eval_ptr);

        _RB_outputs_all_timesteps.resize(_n_time_steps+1);

        for (unsigned int _t = 0; _t <= _n_time_steps; _t++)
        {
          _RB_outputs_all_timesteps[_t].resize(_n_outputs);

          for (unsigned int i = 0; i != _n_outputs; i++)
            _RB_outputs_all_timesteps[_t][i] = trans_rb_eval.RB_outputs_all_k[i][_t];
        }

          _fe_problem.outputStep(EXEC_TIMESTEP_END);
      }

      Moose::perf_log.pop("onlineStage()", "Execution");

      Moose::perf_log.push("DataTransfer()", "Execution");
      if(_output_file)
      {
         _initialize_rb_system._rb_eval_ptr->read_in_basis_functions(*_initialize_rb_system._rb_con_ptr);

         for (unsigned int _time_step = 0; _time_step <= _n_time_steps; _time_step++)
        {
          _initialize_rb_system._rb_con_ptr->set_time_step(_time_step);
          _initialize_rb_system._rb_con_ptr->load_rb_solution();
          *_es.get_system(_system_name).solution = *_es.get_system("RBSystem").solution;
          _fe_problem.getNonlinearSystemBase().update();
          _fe_problem.timeStep()=_time_step;
          endStep(0);
        }
         
        // Plot the solution
        Moose::perf_log.push("write_exodus()", "Output");

        // Read in the basis functions
        _rb_eval.read_in_basis_functions(*_initialize_rb_system._rb_con_ptr);

        std::string _systems_for_print[] = {"RBSystem"};
        const std::set<std::string>  _system_names_for_print (_systems_for_print, _systems_for_print+sizeof(_systems_for_print)/sizeof(_systems_for_print[0]));

        ExodusII_IO exo(_mesh_ptr->getMesh());
        exo.write_equation_systems(getFileName(), _es, &_system_names_for_print);

        for (unsigned int _time_step = 1; _time_step <= _initialize_rb_system._rb_con_ptr->get_n_time_steps(); _time_step++)
        {
          exo.append(true);
          _initialize_rb_system._rb_con_ptr->pull_temporal_discretization_data(_rb_eval);
          _initialize_rb_system._rb_con_ptr->set_time_step(_time_step);
          _initialize_rb_system._rb_con_ptr->load_rb_solution();
          exo.write_timestep(getFileName(), _es, _time_step, _time_step * _initialize_rb_system._rb_con_ptr->get_delta_t());
        }
      }
      Moose::perf_log.pop("DataTransfer()", "Execution");
    }* / / *
        else {
      //Moose::perf_log.push("onlineStage()", "Execution");
      
        #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataDeserialization::RBEIMEvaluationDeserialization _rb_eim_eval_reader(_initialize_rb_system._eim_con_ptr -> get_rb_evaluation());
      rb_eim_eval_reader.read_from_file("rb_eim_eval.bin");
      #else
      _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("eim_data");
      #endif
      _initialize_rb_system._eim_eval_ptr -> initialize_eim_theta_objects();
      for (unsigned int _i = 0; _i < _fe_problem.mesh().meshSubdomains().size() ; _i++) // add conditional statement later to handle multiple cases
          _initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
      //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
      
            #if defined(LIBMESH_HAVE_CAPNPROTO)
        RBDataDeserialization::TrasientRBEvaluationDeserialization _rb_eval_reader(_rb_eval);
        _rb_eval_reader.read_from_file("trans_rb_eval.bin", /*read_error_bound_data*/ /*true); */
                /*
      #else
        _initialize_rb_system._rb_eval_ptr->legacy_read_offline_data_from_files();
      #endif
            _initialize_rb_system._rb_con_ptr->computeTissueDamage(_num_online_solves, _online_mu_vec);}//onlineStageEIM();}*/
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
DwarfElephantOfflineOnlineStageTransient::endStep(Real /*input_time*/)
{
    // Real _time = input_time;

    // Compute the Error Indicators and Markers
    _fe_problem.computeIndicators();
    _fe_problem.computeMarkers();

    _fe_problem.execute(EXEC_CUSTOM);

    // Perform the output of the current time step
    _fe_problem.outputStep(EXEC_TIMESTEP_END);

    // output
   // if (_time_interval && (_time + _timestep_tolerance >= _next_interval_output_time))
   //   _next_interval_output_time += _time_interval_output_interval;
}

void 
DwarfElephantOfflineOnlineStageTransient::process_mem_usage(double& vm_usage, double& resident_set)
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
