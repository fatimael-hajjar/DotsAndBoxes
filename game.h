#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

/* Grid dimensions*/
#define ROWS 5
#define COLS 6

/*Function prototypes*/

// Initializes the game board with empty
void initBoard();

//Displays the board currently
void printBoard();

//Draw line between two points chosen by the player and returns 1 if works, 0 if not
int addLine(int r1, int c1, int r2, int c2, char player);

//Checks if the last move completed any boxes, returns the numbers of boxes completed to update the score
int checkForBoxes(char player);

#endif
