#include <math.h>

// encoding_lvl array. filled in with random numbers rn.
static int encoding_lvl[3][2] = {
        {1, M_PI/4},  // encoding lvl zero (height, theta)
        {2, M_PI/1},  // encoding lvl one  (height, theta)
        {3, -M_PI/4}  // encoding lvl two  (height, theta)
    };


double time_to_phi(double time, double freq);
Matrix matrix_spherical_to_cartesian(double phi, double theta, double r);
Matrix point_to_encoding(double phi, double theta, double r);
Matrix encoding_to_lidar(double x, double y, double z);
Matrix lidar_to_vehicle(double x, double y, double z);
Matrix vehicle_to_world(double yaw, double pitch, double roll, double x, double y, double z);
Point encoding_to_world(Point p, time, freq, encoding_lvl_num, r, veh_yaw, veh_pitch, veh_roll, veh_x, veh_y, veh_z);
Matrix general_transformation(double yaw, double pitch, double roll, double x, double y, double z);
