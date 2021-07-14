#include "DwarfElephantComputeEIMInnerProductMatrixTransient.h"
#include "DwarfElephantInitializeRBSystemTransient.h"
#include "DwarfElephantAppTypes.h"
#include <chrono>
//#include "libmesh/quadrature.h"

template <>
InputParameters validParams<DwarfElephantComputeEIMInnerProductMatrixTransient> ()
{
  InputParameters params = validParams<ElementUserObject>();
  params.addRequiredParam<NonlinearVariableName>("variable","The name of the variable that this UserObject operates on");
  params.addRequiredParam<UserObjectName>("initialize_rb_userobject","Name of the userobject used to initialize the RBEIM system");
  ExecFlagEnum & exec = params.set<ExecFlagEnum>("execute_on");
  exec.addAvailableFlags(EXEC_EIM);
  params.setDocString("execute_on", exec.getDocString());

  return params;
}

DwarfElephantComputeEIMInnerProductMatrixTransient::DwarfElephantComputeEIMInnerProductMatrixTransient(const InputParameters & parameters) : 
  ElementUserObject(parameters),
  MooseVariableInterface<Real>(this, false, "variable"),
  _var(*mooseVariable()),
  _test(_var.phi()),
  _initialize_rb_system(getUserObject<DwarfElephantInitializeRBSystemTransient>("initialize_rb_userobject"))
{
  std::cout << "DwarfElephantComputeEIMInnerProductMatrixTransient object created" << std::endl;
}

void
DwarfElephantComputeEIMInnerProductMatrixTransient::initialize()
{
  std::cout << "Starting DwarfElephantComputeEIMInnerProductMatrixTransientInitialize" << std::endl;
  //_initialize_rb_system._inner_product_matrix_eim -> init();
}

void
DwarfElephantComputeEIMInnerProductMatrixTransient::execute()
{
  //DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());
  _local_ke.resize(_test.size(), _test.size());//ke.m(), ke.n());
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
DwarfElephantComputeEIMInnerProductMatrixTransient::getValue()
{
  //gatherSum(_integral_value);
  return 0;//_integral_value;
}

void
DwarfElephantComputeEIMInnerProductMatrixTransient::threadJoin(const UserObject &/* y*/)
{
  // Is not executed in parallel runs
  //const DwarfElephantComputeEIMInnerProductMatrixTransient & pps = static_cast<const DwarfElephantComputeEIMInnerProductMatrixTransient &>(y);
  std::cout << "Executing threadJoin()" << std::endl;
  //_integral_value += pps._integral_value;
}

Real
DwarfElephantComputeEIMInnerProductMatrixTransient::computeIntegral(unsigned int _i, unsigned int _j)
{
  Real sum = 0;

  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
    sum += _JxW[_qp] * _coord[_qp] * _test[_i][_qp] * _test[_j][_qp];
  return sum;
}

void DwarfElephantComputeEIMInnerProductMatrixTransient::finalize()
{
  if (_initialize_rb_system._offline_stage)
  {
            _initialize_rb_system._inner_product_matrix_eim -> close();
            _initialize_rb_system._eim_con_ptr->train_reduced_basis();
            #if defined(LIBMESH_HAVE_CAPNPROTO)
                RBDataSerialization::RBEvaluationSerialization rb_eim_eval_writer(*(_initialize_rb_system._eim_eval_ptr));
                rb_eim_eval_writer.write_to_file("rb_eim_eval.bin");
            #else
                _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().legacy_write_offline_data_to_files("eim_data");
            #endif
            //_initialize_rb_system._eim_eval_ptr->write_EIM_data();
            //_initialize_rb_system._rb_con_ptr->write_num_subdomains();

            _initialize_rb_system.processParameters();
            _initialize_rb_system._eim_eval_ptr -> initialize_eim_theta_objects();
            for (_i = 0 ; _i < _fe_problem.mesh().meshSubdomains().size() ; _i++) // add conditional statement later to handle multiple cases
                _initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
        
            //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_A_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects()); // Add in-case the A terms contain the function that has been affine-approximated using EIM (Martin's EIM example)
            _initialize_rb_system._eim_con_ptr -> initialize_eim_assembly_objects();
            //_initialize_rb_system._rb_eval_ptr -> get_rb_theta_expansion().attach_multiple_F_theta(_initialize_rb_system._eim_eval_ptr -> get_eim_theta_objects());
            _initialize_rb_system._rb_con_ptr -> print_info();
  
            _initialize_rb_system._rb_con_ptr -> initialize_rb_construction(_initialize_rb_system._skip_matrix_assembly_in_rb_system, _initialize_rb_system._skip_vector_assembly_in_rb_system);
            _initialize_rb_system._rb_con_ptr -> allocate_RB_error_structures();
            // Train reduced basis will be called after the kernel assembles the RB affine matrices and vectors
  
            _initialize_rb_system.AssignAffineMatricesAndVectors();
  }
}


