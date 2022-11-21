#ifndef CASSEBRIQUE_JOUEUR_H
#define CASSEBRIQUE_JOUEUR_H


#include "struct.h"
#include "Map.h"
#include "Bombe.h"
#include <stdlib.h>

//Libérer un joueur créé en mémoire
void free_player(Joueur *j);


// Check if input is valable
int checkInput(char input);


bool isAlive(Joueur* j);


void removeLife(Joueur* j);


// Check if the moove can be done and do it
int checkTheMooveAndMoove(Map map, char move, Joueur joueur);

// TODO : verif
// Check end game conditions
int verif_victoire(int maxPlayer, Joueur* playerList);


#endif //CASSEBRIQUE_JOUEUR_H
