#include <math.h>

double time_to_theta(double time, double freq);

Matrix matrix_spherical_to_cartesian(double theta, double phi);

Matrix matrix_encoding_to_lidar(double theta, double encoding_lvl);

Matrix lidar_to_vehicle();

Matrix vehicle_to_world();
