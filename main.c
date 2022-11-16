#include "Map.h"
#include "Menu.h"

int main(int argc, char** argv) {
    int choix = 0;

    while (!choix){
        accueil();
        choixPossible();
        choix = choixUtilisateur();
    }

///////////////////////////////////////////////////////
    // MAP D'EXEMPLE

    //int **map1 = garbage();



    // TODO : sélectionner une map dans la pool et récupérer les informations de cette map dans un tableau
    


    return 0;
}

/*
int **garbage() {
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
    return map1;
}

*/