// MOOSE includes
#include "NonlinearSystemBase.h"
#include "FEProblem.h"

#include "DwarfElephantFEMatriciesAndVectorsOutput.h"

template <>
InputParameters
validParams<DwarfElephantFEMatriciesAndVectorsOutput>()
{
  InputParameters params = validParams<FileOutput>();
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for the  offline and online stage of the RB system");
  params.addParam<std::vector<unsigned int>>("ID_Aq",std::vector<unsigned int> {0},"ID of the Aq you want to extract.");
  params.addParam<std::vector<unsigned int>>("ID_Fq",std::vector<unsigned int> {0},"ID of the Fq you want to extract.");
  params.addParam<std::vector<unsigned int>>("ID_Mq",std::vector<unsigned int> {0},"ID of the Mq you want to extract.");
  params.addParam<bool>("print_Aq",true, "Aq with specified ID is printed to file.");
  params.addParam<bool>("print_Fq", true, "Fq with specified ID is printed to file.");
  params.addParam<bool>("print_Mq", false, "Mq with specified ID is printed to file.");
  params.addParam<bool>("print_inner_product_matrix", false, "Inner product matrix is printed to file.");
  params.addParam<bool>("print_L2_matrix", false, "L2 matrix is printed to file.");
  return params;
}

DwarfElephantFEMatriciesAndVectorsOutput::DwarfElephantFEMatriciesAndVectorsOutput(const InputParameters & parameters) :
    FileOutput(parameters),
    _simulation_type(getParam<std::string>("simulation_type")),
    _initialize_rb_system_name(getParam<UserObjectName>("initial_rb_userobject")),
    _ID_Aq(getParam<std::vector<unsigned int>>("ID_Aq")),
    _ID_Fq(getParam<std::vector<unsigned int>>("ID_Fq")),
    _ID_Mq(getParam<std::vector<unsigned int>>("ID_Mq")),
    _print_Aq(getParam<bool>("print_Aq")),
    _print_Fq(getParam<bool>("print_Fq")),
    _print_Mq(getParam<bool>("print_Mq")),
    _print_inner_product_matrix(getParam<bool>("print_inner_product_matrix")),
    _print_L2_matrix(getParam<bool>("print_L2_matrix"))
{
  if(!_es_ptr->has_system("rb0"))
    mooseError("This Output Class requires the RB System 'rb0'.");

  if(_simulation_type=="steady" && _print_Mq)
    mooseError("Mqs are only existent for transient systems. So either set 'print_Mq' to false or 'simulation_type' to transient.");

  if(_simulation_type=="steady" && _print_L2_matrix)
    mooseError("The L2 matrix is only existent for transient systems. So either set 'print_L2_matrix' to false or 'simulation_type' to transient.");


  std::ifstream input_file(filename());

  if (input_file)
  {
    remove(filename().c_str());
  }

}
