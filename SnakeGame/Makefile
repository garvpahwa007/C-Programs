CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2

snake: snake.c
	$(CC) $(CFLAGS) snake.c -o snake

run: snake
	./snake

clean:
	unlink snake 2>/dev/null || true

.PHONY: run clean
