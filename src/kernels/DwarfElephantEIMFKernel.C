#include "DwarfElephantEIMFKernel.h"

//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/petsc_vector.h"

template<>
InputParameters validParams<DwarfElephantEIMFKernel> ()
{
	InputParameters params  = validParams<Kernel>();
	params.addClassDescription("Implements a non-affine source term for which an affine decomposition will be found using the empirical interpolation method");
        params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for  initializing the RB system");
	return params;
}

DwarfElephantEIMFKernel::DwarfElephantEIMFKernel(const InputParameters & parameters) :
    Kernel(parameters)
    
{
}

void DwarfElephantEIMFKernel::computeResidual()
{		
    std::vector<Number> & _eim_values_ref = _eim_values;        
    DenseVector<Number> 	& re = _assembly.residualBlock(_var.number());
    _local_re.resize(re.size());
    unsigned int _i_subdomain = _current_elem->subdomain_id();
    unsigned int _ID_first_block = *_fe_problem.mesh().meshSubdomains().begin();
    
    const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
    if (_initialize_rb_system._use_hp_EIM && (_initialize_rb_system._offline_stage || _initialize_rb_system._hp_EIM_testing))
    {
        unsigned int _i_overall_eim_basis_function = 0;
        for (unsigned int _i_hp_eim_leaf = 0; _i_hp_eim_leaf < _initialize_rb_system._hp_eim_tree_ptr->leaf_nodes.size(); _i_hp_eim_leaf++)
        {
            for (unsigned int _i_eim_basis_function = 0; _i_eim_basis_function < _initialize_rb_system._hp_eim_tree_ptr->leaf_nodes[_i_hp_eim_leaf]->_eim_con_ptr->get_rb_evaluation().get_n_basis_functions(); _i_eim_basis_function++)
            {
                _local_re.zero();
                _initialize_rb_system._hp_eim_tree_ptr->leaf_nodes[_i_hp_eim_leaf]->_eim_con_ptr->_rb_eim_assembly_objects_new[_i_eim_basis_function]->get_eim_basis_function_values(_assembly.elem(),_qrule,_eim_values_ref);
                for (_i = 0; _i < _test.size(); _i++)
                    for (_qp = 0; _qp < _qrule->n_points(); _qp++)
                        _local_re(_i)  += _JxW[_qp] * _coord[_qp] * _test[_i][_qp] * _eim_values_ref[_qp];
                
                re += _local_re;
                if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())
                    _initialize_rb_system._residuals[_i_overall_eim_basis_function]->add_vector(_local_re,_var.dofIndices());
                _i_overall_eim_basis_function++;
            }
        }
    }
   if (_initialize_rb_system._use_EIM) 
    {
        for (unsigned int _i_eim_basis_function = 0; _i_eim_basis_function < _initialize_rb_system._eim_con_ptr -> get_rb_evaluation().get_n_basis_functions(); _i_eim_basis_function++)
        {
            _local_re.zero();
            _initialize_rb_system._eim_con_ptr -> _rb_eim_assembly_objects_new[_i_eim_basis_function] -> get_eim_basis_function_values(_assembly.elem(), _qrule, _eim_values_ref);
	    for (_i = 0; _i < _test.size(); _i++)
                for (_qp = 0; _qp < _qrule -> n_points(); _qp++)
		{
		    _local_re(_i) += _JxW[_qp] * _coord[_qp] * _test[_i][_qp] * _eim_values_ref[_qp];
		}
	    re += _local_re;
	    if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())		
	        _initialize_rb_system._residuals[(_i_subdomain - _ID_first_block)*_initialize_rb_system._eim_con_ptr -> get_rb_evaluation().get_n_basis_functions() + _i_eim_basis_function] -> add_vector(_local_re, _var.dofIndices());
	}
    }
}

Real DwarfElephantEIMFKernel::computeQpResidual()
{
	
	return 1.0;
}

Real DwarfElephantEIMFKernel::computeQpJacobian()
{
	return 0;
}
