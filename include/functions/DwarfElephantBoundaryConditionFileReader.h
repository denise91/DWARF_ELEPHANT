#ifndef DWARFELEPHANTBOUNDARYCONDITIONFILEREADER_H
#define DWARFELEPHANTBOUNDARYCONDITIONFILEREADER_H

#include "Function.h"

class DwarfElephantBoundaryConditionFileReader;

template <>
InputParameters validParams<DwarfElephantBoundaryConditionFileReader>();

///This function is responsible for reading boundary condition values from file.
class DwarfElephantBoundaryConditionFileReader : public Function
{
public:
  DwarfElephantBoundaryConditionFileReader(const InputParameters & parameters);

  virtual Real value(Real t, const Point & p) const override;
  // virtual RealGradient gradient(Real t, const Point & p) const override;

protected:
  std::vector<std::string> _file;
  // std::string _dx_file;
  // std::string _dy_file;
  unsigned int _dimension;
  // unsigned int _ID_data_layer;
  unsigned int _num_points;
  // std::vector<unsigned int> _data_array_dimensions;
  // std::vector<Real> _step_sizes;
  Real _tolerance;
  bool _interpolate_space;
  bool _interpolate_time;
  // bool _access_multiple_times;
  // bool _gradients;

  std::vector<Real> _time_frames;
  std::vector<std::vector<Real>> _x_coordinates;
  std::vector<std::vector<Real>> _y_coordinates;
  std::vector<std::vector<Real>> _z_coordinates;
  std::vector<std::vector<Real>> _variable_values;
  // std::vector<Real> _dx;
  // std::vector<Real> _dy;
  // std::vector<std::vector<Real>> _data_array;
  // std::vector<std::vector<Real>> _dx_data_array;
  // std::vector<std::vector<Real>> _dy_data_array;

private:
  void fileParser(unsigned int time_frame);
  // std::vector<Real>  fileParserGradients(std::string & file);
  Real setValue(Real _t, Real _x_coord, Real _y_coord) const;
  Real setValueInterpolateTime(Real _t, Real _x_coord, Real _y_coord) const;
  Real findValue(Real _t, Real _x_coord, Real _y_coord) const;
  Real interpolateValue(Real _t, Real _x_coord, Real _y_coord) const;
  Real interpolateValueSetTime(Real _t, Real _x_coord, Real _y_coord) const;
  Real interpolateValueInterpolateTime(Real _t, Real _x_coord, Real _y_coord) const;
  // std::vector<Real> findGradient(Real _x_coord, Real _y_coord) const;
};

#endif // DWARFELEPHANTBOUNDARYCONDITIONFILEREADER_H
