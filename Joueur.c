#include "Joueur.h"


Joueur *createJoueur(char *nom, int numJoueur, int x, int y, int nbBombes, Bombe *bombes){
    Joueur *j = malloc(sizeof(Joueur));
    *j = (Joueur){
            .nom = nom,
            .numJoueur = numJoueur,
            .x = x,
            .y = y,
            .nbBombes = nbBombes,
    };
    return j;
}

void deposerBombe(Joueur *j){
    j->nbBombes--;
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