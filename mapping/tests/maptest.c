#include "mapdefs.h"
#include "map.h"

int main(){
    Map map;
    initMap(&map);

    Mapobj obj = {1,2,3, OBJ_CONE_L};
    addObj(&map, &obj);
    obj.type = OBJ_CONE_R;
    addObj(&map, &obj);

    Mapobj **objs = allObjs(&map);
    for (int i = 0; i < map.numObjs; i ++) {
        printf("Obj %d: %d \n", i, objs[i]->type);
    }
    return 0;
}
