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
            .x = rand() % map->rows,
            .y = rand() % map->columns
    };

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

bool isAWall(Mur *mur, int x, int y){
    return mur->x != x && mur->y != y;
}

void freeMap(Map *m, int r){
    freeTab(m->tab, r);
    free(m);
}


/* Creation de plateaux de jeu
// premiere map test : 7x7 :
// 0 : vide                     (255)
// 1 : mur destructible         (176)
// 2 : mur infranchissable      (219)
// 3 : J1   (80)
// 4 : J2   (80)
// 5 : J3   (80)
// 6 : J4   (80)
// 7 : bombe J1     (ò)
// 8 : bombe J2
// 9 : bombe J3
// 10 : bombe J4
*/
void displayMap(int r, int c, int map[r][c]){
    int i, j;
    int graphismesHD[] = {255, 176, 219, 80, 162};

    for(i = 0; i < r; ++i){
        for (j = 0; j < c; ++j){
            int sprite = map[i][j];

            if (i == 0 ||i == r-1){
                if(j != c-1){
                    printf("%c", 219);
                }
            } else if(j > 0){
                printf(" ");
            }

            if(sprite > 2 && sprite < 7){
                printf("%c", graphismesHD[3]);
            } else if (sprite > 6 ){
                printf("%c", graphismesHD[4]);
            } else {
                printf("%c", graphismesHD[sprite]);
            }
        }
        printf("\n");
    }
}
