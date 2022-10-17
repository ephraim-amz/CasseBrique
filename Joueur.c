#include "Joueur.h"


Joueur *createJoueur(char *nom, int numJoueur, int x, int y, int nbBombes){
    Joueur *j = malloc(sizeof(Joueur));
    Bombe **b = malloc(sizeof(Bombe*));
    for (int i = 0; i < j->nbBombes; ++i) {
        b[i] = createBombe();
    }
    *j = (Joueur){
            .nom = nom,
            .numJoueur = numJoueur,
            .x = x,
            .y = y,
            .nbBombes = nbBombes,
            .bombes = b
    };

    return j;
}

void deposerBombe(Joueur *j){
    if(j->nbBombes <= 0) {
        printf("Vous n'avez pas assez de bombes");
    } else {
        j->nbBombes--;

    }
}

void deplacerJoueur(Joueur *j, Map *m, int direction){
    switch (direction) {
        case 1:
            if (isFree(m, j->x, j->y)){
                j->x--;
            }
            break;
        case 2:
            if(isFree(m, j->x, j->y)){
                j->x++;
            }
            break;
        case 3:
            if(isFree(m, j->x, j->y)){
                j->y--;
            }
            break;
        case 4:
            if(isFree(m, j->x, j->y)){
                j->y++;
            }
            break;
    }
}
void bombUp(Joueur *j){
    j->nbBombes++;
}

void bombDown(Joueur *j){
    j->nbBombes--;
}

void free_player(Joueur *j){
    free(j->nom);
    free(j);
}