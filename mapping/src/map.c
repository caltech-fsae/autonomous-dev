#include "map.h"


// Initializes a newly created map
int initMap(Map *map) {
    map->numBuckets = 32;
    map->numObjs = 0;
    map->buckets = safemalloc(map->numBuckets * sizeof(Vox*));
    return 0;
}
// TODO- deinitialize/delete map

// Mallocs block and checks for error, and zeros out memory
void *safemalloc(size_t n) {
    void *ptr = malloc(n);
    if (ptr == NULL) {
        fprintf(stderr, "Couldn't malloc %ld", n);
        exit(1);
    }
    memset(ptr, 0, n);
    return ptr;
}

unsigned int hash(Vox *v) {
    // TODO- Actually good hash function
    // Want positive output
    return (unsigned int)(v->x) 
                * (unsigned int)(v->y) 
                * (unsigned int)(v->z);
}

// Sets a voxel in a map
// Updates the voxel if it exists,
// or adds it as a new voxel if it does not.
int addObj(Map *map, Vox *vox) {
    unsigned int h = hash(vox);
    unsigned int bucket = h % map->numBuckets;

    Mapnode *next = map->buckets[bucket];
    // Iterate all voxels in this bucket
    while (next != NULL) {
        // See if we are setting a voxel that already exists
        // If voxel exists, update it
        if (vox->x == next->vox->x && vox->y == next->vox->y && vox->z == next->vox->z) {
            // TODO- Proper update based on object types
            // Should update vox based on existing values,
            // delete existing voxel,
            // and replace with vox.
            next->vox->confs[0] = vox->confs[0];
            next->vox->confs[1] = vox->confs[1];
            next->vox->confs[2] = vox->confs[2];
            return 0;
        }
        next = next->next;
    }

    // Voxel does not exist, allocate new one
    Mapnode *node = safemalloc(sizeof(Mapnode));
    node->hash = h;
    node->vox = vox;
    // Insert at front of linked list
    node->next = map->buckets[bucket];
    map->buckets[bucket] = node;
    map->numObjs ++;
    return 0;
}

// Returns array of pointers to all voxels in a given map
Vox **allObjs(Map *map) {
    Vox **voxels = safemalloc(sizeof(Vox*) * map->numObjs);
    // Count of voxels that have been iterated through
    int count = 0;
    // For each bucket
    for (int i = 0; i < map->numBuckets; i ++) {
        Mapnode *next = map->buckets[i];
        // For each voxel in the bucket
        while (next != NULL) {
            voxels[count] = next->vox;
            count ++;
            next = next->next;
        }
    }
    return voxels;
}

// Converts a map Vox to a protobuf message Voxel
Voxel voxToProto(Vox *vox) {
    Voxel msg = VOXEL__INIT;
    msg.x = vox->x;
    msg.y = vox->y;
    msg.z = vox->z;
    // TODO- objects and confidences
    return msg;
}
