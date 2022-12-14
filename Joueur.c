#include "Joueur.h"
#include "colors.h"

void free_player(Joueur* j){
    free(j);
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
    // Verification si joueur invincible
    if(j->invincible == 0)
    {
        if(j->coeur > 0)
        {
            j->coeur = -1;
        }
        else
        {
            j->nbVies--;
        }
    }
}


int checkTheMooveAndMoove(Map map, char move, Joueur joueur){
    int r = map.nbLignes;
    int c = map.nbColonnes;
    int** tab = map.tab;
    int timerOfABomb = map.bombe_compteur;

    int actualRow, actualColumn;
    int found = 0;
    int actualPlayer = 10000 * joueur.id;
    int gotBoots = joueur.boots;
    int gotPass = joueur.pass;

    // Find the position of the player
    for(actualRow = 0; actualRow < r; ++actualRow){
        for(actualColumn = 0; actualColumn < c; ++actualColumn){
            if(
                    tab[actualRow][actualColumn] >= actualPlayer
                    && tab[actualRow][actualColumn] <= actualPlayer + 9999
                    ){
                found = 1;
                break;
            }
        }
        if (found){
            break;
        }
    }
    
    if (!found){
        printf("ERREUR : Joueur non present sur le terrain.");
        exit(0);
    }


    int rowToCheck = actualRow, colToCheck = actualColumn;
    // En fonction du mouvement souhaite : trouver les coordonnees de la case d'arrivee
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
            // Verifier s'il n'y a pas d??j?? une bombe sur la case et si le joueur a encore des bombes en stock
            if(tab[actualRow][actualColumn] % 10000 > 0 || joueur.nbBombesActuel == joueur.nbBombesMax)
            {
                return 0;
            }
            else
            {
                int newBomb = joueur.id * 1000 + joueur.powerBombe * 100 + timerOfABomb;
                tab[actualRow][actualColumn] += newBomb;
                ++joueur.nbBombesActuel;
                return 1;
            }
        case 'w':
            return 1;
        default :
            return 0;
    }

    // Verification de ce qu'il y a dans la case d'arriv??e : si upgrade ou case vide -> d??placement OK
    int destination = tab[rowToCheck][colToCheck];

    if(
            destination == 0                                                 // case vide
            || (destination >= 3 && destination <= 12)                       // item
            || (gotPass && (destination >= 1000 && destination <= 9999))     // bombe mais a un item pass
            )
    {
        tab[actualRow][actualColumn] -= actualPlayer;
        tab[rowToCheck][colToCheck] += actualPlayer;

        // catch item
        if(destination >= 3 && destination <= 12){
            switch (destination) {
                case 3:
                    ++joueur.nbBombesMax ;
                    break;
                case 4:
                    if(joueur.nbBombesMax > 1){
                        --joueur.nbBombesMax;
                    }
                    break;
                case 5:
                    if(joueur.powerBombe < 9){
                        ++joueur.powerBombe ;
                    }
                    break;
                case 6:
                    if(joueur.powerBombe > 1){
                        --joueur.powerBombe ;
                    }
                    break;
                case 7:
                    joueur.pass = 1 ;
                    joueur.boots = 0;
                    break;
                case 8:
                    joueur.pass = 0 ;
                    joueur.boots = 1;
                    break;
                case 9:
                    if(joueur.coeur != -1){
                        joueur.coeur = 1;
                    }
                    break;
                case 10:
                    ++joueur.nbVies;
                    break;
                case 11:
                    joueur. invincible = 2;
                    break;
                case 12:
                    joueur.powerBombe = 9;
                    break;
                default:
                    break;
            }
            // l'objet disparait
            tab[rowToCheck][colToCheck] -= destination;
        }
        return 1;
    }

    // S'il y a une bombe, mais que le joueur a des boots --> deplacement OK
    else if(gotBoots && (destination >= 1000 && destination <= 9999)){
        // TODO : calculer la case d'arriv??e de la bombe et l'y d??placer

        return 1;
    }

    return 0;
}


int verif_victoire(int maxPlayer, Joueur* playerList){
    int players_alive = maxPlayer;
    int winnerID = 0;


    for (int i = 0; i < maxPlayer; i ++){
        if(playerList[i].nbVies == 0){
            players_alive -= 1;
        } else {
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