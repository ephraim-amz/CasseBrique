#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#ifndef CASSEBRIQUE_MAP_H
#define CASSEBRIQUE_MAP_H

/**
 * @brief Structure map
 */
typedef struct {
    int **tab;
    int rows;
    int columns;
} Map;

/**
 * @brief Structure mur
 */
typedef struct {
    int x;
    int y;
} Mur;

Map *createMap(int rows, int columns);

Mur *createMur(Map *m);

bool isFree(Map *m, int x, int y);

bool isAWall(Mur *mur, int x, int y);

int **createTab(int rows, int columns);

void freeTab(int **tab, int r);

void freeMap(Map *map, int r);

void printTab(int** tab, int r, int c);

#endif //CASSEBRIQUE_MAP_H
