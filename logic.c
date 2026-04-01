#include "game.h"
#include <stdio.h>
#include <stdlib.h>

int h[5][5]; //stores horizontal lines (1 if drawn, 0 if empty)
int v[4][6]; //Stores vertical line
char boxes[4][5]; //stores the character of the player who closed the box

void initBoard() {
	//Initialize all horizontal lines to 0 at the beginning
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			h[i][j] = 0;
		}
	}

	//initialize all vertical to 0
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			v[i][j] = 0;
		}
	}

	//Initialize all boxes to empty
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			boxes[i][j] = ' ';
		}
	}
}

void printBoard() {
	printf("\n --- DOTS & BOXES ---\n");
	for (int i = 0; i < 5; i++) {

		//Print dots and horizontal lines
		for (int j = 0; j < 6; j++) {
			printf(".");

			//If the horizontal line exists, draw it otherwise leave empty
			if (j < 5) {
				printf(h[i][j] == 1 ? "---" : "   ");
			}
		}
		printf("\n");

		//Print vertical lines and box contents
		if (i < 4) {
			for (int j = 0; j < 6; j++) {

				//Draw vertical line if valid
				printf(v[i][j] == 1 ? "|  " : "   ");

				//Draw the player's initial inside the box if it's completee
				if (j < 5) printf("%c", boxes[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}

int addLine(int r1, int c1, int r2, int c2, char player) {

	//Calculate the distance between the two points
	int rowdif = abs(r1 - r2);
	int coldif = abs(c1 - c2);

	//Line must be exactly 1 unit long either way but not both
	if ((rowdif == 1 && coldif == 0) || (rowdif == 0 && coldif == 1)) {

		//Horizontal lines the same
		if (r1 == r2) {
			int scol = (c1 < c2) ? c1 : c2; //Get the leftmost column index
			if (h[r1][scol] == 1) return -1; //Error: line already exists
			h[r1][scol] = 1; //Mark horizontal line as drawn

		//Case 2 for vertical
		} else {
			int srow = (r1 < r2) ? r1 : r2; //Get the topmost row index
			if (v[srow][c1] == 1) return -1; //Error: Line already exists
			v[srow][c1] = 1; //Mark vertical line as drawn
		}
		return 0;
	}
	return -1; //Too long or diagonal
}

int checkForBoxes(char player) {
	int newbox = 0;

	//Loop through every possible box in the grid
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {

			//Only check boxes that haven't been claimed yet
			if (boxes[i][j] == ' ') {
				if (h[i][j] == 1 && h[i+1][j] == 1 && v[i][j] == 1 && v[i][j+1] == 1) {
					boxes[i][j] = player;
					newbox++;
				}
			}
		}
	}
	return newbox; //Return total boxes closed to update the score
}
