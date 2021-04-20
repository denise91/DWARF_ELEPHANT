/**
 * This UserObject implements the Offline and Online stage of the RB method.
 */

///---------------------------------INCLUDES--------------------------------
#include <sstream>
#include <iomanip>
#include <cstring>
#include "libmesh/vtk_io.h"
// MOOSE includes (DwarfElephant package)
#include "DwarfElephantOfflineOnlineStageSteadyState.h"
#include "DwarfElephantRBClassesSteadyState.h"
#include <random>
///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantOfflineOnlineStageSteadyState>()
{
    InputParameters params = validParams<GeneralUserObject>();

    params.addParam<bool>("use_displaced", false, "Enable/disable the use of the displaced mesh for the data retrieving.");
    params.addParam<bool>("store_basis_functions", true, "Determines whether the basis functions are stored or not.");
    params.addParam<bool>("compliant", true, "Determines whether F is equal to the output vector or not.");
    params.addParam<bool>("skip_matrix_assembly_in_rb_system", true, "Determines whether the matrix is assembled in the RB System or in the nl0 system.");
    params.addParam<bool>("skip_vector_assembly_in_rb_system", true, "Determines whether the vectors are assembled in the RB System or in the nl0 system.");
    params.addParam<bool>("online_stage", false, "Determines whether the Online stage will be calculated or not.");
    params.addParam<bool>("offline_error_bound", false, "Determines which error bound is used.");
    params.addParam<bool>("output_file", true, "Determines whether an output file is generated or not.");
    params.addParam<bool>("compute_output", false, "Determines whether an output of interest is computed or not.");
    params.addParam<std::string>("system","rb0","The name of the system that should be read in.");
    params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system.");
    params.addRequiredParam<unsigned int>("online_N", "Defines the dimension of the online stage.");
    params.addParam<Real>("mu_bar", 1., "Value for mu-bar");
    params.addRequiredParam<std::vector<Real>>("online_mu", "Current values of the different layers for which the RB Method is solved.");
    params.addRequiredParam<unsigned int>("mesh_num","The mesh refinement index starting at 0");
    params.addRequiredParam<std::string>("param_str","param_min, param_ref or param_max");
    params.addRequiredParam<std::string>("vec_file_location","Location to store F vectors");
    return params;
}

///-------------------------------CONSTRUCTOR-------------------------------
DwarfElephantOfflineOnlineStageSteadyState::DwarfElephantOfflineOnlineStageSteadyState(const InputParameters & params):
    GeneralUserObject(params),
    _use_displaced(getParam<bool>("use_displaced")),
    _store_basis_functions(getParam<bool>("store_basis_functions")),
    _skip_matrix_assembly_in_rb_system(getParam<bool>("skip_matrix_assembly_in_rb_system")),
    _skip_vector_assembly_in_rb_system(getParam<bool>("skip_matrix_assembly_in_rb_system")),
    _compliant(getParam<bool>("compliant")),
    _online_stage(getParam<bool>("online_stage")),
    _offline_error_bound(getParam<bool>("offline_error_bound")),
    _output_file(getParam<bool>("output_file")),
    _compute_output(getParam<bool>("compute_output")),
    _online_N(getParam<unsigned int>("online_N")),
    _system_name(getParam<std::string>("system")),
    _es(_use_displaced ? _fe_problem.getDisplacedProblem()->es() : _fe_problem.es()),
    _sys(_es.get_system<TransientNonlinearImplicitSystem>(_system_name)),
    _initialize_rb_system(getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject")),
    _mesh_ptr(&_fe_problem.mesh()),
    _subdomain_ids(_mesh_ptr->meshSubdomains()),
    _mu_bar(getParam<Real>("mu_bar")),
    _online_mu_parameters(getParam<std::vector<Real>>("online_mu")),
    _rb_problem(cast_ptr<DwarfElephantRBProblem *>(&_fe_problem)),
    _mesh_num(getParam<unsigned int>("mesh_num")),
    _param_str(getParam<std::string>("param_str")),
    _vec_file_location(getParam<std::string>("vec_file_location"))
{
}

void
DwarfElephantOfflineOnlineStageSteadyState::setAffineMatrices()
{  
   _initialize_rb_system._inner_product_matrix->close();
    for(unsigned int _q=0; _q<_initialize_rb_system._qa; _q++)
    {
      //_rb_problem->rbAssembly(0).setCachedJacobianContributions(*_initialize_rb_system._jacobian_subdomain[_q]); // for EIM example in Martin's publication
      //_initialize_rb_system._jacobian_subdomain[_q]->print_matlab("./3DRBRFAMatrices/RBRFA3DNoPerf_Aq_"+std::to_string(_q)+".m");
        _initialize_rb_system._jacobian_subdomain[_q] ->close();
   
      
      _initialize_rb_system._inner_product_matrix->add(_mu_bar, *_initialize_rb_system._jacobian_subdomain[_q]);
    }
   //_initialize_rb_system._inner_product_matrix -> print_matlab("./3DRBRFAMatrices/RBRFA3DNoPerf_InnerProdMat.m"); 
   _initialize_rb_system._inner_product_matrix -> close();
    
}

void
DwarfElephantOfflineOnlineStageSteadyState::transferAffineVectors()
{
    // Transfer the vectors
    // Transfer the data for the F vectors.
    for(unsigned int _q=0; _q<_initialize_rb_system._qf; _q++)
    {
      
      //_rb_problem->rbAssembly(0).setCachedResidual(*_initialize_rb_system._residuals[_q]); // line added for compatibility with libMesh EIM example 
      _initialize_rb_system._residuals[_q]->close();
      //_initialize_rb_system._residuals[_q]->print_matlab(_vec_file_location + "/mesh" + std::to_string(_mesh_num) + "/Fq_"+std::to_string(_q)+".m"); //CHECK TESTCASE OR ACTUAL CASE 
    }

    if(_compute_output)
    {
      // Transfer the data for the output vectors.
      for(unsigned int i=0; i < _initialize_rb_system._n_outputs; i++)
      {
        for(unsigned int _q=0; _q < _initialize_rb_system._ql[i]; _q++)
        {
          //_rb_problem->rbAssembly(_q).setCachedOutput(*_initialize_rb_system._outputs[i][_q]);
          _initialize_rb_system._outputs[i][_q]->close();
        }
      }
    }
}

void
DwarfElephantOfflineOnlineStageSteadyState::offlineStageEIM()
{
    for (unsigned int  _q = 0; _q != _online_mu_parameters.size(); _q++)
    {
        std::string  _mu_name = "mu_" + std::to_string(_q);
        _rb_online_mu.set_value(_mu_name, _online_mu_parameters[_q]);
    }

    //_initialize_rb_system._rb_con_ptr->GreedyOutputFile.open("RBGreedyOutputFile.csv");
    //_initialize_rb_system._rb_con_ptr->GreedyOutputFile << "mu_0, mu_1, MaxErrorBound" << std::endl;
    //_initialize_rb_system._rb_con_ptr->train_reduced_basis();
    //_initialize_rb_system._rb_con_ptr->GreedyOutputFile.close();

    _initialize_rb_system._eim_eval_ptr ->set_parameters(_rb_online_mu);
    _initialize_rb_system._eim_eval_ptr->rb_solve(_initialize_rb_system._eim_eval_ptr->get_n_basis_functions());
    _initialize_rb_system._eim_con_ptr->load_rb_solution();
    _initialize_rb_system._rb_con_ptr->do_RB_vs_FE_Error_analysis(_rb_online_mu, _es);
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
DwarfElephantOfflineOnlineStageSteadyState::offlineStageRBOnly()
{
    for (unsigned int  _q = 0; _q != _online_mu_parameters.size(); _q++)
    {
        std::string  _mu_name = "mu_" + std::to_string(_q);
        _rb_online_mu.set_value(_mu_name, _online_mu_parameters[_q]);
    }
    _initialize_rb_system._rb_con_ptr->GreedyOutputFile.open("RBGreedyOutputFile.csv");
    _initialize_rb_system._rb_con_ptr->GreedyOutputFile << "mu_0, mu_1, MaxErrorBound" << std::endl;
    _initialize_rb_system._rb_con_ptr->train_reduced_basis();
    _initialize_rb_system._rb_eval_ptr ->set_parameters(_rb_online_mu);
    _initialize_rb_system._rb_con_ptr->do_RB_vs_FE_Error_analysis(_rb_online_mu, _es);
    _initialize_rb_system._rb_con_ptr->GreedyOutputFile.close();
    //_initialize_rb_system._eim_eval_ptr -> initialize_eim_theta_objects();
      //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
    #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataSerialization::RBEvaluationSerialization _rb_eval_writer(_initialize_rb_system._rb_con_ptr->get_rb_evaluation());
      _rb_eval_writer.write_to_file("rb_eval.bin");
     // RBDataSerialization::RBSCMEvaluationSerialization _rb_scm_eval_writer (_initialize_rb_system._rb_scm_con_ptr->get_rb_scm_evaluation());
     // _rb_scm_eval_writer.write_to_file("rb_scm_eval.bin");
    #else
      // Write the offline data to file (xdr format).
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().legacy_write_offline_data_to_files("offline_data");
     // _initialize_rb_system._rb_scm_con_ptr->get_rb_scm_evaluation().legacy_write_offline_data_to_files("scm_data");
    #endif

    // If desired, store the basis functions (xdr format).
    if (_store_basis_functions)
    { 
      _initialize_rb_system._rb_con_ptr->get_rb_evaluation().write_out_basis_functions(*_initialize_rb_system._rb_con_ptr,"offline_data");
    }

//    _initialize_rbeim_system._rb_con_ptr->print_basis_function_orthogonality();
}

void
DwarfElephantOfflineOnlineStageSteadyState::setOnlineParameters()
{
    for (unsigned int  _q = 0; _q != _online_mu_parameters.size(); _q++)
    {
        std::string  _mu_name = "mu_" + std::to_string(_q);
        _rb_online_mu.set_value(_mu_name, _online_mu_parameters[_q]);
    }
}

void DwarfElephantOfflineOnlineStageSteadyState::onlineStagehpEIM()
{
    //Moose::perf_log.push("onlineStage()", "Execution");
//        std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<> dis(-0.03,0.03);
    //std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();    
    setOnlineParameters();
    _initialize_rb_system._hp_eim_tree_ptr->online_solve(_rb_online_mu, _online_N, true, _es, _fe_problem, _mesh_ptr, _initialize_rb_system._rb_con_ptr, _initialize_rb_system._hp_EIM_testing);
    /*
    unsigned int testcases = 40;
    for (unsigned int i = 0; i < testcases; i++)
    { 
        for (unsigned int j = 0; j < testcases; j++)
        {
            //for (unsigned int  _q = 0; _q < _online_mu_parameters.size(); _q++)
            //{
                //std::string  _mu_name = "mu_" + std::to_string(_q);
                //_rb_online_mu.set_value(_mu_name, dis(gen));
            //}
            _rb_online_mu.set_value("mu_0", -0.03 + 0.06*static_cast<double>(i)/(testcases-1));
            _rb_online_mu.set_value("mu_1", -0.03 + 0.06*static_cast<double>(j)/(testcases-1));
            std::cout << "Online params: " << -0.03 + 0.06*static_cast<double>(i)/(testcases-1) << " " << -0.03 + 0.06*static_cast<double>(j)/(testcases-1) << std::endl;
            _initialize_rb_system._hp_eim_tree_ptr->online_solve(_rb_online_mu, _online_N, false, _es, _fe_problem, _mesh_ptr, _initialize_rb_system._rb_con_ptr, _initialize_rb_system._hp_EIM_testing);
        }
    }*/
    
    //std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    //std::cout << "Average time taken per online solve: " << duration/(1e6*std::pow(testcases,2)) << " seconds." << std::endl;
    
    // model now ready for operation in online multiple query context
    // search for _rb_online_mu in the hp EIM tree
    // do an rb_solve
    
}


void DwarfElephantOfflineOnlineStageSteadyState::onlineStageEIM()
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
      //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_A_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects()); // for EIM example in Martin's publication

      #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataSerialization::RBEvaluationDeserialization rb_eval_reader(_initialize_rb_system._rb_con_ptr -> get_rb_evaluation());
      rb_eval_reader.read_from_file("rb_eval.bin");
      #else
      _initialize_rb_system._rb_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("offline_data");
      #endif

      setOnlineParameters();
      _initialize_rb_system._rb_eval_ptr ->set_parameters(_rb_online_mu);

      _console << "---- Online Stage ----" << std::endl;
      _initialize_rb_system._rb_eval_ptr ->print_parameters();
      std::cout << "Online N = " << _online_N << std::endl;

      if (_online_N == 0)
        _online_N = _initialize_rb_system._rb_eval_ptr->get_n_basis_functions();

      if(_offline_error_bound)
       _initialize_rb_system._rb_eval_ptr->evaluate_RB_error_bound = false;

      _initialize_rb_system._rb_eval_ptr->rb_solve(_online_N);
/*
      if (_compute_output)
        for (unsigned int i = 0; i != _initialize_rbeim_system._n_outputs_rb; i++)
          for (unsigned int _q = 0; _q != _initialize_rbeim_system._ql_rb[i]; _q++)
            _console << "Output " << std::to_string(i) << ": value = " << _rb_eval.RB_outputs[i]
            << ", error bound = " << _rb_eval.RB_output_error_bounds[i] << std::endl;
*/
      // Back transfer of the data to use MOOSE Postprocessor and Output classes
      //Moose::perf_log.push("DataTransfer()", "Execution");
      if(_output_file)
      {
         _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().read_in_basis_functions(_initialize_rb_system._eim_con_ptr->get_explicit_system(),"eim_data");
         _initialize_rb_system._rb_con_ptr -> get_rb_evaluation().read_in_basis_functions(*_initialize_rb_system._rb_con_ptr,"offline_data");

         _initialize_rb_system._eim_con_ptr -> load_rb_solution();
         _initialize_rb_system._rb_con_ptr -> load_rb_solution();

         //*_es.get_system(_system_name).solution = *_es.get_system("RBSystem").solution;
         //_fe_problem.getNonlinearSystemBase().update();
         std::stringstream ss;
         
            
            *_es.get_system("rb0").solution = *_es.get_system("RBSystem").solution;
            *_es.get_system("aux0").solution = *_es.get_system("EIMSystem_explicit_sys").solution;
            //_fe_problem.getNonlinearSystemBase().update();
            unsigned int num_sys = _es.n_systems();
            std::vector<std::string> sys_names;
            for (unsigned int i = 0; i < num_sys; i++)
                sys_names.push_back(_es.get_system(i).name());
            
            /*for (unsigned int i = 0; _es.n_systems() > 2; i++)
            {
               
                if ((sys_names[i] != "rb0") && (sys_names[i] != "aux0"))
                {    
                    _es.delete_system(sys_names[i]);
                }
                //std::cout <<"Number of systems left" <<  _es.n_systems() << std::endl;
            }*/

         ss << std::setw(2) << std::setfill('0') << _online_N;
         
		 #ifdef LIBMESH_HAVE_EXODUS_API
		 ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("RB_sol_DwarfElephant.e-s"+ss.str(),_es);
		 #endif
                 VTKIO(_mesh_ptr->getMesh()).write_equation_systems("out.pvtu", _es);
      }
}

void DwarfElephantOfflineOnlineStageSteadyState::onlineStageRBOnly()
{
      Moose::perf_log.push("onlineStage()", "Execution");
      #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataSerialization::RBEvaluationDeserialization rb_eval_reader(_initialize_rb_system._rb_con_ptr -> get_rb_evaluation());
      rb_eval_reader.read_from_file("rb_eval.bin");
     // RBDataDeserialization::RBSCMEvaluationDeserialization rb_scm_eval_reader(_initialize_rb_system._rb_scm_con_ptr->get_rb_scm_evaluation());
    //  rb_scm_eval_reader.read_from_file("rb_scm_eval.bin");
      #else
      _initialize_rb_system._rb_con_ptr -> get_rb_evaluation().legacy_read_offline_data_from_files("offline_data");
     // _initialize_rb_system._rb_scm_con_ptr -> get_rb_scm_evaluation().legacy_read_offline_data_from_files("scm_data");
      #endif

      setOnlineParameters();
      _initialize_rb_system._rb_eval_ptr ->set_parameters(_rb_online_mu);

      _console << "---- Online Stage ----" << std::endl;
      _initialize_rb_system._rb_eval_ptr ->print_parameters();
      std::cout << "Online N = " << _online_N << std::endl;

      if (_online_N == 0)
        _online_N = _initialize_rb_system._rb_eval_ptr->get_n_basis_functions();

      if(_offline_error_bound)
       _initialize_rb_system._rb_eval_ptr->evaluate_RB_error_bound = false;

      _initialize_rb_system._rb_eval_ptr->rb_solve(_online_N);
/*
      if (_compute_output)
        for (unsigned int i = 0; i != _initialize_rbeim_system._n_outputs_rb; i++)
          for (unsigned int _q = 0; _q != _initialize_rbeim_system._ql_rb[i]; _q++)
            _console << "Output " << std::to_string(i) << ": value = " << _rb_eval.RB_outputs[i]
            << ", error bound = " << _rb_eval.RB_output_error_bounds[i] << std::endl;
*/
      // Back transfer of the data to use MOOSE Postprocessor and Output classes
      //Moose::perf_log.push("DataTransfer()", "Execution");
      if(_output_file)
      {
         _initialize_rb_system._rb_con_ptr -> get_rb_evaluation().read_in_basis_functions(*_initialize_rb_system._rb_con_ptr,"offline_data");

         _initialize_rb_system._rb_con_ptr -> load_rb_solution();

         *_es.get_system(_system_name).solution = *_es.get_system("RBSystem").solution;
         _fe_problem.getNonlinearSystemBase().update();
         std::stringstream ss;
         
         ss << std::setw(2) << std::setfill('0') << _online_N;
         
		 #ifdef LIBMESH_HAVE_EXODUS_API
		 //ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("RB_sol_DwarfElephant.e",_es);//-s"+ss.str(),_es);
		 #endif
                VTKIO(_mesh_ptr->getMesh()).write_equation_systems("out.pvtu", _es);
      }
}

void
DwarfElephantOfflineOnlineStageSteadyState::initialize()
{

}

void
DwarfElephantOfflineOnlineStageSteadyState::execute()
{

    // Build the RBEvaluation object
    // Required for both the Offline and Online stage.
    // DwarfElephantEIMEvaluationSteadyState _eim_eval(_mesh_ptr->comm() , _fe_problem)
    // DwarfElephantRBEvaluationSteadyState _rb_eval(_mesh_ptr->comm() , _fe_problem);
    // Pass a pointer of the RBEvaluation object to the
    // RBConstruction object
    //_initialize_rbeim_system._eim_con_ptr->set_rb_evaluation(_eim_eval);
    //_initialize_rbeim_system._rb_con_ptr->set_rb_evaluation(_rb_eval);

    if (_initialize_rb_system._offline_stage)
    {
       // Transfer the affine vectors to the RB system.
       if(_skip_vector_assembly_in_rb_system)
        transferAffineVectors(); // runs fine
      
       //_initialize_rb_system._eim_con_ptr -> load_rb_solution();// temporary code for debugging
       //*_es.get_system("aux0").solution = *_es.get_system("EIMSystem_explicit_sys").solution;// temporary code for debugging
       VTKIO(_mesh_ptr->getMesh()).write_equation_systems("EIMSoln.pvtu", _es);// temporary code for debugging
      // Transfer the affine matrices to the RB system.
      if(_skip_matrix_assembly_in_rb_system)
        setAffineMatrices(); // problem
      // Perform the offline stage.
      _console << std::endl;
      if (_initialize_rb_system._use_EIM) 
      { 
          offlineStageEIM();
          //read_and_create_hpEIM_tree(_initialize_rb_system._es, _initialize_rb_system._mesh_ptr, _initialize_rb_system._eim_data_in, "hp_EIM_Tree.txt", _online_hp_eim_tree_ptr);
          //_online_hp_eim_tree_ptr->print_info("online");
      }
      else if (_initialize_rb_system._use_hp_EIM)
      {
          _initialize_rb_system._hp_eim_tree_ptr->train_all_rb_models(_initialize_rb_system._es, _mesh_ptr, _fe_problem, _initialize_rb_system._rb_data_in,_initialize_rb_system._rb_con_ptr);
          _initialize_rb_system._hp_eim_tree_ptr->write_tree("hpEIMtree.txt");
      }
      else offlineStageRBOnly();
      _console << std::endl;
    }

    if(_online_stage)
    {
        if (_initialize_rb_system._use_EIM) { onlineStageEIM();}
        else if (_initialize_rb_system._use_hp_EIM) 
        { 
            if (_initialize_rb_system._hp_EIM_testing)
            {
                if(_skip_vector_assembly_in_rb_system)
                    transferAffineVectors(); // runs fine

                // Transfer the affine matrices to the RB system.
                if(_skip_matrix_assembly_in_rb_system)
                    setAffineMatrices(); // problem
            }
            
            onlineStagehpEIM();
        }
        else onlineStageRBOnly();
//        How to write own Exodus file  // not required anymore
//        Moose::perf_log.push("write_Exodus()", "Output");
//
//        std::string _systems_for_print[] = {"RBSystem"};
//        const std::set<std::string>  _system_names_for_print (_systems_for_print, _systems_for_print+sizeof(_systems_for_print)/sizeof(_systems_for_print[0]));
//
//        _rb_eval.read_in_basis_functions(*_initialize_rb_system._rb_con_ptr);
//        _initialize_rb_system._rb_con_ptr->load_rb_solution();
//
//        ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("TestDakotaRB.e", _es, &_system_names_for_print);
////
////      _initialize_rb_system._rb_con_ptr->load_basis_function(0);
////      ExodusII_IO(_mesh_ptr->getMesh()).write_equation_systems("bf0.e", _es);
      
    }
}

void
DwarfElephantOfflineOnlineStageSteadyState::finalize()
{
}

//std::string
//DwarfElephantOfflineOnlineStageSteadyState::getFileName()
//{
//  std::string input_filename = _app.getFileName();
//  size_t pos = input_filename.find_last_of('.');
//
//  return input_filename.substr(0, pos) + ".e";
//}

