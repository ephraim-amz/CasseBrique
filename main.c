#include "Map.h"

int main(int argc, char** argv) {
    /*int rows = 2;
    int columns = 3;
    Map *m = createMap(rows,columns);

    printf("%d ", isFree(m, 0, 0));
    freeMap(m, rows);

    ///////////////////////////////////////////////////////
    // MAP D'EXEMPLE
    int map1[][7] = {
            {2,2,2,2,2,2,2},
            {2,100,17,1,0,300,2},
            {2,0,2,1,2,39,2},
            {2,1,1,1,1,1,2},
            {2,42,2,1,2,0,2},
            {2,400,0,1,26,200,2},
            {2,2,2,2,2,2,2}
    };
    displayMap(7, 7, map1);
    */

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


    // TODO : sélectionner une map dans la pool et récupérer les informations de cette map dans un tableau




    // TODO : créer les joueurs en fonction des paramètres de la map

    


    // === BOUCLE DE JEU ===
    int actualPlayer = 1;
    int end = 0;
    char input;

    while(end != 1){
        // TODO : Fonction Affichage ATH
        // Faut aller chercher dans la structure des joueurs leurs paramètres actuels.
        // rajouter en paramètre de la fonction le numéro du joueur pour pouvoir afficher genre "Tour du joueur 1"
        // rajouter en paramètre de la fonction un int code erreur pour afficher genre "Coup invalide. Rejouer"

        // Affichage map
        displayMap(7, 7, map1);


        // Input
        printf("Action a effectuer :");
        scanf("&c", input);
        fflush(stdin);

        // Verif Input
        //TODO : Fonction Vérification d'input
        int verifInput = fonctionVerifInputQuiEstACoder();

        // Si input pas OK on revient au début de la boucle
        if(verifInput == 0) {
            continue;
        }

        // TODO : Màj de la map



        // TODO : Tik des bombes



        // TODO : explosion des bombes (peut être mettre ça dans la fonction de tik des bombes)



        // TODO : Màj de la map



        // TODO : changement du joueur
        if(actualPlayer == nmbPlayer) {
            actualPlayer = 1;
        } else {
            ++actualPlayer;
        }

    }

    return 0;
}
