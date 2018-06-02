#ifndef MAP_H
#define MAP_H

#include "mapdefs.h"
#include "voxel.pb-c.h"
#include <stdio.h>
#include <stdlib.h>
// memset
#include <string.h>

typedef struct Mapnode {
    int hash;
    Vox *vox;
    struct Mapnode *next;
} Mapnode;

typedef struct {
    int numBuckets;
    int numObjs;
    Mapnode **buckets;
} Map;

int initMap(Map *map);
void *safemalloc(size_t n);
unsigned int hash(Vox *v);
int addObj(Map *map, Vox *vox);
Vox **allObjs(Map *map);

#endif /* MAP_H */
