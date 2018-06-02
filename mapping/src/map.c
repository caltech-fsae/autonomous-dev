#include "map.h"


int initMap(Map *map) {
    map->numBuckets = 32;
    map->numObjs = 0;
    map->buckets = safemalloc(map->numBuckets * sizeof(Vox*));
    memset(map->buckets, 0, map->numBuckets * sizeof(Vox*));
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

unsigned int hash(Vox *v) {
    return (unsigned int)(v->x) 
                * (unsigned int)(v->y) 
                * (unsigned int)(v->z);
}

int addObj(Map *map, Vox *vox) {
    unsigned int h = hash(vox);
    unsigned int bucket = h % map->numBuckets;

    Mapnode *next = map->buckets[bucket];
    while (next != NULL) {
        if (vox->x == next->vox->x && vox->y == next->vox->y && vox->z == next->vox->z) {
            next->vox->confs[0] = vox->confs[0];
            next->vox->confs[1] = vox->confs[1];
            next->vox->confs[2] = vox->confs[2];
            return 0;
        }
        next = next->next;
    }

    Mapnode *node = safemalloc(sizeof(Mapnode));
    node->hash = h;
    node->vox = vox;
    node->next = map->buckets[bucket];
    map->buckets[bucket] = node;
    map->numObjs ++;
    return 0;
}

Vox **allObjs(Map *map) {
    Vox **voxels = safemalloc(sizeof(Vox*) * map->numObjs);
    int count = 0;
    for (int i = 0; i < map->numBuckets; i ++) {
        Mapnode *next = map->buckets[i];
        while (next != NULL) {
            voxels[count] = next->vox;
            count ++;
            next = next->next;
        }
    }
    return voxels;
}

Voxel toProto(Vox *vox) {
    Voxel msg = VOXEL__INIT;
    msg.x = vox->x;
    msg.y = vox->y;
    msg.z = vox->z;
    return msg;
}
