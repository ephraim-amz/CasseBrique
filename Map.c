#include "Map.h"
#include "colors.h"


// Fonction problématique dans Joueur.c
Joueur* createJoueur(Map mapPlayed){
    int maxPlayer = mapPlayed.nbMaxPlayer;
    Joueur* playerList = malloc(maxPlayer * sizeof(Joueur));

    for (int i = 0; i < maxPlayer; ++i) {
        playerList[i].id = i+1;
        playerList[i].nbVies = mapPlayed.start_nbVies;
        playerList[i].nbBombesMax = mapPlayed.start_nbBombe;
        playerList[i].nbBombesActuel = mapPlayed.start_nbBombe;
        playerList[i].powerBombe = mapPlayed.start_powerBombe;
        playerList[i].boots = mapPlayed.start_boots;
    }

    return playerList;
}
/*
void freeMap(Map *m, int r){
    freeTab(m->tab, r);
    free(m);
}
*/

void printRules(int x){
    printf("%c%c%c%c||%c", 255,255,255,255,255);
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
void displayMap(int r, int c, int map[r][c]){
    int i, j, ruleLine;

    // Definition des caracteres à utiliser pour l'affichage
    int graphismesHD[] = {255, 176, 219, 162};

    // Verification de la hauteur de la map pour le bon affichage des regles
    ruleLine = r < 7 ? 7 : r;

    // Lecture de ligne
    for(i = 0; i < ruleLine; ++i){
        // Lecture de colonne
        if(i <= r){
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
                if(elementInTheCase >= 1000){
                    elementInTheCase /= 1000;

                    // Apply colors to players
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
                } else if (elementInTheCase >= 10 ){
                    printf("%c", graphismesHD[3]);      // Bombe
                } else {
                    printf("%c", graphismesHD[elementInTheCase]); // murs + boite + vide + powerup
                }
            }
        } else if(ruleLine <= 7) {
            for (int k = 0; k < (c*2)-1; ++k) {
                printf("%c", 255);
            }
        }

        printRules(i);
        printf("\n");
    }
}


void displayATH(Joueur player, int totalPlayer, int actualPlayer) {
    switch (player.id) {
        case 1:
            red();
            break;
        case 2:
            yellow();
            break;
        case 3:
            green();
            break;
        case 4:
            cyan();
            break;
    }

    if(player.nbVies == 0)
    {
        black();
        printf(":dead:%c", 255);
    }

    else if(actualPlayer == player.id)
    {
        printf("->%c%c", 255,255);
    }

    else
    {
        printf("%c%c%c%c", 255,255,255,255);
    }

    printf("J%d, x%d %c | x%d %c | x%d POWA\n", player.id, player.nbVies, 3, player.nbBombesActuel, 162, player.powerBombe);
    resetColor();
}
