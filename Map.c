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
        playerList[i].alreadyHurt = 0;
    }

    return playerList;
}


Map *createMap(int nbLignes, int nbColonnes, int nbVies, int nbCoeur, int nbMaxPlayer, int nbBombeBase, int txLoot, int start_powerBombe, int bombe_compteur, int start_boots, int start_pass) {

    // Initialisation de la map de jeu avec les informations du fichier
    Map *m = malloc(sizeof(Map));
    *m = (Map) {
            .tab = createTab(nbLignes, nbColonnes),
            .nbLignes = nbLignes,
            .nbColonnes = nbColonnes,
            .taux_loot = txLoot,
            .nbMaxPlayer = nbMaxPlayer,
            .start_nbVies = nbVies,
            .start_coeur = nbCoeur,
            .start_nbBombe = nbBombeBase,
            .start_powerBombe = start_powerBombe,
            .bombe_compteur = bombe_compteur,
            .start_boots = start_boots,
            .start_pass = start_pass
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
    long tauxLoot, start_nbVies, nbCoeur, start_powerBombe, bombe_compteur, start_boots, start_pass, nbMaxPlayer;
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
                nbCoeur = strtol(strtok_s(line, "\n", &p), &p, 10);
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
    infos[6] = (int) nbCoeur;
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
    int txLoot = infos[4];
    int nbVies = infos[5];
    int nbCoeur = infos[6];
    int start_powerBombe = infos[7];
    int bombe_compteur = infos[8];
    int start_boots = infos[9];
    int start_pass = infos[10];

    int currentLine = 0;

    Map *map = createMap(nbLignes, nbColonnes, nbVies, nbCoeur, nbPlayers, nbBombes, txLoot, start_powerBombe, bombe_compteur, start_boots, start_pass);
    map->joueurs = createJoueurFromMapData(map);
    int **tab = createTab(nbLignes, nbColonnes);

    int player = 0;
    while (fgets(line, sizeof(line), mapFile) != NULL) {
        if (cpt > 10) {


            for (int i = 0; i < strlen(line) - 1; ++i) {
                if (line[i] == 'p') {
                    player += 10000;
                    tab[currentLine][i] = player;
                }
                if (line[i] == 'm') {
                    tab[currentLine][i] = 1;
                }
                if (line[i] == 'x') {
                    tab[currentLine][i] = 2;
                }
                if (line[i] == '.') {
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

/*
void updateMapAfterExplosion(Map *map, int bombe_power, int row, int column) {
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
        afterExplosion(map, bombe_power, row, column);
    }
}*/


void updateHealth(Joueur joueur){
    if (joueur.invincible == 0){
        if (joueur.coeur == 1)
        {
            joueur.coeur = -1;
        }
        else
        {
            --joueur.nbVies;
        }
    }
}


void afterExplosion(Map* map, int bombe_power, int rowOfBomb, int columnOfBomb, Joueur* joueurList, int owner) {
    // Rendre la bombe à son propriétaire
    joueurList[owner].nbBombesActuel -= 1;

    int x = -1;
    int** mapPlayed = map->tab;
    int nbRow = map->nbLignes;
    int nbCol = map->nbColonnes;
    int taux_loot = map->taux_loot;


    // Détection de joueur sur case initiale
    int joueurSurCase = mapPlayed[rowOfBomb][columnOfBomb] / 10000;

    if(joueurSurCase > 0)
    {
        Joueur joueur = joueurList[joueurSurCase - 1];
        updateHealth(joueur);
    }
    else
    {
        mapPlayed[rowOfBomb][columnOfBomb] = x;
    }


    //int row, col;
    // col = columnOfBomb;
    int rowToCheck, colToCheck;


    // Explosion vers le haut
    for (int i = 1; i <= bombe_power; ++i) {
        colToCheck = columnOfBomb;

        if(rowOfBomb - i < 0)
        {
            rowToCheck = nbRow - 1;
        }
        else
        {
            rowToCheck = rowOfBomb - i;
        }

        int elementInTheCase = mapPlayed[rowToCheck][colToCheck];

        int stop = 0;

        switch (elementInTheCase) {
            case 0:     // case vide
                mapPlayed[rowToCheck][colToCheck] = x;
                break;
            case 1:     // boite
                mapPlayed[rowToCheck][colToCheck] = dropLoot(taux_loot);
            case 2:     // mur
                stop = 1;
                break;

            default:
                if(elementInTheCase < 13)     // item
                {
                    mapPlayed[rowToCheck][colToCheck] = x;     // destruction de l'item
                }
                else
                {
                    joueurSurCase = mapPlayed[rowToCheck][colToCheck] / 10000;

                    if(joueurSurCase > 0)       // joueur
                    {
                        Joueur joueur = joueurList[joueurSurCase - 1];
                        if(joueur.alreadyHurt == 0){
                            updateHealth(joueur);
                            joueur.alreadyHurt = 1;
                        }
                    }

                    int bombeSurCase = mapPlayed[rowToCheck][colToCheck] % 10000;
                    if(bombeSurCase > 0)    // bombe -> nouvelle explosion
                    {
                        int ownerBomb = (bombeSurCase / 1000) - 1;
                        int new_bombePower = (bombeSurCase % 1000) / 100;
                        afterExplosion(map, new_bombePower, rowToCheck, colToCheck, joueurList, ownerBomb);
                    }
                }
                break;
        }
        // Si on rencontre un obstacle, on arrête la fonction
        if(stop)
        {
            break;
        }
    }

    // Explosion vers le bas
    for (int i = 1; i <= bombe_power; ++i) {
        colToCheck = columnOfBomb;

        if(rowOfBomb + i >= nbRow)
        {
            rowToCheck = 0;
        }
        else
        {
            rowToCheck = rowOfBomb + i;
        }

        int elementInTheCase = mapPlayed[rowToCheck][colToCheck];

        int stop = 0;

        switch (elementInTheCase) {
            case 0:     // case vide
                mapPlayed[rowToCheck][colToCheck] = x;
                break;
            case 1:     // boite
                mapPlayed[rowToCheck][colToCheck] = dropLoot(taux_loot);
            case 2:     // mur
                stop = 1;
                break;

            default:
                if(elementInTheCase < 13)     // item
                {
                    mapPlayed[rowToCheck][colToCheck] = x;     // destruction de l'item
                }
                else
                {
                    joueurSurCase = mapPlayed[rowToCheck][colToCheck] / 10000;

                    if(joueurSurCase > 0)       // joueur
                    {
                        Joueur joueur = joueurList[joueurSurCase - 1];
                        if(joueur.alreadyHurt == 0){
                            updateHealth(joueur);
                            joueur.alreadyHurt = 1;
                        }
                    }

                    int bombeSurCase = mapPlayed[rowToCheck][colToCheck] % 10000;
                    if(bombeSurCase > 0)    // bombe -> nouvelle explosion
                    {
                        int ownerBomb = (bombeSurCase / 1000) - 1;
                        int new_bombePower = (bombeSurCase % 1000) / 100;
                        afterExplosion(map, new_bombePower, rowToCheck, colToCheck, joueurList, ownerBomb);
                    }
                }
                break;
        }
        // Si on rencontre un obstacle, on arrête la fonction
        if(stop)
        {
            break;
        }
    }

    // Explosion vers la gauche
    for (int i = 1; i <= bombe_power; ++i) {
        rowToCheck = rowOfBomb;

        if(columnOfBomb - i < nbCol)
        {
            colToCheck = nbCol - 1;
        }
        else
        {
            colToCheck = columnOfBomb - i;
        }

        int elementInTheCase = mapPlayed[rowToCheck][colToCheck];

        int stop = 0;

        switch (elementInTheCase) {
            case 0:     // case vide
                mapPlayed[rowToCheck][colToCheck] = x;
                break;
            case 1:     // boite
                mapPlayed[rowToCheck][colToCheck] = dropLoot(taux_loot);
            case 2:     // mur
                stop = 1;
                break;

            default:
                if(elementInTheCase < 13)     // item
                {
                    mapPlayed[rowToCheck][colToCheck] = x;     // destruction de l'item
                }
                else
                {
                    joueurSurCase = mapPlayed[rowToCheck][colToCheck] / 10000;

                    if(joueurSurCase > 0)       // joueur
                    {
                        Joueur joueur = joueurList[joueurSurCase - 1];
                        if(joueur.alreadyHurt == 0){
                            updateHealth(joueur);
                            joueur.alreadyHurt = 1;
                        }
                    }

                    int bombeSurCase = mapPlayed[rowToCheck][colToCheck] % 10000;
                    if(bombeSurCase > 0)    // bombe -> nouvelle explosion
                    {
                        int ownerBomb = (bombeSurCase / 1000) - 1;
                        int new_bombePower = (bombeSurCase % 1000) / 100;
                        afterExplosion(map, new_bombePower, rowToCheck, colToCheck, joueurList, ownerBomb);
                    }
                }
                break;
        }
        // Si on rencontre un obstacle, on arrête la fonction
        if(stop)
        {
            break;
        }
    }

    // Explosion vers la droite
    for (int i = 1; i <= bombe_power; ++i) {
        rowToCheck = rowOfBomb;

        if(columnOfBomb + i >= nbCol)
        {
            colToCheck = 0;
        }
        else
        {
            colToCheck = columnOfBomb + i;
        }

        int elementInTheCase = mapPlayed[rowToCheck][colToCheck];

        int stop = 0;

        switch (elementInTheCase) {
            case 0:     // case vide
                mapPlayed[rowToCheck][colToCheck] = x;
                break;
            case 1:     // boite
                mapPlayed[rowToCheck][colToCheck] = dropLoot(taux_loot);
            case 2:     // mur
                stop = 1;
                break;

            default:
                if(elementInTheCase < 13)     // item
                {
                    mapPlayed[rowToCheck][colToCheck] = x;     // destruction de l'item
                }
                else
                {
                    joueurSurCase = mapPlayed[rowToCheck][colToCheck] / 10000;

                    if(joueurSurCase > 0)       // joueur
                    {
                        Joueur joueur = joueurList[joueurSurCase - 1];
                        if(joueur.alreadyHurt == 0){
                            updateHealth(joueur);
                            joueur.alreadyHurt = 1;
                        }
                    }

                    int bombeSurCase = mapPlayed[rowToCheck][colToCheck] % 10000;
                    if(bombeSurCase > 0)    // bombe -> nouvelle explosion
                    {
                        int ownerBomb = (bombeSurCase / 1000) - 1;
                        int new_bombePower = (bombeSurCase % 1000) / 100;
                        afterExplosion(map, new_bombePower, rowToCheck, colToCheck, joueurList, ownerBomb);
                    }
                }
                break;
        }
        // Si on rencontre un obstacle, on arrête la fonction
        if(stop)
        {
            break;
        }
    }

}


void freeMap(Map *m, int r) {
    freeBombe(m->joueurs->bombes);
    free_player(m->joueurs);
    freeTab(m->tab, r);
    free(m);
}


void printRules(int x) {
    // Espace entre la map et les règles
    printf("%c%c%c%c||%c", 255, 255, 255, 255, 255);

    // Affichage des règles
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
        if (i < r) {
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
                }
                else if(elementInTheCase >= 0)       // murs + boite + vide + powerup
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
                else
                {
                    if(elementInTheCase == -1){
                        printf("*");
                        map->tab[i][j] = 0;
                    }
                }

                // Bloc supplémentaire entre chaque case pour les bordures hautes et basses de la map
                if ((i == 0 || i == r - 1) && (j != c - 1)) {
                    printf("%c", 219);
                }
            }
        } else
            //
            if (ruleLine <= 7) {
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
    printf("J%d:%c", player.id, 255);                                       // ID player
    printf("x%d%c%c", player.nbVies, 3, 255);                               // Vies
    int bouclier = player.coeur == -1 ? 0 : player.coeur;
    printf("(+%d%c)%c", bouclier, 4, 255);                                  // Bouclier
    int bombesEnPoche = player.nbBombesMax - player.nbBombesActuel;
    printf("| %d/%d %c%c", bombesEnPoche, player.nbBombesMax, 162, 255);    // Bombes
    printf("| x%d POWA%c", player.powerBombe, 255);                         // Puissance

    // equipement
    printf("|%cequipement :%c", 255, 255);
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


// TODO : DELETE
void displayMapDEBUG(int r, int c, Map *map) {
    int i, j, ruleLine;

    // Definition des caracteres à utiliser pour l'affichage
    //int graphismesHD[] = {255, 176, 219, 42, 42, 43, 43, 112, 98, 4, 3, 5, 6, 162};

    // Verification de la hauteur de la map pour le bon affichage des regles
    ruleLine = r < 7 ? 7 : r;

    // Lecture de ligne
    for (i = 0; i < ruleLine; ++i) {
        // Lecture de colonne
        if (i < r) {
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

                    printf("%d", elementInTheCase);
                    resetColor();
                } else if (elementInTheCase >= 1000)       // bombes
                {
                    // bombe s'affiche en rouge si elle est sur le point d'exploser
                    int timer = elementInTheCase % 10;
                    if (timer == 1) {
                        red();
                    }
                    printf("%d", elementInTheCase);
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

                    printf("%d", elementInTheCase);
                    resetColor();
                }

                // Bloc supplémentaire entre chaque case pour les bordures hautes et basses de la map
                if ((i == 0 || i == r - 1) && (j != c - 1)) {
                    printf("%d", 219);
                }
            }
        } else
            //
        if (ruleLine <= 7) {
            for (int k = 0; k < (c * 2) - 1; ++k) {
                printf("%d", 255);
            }
        }

        printRules(i);
        printf("\n");
    }
}

