#include <math.h>

// encoding_lvl array. filled in with random numbers rn.
static int encoding_lvl[3][2] = {
        {1, M_PI/4},  // encoding lvl zero (height, theta)
        {2, M_PI/1},  // encoding lvl one  (height, theta)
        {3, -M_PI/4}  // encoding lvl two  (height, theta)
    };

// fix these
double time_to_theta(double time, double freq);

Matrix matrix_spherical_to_cartesian(double theta, double phi);

Matrix matrix_encoding_to_lidar(double theta, double encoding_lvl);

Matrix lidar_to_vehicle();

Matrix vehicle_to_world();
