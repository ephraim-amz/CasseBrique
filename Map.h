#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Joueur.h"


#ifndef CASSEBRIQUE_MAP_H
#define CASSEBRIQUE_MAP_H


/**
 * @brief Structure map
 */
typedef struct {
    int** tab; // Le tableau en 2d
    int nbColonnes;
    int nbLignes;
    int nbVies;
    int nbMaxPlayer;
    Joueur* joueurs; // La liste des joueurs
    int nbBombeBase;
    float txLoot;
} Map;


Map* createMap(int nbLignes, int nbColonnes, int nbVies, int nbMaxPlayer, int nbBombeBase, float txLoot);

bool checkTheMooveAndMoove(int r, int c, Map *map, int actualPlayer, char move);

bool isFree(Map* m, int row, int column);

bool isAUnbreakableWall(Map* map, int row, int column);

bool isAPlayer(Map *map, int x, int y);

int verifVictoire(int nbr_players, Joueur* joueur_array);

bool isARegularWall(Map* map, int row, int column);

int** createTab(int rows, int columns);

void freeTab(int** tab, int r);

FILE *loadFile(char *filename);

Map *createMapViaFile(char *filename);

int* getInfos(char* filename);

void freeMap(Map* map, int r);

void updateMapAfterExplosion(Map *map, Bombe b, int i, int j);
void afterExplosion(Map *map, Bombe b, int row, int j);

void printTab(int** tab, int nbRows, int nbColumns);

void red();

void yellow();

void green();

void cyan();

void blue();

void black();

void purple();

void resetColor();

void displayMap(int r, int c, int** map);


#endif //CASSEBRIQUE_MAP_H
