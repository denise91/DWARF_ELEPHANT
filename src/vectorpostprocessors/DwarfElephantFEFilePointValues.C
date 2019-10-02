#include "DwarfElephantFEFilePointValues.h"

// MOOSE includes
#include "Function.h"
#include "MooseMesh.h"
#include "MooseVariable.h"
#include "SubProblem.h"

#include "libmesh/system.h"

registerMooseObject("DwarfElephantApp", DwarfElephantFEFilePointValues);

template <>
InputParameters
validParams<DwarfElephantFEFilePointValues>()
{
  InputParameters params = validParams<GeneralVectorPostprocessor>();
  params.addRequiredParam<VariableName>(
      "variable", "The name of the variable that this postprocessor operates on.");
  params.addRequiredParam<std::string>(
    "file", "Name and path of the data file, valid delimiters are space and tab-space.");
  return params;
}

DwarfElephantFEFilePointValues::DwarfElephantFEFilePointValues(const InputParameters & parameters)
  : GeneralVectorPostprocessor(parameters),
    _var_number(_subproblem
                    .getVariable(_tid,
                                 parameters.get<VariableName>("variable"),
                                 Moose::VarKindType::VAR_ANY,
                                 Moose::VarFieldType::VAR_FIELD_STANDARD)
                    .number()),
    _system(_subproblem.getSystem(getParam<VariableName>("variable"))),
    _values(declareVector("_values")),
    _file(getParam<std::string>("file"))
{
  fileParser();
}

void
DwarfElephantFEFilePointValues::initialize()
{
  _values.clear();
}

void
DwarfElephantFEFilePointValues::execute()
{
  _values.resize(_num_points);

  for (unsigned int i=0; i< _num_points; i++)
  {
    Point _point(_x_coordinates[i], _y_coordinates[i], _z_coordinates[i]);
    _values[i]=_system.point_value(_var_number, _point, false);

    /**
     * If we get exactly zero, we don't know if the locator couldn't find an element, or
     * if the solution is truly zero, more checking is needed.
     */
     if (MooseUtils::absoluteFuzzyEqual(_values[i], 0.0))
     {
       auto pl = _subproblem.mesh().getPointLocator();
       pl->enable_out_of_mesh_mode();

       auto * elem = (*pl)(_point);
       auto elem_id = elem ? elem->id() : DofObject::invalid_id;
       gatherMin(elem_id);

       if (elem_id == DofObject::invalid_id)
         mooseError("No element located at ", _point, " in PointValue Postprocessor named: ", name());
     }
  }
}

void
DwarfElephantFEFilePointValues::fileParser()
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
