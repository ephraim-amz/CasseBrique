#ifndef CASSEBRIQUE_JOUEUR_H
#define CASSEBRIQUE_JOUEUR_H

#include "stdbool.h"

typedef struct {
    char *color;
    char token;
    int x;
    int y;
    int nbBombes;
} Joueur;

typedef struct {
    int x;
    int y;
    bool estPose;
} Bombe;

typedef struct {
    int x;
    int y;
} Mur;

typedef struct {
    int x;
    int y;
} Map;

Joueur *create_player(const char *color, char token);

void free_player(Joueur *player);

void print_winner(const Joueur *player);

#endif //CASSEBRIQUE_JOUEUR_H
