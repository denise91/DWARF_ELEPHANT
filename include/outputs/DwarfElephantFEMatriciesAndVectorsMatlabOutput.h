///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "DwarfElephantFEMatriciesAndVectorsOutput.h"
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantInitializeRBSystemTransient.h"

///-------------------------------------------------------------------------
// Forward declerations
class DwarfElephantFEMatriciesAndVectorsMatlabOutput;

///----------------------------INPUT PARAMETERS-----------------------------
template <>
InputParameters validParams<DwarfElephantFEMatriciesAndVectorsMatlabOutput>();



///This Output is required to couple the DwarfElephant package over a fork interface to the multitool kit DAKOTA (developed by Sandia National Labratories).
class DwarfElephantFEMatriciesAndVectorsMatlabOutput : public DwarfElephantFEMatriciesAndVectorsOutput
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFEMatriciesAndVectorsMatlabOutput(const InputParameters & parameters);

  /*Methods*/
  virtual void output(const ExecFlagType & type) override;
  void printAq(std::vector<unsigned int> _id, std::string _simulation_type) override;
  void printFq(std::vector<unsigned int> _id, std::string _simulation_type) override;
  void printMq(std::vector<unsigned int> _id) override;
  void printInnerProductMatrix(std::string _simulation_type) override;
  void printL2Matrix() override;
};
