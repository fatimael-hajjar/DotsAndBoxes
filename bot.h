#ifndef BOT_H
#define BOT_H

typedef struct {
    int r1, c1, r2, c2;
} Move;

Move getBotMove();
int getAllValidMoves (Move moves[]);
int moveCompletesBox (int r1, int c1, int r2, int c2);

#endif
