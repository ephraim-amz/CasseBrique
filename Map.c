#include "Map.h"

int **createTab(int rows, int columns){
    int **tab = malloc(sizeof(int*) * rows);
    for (int i = 0; i < columns; ++i) {
        tab[i] = calloc(columns, sizeof(int));
    }
    return tab;
}


void printTab(int** tab, int r, int c){
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++) {
            // tab[i][j] = ++count;
            printf("%d ", tab[i][j]);
            if(j == r){
                printf("\n");
            }
        }
    }
}

Map *createMap(int rows, int columns){
    Map *m = malloc(sizeof(Map));
    *m = (Map){
            .tab = createTab(rows, columns),
            .rows = rows,
            .columns = columns,
    };
    return m;
}

Mur *createMur(Map *map){
    Mur *m = malloc(sizeof(Mur));

    *m = (Mur){
            .x = NULL,
            .y = NULL
    };
    srand(map->rows);
    srand(map->columns);
    return m;
}

void freeTab(int **tab, int r){
    for (int i = 0; i < r; i++){
        free(tab[i]);
    }
    free(tab);
}

bool isFree(Map *m, int x, int y){
    return m->tab[x][y] == 0;
}

void freeMap(Map *m, int r){
    freeTab(m->tab, r);
    free(m);
}