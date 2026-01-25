#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Get current time in seconds
static double now_sec(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

// Initialize matrix with random values
void init_matrix(double *mat, int n) {
    for (int i = 0; i < n * n; i++) {
        mat[i] = (double)(rand() % 100) * 0.01;
    }
}

// Simple matrix multiplication (can be parallelized)
void matmul(const double *A, const double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = sum;
        }
    }
}

// Sequential "noise" operation (cannot be parallelized)
void sequential_noise(double *mat, int n, int intensity) {
    double sum = 0.0;
    // Simulate sequential work that scales with intensity
    for (int iter = 0; iter < intensity; iter++) {
        for (int i = 0; i < n; i++) {
            sum += mat[i];
        }
    }
    // Prevent optimization from removing the loop
    mat[0] += sum * 1e-10;
}

// Benchmark with varying sequential noise
void benchmark_with_noise(int n, int num_iterations) {
    // Allocate matrices
    double *A = (double*)malloc(n * n * sizeof(double));
    double *B = (double*)malloc(n * n * sizeof(double));
    double *C = (double*)malloc(n * n * sizeof(double));
    
    if (!A || !B || !C) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    init_matrix(A, n);
    init_matrix(B, n);
    
    printf("\nMatrix size: %d x %d\n", n, n);
    printf("Number of iterations: %d\n", num_iterations);
    printf("\n%-20s %-15s %-15s %-15s\n", 
           "Sequential Noise", "Total Time (ms)", "Matmul Time (ms)", "Noise Time (ms)");
    printf("----------------------------------------------------------------\n");
    
    int noise_levels[] = {0, 10, 50, 100, 500, 1000, 5000};
    int num_levels = sizeof(noise_levels) / sizeof(noise_levels[0]);
    
    for (int level_idx = 0; level_idx < num_levels; level_idx++) {
        int noise = noise_levels[level_idx];
        
        double total_matmul_time = 0.0;
        double total_noise_time = 0.0;
        double t_start = now_sec();
        
        for (int iter = 0; iter < num_iterations; iter++) {
            // Time the matrix multiplication (parallelizable part)
            double t0 = now_sec();
            matmul(A, B, C, n);
            double t1 = now_sec();
            total_matmul_time += (t1 - t0) * 1000.0;
            
            // Time the sequential noise
            t0 = now_sec();
            sequential_noise(C, n, noise);
            t1 = now_sec();
            total_noise_time += (t1 - t0) * 1000.0;
        }
        
        double t_end = now_sec();
        double total_time = (t_end - t_start) * 1000.0;
        
        printf("%-20d %-15.2f %-15.2f %-15.2f\n", 
               noise, total_time, total_matmul_time, total_noise_time);
    }
    
    free(A);
    free(B);
    free(C);
}

// Analyze speedup with sequential noise
void analyze_speedup(int n, int num_iterations) {
    printf("\n\nSpeedup Analysis (Amdahl's Law)\n");
    printf("===============================================\n");
    printf("Assumptions:\n");
    printf("  - Matrix multiplication can be perfectly parallelized\n");
    printf("  - Sequential noise cannot be parallelized\n");
    printf("  - No communication or synchronization overhead\n\n");
    
    // Run baseline (no noise)
    double *A = (double*)malloc(n * n * sizeof(double));
    double *B = (double*)malloc(n * n * sizeof(double));
    double *C = (double*)malloc(n * n * sizeof(double));
    
    if (!A || !B || !C) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    init_matrix(A, n);
    init_matrix(B, n);
    
    double t0 = now_sec();
    for (int iter = 0; iter < num_iterations; iter++) {
        matmul(A, B, C, n);
    }
    double t1 = now_sec();
    double baseline_time = (t1 - t0) * 1000.0;
    
    printf("Baseline (no noise, 1 processor): %.2f ms\n\n", baseline_time);
    
    printf("%-15s %-15s %-15s %-15s %-15s\n", 
           "Seq Fraction", "2 procs", "4 procs", "8 procs", "16 procs");
    printf("--------------------------------------------------------------------\n");
    
    double seq_fractions[] = {0.00, 0.05, 0.10, 0.25, 0.50};
    int processors[] = {2, 4, 8, 16};
    
    for (int i = 0; i < 5; i++) {
        double f = seq_fractions[i];
        printf("%-15.2f ", f);
        
        for (int j = 0; j < 4; j++) {
            int p = processors[j];
            double speedup = 1.0 / (f + (1.0 - f) / (double)p);
            printf("%-15.2f ", speedup);
        }
        printf("\n");
    }
    
    printf("\n");
    free(A);
    free(B);
    free(C);
}

int main(int argc, char *argv[]) {
    int n = 256;              // Matrix size
    int num_iterations = 5;   // Number of iterations
    
    if (argc >= 2) {
        n = atoi(argv[1]);
    }
    if (argc >= 3) {
        num_iterations = atoi(argv[2]);
    }
    
    printf("=================================================\n");
    printf("Exercise 4: Sequential Noise and Matrix Multiplication\n");
    printf("=================================================\n");
    
    srand(42);  // Fixed seed for reproducibility
    
    // Run benchmark with varying sequential noise
    benchmark_with_noise(n, num_iterations);
    
    // Theoretical speedup analysis
    analyze_speedup(n, num_iterations);
    
    printf("\n\nKey Observations:\n");
    printf("================================================================\n");
    printf("1. As sequential noise increases, total execution time increases\n");
    printf("2. Even small sequential fractions limit maximum parallel speedup\n");
    printf("3. With 10%% sequential code, maximum speedup is only 10x\n");
    printf("4. The sequential portion becomes the bottleneck\n");
    printf("5. This demonstrates Amdahl's Law in practice\n\n");
    
    printf("Practical Lessons:\n");
    printf("================================================================\n");
    printf("1. Minimize sequential operations between parallel sections\n");
    printf("2. Reduce synchronization points and sequential bottlenecks\n");
    printf("3. Consider the ratio of parallel to sequential work\n");
    printf("4. Profile to identify sequential bottlenecks\n");
    printf("5. Sometimes restructuring the algorithm is necessary\n\n");
    
    return 0;
}
