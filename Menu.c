#include "Menu.h"
#include "Map.h"
#include "Joueur.h"
#include "colors.h"
#include "Decrementation.h"
void accueil() {
    printf("#####################\n");
    printf("# --- BOMBERMAN --- #\n");
    printf("#####################\n");
    //printf("#############");
}


void game(Map *mapPlayed) {
    int maxPlayer = mapPlayed->nbMaxPlayer;

    int actualPlayer = 1, end = 0, inputAllowed = 1, moovePossible = 1;
    char input;

    Joueur *playerList = (Joueur *) mapPlayed->joueurs;

    int test = playerList[0].id;

    while (end != 1) {
        // Vérification si le joueur est toujours vivant pour jouer

        if (playerList[actualPlayer - 1].nbVies > 0) {
            // Affichage ATH
            for (int i = 0; i < maxPlayer; ++i) {
                displayATH(playerList[i], actualPlayer);
            }

            // Affichage map
            displayMap(mapPlayed->nbLignes, mapPlayed->nbColonnes, mapPlayed);

            // Input
            if (!inputAllowed)
            {
                red();
                printf("Mouvement non reconnu. Rejouez.\n");
                inputAllowed = 1;
                resetColor();
            }

            if (!moovePossible)
            {
                red();
                printf("Action impossible. Rejouez.\n");
                moovePossible = 1;
                resetColor();
            }

            // Ask Input
            printf("Tour du Joueur %d \nAction a effectuer :%c", actualPlayer, 255);
            scanf("%c", &input);
            fflush(stdin);
            printf("\n\n");

            // Verification de l'input
            inputAllowed = checkInput(input);

            // Vérifie si le mouvement rentré est un mouvement autorisé
            if (inputAllowed == 0) {
                continue;
            }

            // Vérifie si le mouvement entré est réalisable et si oui le fait
            moovePossible = checkTheMooveAndMoove(*mapPlayed, input, playerList[actualPlayer - 1]);
            if (moovePossible == 0) {
                continue;
            }
        }


        // Une fois que tout le monde a joué :
        // Tik des bombes, explosions et Changement du joueur
        if (actualPlayer == maxPlayer) {
            // Tik des bombes et des buffs d'invincibilité +
            // explosion des bombes (mettre ça dans la fonction de tik des bombes)
            decrementationMap(mapPlayed);

            decrementationInvul(playerList, maxPlayer);

            displayMap(mapPlayed->nbLignes, mapPlayed->nbColonnes, mapPlayed);

            actualPlayer = 1;
        } else {
            ++actualPlayer;
        }

        end = verif_victoire(maxPlayer, playerList);
    }

    freeMap(mapPlayed, mapPlayed->nbLignes);
}


bool loadGame() {
    // Charger les fichiers de map
    char *configurationFiles[] = {"maps/Map1.txt",
                                  "maps/Map2.txt",
                                  "maps/Map3.txt",
                                  "maps/Map4.txt"
    };

    // Choix random de la map
    srand(time(NULL));
    int fileIndex = rand()%4;
    printf("Map selectionnee : %d\n", fileIndex + 1);

    // Créé la structure Map en fonction du fichier de config
    Map *m = createMapViaFile(configurationFiles[fileIndex]);


    // Start game
    game(m);

    // TODO : free memory
    freeMap(m, m->nbLignes);

    return 0;
}

