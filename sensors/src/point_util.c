// using physics coordinates
#include <math.h>
spherical_to_cartesian(double theta, double phi, double rad)
{
    double x;
    double y;
    double z;

    x = rad * sin(theta) * cos(phi);
    y = rad * sin(theta) * sin(phi);
    z = rad * cos(theta);
}