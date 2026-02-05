CC = gcc
CFLAGS = -fopenmp -Wall -O2

all: hello_world

hello_world: hello_world.c
	$(CC) $(CFLAGS) -o hello_world hello_world.c

clean:
	rm -f hello_world

run: hello_world
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./hello_world
	@echo ""
	@echo "Running with 2 threads:"
	@export OMP_NUM_THREADS=2 && ./hello_world

.PHONY: all clean run