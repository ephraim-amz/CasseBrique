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

bool isAlive(Joueur* j){
    return j->nbVies >= 1;
}

void removeLife(Joueur* j){
    if (isAlive(j)){
        j->nbVies--;
        printf("Joueur %d, il vous reste %d vie(s)\n", j->numPlayer, j->nbVies);
    } else{
        printf("Joueur %d, vous venez êtes mort à cause d'une bombe\n", j->numPlayer);
        freePlayer(j);
    }
}

void freePlayer(Joueur *j) {
    freeBombe(j->bombes);
    free(j);
}