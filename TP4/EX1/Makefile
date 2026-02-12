CC = gcc
CFLAGS = -fopenmp -Wall -O2 -lm

all: sections

sections: sections.c
	$(CC) $(CFLAGS) -o sections sections.c

clean:
	rm -f sections

run: sections
	@echo "Running with 3 threads:"
	@export OMP_NUM_THREADS=3 && ./sections
	@echo ""
	@echo "Running with 4 threads:"
	@export OMP_NUM_THREADS=4 && ./sections

.PHONY: all clean run
