#include "src/game/game_logic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{

    char *names[2];
    char buffer[100];

    for (int i = 0; i < 2; i++)
    {
        printf("Entrez le nom du joueur %d: ", i + 1);

        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {

            names[i] = malloc(strlen(buffer) + 1);

            strcpy(names[i], buffer);

            names[i][strcspn(names[i], "\n")] = '\0';
        }
    }

    for (int i = 0; i < 2; i++)
    {
        printf("Joueur %d: %s\n", i + 1, names[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        free(names[i]);
    }
    Game game = initGame(names);

    while (game.winner == -1 && !isBoardFull(&game.board))
    {
        printBoard(&game.board);
        playTurn(&game);
    }

    if (game.winner != -1)
    {
        printBoard(&game.board);
        printf("Félicitations, %s a gagné !\n", names[game.winner - 1]);
    }
    else
    {
        printf("Match nul. Le plateau est plein.\n");
    }

    return 0;
}
