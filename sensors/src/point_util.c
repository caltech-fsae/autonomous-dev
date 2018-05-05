#include <math.h>
#include "point_util.h"

// using physics coordinates
/*  
 * Given angles and radius, can convert to a point
 * in real space. 
 */
Point sphere_to_cart(double theta, double phi, double rad)
{
    Point point = POINT__INIT;

    point.x = rad * sin(theta) * cos(phi);
    point.y = rad * sin(theta) * sin(phi);
    point.z = rad * cos(theta);

    return point;
}