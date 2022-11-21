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


Map *createMap(int nbLignes, int nbColonnes, int nbVies, int nbCoeur, int nbMaxPlayer, int nbBombeBase, int txLoot, int start_powerBombe, int bombe_compteur, int start_boots, int start_pass);

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

void updateMapAfterExplosion(Map *map, int bombe_power, int i, int j);




void updateHealth(Joueur joueur);

void afterExplosion(Map *map, int bombe_power, int rowOfBomb, int columnOfBomb, Joueur* joueurList, int owner);

void displayMap(int r, int c, Map* map);
void displayMapDEBUG(int r, int c, Map* map);
//void displayMap(int r, int c, int** map);


#endif //CASSEBRIQUE_MAP_H
