#include "game.h"
#include "network.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void* network_status_thread(void* arg) {
	while(1) {
		pthread_mutex_lock(&game_lock);
		pthread_mutex_unlock(&game_lock);
		sleep(10);
	}
	return NULL;
}

int main() {
	int r1, c1, r2, c2;
	char role;
	char turn = 'A';
	int scoreA = 0, scoreB = 0, total = 0;
	int connection;
	int choice;

	printf("1. Host Game (You are Player A)\n2. Join Game (You are Player B)\nChoose: ");
	fflush(stdout);
	if (scanf("%d", &choice) != 1) {
		while (getchar() != '\n');
	}

	if (choice == 1) {
		role = 'A';
		connection = setupServer();
	} else {
		char ip[100];
		role = 'B';
		printf("Enter Player A's IP address (use 127.0.0.1 if testing on same PC): ");
		scanf("%s", ip);
		connection = connectToServer(ip);
	}

	initBoard();

	pthread_t thread_id;
	pthread_create(&thread_id, NULL, network_status_thread, NULL);

  while (total < 20) {
    GamePacket movedata;
    memset(&movedata, 0, sizeof(GamePacket));
    printBoard();

    if (turn == role) {
      printf("--- YOUR TURN (%c) ---", role);
      printf("Enter points (r1, c1, r2, c2): ");
      if (scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4) {
        while (getchar() != '\n');
        continue;
      }
			
			movedata.r1 = r1; movedata.c1 = c1; movedata.r2 = r2; movedata.c2 = c2;
			send(connection, &movedata, sizeof(GamePacket), 0);
		} else {
			printf("--- WAITING FOR PLAYER %c'S TURN ---", turn);
			int received;
			do {
				received = recv(connection, &movedata, sizeof(GamePacket), 0);
				if (received <= 0) {
					printf("Connection lost\n");
					close(connection);
					return 0;
				}
			} while (movedata.r1 == 0 && movedata.c1 == 0 && movedata.r2 == 0 && movedata.c2 == 0);

			r1 = movedata.r1; c1 = movedata.c1; r2 = movedata.r2; c2 = movedata.c2;
			printf("Player %c chose: %d %d %d %d\n", turn, r1, c1, r2, c2);
		}

		if (addLine(r1, c1, r2, c2, turn) == 0) {
			int newbox = checkForBoxes(turn);
			if (newbox > 0) {
				if (turn == 'A') scoreA += newbox;
				else scoreB += newbox;
				total += newbox;
				printf("Closed %d box(es)! Continue\n", newbox);
			} else {
				turn = (turn == 'A') ? 'B' : 'A';
			}

		} else {
			if (turn == role) printf("Invalid move, try again.\n");
		}
	}
	printBoard();

	printf("Game Over. Saving results...\nFinal results: Player A: %d | Player B: %d\n", scoreA, scoreB);
	if (scoreA > scoreB) printf("Player A wins.");
	else if (scoreA < scoreB) printf("Player B wins.");
	else printf("It's a tie.");
	close(connection);
  printf("Press Enter to exit...");
  getchar(); 
  getchar(); 
	return 0;
}
