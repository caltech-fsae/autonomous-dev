#include <math.h>
#include "matrix_ops.c"

Matrix matrix_sensor_to_vehicle(double distance, double theta, double phi) {
    Matrix result;
    result.mat[0][0] = sin(theta) * cos(phi);
    result.mat[0][1] = cos(theta) * cos(phi);
    result.mat[0][2] = -cos(phi);
    result.mat[1][0] = sin(theta) * sin(phi);
    result.mat[1][1] = cos(theta) * sin(phi);
    result.mat[1][2] = cos(phi);
    result.mat[2][0] = cos(theta);
    result.mat[2][1] = -sin(phi);
    result.mat[2][2] = 0;

}
