#include "src/game/game_logic.h"
#include <stdio.h>

int main()
{
    char *names[] = {"Joueur 1", "Joueur 2"};
    Game game = initGame(names);

    while (game.winner == -1 && !isBoardFull(&game.board))
    {
        printBoard(&game.board);
        playTurn(&game);
    }

    if (game.winner != -1)
    {
        printf("Félicitations, %s a gagné !\n", names[game.winner - 1]);
    }
    else
    {
        printf("Match nul. Le plateau est plein.\n");
    }

    return 0;
}
