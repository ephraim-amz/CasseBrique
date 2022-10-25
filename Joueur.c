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



int checkInput(char input){
    if(
            input == 'u'
            ||input == 'd'
            ||input == 'l'
            ||input == 'r'
            ||input == 'x'
            ||input == 'w'
            ){
        return 1;
    }
    else {
        return 0;
    }
}


int checkTheMooveAndMoove(int r, int c, int map[r][c], int actualPlayer, char move){
    // Find the position of the player
    int actualRow, actualColumn;
    int found = 0;
    actualPlayer *= 1000;

    for(actualRow = 0; actualRow < r; ++actualRow){
        for(actualColumn = 0; actualColumn < c; ++actualColumn){
            if(
                    map[actualRow][actualColumn] >= actualPlayer
                    && map[actualRow][actualColumn] <= actualPlayer + 999
                    ){
                found = 1;
                break;
            }
        }
        if (found){
            break;
        }
    }


    int rowToCheck = actualRow, colToCheck = actualColumn;
    //int
    switch (move) {
        case 'u':
            if(actualRow == 0){
                rowToCheck = r - 1;
            } else {
                rowToCheck = actualRow - 1;
            }
            break;
        case 'd':
            if(actualRow == r + 1){
                rowToCheck = 0;
            } else {
                rowToCheck = actualRow + 1;
            }

            break;
        case 'l':
            if(actualColumn == 0){
                colToCheck = c - 1;
            } else {
                colToCheck = actualColumn - 1;
            }
            break;
        case 'r':
            if(actualColumn == c + 1){
                colToCheck = 0;
            } else {
                colToCheck = actualColumn + 1;
            }
            break;
        case 'x':
            // TODO
            break;
        case 'w':
            return 1;
        default :
            return 0;
    }

    int destination = map[rowToCheck][colToCheck];

    if(destination == 0 || (destination >= 3 && destination <= 9) ){
        map[actualRow][actualColumn] -= actualPlayer;
        map[rowToCheck][colToCheck] += actualPlayer;
        return 1;
    }

    return 0;
}