#include <stdlib.h>
//#include "Map.h"

#ifndef CASSEBRIQUE_JOUEUR_H
#define CASSEBRIQUE_JOUEUR_H


/**
 * @brief Structure joueur
 */
typedef struct {
    int id;
    int nbVies;
    int nbBombesMax;
    int nbBombesActuel;
    int powerBombe;
    int boots;
} Joueur;


//Libérer un joueur créé en mémoire
void free_player(Joueur *j);


// Check if input is valable
int checkInput(char input);

// Check if the moove can be done and do it
int checkTheMooveAndMoove(int r, int c, int map[r][c], int actualPlayer, char move, int gotBoots);

// Check end game conditions
int verif_victoire(int maxPlayer, Joueur* playerList);

#endif //CASSEBRIQUE_JOUEUR_H
