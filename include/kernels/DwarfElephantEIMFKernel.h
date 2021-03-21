#ifndef DWARFELEPHANTEIMFKERNEL_H
#define DWARFELEPHANTEIMFKERNEL_H

#include "Kernel.h"
#include "DisplacedProblem.h"
#include "NonlinearSystemBase.h"

#include "DwarfElephantInitializeRBSystemSteadyState.h"

#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"

//class DwarfElephantInitializeRBSystemSteadyState;

class DwarfElephantEIMFKernel;

template<>
InputParameters validParams<DwarfElephantEIMFKernel>();

class DwarfElephantEIMFKernel : public Kernel
{
	public:
	DwarfElephantEIMFKernel(const InputParameters & parameters);
        virtual void computeResidual() override;
	
	protected:
	virtual Real computeQpResidual() override;
	virtual Real computeQpJacobian() override;
	
	std::vector<Number> _eim_values;

        unsigned int _EIM_offset;
};

#endif //DWARFELEPHANTEIMFKERNEL_H
