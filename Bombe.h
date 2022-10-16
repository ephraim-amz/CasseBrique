#include "stdlib.h"
#include "stdbool.h"


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
 * @param x
 * @param y
 * @return
 */
Bombe *createBombe(int x, int y);

#endif //CASSEBRIQUE_BOMBE_H
