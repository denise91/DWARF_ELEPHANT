#include "DwarfElephantNodalDifference.h"
#include "Function.h"
#include "DwarfElephantRBClassesSteadyState.h"
#include "libmesh/nonlinear_implicit_system.h"

//namespace libMesh
//{
//    class NonlinearImplicitSystem;
//}

template <>
InputParameters
validParams<DwarfElephantNodalDifference>()
{
  InputParameters params = validParams<NodalVectorPostprocessor>();
  params.addRequiredParam<FunctionName>("function", "The solution to compare against");
  params.addParam<std::string>("system", "rb0", "The name of the used system.");
  return params;
}

DwarfElephantNodalDifference::DwarfElephantNodalDifference(const InputParameters & parameters):
  NodalVectorPostprocessor(parameters),
  _func(getFunction("function")),
  _nodal_difference(declareVector("nodal_difference")),
  _system(getParam<std::string>("system"))
{
}

void
DwarfElephantNodalDifference::initialize()
{
  if(!_unique_node_execute)
    mooseError("This VectorPostprocessor has to be execute with 'unique_node_execute' equal to 'true'.");

  // Initialize solution vector
  _nodal_solution = _fe_problem.es().get_system<NonlinearImplicitSystem>(_system).current_local_solution.get();

  _nodal_difference.clear();
}

void
DwarfElephantNodalDifference::execute()
{
  Point _point(_current_node->operator()(0), _current_node->operator()(1), _current_node->operator()(2));
  _nodal_difference.push_back(_nodal_solution->el(_current_node->id()) - _func.value(_t, _point));
  // _nodal_solution->set(_current_node->id(),_nodal_solution->el(_current_node->id()) - _func.value(_t, _point));
}

void
DwarfElephantNodalDifference::finalize()
{
  // _nodal_solution->print_matlab("solution");
}
