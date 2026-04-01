CC = gcc

game: main.c logic.c
	$(CC) -g  main.c logic.c -o game

run: game
	./game

clean:
	rm -f game
