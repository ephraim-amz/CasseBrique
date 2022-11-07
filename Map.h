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

bool isFree(Map* m, int x, int y);

bool isAWall(Map* map, int x, int y);

bool isAUnbreakableWall(Map* map, int x, int y);

bool isARegularWall(Map* map, int x, int y);

int** createTab(int rows, int columns);

void freeTab(int** tab, int r);

FILE *loadFile(char *filename);

Map *createMapViaFile(char *filename);

int* getInfos(char* filename);

void freeMap(Map* map, int r);

void exploseBombe(Map *m, Bombe* b);

void printTab(int** tab, int r, int c);

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
