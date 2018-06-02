#ifndef MAP_H
#define MAP_H

#include "mapdefs.h"
#include "voxel.pb-c.h"
#include <stdio.h>
#include <stdlib.h>
// memset
#include <string.h>

// Wrapper around a Vox struct,
// contains additional information for inserting into map
// hash, for identifying the voxel's position
// next pointer, for chaining Mapnodes together into linked lists
typedef struct Mapnode {
    int hash;
    Vox *vox;
    struct Mapnode *next;
} Mapnode;

// Map itself
// Contains info about number of "buckets" the hashmap uses
// as well as a count of total number of voxels set in the map
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
