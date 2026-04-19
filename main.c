#include "game.h"
#include "bot.h"
#include <stdio.h>

int main() {
    int r1, c1, r2, c2; //Rows and columns for 2 points

    char player = 'A'; //Start with player A

    int moveres; //Stores result of the move attempt

    int fullbox; //Stored number of boxes completed in a turn

    int scoreA = 0, scoreB = 0;
    int total = 0; //Total boxes completed (game ends at 20)

    int mode;
    printf("1. Human vs Human\n2. Human vs Bot\nChoose: ");
    scanf("%d", &mode);

    initBoard();

    /*The game continues until all 20 boxes have been taken*/
    while (total < 20) {
        printBoard(); //Show grid currently

        if (mode == 2 && player == 'B') {
            Move b = getBotMove();
            r1 = b.r1; c1 = b.c1; r2 = b.r2; c2 = b.c2;
            printf("--- Bot's Turn ---\nBot chose: %d %d %d %d\n", r1, c1, r2, c2);

        } else {
            printf("--- Player %c's Turn ---\n", player);
            printf("Connect Dot 1 (row, column) and Dot 2 (row col): ");
            if (scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4) {
                while(getchar() != '\n');
                continue;
            }
        }

        moveres = addLine(r1, c1, r2, c2, player);

        if (moveres == 0) {
            fullbox = checkForBoxes(player);
            if (fullbox > 0) {
                if (player == 'A') scoreA += fullbox;
                else scoreB += fullbox;
                total += fullbox;

                //Player continues if closed a box
                printf("You have completed %d box(es), continue\n", fullbox);
            //Switch players
            } else {
                if (player == 'A') { player = 'B'; }
                else { player = 'A'; }
            }
        } else {
            printf("Invalid move\n"); 
        }
    }
    printBoard();

    //Show final board shape and game over
    printf("Game Over. Saving results...\nFinal results: Player A: %d | Player B: %d\n", scoreA, scoreB);
    if (scoreA > scoreB) printf("Player A wins.");
    else if (scoreA < scoreB) printf("Player B wins.");
    else printf("It's a tie.");
    return 0;
}
