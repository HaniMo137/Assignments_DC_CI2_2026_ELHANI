CC = mpicc
CFLAGS = -Wall -O2

all: pi_mpi

pi_mpi: pi_mpi.c
	$(CC) $(CFLAGS) -o pi_mpi pi_mpi.c

clean:
	rm -f pi_mpi

run: pi_mpi
	@echo "Running with 1 process:"
	@mpirun -np 1 ./pi_mpi
	@echo ""
	@echo "Running with 4 processes:"
	@mpirun -np 4 ./pi_mpi
	@echo ""
	@echo "Running with 8 processes:"
	@mpirun -np 8 ./pi_mpi

benchmark: pi_mpi
	@echo "Benchmarking PI calculation with MPI"
	@echo "======================================"
	@for n in 1 2 4 8; do \
		echo ""; \
		mpirun -np $$n ./pi_mpi; \
	done

.PHONY: all clean run benchmark
