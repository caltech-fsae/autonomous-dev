#include "mapdefs.h"
#include "map.h"

int main(){
    Mapobj obj = {1,2,3, OBJ_CONE_L};
    addObj(&obj);
    return 0;
}
