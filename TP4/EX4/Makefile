CC = gcc
CFLAGS = -fopenmp -Wall -O2

all: barrier_sync

barrier_sync: barrier_sync.c
	$(CC) $(CFLAGS) -o barrier_sync barrier_sync.c

clean:
	rm -f barrier_sync *.csv

run: barrier_sync
	@echo "Running with 1 thread:"
	@export OMP_NUM_THREADS=1 && ./barrier_sync
	@echo "Running with 2 threads:"
	@export OMP_NUM_THREADS=2 && ./barrier_sync
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./barrier_sync
	@echo "Running with 8 threads:"
	@export OMP_NUM_THREADS=8 && ./barrier_sync

benchmark: barrier_sync
	@echo "threads,version,time,mflops" > benchmark.csv
	@for t in 1 2 4 8 16; do \
		export OMP_NUM_THREADS=$$t; \
		./barrier_sync | grep -A2 "Version" | grep -E "Time|MFLOPS" | awk -v t=$$t 'NR%2==1{time=$$2} NR%2==0{print t",v"int((NR+1)/2)","time","$$2}' >> benchmark.csv; \
	done
	@echo "Results saved to benchmark.csv"

.PHONY: all clean run benchmark
