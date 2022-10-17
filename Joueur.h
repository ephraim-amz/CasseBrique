#include <stdlib.h>
#include "assert.h"
#include "Bombe.h"
#include "Map.h"

#ifndef CASSEBRIQUE_JOUEUR_H
#define CASSEBRIQUE_JOUEUR_H

/**
 * @brief Structure joueur
 */
typedef struct {
    char *nom;
    int numJoueur;
    int x;
    int y;
    int nbBombes;
    Bombe **bombes;
} Joueur;

/**
 * @brief Créer un nouveau joueur avec les paramètres par défaut
 * @param nom
 * @param numJoueur
 * @param x
 * @param y
 * @param nbBombes
 * @return Le nouveau joueur
 */
Joueur *createJoueur(char *nom, int numJoueur, int x, int y, int nbBombes);

/**
 * @brief Libérer un joueur créé en mémoire
 * @param j
 */
void free_player(Joueur *j);

/**
 * @brief Déplacer le joueur
 * @param j Le joueur
 * @param m La carte de jeu
 * @param direction (1 gauche, 2 droite, 3 haut, 4 bas)
 * @warning Le déplacement doit être valide (pas de mur)
 */
void deplacerJoueur(Joueur *j, Map *m, int direction);

/**
 * @brief Permet d'activer une bombe
 * @param b
 */
void enableBombe(Map *m, Bombe *b);

/**
 * @brief Augmente de 1 le nombre de bombes du joueur.
 * @param j
 *
 */
void bombUp(Joueur *j);

/**
 * @brief Diminue de 1 le nombre de bombes du joueur.
 * @param j
 *
 */
void bombDown(Joueur *j);

/**
 * @brief Afficher le gagnant de la partie
 * @param j
 */
void print_winner(const Joueur *j);



#endif //CASSEBRIQUE_JOUEUR_H
