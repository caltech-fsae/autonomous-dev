#include <stdio.h>
#include <stdlib.h>
#include "sensors.pb-c.h"

/*
 * Barebones program that writes a Sensor proto with some arbitrary data.
 * Outputs data on stdout
 * Outputs length of buffer on stderr
 */

int main (int argc, const char *argv[]){
    Sensor mainMsg = SENSOR__INIT;
    Sensor__Translate transMsg = SENSOR__TRANSLATE__INIT;
    Sensor__Rotate rotMsg = SENSOR__ROTATE__INIT;
    Sensor__AccelParams accelMsg = SENSOR__ACCEL_PARAMS__INIT;

    void *buf;
    unsigned len;
    
    transMsg.has_x = 1;
    transMsg.has_y = 1;
    transMsg.has_z = 1;
    transMsg.x = -1.;
    transMsg.y = 1.;
    transMsg.z = 2.;

    rotMsg.has_x = 1;
    rotMsg.has_y = 1;
    rotMsg.has_z = 1;
    rotMsg.x = -0.5;
    rotMsg.y = 0.5;
    rotMsg.z = -1.5;

    accelMsg.accel = 9.8;

    mainMsg.type = SENSOR__SENSOR_TYPE__ACCELERATION;
    mainMsg.translation = &transMsg;
    mainMsg.rotation = &rotMsg;
    mainMsg.accel_params = &accelMsg;

    len = sensor__get_packed_size(&mainMsg);
    fprintf(stderr, "%d\n", len);
    buf = malloc(len);
    sensor__pack(&mainMsg, buf);

    fwrite(buf, len, 1, stdout);

    free(buf);
}
