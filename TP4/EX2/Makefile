CC = gcc
CFLAGS = -fopenmp -Wall -O2

all: master_single

master_single: master_single.c
	$(CC) $(CFLAGS) -o master_single master_single.c

clean:
	rm -f master_single

run: master_single
	@echo "Running with 2 threads:"
	@export OMP_NUM_THREADS=2 && ./master_single
	@echo ""
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./master_single

.PHONY: all clean run
