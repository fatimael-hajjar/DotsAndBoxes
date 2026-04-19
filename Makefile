CC = gcc

game: main.c logic.c bot.c
    $(CC) -g main.c logic.c bot.c -o game

run: game
	./game

clean:
	rm -f game
