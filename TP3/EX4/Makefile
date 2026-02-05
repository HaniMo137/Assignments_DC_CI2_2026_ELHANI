CC = gcc
CFLAGS = -fopenmp -Wall -O2
M = 1000
N = 1000

all: matrix_mult

matrix_mult: matrix_mult.c
	$(CC) $(CFLAGS) -DM=$(M) -DN=$(N) -o matrix_mult matrix_mult.c

clean:
	rm -f matrix_mult benchmark_results.txt

run: matrix_mult
	@echo "Running with 1 thread:"
	@export OMP_NUM_THREADS=1 && ./matrix_mult
	@echo ""
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./matrix_mult
	@echo ""
	@echo "Running with 8 threads:"
	@export OMP_NUM_THREADS=8 && ./matrix_mult

benchmark: matrix_mult
	@chmod +x benchmark.sh
	@./benchmark.sh

.PHONY: all clean run benchmark