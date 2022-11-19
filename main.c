#include "Map.h"

int main(int argc, char** argv) {

    /*
    bool choix = false;




    while (!choix){
        accueil();
        choixPossible();
        choix = choixUtilisateur();
    }
     */

    int* infos = getInfos("map1.txt");

    for (int i = 0; i < 4; ++i) {
        printf("%d\n", infos[i]);
    }


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