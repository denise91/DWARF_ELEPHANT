///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "DwarfElephantFEMatriciesAndVectorsOutput.h"
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantInitializeRBSystemTransient.h"

///-------------------------------------------------------------------------
// Forward declerations
class DwarfElephantFEMatriciesAndVectorsPythonOutput;

///----------------------------INPUT PARAMETERS-----------------------------
template <>
InputParameters validParams<DwarfElephantFEMatriciesAndVectorsPythonOutput>();



///This Output is required to couple the DwarfElephant package over a fork interface to the multitool kit DAKOTA (developed by Sandia National Labratories).
class DwarfElephantFEMatriciesAndVectorsPythonOutput : public DwarfElephantFEMatriciesAndVectorsOutput
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFEMatriciesAndVectorsPythonOutput(const InputParameters & parameters);

  /*Methods*/
  virtual void output(const ExecFlagType & type) override;
  void printAq(std::vector<unsigned int> _id, std::string _simulation_type) override;
  void printFq(std::vector<unsigned int> _id, std::string _simulation_type) override;
  void printIC(std::vector<unsigned int> _id) override;
  void printMq(std::vector<unsigned int> _id) override;
  void printInnerProductMatrix(std::string _simulation_type) override;
  void printL2Matrix() override;
};
