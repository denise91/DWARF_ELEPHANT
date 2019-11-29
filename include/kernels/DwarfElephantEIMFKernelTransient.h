/* 
 * File:   DwarfElephantEIMFKernelTransient.h
 * Author: 310246696
 *
 * Created on November 28, 2019, 8:48 AM
 */

#ifndef DWARFELEPHANTEIMFKERNELTRANSIENT_H
#define	DWARFELEPHANTEIMFKERNELTRANSIENT_H

#include "Kernel.h"
#include "DisplacedProblem.h"
#include "NonlinearSystemBase.h"

#include "DwarfElephantInitializeRBSystemTransient.h"

#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"

//class DwarfElephantInitializeRBSystemSteadyState;

class DwarfElephantEIMFKernelTransient;

template<>
InputParameters validParams<DwarfElephantEIMFKernelTransient>();

class DwarfElephantEIMFKernelTransient : public Kernel
{
	public:
	DwarfElephantEIMFKernelTransient(const InputParameters & parameters);
        virtual void computeResidual() override;
	
	protected:
	virtual Real computeQpResidual() override;
	virtual Real computeQpJacobian() override;
	
	std::vector<Number> _eim_values;
};


#endif	/* DWARFELEPHANTEIMFKERNELTRANSIENT_H */

