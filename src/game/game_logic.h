// File: game_logic.h
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include <stdbool.h>
typedef enum
{
    YELLOW,
    RED,
    VOID
} Color;

typedef struct
{
    Color color;
} Pawn;

#define COLONNE_SIZE 6
typedef struct
{
    Pawn pawn[COLONNE_SIZE];
    int nbPawns;
} Column;

#define BOARD_SIZE 6

typedef struct
{
    Column columns[BOARD_SIZE];
    int nbPlaySinceStart;
} Board;

#define NB_PLAYERS 2

typedef struct
{
    char name[20];
    Color color;
} Player;

typedef struct
{
    Board board;
    Player players[NB_PLAYERS];
    int currentPlayer;
    int winner;
} Game;

void printBoard(const Board *board);
void initBoard(Board *board);
void initPlayer(Player *player, const char *name, Color color);
bool winnableOnCol(Column *column);
bool winnableOnLine(Board *board);
bool winnableOnDiagUp(Board *board);
bool winnableOnDiagDown(Board *board);
bool isBoardFull(const Board *board);
bool isWinningMove(Game *game);

bool isColumnFull(const Column *column);
void initColumn(Column *column);
int addPawnToColumn(Column *column, int player);
bool isWinningMove(Game *game);
Game initGame(char *names[2]);
void printBoard(Board *board);
#endif
