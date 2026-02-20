CC = mpicc
CFLAGS = -Wall -O2

all: hello_world

hello_world: Hello_world.c
	$(CC) $(CFLAGS) -o hello_world Hello_world.c

clean:
	rm -f hello_world

run: hello_world
	@echo "Running with 4 processes:"
	@mpirun -np 4 ./hello_world
	@echo ""
	@echo "Running with 2 processes:"
	@mpirun -np 2 ./hello_world

.PHONY: all clean run
