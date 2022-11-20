#include "Joueur.h"
#include "Map.h"
#include "colors.h"


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


// Fonction problématique dans Joueur.c
Joueur *createJoueurFromMapData(Map *mapPlayed) {
    int maxPlayer = mapPlayed->nbMaxPlayer;
    Joueur *playerList = malloc(maxPlayer * sizeof(Joueur));

    for (int i = 0; i < maxPlayer; ++i) {
        playerList[i].id = i + 1;
        playerList[i].nbVies = mapPlayed->start_nbVies;
        playerList[i].coeur = mapPlayed->start_coeur;
        playerList[i].nbBombesMax = mapPlayed->start_nbBombe;
        playerList[i].nbBombesActuel = 0;
        playerList[i].powerBombe = mapPlayed->start_powerBombe;
        playerList[i].boots = mapPlayed->start_boots;
        playerList[i].pass = mapPlayed->start_pass;
        playerList[i].invincible = 0;
    }

    return playerList;
}


Map *createMap(int nbLignes, int nbColonnes, int nbVies, int nbMaxPlayer, int nbBombeBase, int txLoot) {

    // Initialisation de la map de jeu avec les informations du fichier
    Map *m = malloc(sizeof(Map));
    *m = (Map) {
            .tab = createTab(nbLignes, nbColonnes),
            .nbLignes = nbLignes,
            .nbColonnes = nbColonnes,
            .start_nbVies = nbVies,
            .nbMaxPlayer = nbMaxPlayer,
            .start_nbBombe = nbBombeBase,
            .taux_loot = txLoot
    };

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
    int lineReaded = 0;
    long nbBombes;
    long nbLignes, nbColonnes;
    char *endPtr;
    int *infos = malloc(sizeof(int) * 11);
    long tauxLoot, start_nbVies, start_nbBombe, start_powerBombe, bombe_compteur, start_boots, start_pass, nbMaxPlayer;
    while (fgets(line, sizeof(line), mapFile) != NULL) {
        char *p;
        switch (lineReaded) {
            case 0:
                nbBombes = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 1:
                nbColonnes = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 2:
                nbLignes = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 3:
                nbMaxPlayer = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 4:
                tauxLoot = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 5:
                start_nbVies = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 6:
                start_nbBombe = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 7:
                start_powerBombe = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 8:
                bombe_compteur = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 9:
                start_boots = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            case 10:
                start_pass = strtol(strtok_s(line, "\n", &p), &p, 10);
                break;
            default:
                break;
        }

        lineReaded++;
    }


    infos[0] =  nbBombes;
    infos[1] = (int) nbLignes;
    infos[2] = (int) nbColonnes;
    infos[3] = (int) nbMaxPlayer;
    infos[4] = (int) tauxLoot;
    infos[5] = (int) start_nbVies;
    infos[6] = (int) start_nbBombe;
    infos[7] = (int) start_powerBombe;
    infos[8] = (int) bombe_compteur;
    infos[9] = (int) start_boots;
    infos[10] = (int) start_pass;

    fclose(mapFile);
    return infos;
}


Map *createMapViaFile(char *filename) {
    FILE *mapFile = loadFile(filename);
    char line[128];

    int cpt = 0;
    int *infos = getInfos(filename);
    int nbBombes = infos[0];
    int nbLignes = infos[1];
    int nbColonnes = infos[2];
    int nbPlayers = infos[3];
    int currentLine = 0;

    Map *map = createMap(nbLignes, nbColonnes, 2, nbPlayers, nbBombes, 0);
    map->joueurs = createJoueurFromMapData(map);
    int **tab = createTab(nbLignes, nbColonnes);

    while (fgets(line, sizeof(line), mapFile) != NULL) {
        if (cpt > 11) {
            int player = 0;

            for (int i = 0; i < strlen(line) - 1; ++i) {
                if (line[i] == 'p') {
                    map->nbMaxPlayer++;
                    player += 10000;
                    tab[currentLine][i] = player;
                }
                if (line[i] == 'm') {
                    tab[currentLine][i] = 1;
                }
                if (line[i] == 'x') {
                    tab[currentLine][i] = 2;
                }
                if (line[i] == ' ') {
                    tab[currentLine][i] = 0;
                }
            }
            currentLine++;
        }
        cpt++;
    }

    map->tab = tab;
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


bool isAPlayer(Map *map, int x, int y) {
    return map->tab[x][y] >= 10000;
}


void updateMapAfterExplosion(Map *map, Bombe b, int row, int column) {
    Joueur *playerList = map->joueurs;

    if (isARegularWall(map, row, column)) {
        map->tab[row][column] = 0;
    }
    if (isAPlayer(map, row, column)) {
        int player = map->tab[row][column] / 10000;
        removeLife(&playerList[player - 1]);
        map->tab[row][column] = 0;
    }
    if (map->tab[row][column] >= 110 && map->tab[row][column] <= 199) {
        afterExplosion(map, b, row, column);
    }
}


void afterExplosion(Map *map, Bombe b, int row, int column) {
    map->tab[row][column] = 0;
    for (int k = 1; k <= b.portee; ++k) {
        if (column - k >= 0) {
            updateMapAfterExplosion(map, b, row, column - k);
        }
        if (column + k <= map->nbColonnes) {
            updateMapAfterExplosion(map, b, row, column + k);
        }
        if (row - k >= 0) {
            updateMapAfterExplosion(map, b, row - k, column);
        }
        if (row + k <= map->nbLignes) {
            updateMapAfterExplosion(map, b, row + k, column);
        }
        if (row + k <= map->nbLignes && column + k <= map->nbColonnes) {
            updateMapAfterExplosion(map, b, row + k, column + k);
        }
        if (row - k >= 0 && column - k >= 0) {
            updateMapAfterExplosion(map, b, row - k, column - k);
        }
        if (row + k <= map->nbLignes && column - k >= 0) {
            updateMapAfterExplosion(map, b, row + k, column - k);
        }
        if (row - k >= 0 && column + k <= map->nbColonnes) {
            updateMapAfterExplosion(map, b, row - k, column + k);
        }
        if (k == 2) {
            if (row + k >= 0 && column - 1 >= 0) {
                updateMapAfterExplosion(map, b, row + k, column - 1);
            }
            if (row - 1 >= 0 && column - k >= 0) {
                updateMapAfterExplosion(map, b, row - 1, column - k);
            }
            if (row - k >= 0 && column - 1 >= 0) {
                updateMapAfterExplosion(map, b, row - k, column - 1);
            }
            if (row + 1 >= 0 && column - k >= 0) {
                updateMapAfterExplosion(map, b, row + 1, column - k);
            }
            if (row + 1 <= map->nbLignes && column + k <= map->nbColonnes) {
                updateMapAfterExplosion(map, b, row + 1, column + k);
            }
            if (row + k <= map->nbLignes && column + 1 <= map->nbColonnes) {
                updateMapAfterExplosion(map, b, row + k, column + 1);
            }
            if (row - k >= 0 && column + 1 <= map->nbColonnes) {
                updateMapAfterExplosion(map, b, row - k, column + 1);
            }
            if (row - 1 >= 0 && column + k <= map->nbColonnes) {
                updateMapAfterExplosion(map, b, row - 1, column + k);
            }
        }
    }

    displayMap(map->nbLignes, map->nbColonnes, (Map *) map->tab);
}


void freeMap(Map *m, int r) {
    freeBombe(m->joueurs->bombes);
    free_player(m->joueurs);
    freeTab(m->tab, r);
    free(m);
}


void printRules(int x) {
    printf("%c%c%c%c||%c", 255, 255, 255, 255, 255);
    switch (x) {
        case 0:
            printf("Controles :");
            break;
        case 1:
            printf("'u' pour aller vers le haut");
            break;
        case 2:
            printf("'d' pour aller vers le bas");
            break;
        case 3:
            printf("'l' pour aller vers la gauche");
            break;
        case 4:
            printf("'r' pour aller vers la droite");
            break;
        case 5:
            printf("'x' pour poser une bombe");
            break;
        case 6:
            printf("'w' pour passer son tour");
            break;
        default:
            break;
    }
}


/* Affichage du plateau de jeu
// Légende :
// -1 : explosion               X
// 0 : vide                       (code : 255)
// 1 : mur destructible         ░ (code : 176)
// 2 : mur infranchissable      █ (code : 219)
// 3 : ++ nbBombe               * vert (code : 42)
// 4 : -- nbBombe               * rouge (code : 42)
// 5 : ++ power                 + jaune (code : 43)
// 6 : -- power                 + bleu (code : 43)
// 7 : pass                     p (code : 112)
// 8 : boots                    b (code : 98)
// 9 : coeur/bouclier           ♦ (code : 4)
// 10 : vie                     ♥ (code : 3)
// 11 : invulnérabilité         ♣ (code: 5)
// 12 : powerMax                ♠ rouge (code : 6)
// 110 -> 199 : bombes          ó (code : 162)
// 1000 : joueur 1              1 (code : 49)
// 2000 : joueur 2              2 (code : 50)
// 3000 : joueur 3              3 (code : 51)
// 4000 : joueur 4              4 (code : 52)
// ex : joueur 2 vient de placer une bombe de puissance 3 qui explosera dans 4 tours de jeu
// --> 20000 pour le joueur
// --> 2000 pour le joueur qui a placé la bombe
// --> 300 pour la puissance de la bombe
// --> 04 pour le timer
// = 22304
// Tout ce qui est entre 110 et 999 est une bombe
// Le chiffre des dizaines représente la puissance de la bombe
// Le chiffre des unités représente le compteur avant explosion
// Quand le compteur passe à 0, la bombe explose
// Après chaque mouvement, le compteur est décrémenté
*/
void displayMap(int r, int c, Map *map) {
    int i, j, ruleLine;

    // Definition des caracteres à utiliser pour l'affichage
    int graphismesHD[] = {255, 176, 219, 42, 42, 43, 43, 112, 98, 4, 3, 5, 6, 162};

    // Verification de la hauteur de la map pour le bon affichage des regles
    ruleLine = r < 7 ? 7 : r;

    // Lecture de ligne
    for (i = 0; i < ruleLine; ++i) {
        // Lecture de colonne
        if (i <= r) {
            for (j = 0; j < c; ++j) {
                int elementInTheCase = map->tab[i][j];

                // espaces entre les cases (esthetisme)
                if ((i != 0 && i != r - 1) && (j > 0)) {
                    printf(" ");
                }

                // affichage du contenu des cases
                if (elementInTheCase >= 10000)       // joueur
                {
                    elementInTheCase /= 10000;  // récupération du numéro du joueur

                    // Apply color to the player token
                    switch (elementInTheCase) {
                        case 1 :
                            red();
                            break;
                        case 2 :
                            cyan();
                            break;
                        case 3 :
                            green();
                            break;
                        case 4 :
                            yellow();
                            break;
                        default:
                            resetColor();
                    }

                    printf("%c", elementInTheCase + 48);
                    resetColor();
                } else if (elementInTheCase >= 1000)       // bombes
                {
                    // bombe s'affiche en rouge si elle est sur le point d'exploser
                    int timer = elementInTheCase % 10;
                    if (timer == 1) {
                        red();
                    }
                    printf("%c", graphismesHD[13]);
                    resetColor();
                } else        // murs + boite + vide + powerup
                {
                    switch (elementInTheCase) {
                        case 3:
                            green();
                            break;
                        case 4:
                        case 12:
                            red();
                            break;
                        case 5:
                            yellow();
                            break;
                        case 6:
                            blue();
                            break;
                        default:
                            break;
                    }

                    printf("%c", graphismesHD[elementInTheCase]);
                    resetColor();
                }

                // Bloc supplémentaire entre chaque case pour les bordures hautes et basses de la map
                if ((i == 0 || i == r - 1) && (j != c - 1)) {
                    printf("%c", 219);
                }
            }
        } else if (ruleLine <= 7) {
            for (int k = 0; k < (c * 2) - 1; ++k) {
                printf("%c", 255);
            }
        }

        printRules(i);
        printf("\n");
    }
}


void displayATH(Joueur player, int actualPlayer) {
    switch (player.id) {
        case 1:
            red();
            break;
        case 2:
            cyan();
            break;
        case 3:
            green();
            break;
        case 4:
            yellow();
            break;
    }

    if (player.nbVies == 0) {
        black();
        printf(":dead:%c", 255);
    } else if (actualPlayer == player.id) {
        printf("->%c%c", 255, 255);
    } else {
        printf("%c%c%c%c", 255, 255, 255, 255);
    }

    // Format d'une ligne d'ATH :
    // J1: x1 ♥ (+0♦) | 3/10 ó | x3 POWA | boots
    // Ajout de %c (255) à la fin des print pour être sûr d'avoir l'espace insecable
    printf("J%d:%c", player.id, 255);
    printf("x%d%c%c", player.nbVies, 3, 255);
    int bouclier = player.coeur == -1 ? 0 : player.coeur;
    printf("(+%d%c)%c", bouclier, 4, 255);
    int bombesEnPoche = player.nbBombesMax - player.nbBombesActuel;
    printf("| %d/%d %c%c", bombesEnPoche, player.nbBombesMax, 162, 255);
    printf("| x%d POWA%c", player.powerBombe, 255);

    // equipement
    printf("|%c", 255);
    if (player.boots == 1) {
        printf("boots");
    } else if (player.pass == 1) {
        printf("pass");
    } else {
        printf("none");
    }

    resetColor();
    printf("\n");
}
