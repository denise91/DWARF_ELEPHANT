Real NewCoord(Real OldCoordX, Real OldCoordY, Real OldCoordZ, Real r_0, Real l_0, Real L, Real r, Real l, int subdomain, int Coord_Required)
{
  Real matrix[3][3] = {0}, vec[3][1] = {0}, d = 3*r, h = 1.5*l;
  if (subdomain == 1)
  {
  matrix[0][0] = 1.0;
  matrix[0][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = (d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 2)
  {
  matrix[0][0] = 1.0;
  matrix[0][2] = (d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 3)
  {
  matrix[0][0] = r_0/r;
  matrix[0][2] = (L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = (L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 4)
  {
  matrix[0][0] = r_0/r;
  matrix[0][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 5)
  {
  matrix[0][0] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[0][1] = (r*(1.0/2.0)-r_0*(1.0/2.0))/r;
  matrix[1][0] = (r*(1.0/2.0)-r_0*(1.0/2.0))/r;
  matrix[1][1] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
  vec[0][0] = 0; vec[1][0] = 0; vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 6)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 7)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 8)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 9)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 10)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][1] = (d*r_0+h*r)/(r*(d+h));
  matrix[1][2] = -(d*(r-r_0))/(r*(d+h));
  matrix[2][1] = -(h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0] = 0; vec[2][0] = 0;
  }
  if (subdomain == 11)
  {
  matrix[0][0] = 1.0;
  matrix[0][1] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 12)
  {
  matrix[0][0] = 1.0;
  matrix[0][1] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 13)
  {
  matrix[0][0] = r_0/r;
  matrix[0][1] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 14)
  {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 15)
  {
  matrix[0][0] = (d*r_0+h*r)/(r*(d+h));
  matrix[0][2] = (d*(r-r_0))/(r*(d+h));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][0] = (h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));
  vec[0][0] = 0; vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0] = 0;
  }
  if (subdomain == 16)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 17)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = 1.0;
  matrix[2][0] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 18)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 19)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][0] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = r_0/r;
  matrix[2][0] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 20)
  {
  matrix[0][0] = (L*r-d*r_0)/(r*(L-d));
  matrix[1][1] = (d*r_0+h*r)/(r*(d+h));
  matrix[1][2] = (d*(r-r_0))/(r*(d+h));
  matrix[2][1] = (h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0] = 0; vec[2][0] = 0;
  }
  if (subdomain == 21)
  {
  matrix[0][0] = 1.0;
  matrix[0][1] = -(d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 22)
  {
  matrix[0][0] = 1.0;
  matrix[0][1] = (d*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (h*(l-l_0))/(l*(L-d));
  matrix[2][2] = 1.0;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 23)
  {
  matrix[0][0] = r_0/r;
  matrix[0][1] = -(L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = (L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 24)
  {
  matrix[0][0] = r_0/r;
  matrix[0][1] = (L*(r-r_0))/(r*(L-d));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][1] = -(L*(l-l_0))/(l*(L-d));
  matrix[2][2] = l_0/l;
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0]  = (L*d*(l-l_0)*(-1.0/2.0))/(l*(L-d));
  }
  if (subdomain == 25)
  {
  matrix[0][0] = (d*r_0+h*r)/(r*(d+h));
  matrix[0][2] = -(d*(r-r_0))/(r*(d+h));
  matrix[1][1] = (L*r-d*r_0)/(r*(L-d));
  matrix[2][0] = -(h*(l-l_0))/(l*(d+h));
  matrix[2][2] = (d*l+h*l_0)/(l*(d+h));
  vec[0][0] = 0; vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-d)); vec[2][0] = 0;
  }
  if (subdomain == 26)
  {
  matrix[0][0] = 1.0;
  matrix[0][2] = (d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = (d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 27)
  {
  matrix[0][0] = 1.0;
  matrix[0][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[1][1] = 1.0;
  matrix[1][2] = -(d*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*d*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 28)
  {
  matrix[0][0] = r_0/r;
  matrix[0][2] = (L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 29)
  {
  matrix[0][0] = r_0/r;
  matrix[0][2] = -(L*(r-r_0))/(r*(L-h));
  matrix[1][1] = r_0/r;
  matrix[1][2] = (L*(r-r_0))/(r*(L-h));
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
 vec[0][0]  = (L*h*(r-r_0)*(-1.0/2.0))/(r*(L-h)); vec[1][0]  = (L*h*(r-r_0)*(1.0/2.0))/(r*(L-h)); vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 30)
  {
  matrix[0][0] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[0][1] = (r*(-1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[1][0] = (r*(-1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[1][1] = (r*(1.0/2.0)+r_0*(1.0/2.0))/r;
  matrix[2][2] = (L*l-h*l_0)/(l*(L-h));
  vec[0][0] = 0; vec[1][0] = 0; vec[2][0]  = (L*h*(l-l_0)*(1.0/2.0))/(l*(L-h));
  }
  if (subdomain == 31)
  {
  matrix[0][0] = r_0/r;
  matrix[1][1] = r_0/r;
  matrix[2][2] = l_0/l;
  vec[0][0] = 0; vec[1][0] = 0; vec[2][0] = 0;
  }
  if (subdomain == 32)
  {
  matrix[0][0] = r_0/r;
  matrix[1][1] = r_0/r;
  matrix[2][2] = l_0/l;
  vec[0][0] = 0; vec[1][0] = 0; vec[2][0] = 0;
  }
    return matrix[Coord_Required][0]*OldCoordX + matrix[Coord_Required][1]*OldCoordY + matrix[Coord_Required][2]*OldCoordZ + vec[Coord_Required][0];
}
