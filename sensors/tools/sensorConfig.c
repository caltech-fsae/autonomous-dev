#include <stdio.h>
#include <stdlib.h>
#include "configProto.pb-c.h"

int main (int argc, const char *argv[]){
    Sensors__SensorConfig msg = SENSORS__SENSOR_CONFIG__INIT;
    void *buf;
    unsigned len;
    
    msg.has_x_pos = 1;
    msg.x_pos = 123.456;

    len = sensors__sensor_config__get_packed_size(&msg);
    printf("%d\n", len);
    buf = malloc(len);
    sensors__sensor_config__pack(&msg, buf);

    fwrite(buf, len, 1, stdout);
    printf("\n");

    free(buf);
}
