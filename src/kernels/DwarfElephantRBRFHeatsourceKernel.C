#include "DwarfElephantRBRFHeatsourceKernel.h"
#include "Function.h"

template<>
InputParameters
validParams<DwarfElephantRBRFHeatsourceKernel>()
{
  InputParameters params = validParams<DwarfElephantRBKernel>();
  params.addClassDescription("Implements a RF heatsource function using the RBKernel.");
  //params.addRequiredParam<FunctionName>("heat_source_function","Name of the function approximating the RF heat source.");
  params.addParam<Real>("needle_center_x",0.0,"X coordinate of needle center.");
  params.addParam<Real>("needle_center_y",0.0,"Y coordinate of needle center.");
  params.addParam<Real>("needle_center_z",0.0,"Z coordinate of needle center.");
  params.addParam<Real>("needle_axis_theta",0.0,"Polar angle of needle axis.");
  params.addParam<Real>("needle_axis_phi",0.0,"Azimuthal angle of needle axis.");
  params.addRequiredParam<Real>("r0","Cylinder radius in the deformed geometry.");
  params.addRequiredParam<Real>("l0","Cylinder length in the deformed geometry.");
  params.addRequiredParam<Real>("r","Cylinder radius in the reference geometry.");
  params.addRequiredParam<Real>("l","Cylinder length in the reference geometry.");
  return params;
}

DwarfElephantRBRFHeatsourceKernel::DwarfElephantRBRFHeatsourceKernel(const InputParameters & parameters) :
  DwarfElephantRBKernel(parameters),
  //_function(getFunction("heat_source_function")),
        _needle_center_x(getParam<Real>("needle_center_x")),
        _needle_center_y(getParam<Real>("needle_center_y")),
        _needle_center_z(getParam<Real>("needle_center_z")),
        _needle_axis_theta(getParam<Real>("needle_axis_theta")),
        _needle_axis_phi(getParam<Real>("needle_axis_phi")),
        r_0(getParam<Real>("r0")),
        l_0(getParam<Real>("l0")),
        r(getParam<Real>("r")),
        l(getParam<Real>("l"))
{
}

Real DwarfElephantRBRFHeatsourceKernel::computeQpResidual()
{
    Number x_new, y_new, z_new, t0, subdomain_jac;
    double matrix[3][3]={0}, vec[3][1]={0}, L = 0.1;
    double d = (8.0/3.0)*r, h = (4.0/3.0)*l;

    //const DwarfElephantInitializeRBSystemTransient & _initialize_rb_system = getUserObject<DwarfElephantInitializeRBSystemTransient>("initial_rb_userobject");
    
    if (_current_elem->subdomain_id() == 1)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = (d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 2)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = (d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 3)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = (L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = (L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 4)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 5)
 {
  matrix[0][0] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[0][1] = (r*(1.0/2.0)-r_0*(1.0/2.0))/r;
  matrix[1][0] = (r*(1.0/2.0)-r_0*(1.0/2.0))/r;
  matrix[1][1] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));  vec[0][0] = 0; vec[1][0] = 0; vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l*r_0-h*l_0*r_0)/(fabs(l)*fabs(r)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 6)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 7)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 8)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 9)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 10)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][1] = (d*r_0+h*r)/(r*(d+h));
  matrix[1][2] = -(d*(r-r_0))/(r*(d+h));
  matrix[2][1] = -(h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h)); vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 11)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 12)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 13)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 14)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 15)
 {
  matrix[0][0] = (d*r_0+h*r)/(r*(d+h));
  matrix[0][2] = (d*(r-r_0))/(r*(d+h));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][0] = (h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));  vec[0][0] = 0; vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 16)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 17)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 18)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 19)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 20)
 {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][1] = (d*r_0+h*r)/(r*(d+h));
  matrix[1][2] = (d*(r-r_0))/(r*(d+h));
  matrix[2][1] = (h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h)); vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 21)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 22)
 {
  matrix[0][0] = 1.0;
  matrix[0][1] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = fabs(L*r-d*r_0)/(fabs(L-d)*fabs(r));
}
if (_current_elem->subdomain_id() == 23)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 24)
 {
  matrix[0][0] = r_0/r;
  matrix[0][1] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l; vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  t0 = (fabs(l_0*r_0*(L*r-d*r_0))*1.0/pow(fabs(r),2.0))/(fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 25)
 {
  matrix[0][0] = (d*r_0+h*r)/(r*(d+h));
  matrix[0][2] = -(d*(r-r_0))/(r*(d+h));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][0] = -(h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));  vec[0][0] = 0; vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0] = 0;
  t0 = (fabs((d*d)*l*(r_0*r_0)-L*h*l_0*(r*r)-L*d*l*r*r_0+d*h*l_0*r*r_0)*1.0/pow(fabs(r),2.0))/(fabs(d+h)*fabs(l)*fabs(L-d));
}
if (_current_elem->subdomain_id() == 26)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = (d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = (d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 27)
 {
  matrix[0][0] = 1.0;
  matrix[0][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l-h*l_0)/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 28)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = (L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 29)
 {
  matrix[0][0] = r_0/r;
  matrix[0][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = (L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h)); vec[0][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = (fabs(L*l-h*l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/(fabs(l)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 30)
 {
  matrix[0][0] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[0][1] = (r*(-1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[1][0] = (r*(-1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[1][1] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));  vec[0][0] = 0; vec[1][0] = 0; vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  t0 = fabs(L*l*r_0-h*l_0*r_0)/(fabs(l)*fabs(r)*fabs(L-h));
}
if (_current_elem->subdomain_id() == 31)
 {
  matrix[0][0] = r_0/r;
  matrix[1][1] = r_0/r;
  matrix[2][2] = l_0/l;  vec[0][0] = 0; vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs(l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/fabs(l);
}
if (_current_elem->subdomain_id() == 32)
 {
  matrix[0][0] = r_0/r;
  matrix[1][1] = r_0/r;
  matrix[2][2] = l_0/l;  vec[0][0] = 0; vec[1][0] = 0; vec[2][0] = 0;
  t0 = (fabs(l_0)*1.0/pow(fabs(r),2.0)*pow(fabs(r_0),2.0))/fabs(l);
}
/*
    for (int i = 0; i < 4; i++)
    {
        x_new = matrix[0][0]*(_current_elem->point(i))(0) + matrix[0][1]*(_current_elem->point(i))(1) + matrix[0][2]*(_current_elem->point(i))(2) + vec[0][0];
        y_new = matrix[1][0]*(_current_elem->point(i))(0) + matrix[1][1]*(_current_elem->point(i))(1) + matrix[1][2]*(_current_elem->point(i))(2) + vec[1][0];
        z_new = matrix[2][0]*(_current_elem->point(i))(0) + matrix[2][1]*(_current_elem->point(i))(1) + matrix[2][2]*(_current_elem->point(i))(2) + vec[2][0];
        if (sqrt( pow(x_new - _needle_center_x,2) + pow(y_new - _needle_center_y,2) + pow(z_new - _needle_center_z,2)) <= 0.02)    
        {
            std::vector<dof_id_type>::iterator it = std::find(_initialize_rb_system._temp_averaging_node_ids.begin(), _initialize_rb_system._temp_averaging_node_ids.end(), _current_elem->node_id(i));
            if (it == _initialize_rb_system._temp_averaging_node_ids.end())
	        _initialize_rb_system._temp_averaging_node_ids.push_back(_current_elem->node_id(i));
        }
    }
*/
    
x_new = matrix[0][0]*_q_point[_qp](0) + matrix[0][1]*_q_point[_qp](1) + matrix[0][2]*_q_point[_qp](2) + vec[0][0];
y_new = matrix[1][0]*_q_point[_qp](0) + matrix[1][1]*_q_point[_qp](1) + matrix[1][2]*_q_point[_qp](2) + vec[1][0];
z_new = matrix[2][0]*_q_point[_qp](0) + matrix[2][1]*_q_point[_qp](1) + matrix[2][2]*_q_point[_qp](2) + vec[2][0];
    Real _needle_power = 1.0;
  RealVectorValue _A_bar(x_new,y_new,z_new);
  RealVectorValue _Z_cap(std::sin(_needle_axis_theta)*std::cos(_needle_axis_phi),std::sin(_needle_axis_theta)*std::sin(_needle_axis_phi),std::cos(_needle_axis_theta));
  RealVectorValue _O_cap(_needle_center_x, _needle_center_y, _needle_center_z);
  RealVectorValue _temp_vec = _A_bar - _O_cap;
  RealVectorValue _r_A_bar = _temp_vec - _Z_cap * (_temp_vec * _Z_cap);
  Real _r_needle = _r_A_bar.norm();
  Real _z_needle = _temp_vec * _Z_cap; 
  Real Q_G = exp(-pow(_r_needle,2)/(2. * pow(2.201e-3,2)));
  Real _sigmoid_plus = 1./(1. + exp(-1.303e4*(_z_needle - 1.052e-2)));
  Real _sigmoid_minus = 1./(1. + exp(-1.303e4*(_z_needle + 1.052e-2)));
  Real P = (_needle_power * 1.383e15 * pow(_z_needle,4) + 2.624e6)*(_sigmoid_minus *(1. - _sigmoid_plus));
  subdomain_jac = fabs( matrix[0][0] * (matrix[1][1]*matrix[2][2] - matrix[2][1]*matrix[1][2])
                     - matrix[0][1] * (matrix[1][0]*matrix[2][2] - matrix[2][0]*matrix[1][2])
                     + matrix[0][2] * (matrix[1][0]*matrix[1][1] - matrix[1][1]*matrix[2][0]));
  return P*Q_G* _test[_i][_qp]*t0;//1.0*t0*_test[_i][_qp];//
    //return _function.value(_t,_q_point[_qp]) * _test[_i][_qp];
}

Real DwarfElephantRBRFHeatsourceKernel::computeQpJacobian()
{
  return 0.0;
}
