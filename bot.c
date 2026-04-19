#include "game.h"
#include "bot.h"

int getAllValidMoves(Move moves[]) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (h[i][j] == 0) {
                moves[count].r1 = i;
                moves[count].c1 = j;
                moves[count].r2 = i;
                moves[count].c2 = j + 1;
                count++;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            if (v[i][j] == 0) {
                moves[count].r1 = i;
                moves[count].c1 = j;
                moves[count].r2 = i + 1;
                moves[count].c2 = j;
                count++;
            }
        }
    }
    return count;
}

int moveCompletesBox(int r1, int c1, int r2, int c2) {
    int res = 0;
    if (r1 == r2) {
        int scol = (c1 < c2) ? c1 : c2;
        h[r1][scol] = 1;
    } else {
        int srow = (r1 < r2) ? r1 : r2;
        v[srow][c1] = 1;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (boxes[i][j] == ' ' && h[i][j] && h[i+1][j] && v[i][j] && v[i][j+1]) res++;
        }
    }
    if (r1 == r2) h[r1][(c1 < c2 ? c1 : c2)] = 0;
    else v[(r1 < r2 ? r1 : r2)][c1] = 0;
    return res;
}

Move getBotMove() {
    Move moves[1000];
    int total = getAllValidMoves(moves);
    for (int i = 0; i < total; i++) {
        if (moveCompletesBox(moves[i].r1, moves[i].c1, moves[i].r2, moves[i].c2) > 0) {
            return moves[i];
        }
    }
    return moves[0];
}
