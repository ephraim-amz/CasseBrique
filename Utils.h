#ifndef CASSEBRIQUE_UTILS_H
#define CASSEBRIQUE_UTILS_H

#include "Joueur.h"

typedef struct {
    int row;
    int column;
    Joueur **state;
} Board;

typedef struct {
    Joueur **players;
    int playerCount;
    Board *board;
} Game;

Board *create_board(int row, int column, int winCount);

Game *init_game(int playerCount, int row, int column, int winCount);

int wait_column_input();

int play(const Board *board, Joueur *player, int column);

void free_game(Game *game);

void free_board(Board *board);

void print_board(const Board *board);

void print_game_over();

#endif //CASSEBRIQUE_UTILS_H
