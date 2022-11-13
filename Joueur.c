#include "Joueur.h"
#include "Map.h"
#include "colors.h"

void free_player(Joueur* j){
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
            if(actualRow == r - 1){
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
            if(actualColumn == c - 1){
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


int verif_victoire(int maxPlayer, Joueur* playerList){
    int players_alive = maxPlayer;
    int winnerID = 0;


    for (int i = 0; i < maxPlayer; i ++)
    {
        if(playerList[i].nbVies == 0)
        {
            players_alive -= 1;
        }
        else
        {
            winnerID = playerList[i].id;
        }
    }

    if(players_alive == 1){
        green();
        printf("Le gagnant est J%d", winnerID);
        resetColor();
        return 1;
    }
    if(players_alive == 0){
        red();
        printf("Tout le monde est mort !!");
        resetColor();
        return 1;
    }
    return 0;
}