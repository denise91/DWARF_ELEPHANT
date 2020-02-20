/* 
 * File:   DwarfElephantFTestKernelTransient.h
 * Author: 310246696
 *
 * Created on February 19, 2020, 5:01 PM
 */

#ifndef DWARFELEPHANTFTESTKERNELTRANSIENT_H
#define	DWARFELEPHANTFTESTKERNELTRANSIENT_H

#include "Kernel.h"
#include "DisplacedProblem.h"
#include "NonlinearSystemBase.h"

#include "DwarfElephantInitializeRBSystemTransient.h"

#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"



class DwarfElephantFTestKernelTransient;

template<>
InputParameters validParams<DwarfElephantFTestKernelTransient>();

class DwarfElephantFTestKernelTransient : public Kernel
{
	public:
	DwarfElephantFTestKernelTransient(const InputParameters & parameters);
        virtual void computeResidual() override;
	
	protected:
	virtual Real computeQpResidual() override;
	virtual Real computeQpJacobian() override;
        
        Real _r_0;
        Real _l_0;
        
        Real _center_x;
        Real _center_y;
        Real _center_z;
        
        RBParameters _mu;
};


#endif	/* DWARFELEPHANTFTESTKERNELTRANSIENT_H */

