CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lncurses

snake: snake.c
	$(CC) $(CFLAGS) snake.c -o snake $(LIBS)

clean:
	rm -f snake
