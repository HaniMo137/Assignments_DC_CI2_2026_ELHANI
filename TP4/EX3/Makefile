CC = gcc
CFLAGS = -fopenmp -Wall -O2 -lm

all: load_balance

load_balance: load_balance.c
	$(CC) $(CFLAGS) -o load_balance load_balance.c

clean:
	rm -f load_balance

run: load_balance
	@echo "Running with 3 threads:"
	@export OMP_NUM_THREADS=3 && ./load_balance
	@echo ""
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./load_balance

.PHONY: all clean run
