#include "Map.h"
#include "Menu.h"
#include "colors.h"

int main(int argc, char** argv) {
    bool choix = false;

    while (!choix) {
        accueil();
        choix = choixUtilisateur();
    }

    // TODO : free memory


    return 0;
}
