#include "Bombe.h"

Bombe *createBombe(int x, int y){
    Bombe *b = malloc(sizeof(Bombe));
    *b = (Bombe){
            .x = x,
            .y = y,
            .portee = 2,
            .estPose = false,
    };
    return b;
}