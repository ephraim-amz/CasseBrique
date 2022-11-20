#include <stdlib.h>
//#include "Map.h"

#ifndef CASSEBRIQUE_JOUEUR_H
#define CASSEBRIQUE_JOUEUR_H

#include "Bombe.h"


/**
 * @brief Structure joueur
 */
typedef struct {
    int id;                 // id du joueur
    int nbVies;             // nombre d'explosions nécessaires pour tuer un joueur
    int coeur;              // bouclier
    int nbBombesMax;        // nombre maximum de bombe posable par le joueur
    int nbBombesActuel;     // nombre de bombes du joueur en ce moment même sur le terrain
    int powerBombe;         // puissance de la bombe
    int boots;              // équipement permettant de déplacer les bombes
    int pass;               // équipement permettant de passer sur une bombe
    int invincible;         // nombre de tours d'invincibilite
    
    // TODO : verif
    Bombe* bombes;
} Joueur;

// TODO : verif
Joueur createJoueur(int nbVies, int nbBombesMax, int nbBombesActuel, int powerBombe, int numPlayer);

//Libérer un joueur créé en mémoire
void free_player(Joueur *j);


// Check if input is valable
int checkInput(char input);

bool isAlive(Joueur* j);
void removeLife(Joueur* j);
// Check if the moove can be done and do it
int checkTheMooveAndMoove(int r, int c, int map[r][c], char move, int timerOfABomb, Joueur joueur);

// TODO : verif
// Check end game conditions
int verif_victoire(int maxPlayer, Joueur* playerList);

#endif //CASSEBRIQUE_JOUEUR_H
