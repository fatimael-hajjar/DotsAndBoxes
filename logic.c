#include "game.h"
pthread_mutex_t game_lock = PTHREAD_MUTEX_INITIALIZER;

int h[5][5];
int v[4][6];
char boxes[4][5];

void initBoard() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			h[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			v[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			boxes[i][j] = ' ';
		}
	}
}

void printBoard() {
	printf("\n --- DOTS & BOXES ---\n");
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			printf(".");

			if (j < 5) {
				printf(h[i][j] == 1 ? "---" : "   ");
			}
		}
		printf("\n");

		if (i < 4) {
			for (int j = 0; j < 6; j++) {
				printf(v[i][j] == 1 ? "|  " : "   ");
				if (j < 5) printf("%c", boxes[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}

int addLine(int r1, int c1, int r2, int c2, char player) {
	pthread_mutex_lock(&game_lock);

	int rowdif = abs(r1 - r2);
	int coldif = abs(c1 - c2);
	int result = -1;

	if ((rowdif == 1 && coldif == 0) || (rowdif == 0 && coldif == 1)) {

		if (r1 == r2) {
			int scol = (c1 < c2) ? c1 : c2;
			if (h[r1][scol] == 1) {
        pthread_mutex_unlock(&game_lock);
        return -1;
      }
			h[r1][scol] = 1;
		} else {
			int srow = (r1 < r2) ? r1 : r2;
      if (v[srow][c1] == 1) {
        pthread_mutex_unlock(&game_lock);
        return -1;
      }
			v[srow][c1] = 1;
		}
		pthread_mutex_unlock(&game_lock);
		return 0;
	}
	pthread_mutex_unlock(&game_lock);
	return -1;
}

int checkForBoxes(char player) {
	pthread_mutex_lock(&game_lock);
	int newbox = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (boxes[i][j] == ' ') {
				if (h[i][j] == 1 && h[i+1][j] == 1 && v[i][j] == 1 && v[i][j+1] == 1) {
					boxes[i][j] = player;
					newbox++;
				}
			}
		}
	}
	pthread_mutex_unlock(&game_lock);
	return newbox;
}
