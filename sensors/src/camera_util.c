#include <assert.h>
#include "camera_util.h"

Ray ray_for_pixel(Sensor c, Point p) { 
    Ray retRay = RAY__INIT;
    assert(validate_camera(c));

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
