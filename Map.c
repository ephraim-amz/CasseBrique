#include "Joueur.h"
#include "Map.h"

int **createTab(int rows, int columns) {
    int **tab = malloc(sizeof(int *) * rows);
    for (int i = 0; i < columns; ++i) {
        tab[i] = malloc(sizeof(int) * columns);
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            tab[i][j] = 0;
        }
    }
    return tab;
}

void printTab(int **tab, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            // tab[i][j] = ++count;
            printf("%d ", tab[i][j]);
            if (j == c - 1) {
                printf("\n");
            }
        }
    }
}

Map *createMap(int nbLignes, int nbColonnes, int nbVies, int nbMaxPlayer, int nbBombeBase, float txLoot) {

    Map *m = malloc(sizeof(Map));
    *m = (Map) {
            .tab = createTab(nbLignes, nbColonnes),
            .nbLignes = nbLignes,
            .nbColonnes = nbColonnes,
            .nbVies = nbVies,
            .nbMaxPlayer = nbMaxPlayer,
            .nbBombeBase = nbBombeBase,
            .txLoot = txLoot
    };
    m->joueurs = malloc(sizeof(Joueur) * nbMaxPlayer);
    for (int i = 0; i < nbMaxPlayer; ++i) {
        m->joueurs[i] = createJoueur(nbVies, nbBombeBase, nbBombeBase, 2, i);
    }

    return m;
}

FILE *loadFile(char *filename) {
    FILE *f;
    errno_t err = fopen_s(&f, filename, "r");

    if (err != 0) {
        perror("Le fichier n'a pas pu être chargé\n");
        exit(-1);
    } else {
        //printf("Le fichier a pu etre charge\n");
        return f;
    }
}


int *getInfos(char *filename) {
    FILE *mapFile = loadFile(filename);
    char line[128];
    int cpt = 0;
    long nbBombes;
    long nbLignes, nbColonnes;
    int nbPlayers = 0;
    char *endPtr;
    while (fgets(line, sizeof(line), mapFile) != NULL) {
        if (cpt == 0) {
            char *p;
            nbBombes = strtol(strtok_s(line, "\n", &p), &p, 10);
        } else if (cpt == 1) {
            char *e;
            int spaceIndex;
            e = strchr(line, ' ');
            spaceIndex = (int) (e - line);
            char nbC[spaceIndex - 1];
            int lenCol = strlen(line);
            char nbL[lenCol];


            for (int i = 0; i < spaceIndex; ++i) {
                nbC[i] = line[i];
            }

            int cptL = 0;
            for (int i = spaceIndex + 1; i < lenCol; ++i) {
                if (line[i] != '\n') {
                    nbL[cptL] = line[i];
                    cptL++;
                } else {
                    break;
                }
            }

            nbLignes = strtol(nbL, &endPtr, 10);
            nbColonnes = strtol(nbC, &endPtr, 10);

        } else {
            for (int i = 0; i < strlen(line) - 1; ++i) {
                if (line[i] == 'p') {
                    nbPlayers++;
                }
            }
        }

        cpt++;
    }

    int *infos = malloc(sizeof(int) * 4);
    infos[0] = nbBombes;
    infos[1] = (int) nbLignes;
    infos[2] = (int) nbColonnes;
    infos[3] = nbPlayers;
    fclose(mapFile);
    return infos;
}

Map *createMapViaFile(char *filename) {
    FILE *mapFile = loadFile(filename);
    int *infos = getInfos(filename);
    int nbBombes = infos[0];
    int nbLignes = infos[1];
    int nbColonnes = infos[2];
    int nbPlayers = infos[3];
    Map *map = createMap(nbLignes, nbColonnes, 2, nbPlayers, nbBombes, 0.);
    int col = 0;
    int row = 0;
    int player = 0;
    char c2;
    while ((c2 = fgetc(mapFile)) != EOF) {
        col++;
        if (c2 == '\n' || c2 == '\0') {
            row++;
            col = 0;
        }
        if (c2 == 'm') {
            /*
            int tempr = row-2;
            int tempc = col-1;
            printf("Mur destructible cree en %d %d\n", tempr, tempc);
            // map[row][col] = 0;
             */
            map->tab[row - 2][col - 1] = 1;
        }
        if (c2 == 'x') {
            /*
            int tempr = row-2;
            int tempc = col-1;
            printf("Mur indestructible cree en %d %d\n", tempr, tempc);
             */
            map->tab[row - 2][col - 1] = 2;
        }
        if (c2 == 'p') {

            int tempr = row - 2;
            int tempc = col - 1;
            player += 1000;
            //printf("Joueur numéro %d cree en %d %d\n", player, tempr, tempc);

            map->tab[row - 2][col - 1] = player;
        }
        if (c2 == ' ' && row >= 2) {
            /*
            int tempr = row-2;
            int tempc = col-1;
            printf("Espace libre cree en %d %d\n", tempr, tempc);
             */
            map->tab[row][col - 1] = 0;
        }

    }

    // printTab(map->tab, map->nbLignes, map->nbColonnes);
    fclose(mapFile);
    free(infos);
    return map;
}

void freeTab(int **tab, int r) {
    for (int i = 0; i < r; i++) {
        free(tab[i]);
    }
    free(tab);
}

bool isFree(Map *map, int x, int y) {
    return map->tab[x][y] == 0;
}

bool isAUnbreakeableWall(Map *map, int x, int y) {
    return map->tab[x][y] == 2;
}

bool isARegularWall(Map *map, int x, int y) {
    return map->tab[x][y] == 1;
}

bool isAWall(Map *map, int x, int y) {
    return isARegularWall(map, x, y) || isAUnbreakeableWall(map, x, y);
}

bool isAPlayer(Map *map, int x, int y) {
    return map->tab[x][y] >= 1000;
}

void freeMap(Map *m, int r) {
    freeTab(m->tab, r);
    free(m);
}

void red() {
    printf("\033[1;31m");
}

void yellow() {
    printf("\033[1;33m");
}

void green() {
    printf("\033[1;32m");
}

void cyan() {
    printf("\033[1;36m");
}

void blue() {
    printf("\033[1;34m");
}

void black() {
    printf("\033[0;30m");
}

void purple() {
    printf("\033[1;35m");
}

void resetColor() {
    printf("\033[0m");
}

/* Creation de plateaux de jeu
// Légende :
// 0 : vide                       (code : 255)
// 1 : mur destructible         ░ (code : 176)
// 2 : mur infranchissable      █ (code : 219)
// 3 -> 9 : powerups (à définir)
// 110 -> 199 : bombes           ó (code : 162)
// 1000 : joueur 1               1 (code : 49)
// 2000 : joueur 2               2 (code : 50)
// 3000 : joueur 3               3 (code : 51)
// 4000 : joueur 4               4 (code : 52)
// ex : joueur 2 vient de placer une bombe de puissance 3 qui explosera dans 8 tours de jeu
// --> 2000 pour le joueur
// --> 200 pour le joueur qui a placé la bombe
// --> 30 pour la puissance de la bombe
// --> 8 pour le timer
// = 2238
// Tout ce qui est entre 10 et 99 est une bombe
// Le chiffre des dizaines représente la puissance de la bombe
// Le chiffre des unités représente le compteur avant explosion
// Quand le compteur passe à 0, la bombe explose
// Après chaque mouvement, le compteur est décrémenté
*/
void displayMap(int r, int c, int **map) {
    int i, j;
    int graphismesHD[] = {255, 176, 219, 162};

    for (i = 0; i < r; ++i) {
        for (j = 0; j < c; ++j) {
            int elementInTheCase = map[i][j];

            // espaces entre les cases
            if (i == 0 || i == r - 1) {
                if (j != c - 1) {
                    printf("%c", 219);
                }
            } else if (j > 0) {
                printf(" ");
            }

            // cases
            if (elementInTheCase >= 1000) {
                elementInTheCase /= 1000;
                /*switch (elementInTheCase) {
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
                }*/
                printf("%c", elementInTheCase + 48);      // Joueur
                //resetColor();
            } else if (elementInTheCase >= 10) {
                printf("%c", graphismesHD[3]);      // Bombe
            } else {
                printf("%c", graphismesHD[elementInTheCase]); // murs + boite + vide + powerup
            }
        }
        printf("\n");
    }
}

bool checkTheMooveAndMoove(int r, int c, Map *map, int actualPlayer, char move) {
    // Find the position of the player
    int actualRow, actualColumn;
    int found = 0;
    actualPlayer *= 1000;

    for (actualRow = 0; actualRow < r; ++actualRow) {
        for (actualColumn = 0; actualColumn < c; ++actualColumn) {
            if (
                    map->tab[actualRow][actualColumn] >= actualPlayer
                    && map->tab[actualRow][actualColumn] <= actualPlayer + 999
                    ) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
    }


    int rowToCheck = actualRow, colToCheck = actualColumn;
    //int
    switch (move) {
        case 'u':
            if (actualRow == 0) {
                rowToCheck = r - 1;
            } else {
                rowToCheck = actualRow - 1;
            }

            break;
        case 'd':
            if (actualRow == r + 1) {
                rowToCheck = 0;
            } else {
                rowToCheck = actualRow + 1;
            }

            break;
        case 'l':
            if (actualColumn == 0) {
                colToCheck = c - 1;
            } else {
                colToCheck = actualColumn - 1;
            }
            break;
        case 'r':
            if (actualColumn == c + 1) {
                colToCheck = 0;
            } else {
                colToCheck = actualColumn + 1;
            }
            break;
        case 'x':
            // TODO
            map->tab[actualRow][actualColumn] = 100 * actualPlayer / 1000 + 100;
            break;
        case 'w':
            return 1;
        default:
            return 0;
    }

    int destination = map->tab[rowToCheck][colToCheck];

    if (destination == 0 || (destination >= 3 && destination <= 9)) {
        map->tab[actualRow][actualColumn] -= actualPlayer;
        map->tab[rowToCheck][colToCheck] += actualPlayer;
        return 1;
    }

    return 0;
}

int verifVictoire(int nbr_players, Joueur* joueur_array) {
    int players_alive = nbr_players;
    /// nbr de joueurs en vies
    for (int i = 0; i < nbr_players; i++)
    {
        if (joueur_array[i].nbVies == 0)
        {
            players_alive -= 1;
            freePlayer(&joueur_array[i]);
        }
    }

    if (players_alive == 1) {

        for (int i = 0; i < nbr_players; i++) {

            if (joueur_array[i].nbVies >= 1)
            {
                green();
                printf("Le gagnant est J%d", joueur_array[i].numPlayer);
                resetColor();
            }
        }
    }
    if (players_alive == 0) {
        red();
        printf("Tout le monde est mort !!");
        resetColor();
    }
    return 0;
}