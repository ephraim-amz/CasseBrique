#ifndef CASSEBRIQUE_BOMBE_H
#define CASSEBRIQUE_BOMBE_H
#include "stdlib.h"
#include "stdbool.h"
#include "Map.h"


int dropLoot(int taux_loot);
/*
typedef struct {
    int portee;
    bool estPose;
} Bombe;
*/
/**
 * @brief Permet de créer une bombe
 * @return
 */
Bombe createBombe(int portee);


void freeBombe(Bombe *b);


#endif //CASSEBRIQUE_BOMBE_H