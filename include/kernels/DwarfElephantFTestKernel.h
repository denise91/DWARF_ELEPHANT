#ifndef DWARFELEPHANTFTESTKERNEL_H
#define DWARFELEPHANTFTESTKERNEL_H

#include "Kernel.h"
#include "DisplacedProblem.h"
#include "NonlinearSystemBase.h"

#include "DwarfElephantInitializeRBSystemSteadyState.h"

#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"

//class DwarfElephantInitializeRBSystemSteadyState;

class DwarfElephantFTestKernel;

template<>
InputParameters validParams<DwarfElephantFTestKernel>();

class DwarfElephantFTestKernel : public Kernel
{
	public:
	DwarfElephantFTestKernel(const InputParameters & parameters);
        virtual void computeResidual() override;
	
	protected:
	virtual Real computeQpResidual() override;
	virtual Real computeQpJacobian() override;
};

#endif //DWARFELEPHANTFTESTKERNEL_H
