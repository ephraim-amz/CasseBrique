#include <stdio.h>
#include "struct.h"
#include "Map.h"
#include "Joueur.h"

#ifndef CASSEBRIQUE_DECREMENTATION_H
#define CASSEBRIQUE_DECREMENTATION_H


int decrementationMap(Map *m);

int boom(Map *m);

int decrementation(int **tab, int r, int c, Joueur *joueur_array, int nbr_players);

#endif //CASSEBRIQUE_DECREMENTATION_H
