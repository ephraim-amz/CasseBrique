#include "Map.h"
#include "Joueur.h"

int main(int argc, char** argv) {
///////////////////////////////////////////////////////
    // MAP D'EXEMPLE
    int row = 7, column = 7;
    int map1[][7] = {
            {2,2,2,2,2,2,2},
            {2,1000,0,1,0,3000,2},
            {2,0,2,1,2,0,2},
            {2,1,1,1,1,1,2},
            {2,0,2,1,2,0,2},
            {2,4000,0,1,0,2000,2},
            {2,2,2,2,2,2,2}
            };
    //displayMap(7, 7, map1);

/*
    // Nombre de joueurs à placer
    int nmbPlayer;
    printf("Nombre de joueurs (max : 4) :");
    scanf("&d", nmbPlayer);
    fflush(stdin);

    if(nmbPlayer < 2 || nmbPlayer > 4){
        nmbPlayer = 2;
    }

    // Nombre de bots parmi ces joueurs
    int nmbBots;
    printf("Nombre de bots (max : %d, defaut : 0) :", nmbPlayer);
    scanf("&d", nmbBots);
    fflush(stdin);

    if(nmbBots < 0 || nmbBots > nmbPlayer){
        nmbBots = 0;
    }
*/

    // TODO : sélectionner une map dans la pool et récupérer les informations de cette map dans un tableau




    // TODO : créer les joueurs en fonction des paramètres de la map

    


    // === BOUCLE DE JEU ===
    int actualPlayer = 1;
    int maxPlayer = 4;
    int end = 0;
    int inputAllowed = 1, moovePossible = 1;
    char input;

    while(end != 1){
        // TODO : Fonction Affichage ATH
        // Faut aller chercher dans la structure des joueurs leurs paramètres actuels.
        // rajouter en paramètre de la fonction le numéro du joueur pour pouvoir afficher genre "Tour du joueur 1"
        // rajouter en paramètre de la fonction un int code erreur pour afficher genre "Coup invalide. Rejouer"

        // Affichage map
        displayMap(7, 7, map1);

        // Input
        if(!inputAllowed){
            printf("Mouvement non reconnu. Rejouez.\n");
            inputAllowed = 1;
        }
        if(!moovePossible){
            printf("Mouvement impossible. Rejouez.\n");
            moovePossible = 1;
        }

        // Ask Input
        printf("Tour du Joueur %d \nAction a effectuer :", actualPlayer);
        scanf("%c", &input);
        fflush(stdin);

        // Verification de l'input
        inputAllowed = checkInput(input);

        // Si input pas OK on revient au début de la boucle
        if(inputAllowed == 0) {
            continue;
        }

        moovePossible = checkTheMooveAndMoove(row, column, map1, actualPlayer, input);
        if(moovePossible == 0) {
            continue;
        }

        // TODO : Màj de la map



        // TODO : Tik des bombes



        // TODO : explosion des bombes (peut être mettre ça dans la fonction de tik des bombes)



        // TODO : Màj de la map



        // TODO : changement du joueur
        if(actualPlayer == maxPlayer) {
            actualPlayer = 1;
        } else {
            ++actualPlayer;
        }
        //end =1;
    }

    return 0;
}
