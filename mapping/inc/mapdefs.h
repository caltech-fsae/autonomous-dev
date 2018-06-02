/**
 * Common definitions for anything using mapping
 */

#ifndef MAPDEFS_H
#define MAPDEFS_H

// Types of objects in the map
enum objtype {
    OBJ_CONE_L,
    OBJ_CONE_R,
    OBJ_UNKNOWN,
    OBJ_NUMTYPES
};
typedef enum objtype Objtype;

// An individual voxel in the map
// Holds its position, and up to 3 object types/confidences.
typedef struct {
    int x;
    int y;
    int z;
    Objtype types[3];
    double confs[3];
} Vox;

#endif /* MAPDEFS_H */
