#include "Map.h"

int main(int argc, char** argv) {
    int rows = 2;
    int columns = 3;
    Map *m = createMap(rows,columns);

    printf("%d ", isFree(m, 0, 0));
    freeMap(m, rows);


    printf("%c\n", 176);

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


    // === BOUCLE DE JEU ===
    int end = 0;
    char input;

    while(end != 1){
        // TODO : Fonction Affichage ATH

        // Affichage map
        displayMap(7, 7, map1);

        // Input
        printf("Action a effectuer :");
        scanf("&c", input);
        fflush(stdin);

        // Verif Input
        //TODO : Fonction Vérification d'input
        int verifInput = fonctionVerifInputQuiEstACoder();

        // Si input pas OK
        if(verifInput == 0) {
            continue;
        }

        // TODO : Màj de la map


        // TODO : Tik des bombes


        // TODO : explosion des bombes (peut être mettre ça dans la fonction de tik des bombes)


        // TODO : Màj de la map
        

        }

    }

    return 0;
}
