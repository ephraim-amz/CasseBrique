#include "Map.h"
#include "colors.h"


// Fonction problématique dans Joueur.c
Joueur* createJoueur(Map mapPlayed){
    int maxPlayer = mapPlayed.nbMaxPlayer;
    Joueur* playerList = malloc(maxPlayer * sizeof(Joueur));

    for (int i = 0; i < maxPlayer; ++i) {
        playerList[i].id = i+1;
        playerList[i].nbVies = mapPlayed.start_nbVies;
        playerList[i].coeur = mapPlayed.start_coeur;
        playerList[i].nbBombesMax = mapPlayed.start_nbBombe;
        playerList[i].nbBombesActuel = 0;
        playerList[i].powerBombe = mapPlayed.start_powerBombe;
        playerList[i].boots = mapPlayed.start_boots;
        playerList[i].pass = mapPlayed.start_pass;
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
void displayMap(int r, int c, int map[r][c]){
    int i, j, ruleLine;

    // Definition des caracteres à utiliser pour l'affichage
    int graphismesHD[] = {255, 176, 219, 42, 42, 43, 43, 112, 98, 4, 3, 5, 6, 162};

    // Verification de la hauteur de la map pour le bon affichage des regles
    ruleLine = r < 7 ? 7 : r;

    // Lecture de ligne
    for(i = 0; i < ruleLine; ++i){
        // Lecture de colonne
        if(i <= r){
            for (j = 0; j < c; ++j){
                int elementInTheCase = map[i][j];

                // espaces entre les cases (esthetisme)
                if ((i != 0 && i != r-1) && (j > 0)) {
                    printf(" ");
                }

                // affichage du contenu des cases
                if(elementInTheCase >= 10000)       // joueur
                {
                    elementInTheCase /= 10000;  // récupération du numéro du joueur

                    // Apply color to the player token
                    switch (elementInTheCase)
                    {
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
                }
                else if (elementInTheCase >= 1000 )       // bombes
                {
                    // bombe s'affiche en rouge si elle est sur le point d'exploser
                    int timer = elementInTheCase % 10;
                    if(timer == 1)
                    {
                        red();
                    }
                    printf("%c", graphismesHD[13]);
                    resetColor();
                }
                else        // murs + boite + vide + powerup
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
                if ((i == 0 || i == r-1) && (j != c-1)) {
                    printf("%c", 219);
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

    // Format d'une ligne d'ATH :
    // J1: x1 ♥ (+0♦) | 3/10 ó | x3 POWA | boots
    // Ajout de %c (255) à la fin des print pour être sûr d'avoir l'espace insecable
    printf("J%d:%c", player.id,255);
    printf("x%d%c%c", player.nbVies, 3, 255);
    int bouclier =  player.coeur == -1 ? 0 : player.coeur;
    printf("(+%d%c)%c", bouclier, 4, 255);
    int bombesEnPoche = player.nbBombesMax - player.nbBombesActuel;
    printf("| %d/%d %c%c", bombesEnPoche, player.nbBombesMax, 162, 255);
    printf("| x%d POWA%c", player.powerBombe, 255);

    // equipement
    printf("|%c", 255);
    if (player.boots == 1)
    {
        printf("boots");
    }
    else if (player.pass == 1)
    {
        printf("pass");
    }
    else
    {
        printf("none");
    }

    resetColor();
    printf("\n");
}
