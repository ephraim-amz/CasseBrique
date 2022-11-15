#include "Map.h"
#include "colors.h"

int main(int argc, char** argv) {
///////////////////////////////////////////////////////
    // TODO : sélectionner une map dans la pool et récupérer ses informations
    // TODO créer la structure de la map à partir des information récupérées
    // MAP D'EXEMPLE
    int map1[7][7] = {
            {2,2,2,2,2,2,2},
            {2,1000,0,1,0,3000,2},
            {2,0,2,1,2,0,2},
            {2,1,1,1,1,1,2},
            {2,0,2,1,2,0,2},
            {2,4000,0,1,0,2000,2},
            {2,2,2,2,2,2,2}
    };

    Map mapPlayed = {
            .tab = (int **) map1,
            .nbColonnes = 7,
            .nbLignes = 7,

            .nbMaxPlayer = 4,
            .start_nbVies = 1,
            .start_nbBombe = 1,
            .start_powerBombe = 1,
            .start_boots = 0
    };
    //displayMap(mapPlayed.nbLignes, mapPlayed.nbColonnes, mapPlayed.tab);

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
    }*/



    // Création des joueurs en fonction des paramètres de la map
    Joueur* playerList = createJoueur(mapPlayed);


    // === BOUCLE DE JEU ===
    int maxPlayer = mapPlayed.nbMaxPlayer;

    int actualPlayer = 1, end = 0, inputAllowed = 1, moovePossible = 1;
    char input;

    while(end != 1){
        // Vérification si le joueur peut jouer
        if(playerList[actualPlayer].nbVies > 0)
        {
            // Affichage ATH
            for (int i = 0; i < maxPlayer; ++i) {
                displayATH(playerList[i], maxPlayer, actualPlayer);
            }

            // Affichage map
            // TODO : correct the issue of map1 : can't pass the map from the struct
            displayMap(mapPlayed.nbLignes, mapPlayed.nbColonnes, map1);

            // Input
            if(!inputAllowed){
                red();
                printf("Mouvement non reconnu. Rejouez.\n");
                inputAllowed = 1;
                resetColor();
            }
            if(!moovePossible){
                red();
                printf("Action impossible. Rejouez.\n");
                moovePossible = 1;
                resetColor();
            }

            // Ask Input
            printf("Tour du Joueur %d \nAction a effectuer :", actualPlayer);
            scanf("%c", &input);
            fflush(stdin);

            // Verification de l'input
            inputAllowed = checkInput(input);

            // Si input pas OK ou moove impossible on revient au début de la boucle
            if(inputAllowed == 0) {
                continue;
            }

            moovePossible = checkTheMooveAndMoove(mapPlayed.nbLignes, mapPlayed.nbColonnes, map1, actualPlayer, input);
            if(moovePossible == 0) {
                continue;
            }

            // TODO : Màj de la map



            // TODO : Tik des bombes



            // TODO : explosion des bombes (peut être mettre ça dans la fonction de tik des bombes)



            // TODO : Màj de la map


        }


        // Changement du joueur
        if(actualPlayer == maxPlayer) {
            actualPlayer = 1;
        } else {
            ++actualPlayer;
        }

        end = verif_victoire(maxPlayer, playerList);
    }

    return 0;
}
