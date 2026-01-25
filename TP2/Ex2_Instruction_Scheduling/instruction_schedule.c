#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000

// Helper function to get current time in seconds
static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

// Version 1: Sequential dependencies (poor instruction scheduling)
double compute_sequential(double *data, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result = result + data[i];           // Dependent on previous result
        result = result * 1.0001;            // Dependent on previous operation
        result = result - 0.0001;            // Dependent on previous operation
    }
    return result;
}

// Version 2: Independent operations (better instruction scheduling)
double compute_parallel(double *data, int n) {
    double result1 = 0.0;
    double result2 = 0.0;
    double result3 = 0.0;
    double result4 = 0.0;
    
    int i;
    for (i = 0; i < n - 3; i += 4) {
        result1 += data[i];                  // Independent
        result2 += data[i + 1];              // Independent
        result3 += data[i + 2];              // Independent
        result4 += data[i + 3];              // Independent
    }
    
    // Handle remaining elements
    for (; i < n; i++) {
        result1 += data[i];
    }
    
    return (result1 + result2 + result3 + result4);
}

// Version 3: Unrolled with mixed dependencies
double compute_mixed(double *data, int n) {
    double acc1 = 0.0;
    double acc2 = 0.0;
    
    int i;
    for (i = 0; i < n - 1; i += 2) {
        acc1 = acc1 + data[i] * 1.0001;      // Some dependency
        acc2 = acc2 + data[i + 1] * 1.0001;  // Independent from acc1
    }
    
    if (i < n) {
        acc1 += data[i];
    }
    
    return acc1 + acc2;
}

int main(void) {
    // Allocate and initialize data
    double *data = (double*)malloc(N * sizeof(double));
    if (!data) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < N; i++) {
        data[i] = (double)i * 0.001;
    }
    
    printf("Instruction Scheduling Performance Comparison\n");
    printf("==============================================\n");
    printf("Array size: %d elements\n\n", N);
    
    // Warm up
    volatile double dummy = compute_sequential(data, 1000);
    
    // Test Version 1: Sequential
    double t0 = now_sec();
    double result1 = compute_sequential(data, N);
    double t1 = now_sec();
    double time_seq = (t1 - t0) * 1000.0;
    
    // Test Version 2: Parallel
    t0 = now_sec();
    double result2 = compute_parallel(data, N);
    t1 = now_sec();
    double time_par = (t1 - t0) * 1000.0;
    
    // Test Version 3: Mixed
    t0 = now_sec();
    double result3 = compute_mixed(data, N);
    t1 = now_sec();
    double time_mix = (t1 - t0) * 1000.0;
    
    // Print results
    printf("Version 1 (Sequential dependencies):\n");
    printf("  Time: %.3f ms\n", time_seq);
    printf("  Result: %.6e\n\n", result1);
    
    printf("Version 2 (Independent operations):\n");
    printf("  Time: %.3f ms\n", time_par);
    printf("  Result: %.6e\n", result2);
    printf("  Speedup: %.2fx\n\n", time_seq / time_par);
    
    printf("Version 3 (Mixed dependencies):\n");
    printf("  Time: %.3f ms\n", time_mix);
    printf("  Result: %.6e\n", result3);
    printf("  Speedup: %.2fx\n\n", time_seq / time_mix);
    
    free(data);
    return 0;
}
