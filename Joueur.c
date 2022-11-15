#include "Joueur.h"
#include "Map.h"

Joueur createJoueur(int nbVies, int nbBombesMax, int nbBombesActuel, int powerBombe, int numPlayer) {
    Bombe *b = malloc(sizeof(Bombe) * nbBombesMax);
    for (int i = 0; i < nbBombesMax; ++i) {
        b[i] = createBombe(powerBombe);
    }
    Joueur j = {
            .nbVies = nbVies,
            .nbBombesMax = nbBombesMax,
            .nbBombesActuel = nbBombesActuel,
            .powerBombe = powerBombe,
            .bombes = b,
            .numPlayer = numPlayer
    };

    return j;
}

int checkInput(char input) {
    if (
            input == 'u'
            || input == 'd'
            || input == 'l'
            || input == 'r'
            || input == 'x'
            || input == 'w'
            ) {
        return 1;
    } else {
        return 0;
    }
}


void freePlayer(Joueur *j) {
    freeBombe(j->bombes);
    free(j);
}