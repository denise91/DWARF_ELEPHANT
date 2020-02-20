
#include "DwarfElephantFTestKernelTransient.h"

//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/petsc_vector.h"

#include "3DRBRFA_CoordinateTrafo.h"

template<>
InputParameters validParams<DwarfElephantFTestKernelTransient> ()
{
	InputParameters params  = validParams<Kernel>();
	params.addClassDescription("Implements a non-affine source term for which an affine decomposition will be found using the empirical interpolation method");
        params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for  initializing the RB system");
        params.addRequiredParam<Real>("r_0","Vessel radius in transformed geometry.");
        params.addRequiredParam<Real>("l_0","Vessel length in transformed geometry.");
        params.addRequiredParam<Real>("center_x","X coord of gaussian source.");
        params.addRequiredParam<Real>("center_y","Y coord of gaussian source.");
        params.addRequiredParam<Real>("center_z","Z coord of gaussian source.");
	return params;
}

DwarfElephantFTestKernelTransient::DwarfElephantFTestKernelTransient(const InputParameters & parameters) :
    Kernel(parameters),
        _r_0(getParam<Real>("r_0")),
        _l_0(getParam<Real>("l_0")),
        _center_x(getParam<Real>("center_x")),
        _center_y(getParam<Real>("center_y")),
        _center_z(getParam<Real>("center_z"))
        
    
{
    
    _mu.set_value("mu_0",_r_0);
    _mu.set_value("mu_1",_l_0);
    _mu.set_value("mu_2",_center_x);
    _mu.set_value("mu_3",_center_y);
    _mu.set_value("mu_4",_center_z);
    
}

void DwarfElephantFTestKernelTransient::computeResidual()
{		      
	DenseVector<Number> 	& re = _assembly.residualBlock(_var.number());
	_local_re.resize(re.size());
	const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

        _local_re.zero();
	for (_i = 0; _i < _test.size(); _i++)
	  	for (_qp = 0; _qp < _qrule -> n_points(); _qp++)
		{
		    Real x_new = NewCoord(_q_point[_qp](0), _q_point[_qp](1), _q_point[_qp](2), _r_0, _l_0, 0.1, 3e-3, 5e-2, _current_elem->subdomain_id(), 0);
                    Real y_new = NewCoord(_q_point[_qp](0), _q_point[_qp](1), _q_point[_qp](2), _r_0, _l_0, 0.1, 3e-3, 5e-2, _current_elem->subdomain_id(), 1);
                    Real z_new = NewCoord(_q_point[_qp](0), _q_point[_qp](1), _q_point[_qp](2), _r_0, _l_0, 0.1, 3e-3, 5e-2, _current_elem->subdomain_id(), 2);
                    Real GeomTrafoJac = dynamic_cast<Geom3DTransientRBThetaExpansion&>(_initialize_rb_system._rb_eval_ptr->get_rb_theta_expansion()).subdomain_jac_rbthetas[_current_elem->subdomain_id()-1]->evaluate(_mu);
                    _local_re(_i) += _JxW[_qp] * _coord[_qp] * _test[_i][_qp] * 10.*exp((-pow(x_new - _center_x,2) - pow(y_new - _center_y,2) - pow(z_new - _center_z,2))) * GeomTrafoJac;
		}
	  re += _local_re;
	  if (_fe_problem.getNonlinearSystemBase().computingInitialResidual())		
	  	_initialize_rb_system._fullFEnonAffineF -> add_vector(_local_re, _var.dofIndices());

}

Real DwarfElephantFTestKernelTransient::computeQpResidual()
{
	
	return 1.0;
}

Real DwarfElephantFTestKernelTransient::computeQpJacobian()
{
	return 0;
}
