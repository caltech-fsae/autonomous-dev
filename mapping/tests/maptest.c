#include "mapdefs.h"
#include "map.h"

void printMap(Map *map) {
    Vox **objs = allObjs(map);
    for (int i = 0; i < map->numObjs; i ++) {
        printf("Obj %d: %f, %f, %f\n", i, objs[i]->confs[0], objs[i]->confs[1], objs[i]->confs[2]);
    }
}

int main(){
    Map map;
    initMap(&map);

    printf("Adding 2 objects\n");
    Vox obj1 = {1,2,3, {OBJ_CONE_L, OBJ_CONE_R, OBJ_UNKNOWN}, {.5, .1, .4}};
    addObj(&map, &obj1);
    Vox obj2 = {4,5,6, {OBJ_CONE_L, OBJ_CONE_R, OBJ_UNKNOWN}, {.1, .8, .1}};
    addObj(&map, &obj2);

    printMap(&map);

    printf("Updating Object 0\n");
    obj1.confs[0] = 0.7;
    obj1.confs[1] = 0.1;
    obj1.confs[2] = 0.2;
    addObj(&map, &obj1);
    printMap(&map);

    return 0;
}
