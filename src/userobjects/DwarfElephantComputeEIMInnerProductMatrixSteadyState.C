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
  params.addRequiredParam<bool>("use_hp_EIM", "True if hp-EIM is to be used. False if not.");

  return params;
}

DwarfElephantComputeEIMInnerProductMatrixSteadyState::DwarfElephantComputeEIMInnerProductMatrixSteadyState(const InputParameters & parameters) : 
  ElementUserObject(parameters),
  MooseVariableInterface<Real>(this, false, "variable"),
  _var(*mooseVariable()),
  _test(_var.phi()),
  _initialize_rb_system(getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initialize_rb_userobject")),
  _use_hp_EIM(getParam<bool>("use_hp_EIM"))
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
  DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());
  _local_ke.resize(ke.m(), ke.n());
  _local_ke.zero();

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
DwarfElephantComputeEIMInnerProductMatrixSteadyState::threadJoin(const UserObject & y)
{
  // Is not executed in parallel runs
  const DwarfElephantComputeEIMInnerProductMatrixSteadyState & pps = static_cast<const DwarfElephantComputeEIMInnerProductMatrixSteadyState &>(y);
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
    if (_use_hp_EIM)
    {
    _initialize_rb_system._inner_product_matrix_eim -> close();
 
    //t1 = std::chrono::high_resolution_clock::now();
    _initialize_rb_system._hp_eim_tree_ptr->train_EIM_basis(_initialize_rb_system._es, _initialize_rb_system._mesh_ptr,_initialize_rb_system._inner_product_matrix_eim);
    //t2 = std::chrono::high_resolution_clock::now();
    //duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    //std::cout << "Time spent in hp eim tree train_reduced_basis() : " << duration << std::endl;
    _initialize_rb_system._hp_eim_tree_ptr->print_info("offline");
    
    _initialize_rb_system._hp_eim_tree_ptr->get_leaf_nodes(_initialize_rb_system._hp_eim_tree_ptr->root);
    _initialize_rb_system._hp_eim_tree_ptr->write_leaf_nodes("offline");
    /*
    _initialize_rb_system.processRBParameters();
    // do the following such that the F theta objects from all the hpEIM bases contained in the leaf nodes of the tree are attached to the standard RB con object
    _initialize_rb_system._eim_eval_ptr -> initialize_eim_theta_objects();
    _initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
    //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_A_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects()); // Add in-case the A terms contain the function that has been affine-approximated using EIM (Martin's EIM example)
    _initialize_rb_system._eim_con_ptr -> initialize_eim_assembly_objects();

    _initialize_rb_system._rb_con_ptr -> print_info();
  
    _initialize_rb_system._rb_con_ptr -> initialize_rb_construction(_initialize_rb_system._skip_matrix_assembly_in_rb_system, _initialize_rb_system._skip_vector_assembly_in_rb_system);
    _initialize_rb_system._rb_con_ptr -> allocate_RB_error_structures();
    // Train reduced basis will be called after the kernel assembles the RB affine matrices and vectors
  
    _initialize_rb_system.AssignAffineMatricesAndVectors();
    
*/
    
    }
    else 
    {
        _initialize_rb_system._inner_product_matrix_eim -> close();
    _initialize_rb_system._inner_product_matrix_eim -> print_matlab("eim_inner_product_matrix_check.m");
    _initialize_rb_system._eim_con_ptr->GreedyOutputFile.open("EIMGreedyOutputFile.csv");
    _initialize_rb_system._eim_con_ptr->GreedyOutputFile << "mu_0, mu_1, MaxGreedyError" << std::endl;
    _initialize_rb_system._eim_con_ptr->train_reduced_basis();

    _initialize_rb_system._eim_con_ptr->GreedyOutputFile.close();
    #if defined(LIBMESH_HAVE_CAPNPROTO)
      RBDataSerialization::RBEvaluationSerialization rb_eim_eval_writer(*(_initialize_rb_system._eim_eval_ptr));
      rb_eim_eval_writer.write_to_file("rb_eim_eval.bin");
    #else
      _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().legacy_write_offline_data_to_files("eim_data");
    #endif
    _initialize_rb_system.processRBParameters();
    _initialize_rb_system._eim_eval_ptr -> initialize_eim_theta_objects();
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
