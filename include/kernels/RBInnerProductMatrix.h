#ifndef RBINNERPRODUCTMATRIX_H
#define RBINNERPRODUCTMATRIX_H

#include "Kernel.h"
#include "DisplacedProblem.h"
#include "NonlinearSystemBase.h"

#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"

//class DwarfElephantInitializeRBSystemSteadyState;

class RBInnerProductMatrix;

template<>
InputParameters validParams<RBInnerProductMatrix>();

class RBInnerProductMatrix : public Kernel
{
	public:
	RBInnerProductMatrix(const InputParameters & parameters);
        virtual void computeJacobian() override;
	
	protected:
	virtual Real computeQpResidual() override;
	virtual Real computeQpJacobian() override;
};

#endif //RBINNERPRODUCTMATRIX_H
