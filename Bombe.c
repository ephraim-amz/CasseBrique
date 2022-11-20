#include "Bombe.h"


void freeBombe(Bombe *b){
    free(b);
}


int dropLoot(int taux_loot) {
    if (taux_loot == 0) {
        return 0;
    }

    // check if loot dropped
    int drop = (rand() + 1) % (taux_loot);

    // Si drop == 0, un loot apparait
    if (drop == 0) {
        int loot = (rand() % 100);

        // Fréquence d'apparition des items : (définit de manière totalement arbitraire)
        // nbBombe ++ :     19%
        // nbBombe -- :     19%
        // power ++ :       19%
        // power -- :       19%
        // équipement :     10% (50% boots, 50% pass)
        // coeur :          5%
        // vie :            5%
        // invul :          3%
        // power max :      1%

        if (loot == 0) {
            // power max
            return 12;
        }
        if (loot >= 1 && loot <= 3) {
            // invulnérabilité
            return 11;
        }
        if (loot >= 4 && loot <= 8) {
            // vie
            return 10;
        }
        if (loot >= 9 && loot <= 13) {
            // coeur
            return 9;
        }
        if (loot >= 14 && loot <= 19) {
            // boots
            return 8;
        }
        if (loot >= 20 && loot <= 24) {
            // pass
            return 7;
        }
        if (loot >= 25 && loot <= 43) {
            // power --
            return 6;
        }
        if (loot >= 44 && loot <= 62) {
            // power ++
            return 5;
        }
        if (loot >= 63 && loot <= 80) {
            // nbBombe --
            return 4;
        }
        if (loot >= 81 && loot <= 99) {
            // nbBombe ++
            return 3;
        }
    }

    return 0;
}