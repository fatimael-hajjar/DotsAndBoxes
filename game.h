#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 5
#define COLS 6

void initBoard();
void printBoard();
int addLine(int r1, int c1, int r2, int c2, char player);
int checkForBoxes(char player);

extern int h[5][5];
extern int v[4][6];
extern char boxes[4][5];
extern pthread_mutex_t game_lock;

#endif
