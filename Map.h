#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "math.h"
#include "Joueur.h"

#ifndef CASSEBRIQUE_MAP_H
#define CASSEBRIQUE_MAP_H

/**
 * @brief Structure map
 */
typedef struct {
    // Infos de la map
    int* tab; // Le tableau en 2d
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
} Map;


Map *createMap(int nbLignes, int nbColonnes, int nbVies, int nbMaxPlayer, int nbBombeBase, float txLoot);

// Fonction problématique dans Joueur.c
// Créer un nouveau joueur avec les paramètres par défaut de la map
Joueur* createJoueur(Map mapPlayed);

void freeMap(Map *map, int r);

void displayATH(Joueur player, int actualPlayer);

void printRules(int x);

void displayMap(int r, int c, int map[r][c]);

#endif //CASSEBRIQUE_MAP_H
