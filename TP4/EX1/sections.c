#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 1000000

int main() {
    double *A = malloc(N * sizeof(double));
    if (A == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    double sum = 0.0;
    double mean = 0.0;
    double stddev = 0.0;
    double max;
    double start_time, end_time;
    
    srand(0);
    for (int i = 0; i < N; i++)
        A[i] = (double)rand() / RAND_MAX;
    
    start_time = omp_get_wtime();
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            sum = 0.0;
            for (int i = 0; i < N; i++) {
                sum += A[i];
            }
            mean = sum / N;
            printf("Section 1: Sum computed by thread %d\n", omp_get_thread_num());
        }
        
        #pragma omp section
        {
            max = A[0];
            for (int i = 1; i < N; i++) {
                if (A[i] > max)
                    max = A[i];
            }
            printf("Section 2: Max computed by thread %d\n", omp_get_thread_num());
        }
    }
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            stddev = 0.0;
            for (int i = 0; i < N; i++)
                stddev += (A[i] - mean) * (A[i] - mean);
            stddev = sqrt(stddev / N);
            printf("Section 3: Stddev computed by thread %d\n", omp_get_thread_num());
        }
    }
    
    end_time = omp_get_wtime();
    
    printf("\nResults:\n");
    printf("Sum     = %f\n", sum);
    printf("Max     = %f\n", max);
    printf("Std Dev = %f\n", stddev);
    printf("Time    = %.6f seconds\n", end_time - start_time);
    
    free(A);
    return 0;
}
