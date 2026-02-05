CC = gcc
CFLAGS = -fopenmp -Wall -O2 -lm

all: pi_parallel

pi_parallel: pi_parallel.c
	$(CC) $(CFLAGS) -o pi_parallel pi_parallel.c

clean:
	rm -f pi_parallel

run: pi_parallel
	@echo "Running with 1 thread:"
	@export OMP_NUM_THREADS=1 && ./pi_parallel
	@echo ""
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./pi_parallel
	@echo ""
	@echo "Running with 8 threads:"
	@export OMP_NUM_THREADS=8 && ./pi_parallel

.PHONY: all clean run