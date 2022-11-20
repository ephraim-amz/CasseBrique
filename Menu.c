#include "Menu.h"
#include "Map.h"
#include "Joueur.h"
#include "colors.h"

void accueil() {
    printf("Bienvenue sur le jeu Casse Brique\n");

    printf("1 - Demarrer une nouvelle partie\n");
    printf("2 - Demarrer le serveur\n");
    printf("3 - Rejoindre un serveur\n");
}

void game(Map *mapPlayed) {
    int maxPlayer = mapPlayed->nbMaxPlayer;

    int actualPlayer = 1, end = 0, inputAllowed = 1, moovePossible = 1;
    char input;

    Joueur *playerList = (Joueur *) mapPlayed->joueurs;

    while (end != 1) {
        // Vérification si le joueur est toujours vivant pour jouer
        if (playerList[actualPlayer].nbVies > 0) {
            // Affichage ATH
            for (int i = 0; i < maxPlayer; ++i) {
                displayATH(playerList[i], actualPlayer);
            }

            // Affichage map
            // TODO : correct the issue of map1 : can't pass the map from the struct
            displayMap(mapPlayed->nbLignes, mapPlayed->nbColonnes,
                       mapPlayed);

            // Input
            if (!inputAllowed) {
                red();
                printf("Mouvement non reconnu. Rejouez.\n");
                inputAllowed = 1;
                resetColor();
            }
            if (!moovePossible) {
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
            if (inputAllowed == 0) {
                continue;
            }

            // Vérifie si le mouvement entré est réalisable et si oui le fait
            moovePossible = checkTheMooveAndMoove(mapPlayed->nbLignes, mapPlayed->nbColonnes, (Map *) mapPlayed->tab, input,
                                                  mapPlayed->bombe_compteur, playerList[actualPlayer]);
            if (moovePossible == 0) {
                continue;
            }
        }


        // Tik des bombes, explosions et Changement du joueur
        if (actualPlayer == maxPlayer) {
            // TODO : Tik des bombes et des buffs d'invincibilité

            // TODO : explosion des bombes (mettre ça dans la fonction de tik des bombes)

            // TODO : affichage d'une map représentant l'explosion


            actualPlayer = 1;
        } else {
            ++actualPlayer;
        }

        end = verif_victoire(maxPlayer, playerList);
    }
}


bool choixUtilisateur() {
    printf("Faites votre choix : \n");

    int choix;
    scanf("%d", &choix);
    fflush(stdin);
    char *configurationFiles[] = {"exampleMap.txt",
                                  "exampleMap2.txt",
                                  "exampleMap3.txt", "exempleMap4.txt"
    };
    switch (choix) {
        case 1:
            printf("Une nouvelle partie commence : %d\n", choix);
            int fileIndex = rand() % 4;

            Map *m = createMapViaFile(configurationFiles[fileIndex]);
            printf("%d", m->nbLignes);
            game(m);
            freeMap(m, m->nbLignes);

        case 2:
            printf("Un nouveau serveur vient d'être lancé : %d\n", choix);
            return true;
        case 3:
            printf("Voici la liste des serveurs disponibles : %d\n", choix);
            return true;
        default:
            printf("Le choix est incorrect : Réessayer : \n");
            return false;
    }
}

