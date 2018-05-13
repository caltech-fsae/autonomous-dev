#include <math.h>
#include "pointCloud.h"

/*  
 * Given angles and radius, can convert to a point
 * in real space. Using physics coordinates.
 * Also need ID of the point.
 */
Point sphere_to_cart(double theta, double phi, double rad, int id)
{
    PointCloud point = POINT__INIT;

    point.theta = thetha;
    point.phi = phi;
    point.distance = rad;

    point.x = rad * sin(theta) * cos(phi);
    point.y = rad * sin(theta) * sin(phi);
    point.z = rad * cos(theta);
    point.obj_id = id;

    return point;
}