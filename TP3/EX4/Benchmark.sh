#!/bin/bash

# Benchmark script for matrix multiplication

PROGRAM="./matrix_mult"
THREADS=(1 2 4 8 16)
OUTPUT_FILE="benchmark_results.txt"

echo "Matrix Multiplication Benchmark" > $OUTPUT_FILE
echo "================================" >> $OUTPUT_FILE
echo "" >> $OUTPUT_FILE

# Test different thread counts
echo "Testing STATIC scheduling:" >> $OUTPUT_FILE
for t in "${THREADS[@]}"; do
    echo "Threads: $t" >> $OUTPUT_FILE
    export OMP_NUM_THREADS=$t
    $PROGRAM >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
done
echo "" >> $OUTPUT_FILE
echo "Testing DYNAMIC scheduling:" >> $OUTPUT_FILE
export OMP_SCHEDULE="dynamic"
for t in "${THREADS[@]}"; do
    echo "Threads: $t" >> $OUTPUT_FILE
    export OMP_NUM_THREADS=$t
    $PROGRAM >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
done

echo "" >> $OUTPUT_FILE
echo "Testing GUIDED scheduling:" >> $OUTPUT_FILE
export OMP_SCHEDULE="guided"
for t in "${THREADS[@]}"; do
    echo "Threads: $t" >> $OUTPUT_FILE
    export OMP_NUM_THREADS=$t
    $PROGRAM >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
done
echo "Benchmark completed. Results saved to $OUTPUT_FILE"

# Calculate speedup
echo ""
echo "Speedup Analysis:"
echo "================="

# Extract times from results
times=()
for t in "${THREADS[@]}"; do
    time=$(grep -A 2 "Threads: $t" $OUTPUT_FILE | grep "CPU time" | awk '{print $3}')
    times+=($time)
    echo "Threads: $t, Time: $time seconds"
done

# Calculate speedup (base time = 1 thread)
base_time=${times[0]}
echo ""
echo "Speedup relative to 1 thread:"
for i in "${!THREADS[@]}"; do
    if [ -n "${times[$i]}" ] && [ -n "$base_time" ]; then
        speedup=$(echo "scale=3; $base_time / ${times[$i]}" | bc)
        efficiency=$(echo "scale=3; $speedup / ${THREADS[$i]}" | bc)
        echo "Threads: ${THREADS[$i]}, Speedup: $speedup, Efficiency: $efficiency"
    fi
done