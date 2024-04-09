// File: game_logic.h
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

typedef enum
{
    NOIR,
    ROUGE,
    VIDE
} Color;

typedef struct
{
    Color color;
} Pawn;

#define COLONNE_SIZE 6
typedef struct
{
    Pawn pawn[COLONNE_SIZE];
    int nbPawn;
} Column;

void initColumn(Column *column);
int addPawnToColumn(Column *column, Color color);
int checkWinCondition(const Column columns[], int nbColumns);
void initGame(Column columns[], int nbColumns);

#endif
