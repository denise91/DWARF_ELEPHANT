// MOOSE includes
#include "NonlinearSystemBase.h"
#include "FEProblem.h"

#include "DwarfElephantFEMatriciesAndVectorsPythonOutput.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEMatriciesAndVectorsPythonOutput);

template <>
InputParameters
validParams<DwarfElephantFEMatriciesAndVectorsPythonOutput>()
{
  InputParameters params = validParams<DwarfElephantFEMatriciesAndVectorsOutput>();

  return params;
}

DwarfElephantFEMatriciesAndVectorsPythonOutput::DwarfElephantFEMatriciesAndVectorsPythonOutput(const InputParameters & parameters) :
    DwarfElephantFEMatriciesAndVectorsOutput(parameters)
{

}

void
DwarfElephantFEMatriciesAndVectorsPythonOutput::output(const ExecFlagType & /*type*/)
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
DwarfElephantFEMatriciesAndVectorsPythonOutput::printAq(std::vector<unsigned int> _id, std::string _simulation_type)
{
  if(_simulation_type=="steady")
  {
    DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system =
      _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemSteadyState>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQa())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Aq is out of range.");

      std::ofstream _python_out("Aq"+std::to_string(_id[q]), std::ios::out);
      _python_out << "Number of Rows: "<< _initialize_rb_system.getJacobianSubdomain()[_id[q]]->m() << std::endl;
      _python_out << "Number of Columns: "<< _initialize_rb_system.getJacobianSubdomain()[_id[q]]->n() << std::endl;
      _initialize_rb_system.getJacobianSubdomain()[_id[q]]->print(_python_out, true);
      _python_out.close();
    }
  }else{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQa())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Aq is out of range.");

      std::ofstream _python_out("Aq"+std::to_string(_id[q]), std::ios::out);
      _python_out << "Number of Rows: "<< _initialize_rb_system.getJacobianSubdomain()[_id[q]]->m() << std::endl;
      _python_out << "Number of Columns: "<< _initialize_rb_system.getJacobianSubdomain()[_id[q]]->n() << std::endl;
      _initialize_rb_system.getJacobianSubdomain()[_id[q]]->print(_python_out, true);
      _python_out.close();
    }
  }
}

void
DwarfElephantFEMatriciesAndVectorsPythonOutput::printFq(std::vector<unsigned int> _id, std::string _simulation_type)
{
  if(_simulation_type=="steady")
  {
    DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system =
      _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemSteadyState>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQf())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Fq is out of range.");

      std::ofstream _python_out("Fq"+std::to_string(_id[q]), std::ios::out);
      _initialize_rb_system.getResiduals()[_id[q]]->print(_python_out);
      _python_out.close();
    }
  }else{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQf())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Fq is out of range.");

      std::ofstream _python_out("Fq"+std::to_string(_id[q]), std::ios::out);
      _initialize_rb_system.getResiduals()[_id[q]]->print(_python_out);
      _python_out.close();
    }
  }
}

void
DwarfElephantFEMatriciesAndVectorsPythonOutput::printMq(std::vector<unsigned int> _id)
{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);
    for(unsigned int q = 0; q<_id.size(); q++)
    {
      if(_id[q] >= _initialize_rb_system.getQm())
        mooseError("The ID '" + std::to_string(_id[q]) + "' of Mq is out of range.");

      std::ofstream _python_out("Mq"+std::to_string(_id[q]), std::ios::out);
      _python_out << "Number of Rows: "<< _initialize_rb_system.getMassMatrixSubdomain()[_id[q]]->m() << std::endl;
      _python_out << "Number of Columns: "<< _initialize_rb_system.getMassMatrixSubdomain()[_id[q]]->n() << std::endl;
      _initialize_rb_system.getMassMatrixSubdomain()[_id[q]]->print(_python_out, true);
      _python_out.close();
    }
}

void
DwarfElephantFEMatriciesAndVectorsPythonOutput::printInnerProductMatrix(std::string _simulation_type)
{
  if(_simulation_type=="steady")
  {
    DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system =
      _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemSteadyState>(_initialize_rb_system_name);

    std::ofstream _python_out("InnerProductMatrix", std::ios::out);
    _python_out << "Number of Rows: "<< _initialize_rb_system.getInnerProductMatrix()->m() << std::endl;
    _python_out << "Number of Columns: "<< _initialize_rb_system.getInnerProductMatrix()->n() << std::endl;
    _initialize_rb_system.getInnerProductMatrix()->print(_python_out, true);
    _python_out.close();

  }else{
    DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
      _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);

    std::ofstream _python_out("InnerProductMatrix", std::ios::out);
    _python_out << "Number of Rows: "<< _initialize_rb_system.getInnerProductMatrix()->m() << std::endl;
    _python_out << "Number of Columns: "<< _initialize_rb_system.getInnerProductMatrix()->n() << std::endl;
    _initialize_rb_system.getInnerProductMatrix()->print(_python_out, true);
    _python_out.close();
  }
}

void
DwarfElephantFEMatriciesAndVectorsPythonOutput::printL2Matrix()
{
  DwarfElephantInitializeRBSystemTransient & _initialize_rb_system =
    _problem_ptr->getUserObjectTempl<DwarfElephantInitializeRBSystemTransient>(_initialize_rb_system_name);

  std::ofstream _python_out("L2Matrix", std::ios::out);
  _python_out << "Number of Rows: "<< _initialize_rb_system.getL2Matrix()->m() << std::endl;
  _python_out << "Number of Columns: "<< _initialize_rb_system.getL2Matrix()->n() << std::endl;
  _initialize_rb_system.getL2Matrix()->print(_python_out, true);
  _python_out.close();
}
