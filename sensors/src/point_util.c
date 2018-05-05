#include <math.h>
#include "point_util.h"

// using physics coordinates
/*  
 * Given angles and radius, can convert to a point
 * in real space. Just changes value of point, doesn't
 * return anything.
 */
spherical_to_cartesian(double theta, double phi, double rad)
{
    double x;
    double y;
    double z;

    x = rad * sin(theta) * cos(phi);
    y = rad * sin(theta) * sin(phi);
    z = rad * cos(theta);
}