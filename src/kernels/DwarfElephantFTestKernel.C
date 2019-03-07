#include "DwarfElephantFTestKernel.h"

//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/petsc_vector.h"

template<>
InputParameters validParams<DwarfElephantFTestKernel> ()
{
	InputParameters params  = validParams<Kernel>();
	params.addClassDescription("Implements a non-affine source term for which an affine decomposition will be found using the empirical interpolation method");
        params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for  initializing the RB system");
	return params;
}

DwarfElephantFTestKernel::DwarfElephantFTestKernel(const InputParameters & parameters) :
    Kernel(parameters)
    
{
}

void DwarfElephantFTestKernel::computeResidual()
{		      
	DenseVector<Number> 	& re = _assembly.residualBlock(_var.number());
	_local_re.resize(re.size());
	const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");

        _local_re.zero();
	for (_i = 0; _i < _test.size(); _i++)
	  	for (_qp = 0; _qp < _qrule -> n_points(); _qp++)
		{
			_local_re(_i) += _JxW[_qp] * _coord[_qp] * _test[_i][_qp] * exp(-pow(_q_point[_qp](0) + 0.6,2) - pow(_q_point[_qp](1) + 0.3,2));
		}
	  re += _local_re;
	  if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())		
	  	_initialize_rb_system._fullFEnonAffineF -> add_vector(_local_re, _var.dofIndices());

}

Real DwarfElephantFTestKernel::computeQpResidual()
{
	
	return 1.0;
}

Real DwarfElephantFTestKernel::computeQpJacobian()
{
	return 0;
}
