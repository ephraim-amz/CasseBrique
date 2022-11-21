#include "Decrementation.h"

// Décrementation du compteur des bombes
// vérification d'explosion de bombe
// Rajout d'une bombe dans la struct du J concerné
void decrementationMap(Map *m) {

    for (int k = 1; k <= m->nbMaxPlayer; k++) {
        // on cherche ici des bombes en fonction des joueurs et de la puissance
        // (ex : bombe 225 ou 2225 (si le J2 est posé dessus))
        int valeur_min_bombe = (k * 1000) + 100;
        int valeur_max_bombe = (k * 1000) + 999;
        int valeur_min_bombe_joueur = valeur_min_bombe + (k * 10000);
        int valeur_max_bombe_joueur = valeur_max_bombe + (k * 10000);
        int valMaxPowerUp = 9;


        for (int i = 0; i < m->nbLignes; i++) {
            for (int j = 0; j < m->nbColonnes; j++) {
                // si la valeur est supérieure à la valeur minimale (ex : 110)
                // alors elle n'a pas encore explosée donc --> décrementation
                if ((m->tab[i][j] > valeur_min_bombe && m->tab[i][j] < valeur_max_bombe) ||
                    (m->tab[i][j] > valeur_min_bombe_joueur && m->tab[i][j] <
                                                               valeur_max_bombe_joueur)) // j'ai besoin de la "valeur_max_bombe_joueur" si le J est posé dessus
                {
                    // Décrémentation du compteur de la bombe
                    m->tab[i][j] -= 1;

                    // on vérifie si une bombe explose
                    int valeur_min_check = valeur_min_bombe;
                    int valeur_min_check_joueur = valeur_min_bombe_joueur;

                    // on a fait la décrementation en amont donc si une valeur atteint la "valeur min" alors il y a explosion
                    for (int x = 0; x < valMaxPowerUp; x++) // 9 est la valeur max des power up
                    {
                        if (m->tab[i][j] == valeur_min_check || m->tab[i][j] == valeur_min_check_joueur) {

                            // bombe_joueur retrouve le numéro du joueur (-1 pour l'index dans le tableau de joueurs)
                            int bombe_joueur = ((m->tab[i][j] % 10000) / 1000) - 1;
                            int bombe_power = (m->tab[i][j] % 1000) / 100;
                            Joueur* joueurList = m->joueurs;

                            // dégâts de l'explosion
                            afterExplosion(m, bombe_power, i, j, joueurList, bombe_joueur);


                            displayMap(m->nbLignes, m->nbColonnes, (Map *) m->tab);

                            break;

                        } else {
                            // +10 correspond aux différentes valeurs que pourrait posséder une bombe (en fonction des power up)
                            valeur_min_check += 100;
                            valeur_min_check_joueur += 100;
                        }
                    }
                }
            }
        }
    }
}


void decrementationInvul(Joueur* playerList, int maxPlayer){
    for (int i = 0; i < maxPlayer; ++i) {
        if(playerList[i].invincible > 0){
            playerList[i].invincible -= 1;
        }
        playerList[i].alreadyHurt = 0;
    }
}