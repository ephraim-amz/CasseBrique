#include <stdlib.h>
#include "Bombe.h"

#ifndef CASSEBRIQUE_JOUEUR_H
#define CASSEBRIQUE_JOUEUR_H

/**
 * @brief Structure joueur
 */
typedef struct {
    int nbVies;
    int nbBombesMax;        //2
    int nbBombesActuel;        //2
    int powerBombe;
    bool isAlive;
    Bombe *bombes;
} Joueur;

/**
 * Créer un nouveau joueur avec les paramètres par défaut
 * @param nbVies
 * @param nbBombesMax
 * @param nbBombesActuel
 * @param powerBombe
 * @return
 */
Joueur createJoueur(int nbVies, int nbBombesMax, int nbBombesActuel, int powerBombe);

/**
 * @brief Libérer un joueur créé en mémoire
 * @param j
 */
void free_player(Joueur *j);


#endif //CASSEBRIQUE_JOUEUR_H
