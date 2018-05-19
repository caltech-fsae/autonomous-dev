#include "map.h"


int addObj(Mapobj *obj) {
    printf("TODO: Add object %d\n", obj->type);
    return 0;
}

Object toProto(Mapobj *obj) {
    Object msg = OBJECT__INIT;
    msg.x = obj->x;
    msg.y = obj->y;
    msg.z = obj->z;
    msg.type = obj->type;
    return msg;
}

Mapobj *toMapobj(Object *obj) {
