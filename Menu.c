#include "Menu.h"
#include "Map.h"
#include "Joueur.h"

void accueil() {
    setbuf(stdout, 0);
    printf("Bienvenue sur le jeu Casse Brique\n");
}

void choixPossible() {
    setbuf(stdout, 0);
    printf("1 - Demarrer une nouvelle partie\n");
    setbuf(stdout, 0);
    printf("2 - Demarrer le serveur\n");
    setbuf(stdout, 0);
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
        printTab(m->tab, m->nbLignes, m->nbColonnes);
        //displayMap(m->nbLignes, m->nbColonnes, m->tab);

        // Input
        if (!inputAllowed) {
            setbuf(stdout, 0);
            printf("Mouvement non reconnu. Rejouez.\n");
            inputAllowed = true;
        }
        if (!moovePossible) {
            setbuf(stdout, 0);
            printf("Mouvement impossible. Rejouez.\n");
            moovePossible = true;
        }

        // Ask Input
        setbuf(stdout, 0);
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
    setbuf(stdout, 0);
    printf("Faites votre choix : \n");

    int choix;
    scanf("%d", &choix);
    fflush(stdin);
    char *configurationFiles[] = {"exampleMap.txt",
                                  "exampleMap2.txt",
                                  "exampleMap3.txt"
    };
    switch (choix) {
        case 1:
            printf("Une nouvelle partie commence : %d\n", choix);
            srand(time(NULL));
            int fileIndex = rand() % 3;

            Map *m = createMapViaFile(configurationFiles[0]);
            printf("%d", m->nbLignes);
            game(m);
            freeMap(m, m->nbLignes);

        case 2:
            setbuf(stdout, 0);
            printf("Un nouveau serveur vient d'être lancé : %d\n", choix);
            return true;
        case 3:
            setbuf(stdout, 0);
            printf("Voici la liste des serveurs disponibles : %d\n", choix);
            return true;
        default:
            setbuf(stdout, 0);
            printf("Le choix est incorrect : Réessayer : \n");
            return false;
    }
}

