CC = gcc
CFLAGS = -fopenmp -O2 -Wall -lm
TARGET = jacobi
SOURCE = jacobi.c

# Default grid size and iterations
VAL_N ?= 1000
VAL_ITER ?= 1000

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) -DVAL_N=$(VAL_N) -DVAL_ITER=$(VAL_ITER)

run: $(TARGET)
	@echo "=== Running with 1 thread ==="
	@export OMP_NUM_THREADS=1 && ./$(TARGET)
	@echo ""
	@echo "=== Running with 2 threads ==="
	@export OMP_NUM_THREADS=2 && ./$(TARGET)
	@echo ""
	@echo "=== Running with 4 threads ==="
	@export OMP_NUM_THREADS=4 && ./$(TARGET)
	@echo ""
	@echo "=== Running with 8 threads ==="
	@export OMP_NUM_THREADS=8 && ./$(TARGET)

benchmark: $(TARGET)
	@./Benchmark.sh

clean:
	rm -f $(TARGET) *.o benchmark_results.txt

.PHONY: all run benchmark clean
