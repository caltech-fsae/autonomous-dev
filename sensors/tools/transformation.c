/*
 * Transformation of a single point from point cloud to world coordinate
 * All tranformation is done using 4x4 matrices 
 * Step 1: trasnform from point to encoding
 * Transforms point in point cloud (in spherical coordinate) to encoding's
 * frame (in Cartesian), where the encoding is located at the origin. Distance
 * r is extracted from the point cloud, angle theta is based on the level of
 * encoding, and angle phi is calculated based on lidar frequency and time
 * Step 2: transform from encoding to sensor
 * Transforms from encoding's frame to sensor's frame based on the height of
 * the encoding on the sensor; information is stored in 2D array of width 2
 * with encoding level corresponding to encoding height.
 * Step 3: transform from sensor to vehicle
 * Transforms from the sensor's frame to the vehicle's frame; depends on the
 * lidar placement of the vehicle but is constant after vehicle is finalized.
 * Step 4: transform from vehicle to world
 * Transforms from the vehicle's frame to world frame. This matrix takes into
 * account of the rotation, measured in yaw, pitch, and roll, and the
 * translation, measured in delta x, y, and z of the vehicle. All information
 * is extracted from the VehicleProse proto.
 */

#include "matrix_ops.c"

double time_to_theta(double time, double freq) {
    /* Time should be in seconds. */
    return (2 * pi * freq * time);
}

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

// For all functions below:
// TransformedVector = TranslationMatrix * RotationMatrix * OriginalVector;

// Need rotation (pitch, yaw) and translation matrices (varies
// based on encoding_lvl)
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
// Need only translation
Matrix lidar_to_vehicle() {
    /* TODO: get x, y, z from lidar. */
    double x;
    double y;
    double z;
    Matrix result;
    // result = general_transformation(0, 0, 0, x, y, z);
    return result;
}

// Need rotation and translation matrices
Matrix vehicle_to_world(){
    double yaw;
    double pitch;
    double roll;
    double x;
    double y;
    double z;
    // result = general_transformation(yaw, pitch, roll, x, y, z);
    // TODO
}

Point encoding_to_world(Point p) {
    // TODO
    /*
    yaw matrix:
    | cos(y) -sin(y)  0 |
    | sin(y)  cos(y)  0 |
    |   0       1     1 |

    pitch matrix:
    | cos(p)  0  sin(p) |
    |   0     1    0    |
    |-sin(p)  0  cos(p) |

    roll matrix:
    | 1    0       0    |
    | 0  cos(r) -sin(r) |
    | 0  sin(r)  cos(r) |


    translation matrix:
    | 1 0 0 X |
    | 0 1 0 Y |
    | 0 0 1 Z |
    | 0 0 0 1 |

    rotation_matrix = yaw * pitch * roll
    | cos(y)cos(p)  cos(y)sin(p)sin(r) - cos(r)sin(y)  cos(y)cos(r)sin(p) + sin(y)sin(r) |
    | cos(p)sin(y)  cos(y)cos(r) + sin(y)sin(p)sin(r)  cos(r)sin(y)sin(p) - cos(y)sin(r) |
    |   -sin(p)           cos(r) + cos(p)sin(r)              cos(p)cos(r) - sin(r)       |


    transformed_point = translation_matrix * rotation_matrix * original_point
    | cos(y)cos(p)  cos(y)sin(p)sin(r) - cos(r)sin(y)  cos(y)cos(r)sin(p) + sin(y)sin(r)   X |
    | cos(p)sin(y)  cos(y)cos(r) + sin(y)sin(p)sin(r)  cos(r)sin(y)sin(p) - cos(y)sin(r)   Y |
    |   -sin(p)           cos(r) + cos(p)sin(r)              cos(p)cos(r) - sin(r)         Z |
    |      0                        0                                   0                  1 |

    */
    Matrix point;
    point.mat[0][0] = p.x;
    point.mat[0][1] = p.y;
    point.mat[0][2] = p.z;
    point.mat[0][3] = 1;

    return Multiply(vehicle_to_world() * lidar_to_vehicle() * matrix_encoding_to_lidar() * point);
}

Matrix general_transformation(double yaw, double pitch, double roll, double x, double y, double z)
{
    Matrix general;
    general.mat[0][0] = cos(yaw)*cos(pitch);
    general.mat[0][1] = cos(yaw)*sin(pitch)*sin(roll) - cos(roll)*sin(yaw);
    general.mat[0][2] = cos(yaw)*cos(roll)*sin(pitch) - sin(yaw)*sin(roll);
    general.mat[0][3] = x;
    general.mat[1][0] = cos(pitch)*sin(yaw);
    general.mat[1][1] = cos(yaw)*cos(roll) + sin(yaw)*sin(pitch)*sin(roll);
    general.mat[1][2] = cos(roll)*sin(yaw)*sin(pitch) - cos(yaw)*sin(roll);
    general.mat[1][3] = y;
    general.mat[2][0] = -sin(pitch);
    general.mat[2][1] = cos(roll) + cos(pitch)*sin(roll);
    general.mat[2][2] = cos(pitch)*cos(roll) - sin(roll);
    general.mat[2][3] = z;
    general.mat[3][0] = 0;
    general.mat[3][1] = 0;
    general.mat[3][2] = 0;
    general.mat[3][3] = 1;

    return general;
}
