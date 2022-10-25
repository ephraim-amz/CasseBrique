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

Map *createMap(int nbLignes, int nbColonnes, int nbVies, int nbMaxPlayer, int nbBombeBase, float txLoot){

    Map *m = malloc(sizeof(Map));
    *m = (Map){
            .tab = createTab(nbLignes, nbColonnes),
            .nbLignes = nbLignes,
            .nbColonnes = nbColonnes,
            .nbVies = nbVies,
            .nbMaxPlayer = nbMaxPlayer,
            .nbBombeBase = nbBombeBase,
            .txLoot = txLoot
    };
    for (int i = 0; i < nbMaxPlayer; ++i) {
        m->joueurs[i] = createJoueur(nbVies, nbBombeBase, nbBombeBase, 2);
    }

    return m;
}

bool isFree(Map *map, int x, int y){
    return map->tab[x][y] == 0;
}

bool isAUnbreakeableWall(Map *map, int x, int y){
    return map->tab[x][y] == 2;
}

bool isARegularWall(Map *map, int x, int y){
    return map->tab[x][y] == 1;
}

bool isAWall(Map *map, int x, int y){
    return isARegularWall(map, x, y) || isAUnbreakeableWall(map, x, y);
}

bool isAPlayer(Map *map, int x, int y){
    return map->tab[x][y] >= 1000;
}
void freeMap(Map *m, int r){
    freeTab(m->tab, r);
    free(m);
}

void red(){
    printf("\033[1;31m");
}
void yellow(){
    printf("\033[1;33m");
}
void green(){
    printf("\033[1;32m");
}
void cyan(){
    printf("\033[1;36m");
}
void blue(){
    printf("\033[1;34m");
}
void purple(){
    printf("\033[1;35m");
}
void resetColor (){
    printf("\033[0m");
}

/* Creation de plateaux de jeu
// Légende :
// 0 : vide                       (code : 255)
// 1 : mur destructible         ░ (code : 176)
// 2 : mur infranchissable      █ (code : 219)
// 3 -> 9 : powerups (à définir)
// 10 -> 99 : bombes            ó (code : 162)
// 100 : joueur 1               1 (code : 49)
// 200 : joueur 2               2 (code : 50)
// 300 : joueur 3               3 (code : 51)
// 400 : joueur 4               4 (code : 52)
// Tout ce qui est entre 10 et 99 est une bombe
// Le chiffre des dizaines représente la puissance de la bombe
// Le chiffre des unités représente le compteur avant explosion
// Quand le compteur passe à 0, la bombe explose
// Après chaque mouvement, le compteur est décrémenté
*/
void displayMap(int r, int c, int map[r][c]){
    int i, j;
    int graphismesHD[] = {255, 176, 219, 162};

    for(i = 0; i < r; ++i){
        for (j = 0; j < c; ++j){
            int elementInTheCase = map[i][j];

            // espaces entre les cases
            if (i == 0 || i == r-1){
                if(j != c-1){
                    printf("%c", 219);
                }
            } else if(j > 0){
                printf(" ");
            }

            // cases
            if(elementInTheCase >= 100){
                elementInTheCase /= 100;
                switch (elementInTheCase) {
                    case 1 :
                        red();
                        break;
                    case 2 :
                        blue();
                        break;
                    case 3 :
                        green();
                        break;
                    case 4 :
                        yellow();
                        break;
                }
                printf("%c", elementInTheCase + 48);      // Joueur
                resetColor();
            } else if (elementInTheCase >= 10 ){
                printf("%c", graphismesHD[3]);      // Bombe
            } else {
                printf("%c", graphismesHD[elementInTheCase]); // murs + boite + vide + powerup
            }
        }
        printf("\n");
    }
}
