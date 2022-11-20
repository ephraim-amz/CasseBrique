#include "Decrementation.h"

// Décrementation du compteur des bombes
// vérification d'explosion de bombe
// Rajout d'une bombe dans la struct du J concerné

// Posibilité de stocker la position de la bombe qui explose

/// PROBLEME, NE REMET PAS A JOUR LE NBR DE BOMB DANS STRUCT LORSQUE LE J EST SUR LA BOMBE

int decrementation(int **tab, int r, int c, Joueur *joueur_array, int nbr_players) {
    int explosion = 0;
    for (int k = 1; k <= nbr_players; k++) {
        // on cherche ici des bombes en fonction des joueurs et de la puissance (ex : bombe 225 ou 2225 (si le J2 est posé dessus))
        int valeur_min_bombe = (k * 1000) + 100;
        int valeur_max_bombe = (k * 1000) + 990;
        int valeur_min_bombe_joueur = valeur_min_bombe + (k * 10000);
        int valeur_max_bombe_joueur = valeur_max_bombe + (k * 10000);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                // si la valeur est supérieur à la valeur minimale (ex : 110) alors elle n'a pas encore explosée donc --> décrementation
                if ((tab[i][j] > valeur_min_bombe && tab[i][j] < valeur_max_bombe) ||
                    (tab[i][j] > valeur_min_bombe_joueur && tab[i][j] <
                                                            valeur_max_bombe_joueur)) // j'ai besoin de la "valeur_max_bombe_joueur" si le J est posé dessus
                {
                    tab[i][j] -= 1;
                    /// on vérifie si une bombe explose ///
                    int valeur_min_check = valeur_min_bombe;
                    int valeur_min_check_joueur = valeur_min_bombe_joueur;
                    // on a fait la décrementation en amont donc si une valeur atteint la "valeur min" alors il y a explosion
                    for (int x = 0; x < 9; x++) // 9 est la valeur max des power up
                    {
                        if (tab[i][j] == valeur_min_check || tab[i][j] == valeur_min_check_joueur) {
                            explosion = 1;
                            // bombe_joueur retrouve le numéro du joueur (-1 pour l'index dans le tableau de joueurs)
                            int bombe_joueur = (tab[i][j] / 1000) - 1;
                            if (tab[i][j] == valeur_min_check_joueur) {
                                bombe_joueur = (tab[i][j] / 10000) - 1;
                            }
                            if (joueur_array[bombe_joueur].nbBombesActuel < joueur_array[bombe_joueur].nbBombesMax) {
                                // mise à jour du nombre de bombes
                                joueur_array[bombe_joueur].nbBombesActuel += 1;
                            }
                            break;
                        } else {
                            // +10 correspond au différentes valeurs que pourrait posséder une bombe (en fonction des power up)
                            valeur_min_check += 100;
                            valeur_min_check_joueur += 100;
                        }
                    }
                }
            }
        }
    }
    return explosion;
}


int decrementationMap(Map *m) {
    int explosion = 0;
    for (int k = 1; k <= m->nbMaxPlayer; k++) {
        // on cherche ici des bombes en fonction des joueurs et de la puissance (ex : bombe 225 ou 2225 (si le J2 est posé dessus))
        int valeur_min_bombe = (k * 1000) + 100;
        int valeur_max_bombe = (k * 1000) + 999;
        int valeur_min_bombe_joueur = valeur_min_bombe + (k * 10000);
        int valeur_max_bombe_joueur = valeur_max_bombe + (k * 10000);
        int valMaxPowerUp = 9;


        for (int i = 0; i < m->nbLignes; i++) {
            for (int j = 0; j < m->nbColonnes; j++) {
                // si la valeur est supérieure à la valeur minimale (ex : 110) alors elle n'a pas encore explosée donc --> décrementation
                if ((m->tab[i][j] > valeur_min_bombe && m->tab[i][j] < valeur_max_bombe) ||
                    (m->tab[i][j] > valeur_min_bombe_joueur && m->tab[i][j] <
                                                               valeur_max_bombe_joueur)) // j'ai besoin de la "valeur_max_bombe_joueur" si le J est posé dessus
                {
                    m->tab[i][j] -= 1;
                    /// on vérifie si une bombe explose ///
                    int valeur_min_check = valeur_min_bombe;
                    int valeur_min_check_joueur = valeur_min_bombe_joueur;
                    // on a fait la décrementation en amont donc si une valeur atteint la "valeur min" alors il y a explosion
                    for (int x = 0; x < valMaxPowerUp; x++) // 9 est la valeur max des power up
                    {
                        if (m->tab[i][j] == valeur_min_check || m->tab[i][j] == valeur_min_check_joueur) {
                            explosion = 1;

                            // bombe_joueur retrouve le numéro du joueur (-1 pour l'index dans le tableau de joueurs)
                            int bombe_joueur = (m->tab[i][j] / 1000) - 1;


                            afterExplosion(m, m->joueurs[bombe_joueur].bombes[0], i, j);

                            if (m->tab[i][j] == valeur_min_check_joueur) {
                                bombe_joueur = (m->tab[i][j] / 10000) - 1;
                            }

                            if (m->joueurs[bombe_joueur].nbBombesActuel < m->joueurs[bombe_joueur].nbBombesMax) {
                                // mise à jour du nombre de bombes
                                m->joueurs[bombe_joueur].nbBombesActuel += 1;
                            }

                            break;

                        } else {
                            // +10 correspond au différentes valeurs que pourrait posséder une bombe (en fonction des power up)
                            valeur_min_check += 100;
                            valeur_min_check_joueur += 100;
                        }
                    }
                }
            }
        }
    }
    return explosion;
}