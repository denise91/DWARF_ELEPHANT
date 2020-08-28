#include "DwarfElephantInitialConditionFileReader.h"

template <>
InputParameters
validParams<DwarfElephantInitialConditionFileReader>()
{
  InputParameters params = validParams<Function>();
  params.addClassDescription("This file reader is required for reading in the initial conditions. It expects an input format as provided by the VectorPostprocessor class.");
  params.addRequiredParam<std::string>("file", "Name and path of the data file, valid delimiters are space and tab-space.");
  return params;
}

DwarfElephantInitialConditionFileReader::DwarfElephantInitialConditionFileReader(const InputParameters & parameters)
  : Function(parameters),
  _file(getParam<std::string>("file"))
{
  _values.resize(5); // file always contains x y z id value --> always five columns
  _values.clear();
  fileReader();
}

Real
DwarfElephantInitialConditionFileReader::value(Real /*t*/, const Point & /*p*/) const
{
  Real value = 0.0;   // default value to return
  return value;
}

Real
DwarfElephantInitialConditionFileReader::value(const Node & n) const
{
  Real value = 0.0;   // default value to return
  value = _values[4][n.id()];
  return value;
}

void
DwarfElephantInitialConditionFileReader::fileReader()
{
  // define all necessary parameters
  std::string _line;
  int _line_number = 0;

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
    if (_line_number == 0){
      _line_number ++;
      continue;
    }

    std::istringstream _input_string(_line);
    std::vector<Real> _tmp_vec;
    Real _input_value;
    while (_input_string >> _input_value)
      _tmp_vec.push_back(_input_value);

      if (_tmp_vec.size()>5)
        mooseError("Maximum number of allowed columns is five.");

      for (unsigned int i = 0; i < _tmp_vec.size(); i++){
        _values[i].push_back(_tmp_vec[i]);
      }

      _tmp_vec.clear();
  }
  _input_file.close();
}
