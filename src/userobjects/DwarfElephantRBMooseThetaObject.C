#include "DwarfElephantRBMooseThetaObject.h"
#include "Function.h"
// #include "MooseVariable.h"
// #include "SubProblem.h"
// #include "MooseTypes.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBMooseThetaObject);

template <>
InputParameters
validParams<DwarfElephantRBMooseThetaObject>()
{
  InputParameters params = validParams<NodalUserObject>();
  params.addRequiredParam<FunctionName>("function", "The function that describes the Theta Object.");
  params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addParam<unsigned int>("ID_moose_theta_object", 0 , "ID of the MOOSE theta object.");
  return params;
}

DwarfElephantRBMooseThetaObject::DwarfElephantRBMooseThetaObject(const InputParameters & parameters)
  : NodalUserObject(parameters),
  _func(getFunction("function")),
  _simulation_type(getParam<std::string>("simulation_type")),
  _ID_moose_theta_object(getParam<unsigned int>("ID_moose_theta_object"))
{
}

void
DwarfElephantRBMooseThetaObject::initialize()
{
  if(_exec_flags[0] != EXEC_TIMESTEP_END)
    mooseError("The UserObject 'DwarfElephantRBMooseThetaObject' has to be executed on 'timestep_end'. "
             "You defined a wrong state in your 'execute_on' line in the input file. "
             "Please, correct your settings.");

  // if(_simulation_type == "steady")  // SteadyState
  //   _initialize_rb_system = &getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
  // else
    _initialize_rb_system_transient = &getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");

}

void
DwarfElephantRBMooseThetaObject::execute()
{
  // if(_simulation_type == "steady")
  //   _initialize_rb_system->_moose_theta_objects[_ID_moose_theta_object]->set(_current_node->id(),_func.value(_t, *_current_node));
  // else
    // _initialize_rb_system_transient->_moose_theta_objects[_ID_moose_theta_object]->set(_current_node->id(),(_func.value(_t, *_current_node)));
}
