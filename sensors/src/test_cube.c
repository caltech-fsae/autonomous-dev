#include <math.h>

#include "test_cube.h"

int test_cube(int width, int height, int length, Point center, Sensor s) {
    int count = 0;
    Point corner;

    corner.x = center + width/2;
    corner.y = center + height/2;
    corner.z = center + length/2;
    count += isInFOV(corner, s);

    corner.x = center + width/2;
    corner.y = center + height/2;
    corner.z = center - length/2;
    count += isInFOV(corner, s);

    corner.x = center + width/2;
    corner.y = center - height/2;
    corner.z = center + length/2;
    count += isInFOV(corner, s);

    corner.x = center + width/2;
    corner.y = center - height/2;
    corner.z = center - length/2;
    count += isInFOV(corner, s);

    corner.x = center - width/2;
    corner.y = center + height/2;
    corner.z = center + length/2;
    count += isInFOV(corner, s);

    corner.x = center - width/2;
    corner.y = center + height/2;
    corner.z = center - length/2;
    count += isInFOV(corner, s);

    corner.x = center + width/2;
    corner.y = center - height/2;
    corner.z = center + length/2;
    count += isInFOV(corner, s);

    corner.x = center + width/2;
    corner.y = center - height/2;
    corner.z = center - length/2;
    count += isInFOV(corner, s);

    if (count == 8) {
        return 1;
    }
    return 0;
}
