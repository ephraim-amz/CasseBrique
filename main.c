#include "Map.h"
#include "Menu.h"

int main() {

    /*

    bool choix = false;


    while (!choix) {
        accueil();
        choixPossible();
        choix = choixUtilisateur();
    }
     */

    Map *map = createMapViaFile("exampleMap.txt");
    int row = 2, column = 2;
    printTab(map->tab, map->nbLignes, map->nbColonnes);
    printf("\n");
    afterExplosion(map, map->joueurs[0].bombes[0], row, column);
    freeMap(map, map->nbLignes);


    return 0;
}
