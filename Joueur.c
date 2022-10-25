#include "Joueur.h"

Joueur createJoueur(int nbVies, int nbBombesMax, int nbBombesActuel, int powerBombe){
    Bombe *b = malloc(sizeof(Bombe));
    for (int i = 0; i < nbBombesMax; ++i) {
        b[i] = createBombe(powerBombe);
    }
    Joueur j = {
            .nbVies = nbVies,
            .nbBombesMax = nbBombesMax,
            .nbBombesActuel = nbBombesActuel,
            .powerBombe = powerBombe,
            .bombes = b
    };

    return j;
}


void free_player(Joueur *j){
    freeBombe(j->bombes);
    free(j);
}