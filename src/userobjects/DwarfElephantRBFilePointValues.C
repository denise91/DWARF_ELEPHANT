#include "DwarfElephantRBFilePointValues.h"

// MOOSE includes
#include "MooseMesh.h"
#include "MooseVariable.h"
#include "SubProblem.h"

#include "libmesh/system.h"
#include "libmesh/fe_interface.h"
#include "libmesh/fe_compute_data.h"

registerMooseObject("DwarfElephantApp", DwarfElephantRBFilePointValues);

template <>
InputParameters
validParams<DwarfElephantRBFilePointValues>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params.addRequiredParam<std::string>(
    "file", "Name and path of the data file, valid delimiters are space and tab-space.");
  params.addRequiredParam<VariableName>(
      "variable", "The name of the variable that this postprocessor operates on.");
  params.addParam<std::string>("simulation_type", "steady", "Determines whether the simulation is steady state or transient.");
  params.addRequiredParam<UserObjectName>("initial_rb_userobject", "Name of the UserObject for initializing the RB system");
  params.addParam<unsigned int>("outputid",0,"The ID of the output of interest.");
  params.addClassDescription("Outputs an elemental variable value at a particular location");

  return params;
}

DwarfElephantRBFilePointValues::DwarfElephantRBFilePointValues(const InputParameters & parameters)
  : GeneralUserObject(parameters),
    _mesh(_subproblem.mesh()),
    _file(getParam<std::string>("file")),
    _var_number(_subproblem.getVariable(_tid, parameters.get<VariableName>("variable")).number()),
    _simulation_type(getParam<std::string>("simulation_type"))
{
  fileParser();
}

void
DwarfElephantRBFilePointValues::execute()
{
  for(unsigned int i= 0; i<_num_points; i++){
    Point _point(_x_coordinates[i], _y_coordinates[i], _z_coordinates[i]);
    if(_simulation_type=="steady") {
      const DwarfElephantInitializeRBSystemSteadyState & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemSteadyState>("initial_rb_userobject");
      assignPoint(_initialize_rb_system.getOutputs(), i, _point);
    } else {
      const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");
      assignPoint(_initialize_rb_system.getOutputs(), i, _point);
    }
  }
}

void
DwarfElephantRBFilePointValues::assignPoint(const std::vector<std::vector<NumericVector <Number> *> > _outputs,
  unsigned int _outputid, Point _point, bool _insistOnSuccess)
{
  if (_outputid >= _outputs.size())
    mooseError("The outputid you defined is out of range.");

  // This function must be called on every processor because it is not known in
  // advance which processors holds the point of interest.
  parallel_object_only();

  //It is important to check that every processor agrees on the point
  #ifndef NDEBUG
  libmesh_assert(comm().verify(_point(0)));
  #if LIBMESH_DIM > 1
  libmesh_assert(comm().verify(_point(1)));
  #endif
  #if LIBMESH_DIM > 2
  libmesh_assert(comm().verify(_point(2)));
  #endif
  #endif // NDEBUG

  // Use an existing PointLocator or create a new one.
  std::unique_ptr<PointLocatorBase> _locator_ptr = _mesh.getMesh().sub_point_locator();
  PointLocatorBase & _locator = *_locator_ptr;

  if (!_insistOnSuccess || !_mesh.getMesh().is_serial())
    _locator.enable_out_of_mesh_mode();

  // Get a pointer to the element that contains the point.
  const Elem * _element = _locator(_point);

  // Get the DofMap for the element.
  const DofMap & dof_map = _fe_problem.getNonlinearSystemBase().dofMap();
  std::vector<dof_id_type> dof_indices;

  dof_map.dof_indices(_element, dof_indices, _var_number);

  // Prepare the calculation of the weights.
  FEType fe_type = dof_map.variable_type(_var_number);

  Point coor = FEInterface::inverse_map(_element->dim(), fe_type, _element, _point);
  FEComputeData fe_data(_fe_problem.es(), coor);
  FEInterface::compute_data(_element->dim(), fe_type, _element, fe_data);

  // Assign the correct weights to the output of interest vector.
  if (_element && (_element->processor_id() == processor_id()))
  {
    for(unsigned int _q=0; _q < _outputs[_outputid].size(); _q++)
    {
      for(unsigned int _n=0; _n < dof_indices.size(); _n++)
      {
        _outputs[_outputid][_q]->set(dof_indices[_n],fe_data.shape[_n]);
      }
      //_outputs[_outputid][_q]->close();
    }
  }
}

void
DwarfElephantRBFilePointValues::fileParser()
{
  // define all necessary parameters
  std::string _line;

  // Check inputFile and create input stream.
  MooseUtils::checkFileReadable(_file);
  std::ifstream _input_file;

  // Open the inputFile and check it.
  _input_file.open(_file.c_str());
  if (!_input_file.good())
    mooseError("Error while opening the file '", _file, "' within the DwarfElephantFileReader function.");

  // Read the file.
  while (std::getline(_input_file, _line))
  {
    if (_line[0] != '#')
    {
      // Parse the data to the corresponding vectors
      std::istringstream _iss(_line);
      std::vector<Real> _all_data;
      Real _data_value;
      while (_iss >> _data_value)
        _all_data.push_back(_data_value);

      _x_coordinates.push_back(_all_data[0]);
      _y_coordinates.push_back(_all_data[1]);
      _z_coordinates.push_back(_all_data[2]);
    }
  }
  _input_file.close();
  _num_points = _x_coordinates.size();
}
