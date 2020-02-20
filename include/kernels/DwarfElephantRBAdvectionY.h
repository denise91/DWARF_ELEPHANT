/* 
 * File:   DwarfElephantRBAdvectionY.h
 * Author: 310246696
 *
 * Created on January 10, 2020, 5:39 PM
 */

#ifndef DWARFELEPHANTRBADVECTIONY_H
#define	DWARFELEPHANTRBADVECTIONY_H

#include "DwarfElephantRBKernel.h"

class DwarfElephantRBAdvectionY;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBAdvectionY>();

///-------------------------------------------------------------------------
class DwarfElephantRBAdvectionY : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBAdvectionY(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;
};

///-------------------------------------------------------------------------

#endif	/* DWARFELEPHANTRBADVECTIONY_H */

