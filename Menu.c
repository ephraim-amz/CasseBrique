#include "Menu.h"
#include "Map.h"
#include "Joueur.h"

void accueil() {

    printf("Bienvenue sur le jeu Casse Brique\n");
}

void choixPossible() {

    printf("1 - Demarrer une nouvelle partie\n");

    printf("2 - Demarrer le serveur\n");

    printf("3 - Rejoindre un serveur\n");
}

void game(Map *m) {
    int actualPlayer = 1;
    int maxPlayer = m->nbMaxPlayer;
    bool end = false;
    bool inputAllowed = true, moovePossible = true;
    char input;

    while (!end) {
        // TODO : Fonction Affichage ATH
        // Faut aller chercher dans la structure des joueurs leurs paramètres actuels.
        // rajouter en paramètre de la fonction le numéro du joueur pour pouvoir afficher genre "Tour du joueur 1"
        // rajouter en paramètre de la fonction un int code erreur pour afficher genre "Coup invalide. Rejouer"

        // Affichage map
        displayMap(m->nbLignes, m->nbColonnes, m->tab);


        // Input
        if (!inputAllowed) {

            printf("Mouvement non reconnu. Rejouez.\n");
            inputAllowed = true;
        }
        if (!moovePossible) {

            printf("Mouvement impossible. Rejouez.\n");
            moovePossible = true;
        }

        // Ask Input

        printf("Tour du Joueur %d \nAction a effectuer :\n", actualPlayer);
        scanf("%c", &input);
        fflush(stdin);

        // Verification de l'input
        inputAllowed = checkInput(input);

        // Si input pas OK on revient au début de la boucle
        if (inputAllowed == 0) {
            continue;
        }

        moovePossible = checkTheMooveAndMoove(m->nbLignes, m->nbColonnes, m, actualPlayer, input);
        if (!moovePossible) {
            continue;
        }

        // TODO : Màj de la map




        if (actualPlayer == maxPlayer) {
            actualPlayer = 1;
        } else {
            ++actualPlayer;
        }
        //end =1;
        bool isOver = verifVictoire(m->nbMaxPlayer, m->joueurs);
        if (isOver) {
            end = true;
        }
    }

}


bool choixUtilisateur() {

    printf("Faites votre choix : \n");

    int choix;
    scanf("%d", &choix);
    fflush(stdin);
    char *configurationFiles[] = {"exampleMap.txt",
                                  "exampleMap2.txt",
                                  "exampleMap3.txt"
    };
    switch (choix) {
        case 1: {
            int fileIndex = rand() % 3;

            Map *m = createMapViaFile(configurationFiles[fileIndex]);
            printf("Une nouvelle partie commence : %d\n", choix);


            game(m);


            freeMap(m, m->nbLignes);
        }


        case 2:

            printf("Un nouveau serveur vient d'être lancé : \n", choix);
            return true;
        case 3:

            printf("Voici la liste des serveurs disponibles : \n", choix);
            return true;
        default:

            printf("Le choix est incorrect : Réessayer : \n", choix);
            return true;
    }
}

