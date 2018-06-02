/**
 * Common definitions for anything using mapping
 */

#ifndef MAPDEFS_H
#define MAPDEFS_H

enum objtype {
    OBJ_CONE_L,
    OBJ_CONE_R,
    OBJ_UNKNOWN,
    OBJ_NUMTYPES
};
typedef enum objtype Objtype;

typedef struct {
    int x;
    int y;
    int z;
    Objtype types[3];
    double confs[3];
} Vox;

#endif /* MAPDEFS_H */
