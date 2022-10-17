#include "Bombe.h"

Bombe *createBombe(){
    Bombe *b = malloc(sizeof(Bombe));
    *b = (Bombe){
            .x = NULL,
            .y = NULL,
            .portee = 2,
            .estPose = false,
    };
    return b;
}

void enableBombe(Map *m, Bombe *b){
    b->estPose = true;
}

void disableBombe(Bombe *b){
    b->estPose = false;
}