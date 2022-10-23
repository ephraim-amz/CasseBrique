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
            {2,100,17,1,0,300,2},
            {2,0,2,1,2,39,2},
            {2,1,1,1,1,1,2},
            {2,42,2,1,2,0,2},
            {2,400,0,1,26,200,2},
            {2,2,2,2,2,2,2}
    };

    displayMap(7, 7, map1);

    return 0;
}
