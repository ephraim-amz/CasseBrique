#include "Map.h"

int main(int argc, char** argv) {
    int rows = 2;
    int columns = 3;
    Map *m = createMap(rows,columns);

    printf("%d ", isFree(m, 0, 0));
    freeMap(m, rows);


    printf("%c\n", 176);

    int map1[][7] = {
            {2,2,2,2,2,2,2},
            {2,3,7,1,0,5,2},
            {2,0,2,1,2,9,2},
            {2,1,1,1,1,1,2},
            {2,10,2,1,2,0,2},
            {2,6,0,1,8,4,2},
            {2,2,2,2,2,2,2}
    };

    displayMap(7, 7, map1);

    return 0;
}
