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
    double x;
    double y;
    double z;
    Objtype type;
} Mapobj;

#endif /* MAPDEFS_H */
