#!/bin/bash

# Benchmark script for Jacobi method

PROGRAM="./jacobi"
OUTPUT="benchmark_results.txt"
GRID_SIZE=1000
MAX_ITER=500

echo "=== Jacobi Method Benchmark ===" > $OUTPUT
echo "Grid size: ${GRID_SIZE}x${GRID_SIZE}" >> $OUTPUT
echo "Max iterations: ${MAX_ITER}" >> $OUTPUT
echo "" >> $OUTPUT

# Test with different thread counts
for threads in 1 2 4 8 16; do
    echo "Running with $threads threads..."
    export OMP_NUM_THREADS=$threads
    
    echo "--- Threads: $threads ---" >> $OUTPUT
    $PROGRAM $GRID_SIZE $MAX_ITER >> $OUTPUT
    echo "" >> $OUTPUT
done

echo "Benchmark complete. Results saved to $OUTPUT"

# Calculate speedup and efficiency
echo "" >> $OUTPUT
echo "=== Performance Analysis ===" >> $OUTPUT

# Extract execution times (this is a simple version, could be improved)
echo "Thread Count | Time (s) | Speedup | Efficiency" >> $OUTPUT
echo "------------|----------|---------|----------" >> $OUTPUT

echo "See raw output above for detailed timing information" >> $OUTPUT
