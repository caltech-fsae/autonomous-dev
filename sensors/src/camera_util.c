#include <assert.h>
#include <math.h>

#include "camera_util.h"

/* 
 * Using the focal length of the camera,
 * we can use the pinhole method to compute a ray
 * originating from the camera lens to the real world
 * points that could correspond to the pixel.
 */
Ray ray_for_pixel(Sensor c, Point p) { 
    Ray retRay = RAY__INIT;
    assert(validate_camera(c));

    Ray__Parametric x = RAY__PARAMETRIC__INIT;
    Ray__Parametric y = RAY__PARAMETRIC__INIT;
    Ray__Parametric z = RAY__PARAMETRIC__INIT;

    retRay.x = &x;
    retRay.y = &y;
    retRay.z = &z;

    return retRay;
}

/*
 * Validates that the sensor c is a camera.
 * Returns 1 if the sensor is a camera, and
 * 0 otherwise.
 */
int validate_camera(Sensor c) {
    if (c.type != SENSOR__SENSOR_TYPE__CAMERA) {
        return 0;
    }

    if (!c.translation) {
        return 0;
    }

    return 1;
}

void rotateAboutAxis(Point point, int axis, float angle) {
    switch (axis) {
    case 0: // About x-axis
        point.y = (point.y * cos(angle) - point.z * sin(angle));
        point.z = (point.y * sin(angle) + point.z * cos(angle));
        break;
    case 1: // About y-axis
        point.x = (point.x * cos(angle) + point.z * sin(angle));
        point.z = (-point.x * sin(angle) + point.z * cos(angle));
        break;
    case 2: // About z-axis
        point.x = (point.x * cos(angle) - point.y * sin(angle));
        point.y = (point.x * sin(angle) + point.y * cos(angle));
        break;
    }
  
    return;
}

void translate(Point p, int x, int y, int z) {
    p.x += x;
    p.y += y;
    p.z += z;
    return;
}

/* We approximate the field of view of the camera
 * as a cone coming from the location of the camera
 * with the same orientation as the camera.
 * To determine if the point is in the FOV,
 * we translate the point so that it is evaluated
 * from the reference frame of the camera facing forwards
 * at the origin. */
int isInFOV(Point point, Sensor sensor) {
    assert(validate_camera(sensor));

    Point tempPoint;
    tempPoint.x = point.x;
    tempPoint.y = point.y;
    tempPoint.z = point.z;
    
    translate(tempPoint, -sensor.translation->x, -sensor.translation->y, -sensor.translation->z);
    
    rotateAboutAxis(tempPoint, 0, -sensor.rotation->x);
    rotateAboutAxis(tempPoint, 0, -sensor.rotation->y);
    rotateAboutAxis(tempPoint, 0, -sensor.rotation->z);
      
    // Now we have the coordinates of the point in the camera's ref frame
    // Assume that the z-axis points forward
    if (tempPoint.z < 0) { // Behind the camera
      return 0;
    }

    // Now, all we really care about is the angle between the
    // point and the z-axis.
    float magnitude = sqrt(pow(tempPoint.x, 2) + pow(tempPoint.y, 2) + pow(tempPoint.z, 2));
    float pt_cos = ((float) tempPoint.z) / magnitude;

    // Note that we can just compare the cosines, as the FOV is probably less than 180 degrees
    float min_cos = cos(sensor.camera_params->fov);
    if (pt_cos >= min_cos) {
      return 1;
    }

    return 0;
}
