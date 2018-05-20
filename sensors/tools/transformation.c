#include <math.h>
#include "matrix_ops.c"

// for lidar sensor
double time_to_theta(double time, double freq) {
    /* Time should be in seconds. */
    return (2 * pi * freq * time);
}

Matrix matrix_encoding_to_lidar(double distance, double theta,
        double encoding_lvl) {    /* Calculate phi based on encoding level. */
    double phi;
    double height;
    /*
     * TODO: instead of hard coding, have a larger array of smaller 2 value
     * arrays (height and angle) and have the index from large array correspond
     * to encoding level.
    */
    Matrix result;
    /* Only transformation is from height in encoding. */
    result.mat[0][0] = sin(theta) * cos(phi);
    result.mat[0][1] = cos(theta) * cos(phi);
    result.mat[0][2] = -cos(phi);
    result.mat[0][3] = 0;
    result.mat[1][0] = sin(theta) * sin(phi);
    result.mat[1][1] = cos(theta) * sin(phi);
    result.mat[1][2] = cos(phi);
    result.mat[1][3] = 0;
    result.mat[2][0] = cos(theta);
    result.mat[2][1] = -sin(phi);
    result.mat[2][2] = 0;
    result.mat[2][3] = height;
    result.mat[3][0] = 0;
    result.mat[3][1] = 0;
    result.mat[3][2] = 0;
    result.mat[3][3] = 1;
    return result;
}

/* Matrix transformation position from lidar to vehicle. */
Matrix lidar_to_vehicle() {
    /* TODO: get x, y, z from lidar. */
    double x;
    double y;
    double z;
    result.mat[0][0] = 1;
    result.mat[0][1] = 0;
    result.mat[0][2] = 0;
    result.mat[0][3] = x;
    result.mat[1][0] = 0;
    result.mat[1][1] = 1;
    result.mat[1][2] = 0;
    result.mat[1][3] = y;
    result.mat[2][0] = 0;
    result.mat[2][1] = 0;
    result.mat[2][2] = 1;
    result.mat[2][3] = z;
    result.mat[3][0] = 0;
    result.mat[3][1] = 0;
    result.mat[3][2] = 0;
    result.mat[3][3] = 1;
}

// Need rotation (yaw, maybe pitch) and translation matrices
Matrix vehicle_to_world(){
    // TODO
}

Point encoding_to_world() {
    // TODO
    /*
    yaw matrix:
    | cos(x) -sin(x)  0 |
    | sin(x)  cos(x)  0 |
    |   0       1     1 |

    pitch matrix:
    | cos(y)  0  sin(y) |
    |   0     1    0    |
    |-sin(y)  0  cos(y) |

    roll matrix:
    | 1    0       0    |
    | 0  cos(z) -sin(z) |
    | 0  sin(z)  cos(z) |


    translation matrix:
    | 1 0 0 X |
    | 0 1 0 Y |
    | 0 0 1 Z |
    | 0 0 0 1 |

    rotation_matrix = yaw * pitch * roll
    | cos(x)cos(y)  cos(x)sin(y)sin(z) - cos(z)sin(x)  cos(x)cos(z)sin(y) + sin(x)sin(z) |
    | cos(y)sin(x)  cos(x)cos(z) + sin(x)sin(y)sin(z)  cos(z)sin(x)sin(y) - cos(x)sin(z) |
    |   -sin(y)           cos(z) + cos(y)sin(z)              cos(y)cos(z) - sin(z)       |

    
    transformed_point = translation_matrix * rotation_matrix * original_point
    | cos(x)cos(y)  cos(x)sin(y)sin(z) - cos(z)sin(x)  cos(x)cos(z)sin(y) + sin(x)sin(z)   X |
    | cos(y)sin(x)  cos(x)cos(z) + sin(x)sin(y)sin(z)  cos(z)sin(x)sin(y) - cos(x)sin(z)   Y |
    |   -sin(y)           cos(z) + cos(y)sin(z)              cos(y)cos(z) - sin(z)         Z |
    |      0                        0                                   0                  1 |
    
    */
}
