#ifndef MAP_H
#define MAP_H

#include "mapdefs.h"
#include "object.pb-c.h"
#include <stdio.h>
#include <stdlib.h>
// memset
#include <string.h>

typedef struct Mapnode {
    int hash;
    Mapobj *obj;
    struct Mapnode *next;
} Mapnode;

typedef struct {
    int numBuckets;
    int numObjs;
    Mapnode **buckets;
} Map;

int initMap(Map *map);
void *safemalloc(size_t n);
unsigned int hash(Mapobj *obj);
int addObj(Map *map, Mapobj *obj);
Mapobj **allObjs(Map *map);

#endif /* MAP_H */
