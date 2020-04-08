///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "FileOutput.h"
#include "DwarfElephantInitializeRBSystemSteadyState.h"
#include "DwarfElephantInitializeRBSystemTransient.h"

///-------------------------------------------------------------------------
// Forward declerations
class DwarfElephantFEMatriciesAndVectorsOutput;

///----------------------------INPUT PARAMETERS-----------------------------
template <>
InputParameters validParams<DwarfElephantFEMatriciesAndVectorsOutput>();



///This Output is required to couple the DwarfElephant package over a fork interface to the multitool kit DAKOTA (developed by Sandia National Labratories).
class DwarfElephantFEMatriciesAndVectorsOutput : public FileOutput
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFEMatriciesAndVectorsOutput(const InputParameters & parameters);

  /*Methods*/
  virtual void output(const ExecFlagType & /*type*/)override {};
  virtual void printAq(std::vector<unsigned int> /*_id*/, std::string /*_simulation_type*/){};
  virtual void printFq(std::vector<unsigned int> /*_id*/, std::string /*_simulation_type*/){};
  virtual void printMq(std::vector<unsigned int> /*_id*/){};
  virtual void printInnerProductMatrix(std::string /*_simulation_type*/){};
  virtual void printL2Matrix(){};

//--------------------------------PROTECTED---------------------------------
protected:
  /*Attributes*/
  std::string _simulation_type;
  UserObjectName _initialize_rb_system_name;

  std::vector<unsigned int> _ID_Aq;
  std::vector<unsigned int> _ID_Fq;
  std::vector<unsigned int> _ID_Mq;

  bool _print_Aq;
  bool _print_Fq;
  bool _print_Mq;
  bool _print_inner_product_matrix;
  bool _print_L2_matrix;
};
