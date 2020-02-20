/* 
 * File:   DwarfElephantXAdvection.h
 * Author: 310246696
 *
 * Created on January 10, 2020, 5:29 PM
 */

#ifndef DWARFELEPHANTRBADVECTIONX_H
#define	DWARFELEPHANTRBADVECTIONX_H

#include "DwarfElephantRBKernel.h"

class DwarfElephantRBAdvectionX;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantRBAdvectionX>();

///-------------------------------------------------------------------------
class DwarfElephantRBAdvectionX : public DwarfElephantRBKernel
{

//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantRBAdvectionX(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOutput() override;
};

///-------------------------------------------------------------------------

#endif	/* DWARFELEPHANTRBADVECTIONX_H */

