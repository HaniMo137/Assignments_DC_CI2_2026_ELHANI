CC = gcc
CFLAGS = -fopenmp -Wall -O2 -lm

all: pi_loop

pi_loop: pi_loop.c
	$(CC) $(CFLAGS) -o pi_loop pi_loop.c

clean:
	rm -f pi_loop

run: pi_loop
	@echo "Running with 1 thread:"
	@export OMP_NUM_THREADS=1 && ./pi_loop
	@echo ""
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./pi_loop
	@echo ""
	@echo "Running with 8 threads:"
	@export OMP_NUM_THREADS=8 && ./pi_loop

.PHONY: all clean run