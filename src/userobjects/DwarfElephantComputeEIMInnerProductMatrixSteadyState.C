#include "DwarfElephantComputeEIMInnerProductMatrixSteadyState.h"
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantAppTypes.h"
#include <chrono>
//#include "libmesh/quadrature.h"

template <>
InputParameters
validParams<DwarfElephantComputeEIMInnerProductMatrixSteadyState>()
{
  InputParameters params = validParams<ElementUserObject>();
  params.addRequiredParam<NonlinearVariableName>("variable","The name of the variable that this UserObject operates on");
  params.addRequiredParam<UserObjectName>("initialize_rb_userobject","Name of the userobject used to initialize the RBEIM system");
  ExecFlagEnum & exec = params.set<ExecFlagEnum>("execute_on");
  exec.addAvailableFlags(EXEC_EIM);
  params.setDocString("execute_on", exec.getDocString());
  params.addRequiredParam<std::string>("param_str","Indicates the parameter subdomain: max_max/min_min/max_min/min_max");

  return params;
}

DwarfElephantComputeEIMInnerProductMatrixSteadyState::DwarfElephantComputeEIMInnerProductMatrixSteadyState(const InputParameters & parameters) : 
  ElementUserObject(parameters),
  MooseVariableInterface<Real>(this, false, "variable"),
  _var(*mooseVariable()),
  _test(_var.phi()),
  _initialize_rb_system(getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initialize_rb_userobject")),
  _param_str(getParam<std::string>("param_str"))
{
  std::cout << "DwarfElephantComputeEIMInnerProductMatrixSteadyState object created" << std::endl;
}

void
DwarfElephantComputeEIMInnerProductMatrixSteadyState::initialize()
{
  std::cout << "Starting DwarfElephantComputeEIMInnerProductMatrixSteadyStateInitialize" << std::endl;
  //_initialize_rb_system._inner_product_matrix_eim -> init();
}

void
DwarfElephantComputeEIMInnerProductMatrixSteadyState::execute()
{
  _local_ke.resize(_test.size(), _test.size());
  for (_i = 0; _i < _test.size(); _i++)
    for (_j = 0; _j < _test.size(); _j++)
      _local_ke(_i, _j) += computeIntegral(_i, _j);

  if (_initialize_rb_system._offline_stage)
  {
          _initialize_rb_system._inner_product_matrix_eim -> add_matrix(_local_ke, _var.dofIndices());
  }
  // make provision for modifying diagonal values, if required
}

Real
DwarfElephantComputeEIMInnerProductMatrixSteadyState::getValue()
{
  //gatherSum(_integral_value);
  return 0;//_integral_value;
}

void
DwarfElephantComputeEIMInnerProductMatrixSteadyState::threadJoin(const UserObject & /*y*/)
{
  // Is not executed in parallel runs
  //const DwarfElephantComputeEIMInnerProductMatrixSteadyState & pps = static_cast<const DwarfElephantComputeEIMInnerProductMatrixSteadyState &>(y);
  std::cout << "Executing threadJoin()" << std::endl;
  //_integral_value += pps._integral_value;
}

Real
DwarfElephantComputeEIMInnerProductMatrixSteadyState::computeIntegral(unsigned int _i, unsigned int _j)
{
  Real sum = 0;

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    sum += _JxW[_qp] * _coord[_qp] * _test[_i][_qp] * _test[_j][_qp];
  return sum;
}

void DwarfElephantComputeEIMInnerProductMatrixSteadyState::finalize()
{
  if (_initialize_rb_system._offline_stage)
  {
    if (_initialize_rb_system._use_hp_EIM)
    {
        _initialize_rb_system._inner_product_matrix_eim -> close();
 
        //t1 = std::chrono::high_resolution_clock::now();
        _initialize_rb_system._hp_eim_tree_ptr->train_EIM_basis(_initialize_rb_system._es, _initialize_rb_system._mesh_ptr);
        //t2 = std::chrono::high_resolution_clock::now();
        //duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        //std::cout << "Time spent in hp eim tree train_reduced_basis() : " << duration << std::endl;
        _initialize_rb_system._hp_eim_tree_ptr->print_info("offline");
    
        _initialize_rb_system._hp_eim_tree_ptr->get_leaf_nodes();
        
        std::cout << "Printing leaf nodes of hp EIM tree" << std::endl;
        _initialize_rb_system._hp_eim_tree_ptr->print_leaf_nodes("online");
    
        _initialize_rb_system.processRBParameters();
    /*
     * for all leaf nodes of hpEIM tree
     * init eim theta objects
     * attach eim theta objects to standard rb_eval object
     * initialize hp eim assembly objects
     * initialize standard rb construction
     * _initialize_rb_system.AssignAffineMatricesAndVectors();
     */
        for (unsigned int i = 0; i < _initialize_rb_system._hp_eim_tree_ptr->leaf_nodes.size(); i++)
        {
            _initialize_rb_system._hp_eim_tree_ptr->leaf_nodes[i]->_eim_eval_ptr->initialize_eim_theta_objects();
            _initialize_rb_system._rb_eval_ptr->get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._hp_eim_tree_ptr->leaf_nodes[i]->_eim_eval_ptr->get_eim_theta_objects());
            _initialize_rb_system._hp_eim_tree_ptr->leaf_nodes[i]->_eim_con_ptr->initialize_eim_assembly_objects();
        }
        _initialize_rb_system._rb_con_ptr -> print_info();  
        _initialize_rb_system._rb_con_ptr -> initialize_rb_construction(_initialize_rb_system._skip_matrix_assembly_in_rb_system, _initialize_rb_system._skip_vector_assembly_in_rb_system);
        _initialize_rb_system.AssignAffineMatricesAndVectors();  
    }
    else 
    {
        
            _initialize_rb_system._inner_product_matrix_eim -> close();
            _initialize_rb_system._inner_product_matrix_eim -> print_matlab("eim_inner_product_matrix_check.m");
            _initialize_rb_system._eim_con_ptr->GreedyOutputFile.open("EIMGreedyOutputFile.csv");
            _initialize_rb_system._eim_con_ptr->GreedyOutputFile << "mu_0, mu_1, MaxGreedyError" << std::endl;
            std::cout << "Staring eim greedy" << std::endl;
            _initialize_rb_system._eim_con_ptr->train_reduced_basis();

            _initialize_rb_system._eim_con_ptr->GreedyOutputFile.close();
            #if defined(LIBMESH_HAVE_CAPNPROTO)
                RBDataSerialization::RBEvaluationSerialization rb_eim_eval_writer(*(_initialize_rb_system._eim_eval_ptr));
                rb_eim_eval_writer.write_to_file("rb_eim_eval.bin");
            #else
                _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().legacy_write_offline_data_to_files("eim_data");
            #endif
            //_initialize_rb_system._eim_eval_ptr->write_EIM_data(_param_str);
            //_initialize_rb_system._rb_con_ptr->write_num_subdomains();

            _initialize_rb_system.processRBParameters();
            _initialize_rb_system._eim_eval_ptr -> initialize_eim_theta_objects();
            for (_i = 0 ; _i < _fe_problem.mesh().meshSubdomains().size() ; _i++) // add conditional statement later to handle multiple cases
                _initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
        
            //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_A_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects()); // Add in-case the A terms contain the function that has been affine-approximated using EIM (Martin's EIM example)
            _initialize_rb_system._eim_con_ptr -> initialize_eim_assembly_objects();

            _initialize_rb_system._rb_con_ptr -> print_info();
  
            _initialize_rb_system._rb_con_ptr -> initialize_rb_construction(_initialize_rb_system._skip_matrix_assembly_in_rb_system, _initialize_rb_system._skip_vector_assembly_in_rb_system);
            _initialize_rb_system._rb_con_ptr -> allocate_RB_error_structures();
            // Train reduced basis will be called after the kernel assembles the RB affine matrices and vectors
  
            _initialize_rb_system.AssignAffineMatricesAndVectors();
        
    }
  }
}
