/* 
 * File:   RBInnerProductMatrixTransient.h
 * Author: 310246696
 *
 * Created on December 17, 2019, 1:25 PM
 */

#ifndef RBINNERPRODUCTMATRIXTRANSIENT_H
#define	RBINNERPRODUCTMATRIXTRANSIENT_H


#include "Kernel.h"
#include "DisplacedProblem.h"
#include "NonlinearSystemBase.h"

#include "DwarfElephantInitializeRBSystemTransient.h"

#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"

//class DwarfElephantInitializeRBSystemSteadyState;

class RBInnerProductMatrixTransient;

template<>
InputParameters validParams<RBInnerProductMatrixTransient>();

class RBInnerProductMatrixTransient : public Kernel
{
	public:
	RBInnerProductMatrixTransient(const InputParameters & parameters);
        virtual void computeJacobian() override;
	
	protected:
	virtual Real computeQpResidual() override;
	virtual Real computeQpJacobian() override;
};


#endif	/* RBINNERPRODUCTMATRIXTRANSIENT_H */

