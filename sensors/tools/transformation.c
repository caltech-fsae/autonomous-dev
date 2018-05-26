#include "matrix_ops.c"

double time_to_theta(double time, double freq) {
    /* Time should be in seconds. */
    return (2 * pi * freq * time);
}

// For all functions below:
// TransformedVector = TranslationMatrix * RotationMatrix * OriginalVector;

// Need rotation (pitch, yaw) and translation matrices (varies
// based on encoding_lvl)

/* Multiply by r, theta, phi. */
Matrix matrix_spherical_to_cartesian(double theta, double phi) {
    /* Pad with zeroes to turn into a 4x4. */
    Matrix result;
    result.mat[0][0] = sin(theta) * cos(phi);
    result.mat[0][1] = cos(theta) * cos(phi);
    result.mat[0][2] = -sin(phi);
    result.mat[0][3] = 0;
    result.mat[1][0] = sin(theta) * sin(phi);
    result.mat[1][1] = cos(theta) * sin(phi);
    result.mat[1][2] = cos(phi);
    result.mat[1][3] = 0;
    result.mat[2][0] = cos(theta);
    result.mat[2][1] = -sin(phi);
    result.mat[2][2] = 0;
    result.mat[2][3] = 0;
    result.mat[3][0] = 0;
    result.mat[3][1] = 0;
    result.mat[3][2] = 0;
    result.mat[3][3] = 0;
    return result;
}

Matrix matrix_encoding_to_lidar(double theta, double encoding_lvl) {
    /* Calculate phi based on encoding level. */
    double theta;
    double phi;
    double height;
    /*
     * TODO: instead of hard coding, have a larger array of smaller 2 value
     * arrays (height and angle) and have the index from large array correspond
     * to encoding level.
    */
    Matrix result;
    /* Only transformation is from height in encoding. */
    // result = general_transformation(theta, phi, 0, 0, 0, height);
    return result;
}

/* Matrix transformation position from lidar to vehicle. */
// Need translation matrix
Matrix lidar_to_vehicle() {
    /* TODO: get x, y, z from lidar. */
    double x;
    double y;
    double z;
    Matrix result;
    // result = general_transformation(0, 0, 0, x, y, z);
    return result;
}

// Need rotation (yaw, maybe pitch) and translation matrices
Matrix vehicle_to_world(){
    double yaw;
    double pitch;
    double roll;
    double x;
    double y;
    double z;
    // result = general_transformation(yaw, pitch, roll, x, y, z);
}
