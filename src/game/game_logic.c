#include "game_logic.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void initColumn(Column *column)
{
    for (int i = 0; i < COLONNE_SIZE; i++)
    {
        column->pawn[i].color = VOID;
    }
    column->nbPawns = 0;
}

void initBoard(Board *board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        initColumn(&board->columns[i]);
    };
    board->nbPlaySinceStart = 0;
}
void initPlayer(Player *player, char *name, Color color)
{
    strcpy(player->name, name);
    player->color = color;
}

Game initGame(char *names[2])
{
    Game game;
    initBoard(&(game.board)); // Utiliser & pour passer un pointeur si nécessaire
    game.currentPlayer = 1;
    game.winner = -1;
    for (int i = 0; i < 2; i++)
    {
        initPlayer(&(game.players[i]), names[i], i + 1);
    }
    return game;
}

void addPawnToColumn(Column *column, int player)
{
    switch (player)
    {
    case 1:
        column->pawn[column->nbPawns].color = YELLOW;
        break;

    default:
        column->pawn[column->nbPawns].color = RED;
        break;
    }
}

void checkColumn(Column *column, int player)
{
    if (column->nbPawns < COLONNE_SIZE)
    {
        addPawnToColumn(column, player);
        column->nbPawns++;
    }
}

bool winnableOnCol(Column *column)
{
    for (int i = 0; i < COLONNE_SIZE; i++)
    {
        Color precendent;
        int count = 0;
        if (i != 0)
        {
            if (column->pawn[i].color == precendent && precendent != VOID)
            {

                count++;
                if (count == 4)
                {
                    return true;
                }
            }
            else
            {
                count = 1;
            }

            precendent = column->pawn[i].color;
        }
        else
        {

            precendent = column->pawn[i].color;
        }
    }
    return false;
}

/**
 * Checks if there is a winning combination of pawns on any line of the board.
 *
 * @param board The game board.
 * @return true if there is a winning combination, false otherwise.
 */
bool winnableOnLine(Board *board)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        Color precedent = VOID;
        int count = 0;
        for (int j = 0; j < COLONNE_SIZE; j++)
        {
            if (board->columns[j].pawn[i].color == precedent && precedent != VOID)
            {
                count++;
                if (count == 3) // Si on a compté 4 pions consécutifs, count sera à 3.
                {
                    return true;
                }
            }
            else
            {
                // Réinitialisation de count à 1 si la couleur actuelle n'est pas VOID,
                // sinon à 0 si la couleur est VOID.
                count = (board->columns[j].pawn[i].color != VOID) ? 1 : 0;
            }
            precedent = board->columns[j].pawn[i].color;
        }
    }
    return false;
}

bool winnableOnDiagUp(Board *board)
{
    for (int row = 0; row <= BOARD_SIZE - 4; row++)
    {
        for (int col = 0; col <= COLONNE_SIZE - 4; col++)
        {
            Color firstColor = board->columns[col].pawn[row].color;
            if (firstColor != VOID &&
                firstColor == board->columns[col + 1].pawn[row + 1].color &&
                firstColor == board->columns[col + 2].pawn[row + 2].color &&
                firstColor == board->columns[col + 3].pawn[row + 3].color)
            {
                return true;
            }
        }
    }
    return false;
}
bool winnableOnDiagDown(Board *board)
{
    for (int row = 3; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col <= COLONNE_SIZE - 4; col++)
        {
            Color firstColor = board->columns[col].pawn[row].color;
            if (firstColor != VOID &&
                firstColor == board->columns[col + 1].pawn[row - 1].color &&
                firstColor == board->columns[col + 2].pawn[row - 2].color &&
                firstColor == board->columns[col + 3].pawn[row - 3].color)
            {
                return true;
            }
        }
    }
    return false;
}

bool isWinningMove(Game *game)
{
    return winnableOnCol(&game->board.columns[game->board.columns[0].nbPawns - 1]) ||
           winnableOnLine(&game->board) ||
           winnableOnDiagonalUp(&game->board) ||
           winnableOnDiagonalDown(&game->board);
}

bool isColumnFull(Column *column)
{
    return column->nbPawns == COLONNE_SIZE;
}

bool isBoardFull(Board *board)
{
    return board->nbPlaySinceStart == BOARD_SIZE * COLONNE_SIZE;
}

void printBoard(Board *board)
{
    for (int i = 0; i < COLONNE_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            switch (board->columns[j].pawn[i].color)
            {
            case YELLOW:
                printf("Y ");
                break;
            case RED:
                printf("R ");
                break;
            default:
                printf(". ");
                break;
            }
        }
        printf("\n");
    }
}
void playTurn(Game *game)
{
    int col;
    printf("Joueur %d, entrez le numéro de la colonne où vous voulez jouer : ", game->currentPlayer);
    scanf("%d", &col);

    if (col < 1 || col > BOARD_SIZE)
    {
        printf("Colonne invalide. Veuillez essayer à nouveau.\n");
        return;
    }
    col--;

    if (isColumnFull(&game->board.columns[col]))
    {
        printf("Cette colonne est pleine. Veuillez essayer une autre colonne.\n");
    }
    else
    {
        checkColumn(&game->board.columns[col], game->currentPlayer);
        game->board.nbPlaySinceStart++;

        if (isWinningMove(game))
        {
            game->winner = game->currentPlayer;
        }

        game->currentPlayer = (game->currentPlayer == 1) ? 2 : 1;
    }
}