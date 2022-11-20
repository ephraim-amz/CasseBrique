#ifndef CASSEBRIQUE_MENU_H
#define CASSEBRIQUE_MENU_H

#include <time.h>
#include "struct.h"
#include "Map.h"

void accueil();


bool choixUtilisateur();


void game(Map* m);

bool testChoix(int choix);
#endif //CASSEBRIQUE_MENU_H
