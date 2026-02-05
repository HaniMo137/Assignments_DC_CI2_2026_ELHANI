#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#ifndef M
#define M 1000
#endif

#ifndef N
#define N 1000
#endif

int main(int argc, char *argv[]) {
    int m = M, n = N;
    double start_time, end_time;
    
    // Allocate memory dynamically
    double *a = (double *)malloc(m * n * sizeof(double));
    double *b = (double *)malloc(n * m * sizeof(double));
    double *c = (double *)malloc(m * m * sizeof(double));
    
    if (!a || !b || !c) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize matrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i * n + j] = (i + 1) + (j + 1);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            b[i * m + j] = (i + 1) - (j + 1);
        }
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            c[i * m + j] = 0;
        }
    }
    
    start_time = omp_get_wtime();
    
    // Matrix multiplication with collapse
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < n; k++) {
                c[i * m + j] += a[i * n + k] * b[k * m + j];
            }
        }
    }
    
    end_time = omp_get_wtime();
    
    printf("Matrix multiplication completed\n");
    printf("Matrix size: %d x %d\n", m, m);
    printf("Number of threads: %d\n", omp_get_max_threads());
    printf("CPU time: %.6f seconds\n", end_time - start_time);
    
    
    if (m <= 10) {
        printf("\nSample of result matrix C:\n");
        for (int i = 0; i < (m < 5 ? m : 5); i++) {
            for (int j = 0; j < (m < 5 ? m : 5); j++) {
                printf("%.2f ", c[i * m + j]);
            }
            printf("\n");
        }
    }
    
    free(a);
    free(b);
    free(c);
    
    return 0;
}