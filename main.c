#include "Map.h"

int main(int argc, char** argv) {
    int rows = 2;
    int columns = 3;
    Map *m = createMap(rows,columns);

    printf("%d ", isFree(m, 0, 0));
    freeMap(m, rows);
    return 0;
}
