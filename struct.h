#ifndef CASSEBRIQUE_STRUCT_H
#define CASSEBRIQUE_STRUCT_H

#include <stdbool.h>


typedef struct {
    int portee;
    bool estPose;
} Bombe;


typedef struct {
    int id;                 // id du joueur
    int nbVies;             // nombre d'explosions nécessaires pour tuer un joueur
    int coeur;              // bouclier
    int nbBombesMax;        // nombre maximum de bombe posable par le joueur
    int nbBombesActuel;     // nombre de bombes du joueur en ce moment même sur le terrain
    int powerBombe;         // puissance de la bombe
    int boots;              // équipement permettant de déplacer les bombes
    int pass;               // équipement permettant de passer sur une bombe
    int invincible;         // nombre de tours d'invincibilite
    int alreadyHurt;        // dit si le joueur a déjà été blessé dans le tour

    // TODO : verif
    Bombe *bombes;
} Joueur;


typedef struct {
    // Infos de la map
    //int* tab; // Le tableau en 2d
    int** tab; // Le tableau en 2d

    int nbLignes;
    int nbColonnes;
    int taux_loot;        // chance qu'une caisse lache un item = 1/taux_loot

    // Infos pour initialiser les joueurs
    int nbMaxPlayer;

    int start_nbVies;
    int start_coeur;
    int start_nbBombe;
    int start_powerBombe;
    int bombe_compteur;
    int start_boots;
    int start_pass;
    Joueur *joueurs; // La liste des joueurs
} Map;




#endif //CASSEBRIQUE_STRUCT_H
