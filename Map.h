#ifndef CASSEBRIQUE_MAP_H
#define CASSEBRIQUE_MAP_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "struct.h"
#include "Joueur.h"
#include "Bombe.h"


/**
 * @brief Structure map
 */
 /*
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
    struct Joueur *joueurs; // La liste des joueurs
} Map;
*/

Map *createMap(int nbLignes, int nbColonnes, int nbVies, int nbMaxPlayer, int nbBombeBase, int txLoot);

Joueur* createJoueurFromMapData(Map* mapPlayed);

void freeMap(Map *map, int r);

bool isAPlayer(Map *map, int x, int y);

int verifVictoire(int nbr_players, Joueur *joueur_array);

int **createTab(int rows, int columns);

bool isARegularWall(Map *map, int row, int column);

void displayATH(Joueur player, int actualPlayer);

void freeTab(int **tab, int r);

void printRules(int x);

FILE *loadFile(char *filename);

Map *createMapViaFile(char *filename);

int *getInfos(char *filename);

void freeMap(Map *map, int r);

void updateMapAfterExplosion(Map *map, Bombe b, int i, int j);

void afterExplosion(Map *map, Bombe b, int row, int j);

void displayMap(int r, int c, Map* map);
//void displayMap(int r, int c, int** map);


#endif //CASSEBRIQUE_MAP_H
