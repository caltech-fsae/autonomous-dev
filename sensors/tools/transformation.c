#include "matrix_ops.c"
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

// Also, need to fix matrix pointer stuff. 


double time_to_phi(double time, double freq) {
    /* 
        Time should be in seconds. 
        Freq is from lidar in sensors.proto.
    */
    return (2 * M_PI * freq * time);
}

/* Multiply by r, theta, phi. Using physics spherical coordinates.*/
Matrix matrix_spherical_to_cartesian(double phi, double theta, double r) {
    /* 
     * Theta, phi are in radians. Using physics spherical coordinates.
     * Phi is from time_to_phi.
     * Theta is from encoding array.
     * R is from lidar sensor.
     * Pad with zeroes to turn into a 4x4. 
     */
    // translation matrix
    Matrix sphcart;
    sphcart.mat[0][0] = 1;
    sphcart.mat[0][1] = 0;
    sphcart.mat[0][2] = 0;
    sphcart.mat[0][3] = r * sin(theta) * cos(phi);
    sphcart.mat[1][0] = 0;
    sphcart.mat[1][1] = 1;
    sphcart.mat[1][2] = 0;
    sphcart.mat[1][3] = r * sin(theta) * sin (phi);
    sphcart.mat[2][0] = 0;
    sphcart.mat[2][1] = 0;
    sphcart.mat[2][2] = 1;
    sphcart.mat[2][3] = r * cos(theta);
    sphcart.mat[3][0] = 0;
    sphcart.mat[3][1] = 0;
    sphcart.mat[3][2] = 0;
    sphcart.mat[3][3] = 1;
    return sphcart;
}

Matrix point_to_encoding(double phi, double theta, double r){
    /*
     * phi is from time_to_phi. non-static.
     * theta is from encoding_lvl array. static for each encoding_lvl.
     * r is from lidar. non-static.
     */

    return matrix_spherical_to_cartesian(phi, theta, r);
}

Matrix encoding_to_lidar(double x, double y, double z) {
    /* 
     * x, y, z are the translation from the encoding to the sensor.
     * x, y are static and the same value for each encoding_lvl.
     * z (height) is from encoding_lvl array, static for each encoding_lvl. 
     */

    // transformation matrix from encoding to lidar
    // only includes x, y, z; doesn't include phi, theta, r
    Matrix enc_lid;
    enc_lid.mat[0][0] = 1;
    enc_lid.mat[0][1] = 0;
    enc_lid.mat[0][2] = 0;
    enc_lid.mat[0][3] = x;
    enc_lid.mat[1][0] = 0;
    enc_lid.mat[1][1] = 1;
    enc_lid.mat[1][2] = 0;
    enc_lid.mat[1][3] = y;
    enc_lid.mat[2][0] = 0;
    enc_lid.mat[2][1] = 0;
    enc_lid.mat[2][2] = 1;
    enc_lid.mat[2][3] = z;
    enc_lid.mat[3][0] = 0;
    enc_lid.mat[3][1] = 0;
    enc_lid.mat[3][2] = 0;
    enc_lid.mat[3][3] = 1;

    return enc_lid;
}

/* Matrix transformation position from lidar to vehicle. */
// Need only translation
Matrix lidar_to_vehicle(double x, double y, double z) {
    /* 
     * x, y, z are the translation from the lidar to the vehicle.
     * x, y, z are static. 
     */

    Matrix lid_veh;
    lid_veh.mat[0][0] = 1;
    lid_veh.mat[0][1] = 0;
    lid_veh.mat[0][2] = 0;
    lid_veh.mat[0][3] = x;
    lid_veh.mat[1][0] = 0;
    lid_veh.mat[1][1] = 1;
    lid_veh.mat[1][2] = 0;
    lid_veh.mat[1][3] = y;
    lid_veh.mat[2][0] = 0;
    lid_veh.mat[2][1] = 0;
    lid_veh.mat[2][2] = 1;
    lid_veh.mat[2][3] = z;
    lid_veh.mat[3][0] = 0;
    lid_veh.mat[3][1] = 0;
    lid_veh.mat[3][2] = 0;
    lid_veh.mat[3][3] = 1;
    return lid_veh;
}

// Need rotation and translation matrices
Matrix vehicle_to_world(double yaw, double pitch, double roll, double x, double y, double z){
    /*
     * yaw, pitch, roll, x, y, z are passed in from car. all non-static.
     * ideally, if on a flat track, roll and pitch should be 0.
     */

    return general_transformation(yaw, pitch, roll, x, y, z);
}

Point encoding_to_world(Point p, time, freq, encoding_lvl_num, r, veh_yaw, veh_pitch, veh_roll, veh_x, veh_y, veh_z) {
    Matrix point;
    // TODO. This is definitely not how you get x, y, z from a point.
    point.mat[0][0] = p.x;
    point.mat[0][1] = p.y;
    point.mat[0][2] = p.z;
    point.mat[0][3] = 1;   // 1 if transforming pt, 0 if transforming vector


    /* point_to_encoding:
     * takes in time, freq, encoding_lvl_num and r.
     */
    double phi = time_to_phi(time, freq);
    double theta = encoding_lvl[encoding_lvl_num][1];
    // r directly passed to function

    /* encoding_to_lidar:
     * gets encoding_x, encoding_y from lidar in sensors.proto.
     * takes in encoding_lvl_num.
     */
    // TODO. This is definitely not how you get encoding_x, encoding_y from lidar.
    double encoding_x = lidar.encoding_x;
    double encoding_y = lidar.encoding_y;
    double encoding_z = encoding_lvl[encoding_lvl_num][0];

    /* lidar_to_vehicle:
     * gets lidar_x, lidar_y, lidar_z from lidar in sensors.proto.
     */
    // TODO. This is definitely not how you get lidar_x, lidar_y, lidar_z from lidar.
    double lidar_x = lidar.lidar_x;
    double lidar_y = lidar.lidar_y;
    double lidar_z = lidar.lidar_z;

    /* vehicle_to_world:
     * takes in veh_yaw, veh_pitch, veh_roll, veh_x, veh_y, veh_z
     */
    // all variables directly passed to function

    Matrix final;
    final = Multiply(vehicle_to_world(veh_yaw, veh_pitch, veh_roll, veh_x, veh_y, veh_z) * 
                    lidar_to_vehicle(lidar_x, lidar_y, lidar_z) * 
                    encoding_to_lidar(encoding_x, encoding_y, encoding_z) * 
                    point_to_encoding(phi, theta, r) * 
                    point);


    // TODO. This is definitely not how you declare a new point. Or set values in the point.
    Point new_point = new Point;
    point.x = final[0];
    point.y = final[1];
    point.z = final[2];
}

Matrix general_transformation(double yaw, double pitch, double roll, double x, double y, double z)
{
    // TransformedVector = TranslationMatrix * RotationMatrix * OriginalVector;
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
    Matrix general;
    general.mat[0][0] = cos(yaw)*cos(pitch);
    general.mat[0][1] = cos(yaw)*sin(pitch)*sin(roll) - cos(roll)*siny(aw);
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