#include <stdio.h>
#include "Joueur.h"
#include "Map.h"


//// VERIF VICTOIRE ////

int verif_victoire(int nbr_players, Joueur* joueur_array) {
    int players_alive = nbr_players;
    /// nbr de joueurs en vies
    for (int i = 0; i < nbr_players; i++)
    {
        if (joueur_array[i].nbVies == 0)
        {
            players_alive -= 1;
            freePlayer(&joueur_array[i]);
        }
    }

    if (players_alive == 1) {

        for (int i = 0; i < nbr_players; i++) {

            if (joueur_array[i].nbVies >= 1)
            {
                green();
                printf("Le gagnant est J%d", joueur_array[i].numPlayer);
                resetColor();
            }
        }
    }
    if (players_alive == 0) {
        red();
        printf("Tout le monde est mort !!");
        resetColor();
    }
    return 0;
}

//////////////////////////////////////////
//////////////////////////////////////////
/*
int main()
{
    //////////////////////////////////////////
    ////// PARAMETRES ///////////////////////
    //////////////////////////////////////////

    int nbr_players = 4;
    int num_joueur = 1;
    int players_turn = 3;
    Joueur joueur_array[nbr_players];

    //////////////////////////////////////////
    /////// TABLEAU DES JOUEURS /////////

    for (int i = 0; i < nbr_players; i++)
    {
        joueur_array[i].nbVies = 0;
        joueur_array[i].nbBombesMax = 1;
        joueur_array[i].nbBombesActuel = 1;
        joueur_array[i].powerBombe = 1;
        joueur_array[i].numPlayer = num_joueur;
        num_joueur++;
    }

    joueur_array[0].nbVies = 0;
    joueur_array[2].nbVies = 1;

    for (int i = 0; i < nbr_players; i++)
    {

        ///////////
        //Couleurs//
        ///////////

        switch (joueur_array[i].numPlayer) {
            case 1:
                red();
                break;
            case 2:
                yellow();
                break;
            case 3:
                green();
                break;
            case 4:
                cyan();
                break;
        }



        if (joueur_array[i].nbVies == 0) {
            black();
            printf(":dead: J%d, x%d %c | x%d %c | x%d POWA :dead: \n", joueur_array[i].numPlayer, joueur_array[i].nbVies, 3,
                   joueur_array[i].nbBombesActuel, 162, joueur_array[i].powerBombe);
        }
        else {

            if (players_turn == joueur_array[i].numPlayer) {
                printf("->  J%d, x%d %c | x%d %c | x%d POWA\n", joueur_array[i].numPlayer, joueur_array[i].nbVies, 3,
                       joueur_array[i].nbBombesActuel, 162, joueur_array[i].powerBombe);
            }
            else {
                printf("    J%d, x%d %c | x%d %c | x%d POWA\n", joueur_array[i].numPlayer, joueur_array[i].nbVies, 3,
                       joueur_array[i].nbBombesActuel, 162, joueur_array[i].powerBombe);
            }
            resetColor();
        }



    }
    verifVictoire(nbr_players, joueur_array);
    return 0;
}
 */