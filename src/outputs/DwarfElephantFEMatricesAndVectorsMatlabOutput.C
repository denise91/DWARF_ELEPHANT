// MOOSE includes
#include "NonlinearSystemBase.h"
#include "FEProblem.h"

#include "DwarfElephantFEMatriciesAndVectorsMatlabOutput.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEMatriciesAndVectorsMatlabOutput);

template <>
InputParameters
validParams<DwarfElephantFEMatriciesAndVectorsMatlabOutput>()
{
  InputParameters params = validParams<DwarfElephantFEMatriciesAndVectorsOutput>();

  return params;
}

DwarfElephantFEMatriciesAndVectorsMatlabOutput::DwarfElephantFEMatriciesAndVectorsMatlabOutput(const InputParameters & parameters) :
    DwarfElephantFEMatriciesAndVectorsOutput(parameters)
{

}

void
DwarfElephantFEMatriciesAndVectorsMatlabOutput::output(const ExecFlagType & /*type*/)
{
  if(_print_Aq)
    printAq(_ID_Aq, _simulation_type);

  if(_print_Fq)
    printFq(_ID_Fq, _simulation_type);

  if(_print_Mq)
    printMq(_ID_Mq);

  if(_print_inner_product_matrix)
    printInnerProductMatrix(_simulation_type);

  if(_print_L2_matrix)
    printL2Matrix();

}

void
DwarfElephantFEMatriciesAndVectorsMatlabOutput::printAq(std::vector<unsigned int> _id, std::string _simulation_type)
{
  if(_simulation_type=="steady")
  {
    DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system =
      _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemSteadyState>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQa())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Aq is out of range.");
      _initialize_rb_system.getJacobianSubdomain()[_id[q]]->print_matlab("Aq"+std::to_string(_id[q]));
    }
  }else{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQa())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Aq is out of range.");
      _initialize_rb_system.getJacobianSubdomain()[_id[q]]->print_matlab("Aq"+std::to_string(_id[q]));
    }
  }
}

void
DwarfElephantFEMatriciesAndVectorsMatlabOutput::printFq(std::vector<unsigned int> _id, std::string _simulation_type)
{
  if(_simulation_type=="steady")
  {
    DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system =
      _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemSteadyState>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQf())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Fq is out of range.");
      _initialize_rb_system.getResiduals()[_id[q]]->print_matlab("Fq"+std::to_string(_id[q]));
    }
  }else{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQf())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Fq is out of range.");
      _initialize_rb_system.getResiduals()[_id[q]]->print_matlab("Fq"+std::to_string(_id[q]));
    }
  }
}

void
DwarfElephantFEMatriciesAndVectorsMatlabOutput::printMq(std::vector<unsigned int> _id)
{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQm())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Mq is out of range.");
      _initialize_rb_system.getMassMatrixSubdomain()[_id[q]]->print_matlab("Mq"+std::to_string(_id[q]));
    }
}

void
DwarfElephantFEMatriciesAndVectorsMatlabOutput::printInnerProductMatrix(std::string _simulation_type)
{
  if(_simulation_type=="steady")
  {
    DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system =
      _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemSteadyState>(_initialize_rb_system_name);

    _initialize_rb_system.getInnerProductMatrix()->print_matlab("InnerProductMatrix");
  }else{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);

    _initialize_rb_system.getInnerProductMatrix()->print_matlab("InnerProductMatrix");
  }
}

void
DwarfElephantFEMatriciesAndVectorsMatlabOutput::printL2Matrix()
{
  DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
    _problem_ptr->getUserObject<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);

  _initialize_rb_system.getL2Matrix()->print_matlab("L2Matrix");
}
