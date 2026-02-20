CC = mpicc
CFLAGS = -Wall -O2

all: collective

collective: collective.c
	$(CC) $(CFLAGS) -o collective collective.c

clean:
	rm -f collective

run: collective
	@echo "Running with 4 processes:"
	@mpirun -np 4 ./collective
	@echo ""
	@echo "Running with 8 processes:"
	@mpirun -np 8 ./collective

.PHONY: all clean run
