#include "Map.h"
#include "colors.h"

int main(int argc, char** argv) {
///////////////////////////////////////////////////////
    // TODO : sélectionner une map dans la pool et récupérer ses informations
    // TODO créer la structure de la map à partir des information récupérées
    // MAP D'EXEMPLE
    int map1[7][7] = {
            {2,0,2,2,2,2,2},
            {0,10000,0,1,0,30000,0},
            {2,0,2,1,2,0,2},
            {2,1,1,1,1,1,2},
            {2,0,2,1,2,0,2},
            {2,40000,0,1,0,20000,2},
            {2,0,2,2,2,2,2}
    };

    Map mapPlayed = {
            .tab = (int **) map1,
            .nbLignes = 7,
            .nbColonnes = 7,
            .taux_loot = 2,

            .nbMaxPlayer = 4,
            .start_nbVies = 1,
            .start_nbBombe = 1,
            .start_powerBombe = 1,
            .bombe_compteur = 4,
            .start_boots = 0
    };

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
                displayATH(playerList[i], actualPlayer);
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

            // Vérifie si le mouvement rentré est un mouvement autorisé
            if(inputAllowed == 0) {
                continue;
            }

            // Vérifie si le mouvement entré est réalisable et si oui le fait
            moovePossible = checkTheMooveAndMoove(mapPlayed.nbLignes, mapPlayed.nbColonnes, map1, input, mapPlayed.bombe_compteur, playerList[actualPlayer]);
            if(moovePossible == 0) {
                continue;
            }
        }


        // Tik des bombes, explosions et Changement du joueur
        if(actualPlayer == maxPlayer) {
            // TODO : Tik des bombes

            // TODO : explosion des bombes (mettre ça dans la fonction de tik des bombes)

            // TODO : affichage d'une map représentant l'explosion


            actualPlayer = 1;
        } else {
            ++actualPlayer;
        }

        end = verif_victoire(maxPlayer, playerList);
    }

    // TODO : free memory


    return 0;
}
