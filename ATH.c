#include <stdio.h>

void red(){
    printf("\033[1;31m");
}
void yellow(){
    printf("\033[1;33m");
}
void green(){
    printf("\033[1;32m");
}
void cyan(){
    printf("\033[1;36m");
}
void blue(){
    printf("\033[1;34m");
}
void black(){
    printf("\033[0;30m");
}
void resetColor(){
    printf("\033[0m");
}

typedef struct
{
    int vie;
    int nbBombeMax;
    int nbBombActuel;
    int powerBomb;
    int num_player;
}Joueur;

//// VERIF VICTOIRE ////

int verif_victoire(int nbr_players, Joueur *joueur_array){
    int players_alive = nbr_players;
    /// nbr de joueurs en vie
    for (int i = 0; i < nbr_players; i ++)
    {
        if(joueur_array[i].vie == 0)
        {
            players_alive -=1;
        }
    }

    if(players_alive == 1){

        for (int i = 0; i < nbr_players; i ++){

            if(joueur_array[i].vie >= 1)
            {
                green();
                printf("Le gagnant est J%d", joueur_array[i].num_player);
                resetColor();
            }
            }
    }
    if(players_alive == 0){
        red();
        printf("Tout le monde est mort !!");
        resetColor();
    }
    return 0;
}

//////////////////////////////////////////
//////////////////////////////////////////

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

    for(int i = 0; i<nbr_players;i++)
    {
        joueur_array[i].vie = 0;
        joueur_array[i].nbBombeMax = 1;
        joueur_array[i].nbBombActuel = 1;
        joueur_array[i].powerBomb = 1;
        joueur_array[i].num_player = num_joueur;
        num_joueur++;
    }

    joueur_array[0].vie = 0;
    joueur_array[2].vie = 1;

    for(int i =0; i<nbr_players; i++)
    {
        
    ///////////
    //Couleurs//
    ///////////

        switch (joueur_array[i].num_player) {
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



        if(joueur_array[i].vie == 0){
            black();
            printf(":dead: J%d, x%d %c | x%d %c | x%d POWA :dead: \n", joueur_array[i].num_player, joueur_array[i].vie, 3,
            joueur_array[i].nbBombActuel, 162, joueur_array[i].powerBomb);
                                    }
        else{

            if(players_turn == joueur_array[i].num_player){
                printf("->  J%d, x%d %c | x%d %c | x%d POWA\n", joueur_array[i].num_player, joueur_array[i].vie, 3,
                joueur_array[i].nbBombActuel, 162, joueur_array[i].powerBomb);    
            }
            else{
                printf("    J%d, x%d %c | x%d %c | x%d POWA\n", joueur_array[i].num_player, joueur_array[i].vie, 3,
                joueur_array[i].nbBombActuel, 162, joueur_array[i].powerBomb);
        }
        resetColor();
            }



    }
    verif_victoire(nbr_players, joueur_array);
    return 0;
}