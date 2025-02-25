CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99

all: minesweeper

minesweeper: main.o minesweeper.o
	$(CC) $(CFLAGS) -o minesweeper main.o minesweeper.o

main.o: main.c minesweeper.h
	$(CC) $(CFLAGS) -c main.c

minesweeper.o: minesweeper.c minesweeper.h
	$(CC) $(CFLAGS) -c minesweeper.c

clean:
	rm -f *.o minesweeper
