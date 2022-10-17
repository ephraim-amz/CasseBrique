#include "stdlib.h"
#include "stdbool.h"
#include "Map.h"


#ifndef CASSEBRIQUE_BOMBE_H
#define CASSEBRIQUE_BOMBE_H


/**
 * @brief Structure bombe
 */
typedef struct {
    int x;
    int y;
    int portee;
    bool estPose;
} Bombe;


/**
 * @brief Permet de créer une bombe
 * @return
 */
Bombe *createBombe();

/**
 * @brief Permet de désactiver une bombe
 * @param b
 */
void disableBombe(Bombe *b);


#endif //CASSEBRIQUE_BOMBE_H
