#include <stdio.h>
#include "struct.h"
#include "Map.h"
#include "Joueur.h"

#ifndef CASSEBRIQUE_DECREMENTATION_H
#define CASSEBRIQUE_DECREMENTATION_H


void decrementationMap(Map *m);

int boom(Map *m);

void decrementationInvul(Joueur* playerList, int maxPlayer);

#endif //CASSEBRIQUE_DECREMENTATION_H
