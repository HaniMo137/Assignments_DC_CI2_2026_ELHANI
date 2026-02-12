#!/bin/bash

echo "Benchmarking Matrix-Vector Multiplication"
echo "==========================================="
echo ""

OUTPUT="benchmark_results.txt"
> $OUTPUT

for threads in 1 2 4 8 16; do
    echo "Testing with $threads threads..." | tee -a $OUTPUT
    export OMP_NUM_THREADS=$threads
    ./barrier_sync | tee -a $OUTPUT
    echo "" | tee -a $OUTPUT
done

echo "Results saved to $OUTPUT"
