#include "Bombe.h"

Bombe createBombe(int portee){
    Bombe b ={
        .portee = portee,
        .estPose = false,
    };
    return b;
}


void freeBombe(Bombe *b){
    free(b);
}