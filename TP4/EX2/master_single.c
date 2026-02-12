#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

void init_matrix(int n, double *A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i*n + j] = (double)(i + j);
        }
    }
}

void print_matrix(int n, double *A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%6.1f ", A[i*n + j]);
        }
        printf("\n");
    }
}

double sum_matrix(int n, double *A) {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n*n; i++) {
        sum += A[i];
    }
    return sum;
}

int main() {
    double *A;
    double sum;
    double start, end;
    
    A = (double*) malloc(N * N * sizeof(double));
    if (A == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    printf("OpenMP version with %d threads:\n", omp_get_max_threads());
    start = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Master thread %d initializing matrix\n", omp_get_thread_num());
            init_matrix(N, A);
        }
        
        #pragma omp barrier
        
        #pragma omp single
        {
            printf("Single thread %d printing matrix (first 5x5):\n", omp_get_thread_num());
            if (N <= 10) {
                print_matrix(N, A);
            } else {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        printf("%6.1f ", A[i*N + j]);
                    }
                    printf("\n");
                }
            }
        }
    }
    
    sum = sum_matrix(N, A);
    
    end = omp_get_wtime();
    
    printf("Sum = %lf\n", sum);
    printf("Execution time = %lf seconds\n", end - start);
    
    free(A);
    return 0;
}
