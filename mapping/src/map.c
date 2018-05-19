#include "map.h"


int initMap(Map *map) {
    map->numBuckets = 32;
    map->numObjs = 0;
    map->buckets = safemalloc(map->numBuckets * sizeof(Mapobj*));
    memset(map->buckets, 0, map->numBuckets * sizeof(Mapobj*));
    return 0;
}

void *safemalloc(size_t n) {
    void *ptr = malloc(n);
    if (ptr == NULL) {
        fprintf(stderr, "Couldn't malloc %ld", n);
        exit(1);
    }
    return ptr;
}

unsigned int hash(Mapobj *obj) {
    return (unsigned int)(obj->x) 
                * (unsigned int)(obj->y) 
                * (unsigned int)(obj->z);
}

int addObj(Map *map, Mapobj *obj) {
    unsigned int h = hash(obj);
    unsigned int bucket = h % map->numBuckets;

    Mapnode *node = safemalloc(sizeof(Mapnode));
    node->hash = h;
    node->obj = obj;
    node->next = map->buckets[bucket];
    map->buckets[bucket] = node;
    map->numObjs ++;
    return 0;
}

Mapobj **allObjs(Map *map) {
    Mapobj **objs = safemalloc(sizeof(Mapobj*) * map->numObjs);
    int objCount = 0;
    for (int i = 0; i < map->numBuckets; i ++) {
        Mapnode *next = map->buckets[i];
        while (next != NULL) {
            objs[objCount] = next->obj;
            objCount ++;
            next = next->next;
        }
    }
    return objs;
}

Object toProto(Mapobj *obj) {
    Object msg = OBJECT__INIT;
    msg.x = obj->x;
    msg.y = obj->y;
    msg.z = obj->z;
    msg.type = obj->type;
    return msg;
}

//Mapobj *toMapobj(Object *obj) {
