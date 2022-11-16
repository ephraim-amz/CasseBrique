#ifndef CASSEBRIQUE_MENU_H
#define CASSEBRIQUE_MENU_H

#include <time.h>
#include "Map.h"

void accueil();

void choixPossible();

int choixUtilisateur();

void game(Map* m);

bool testChoix(int choix);
#endif //CASSEBRIQUE_MENU_H
