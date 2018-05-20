#include <math.h>
#include "matrix_ops.c"

double time_to_theta(double time, double freq) {
    /* Time should be in seconds. */
    return (2 * pi * freq * time);
}

Matrix matrix_encoding_to_sensor(double distance, double theta,
        double encoding_lvl) {
    /* Calculate phi based on encoding level. */
    double phi;
    /*
     * TODO: instead of hard coding, have a larger array of smaller 2 value
     * arrays (height and angle) and have the index from large array correspond
     * to encoding level.
    */
    Matrix result;
    /* Add last column and row of the matrix. */
    result.mat[0][0] = sin(theta) * cos(phi);
    result.mat[0][1] = cos(theta) * cos(phi);
    result.mat[0][2] = -cos(phi);
    // result.mat[0][3] =;
    result.mat[1][0] = sin(theta) * sin(phi);
    result.mat[1][1] = cos(theta) * sin(phi);
    result.mat[1][2] = cos(phi);
    // result.mat[1][3] =;
    result.mat[2][0] = cos(theta);
    result.mat[2][1] = -sin(phi);
    result.mat[2][2] = 0;
    // result.mat[2][3] =;
    // result.mat[3][0] =;
    // result.mat[3][1] =;
    // result.mat[3][2] =;
    // result.mat[3][3] =;
}