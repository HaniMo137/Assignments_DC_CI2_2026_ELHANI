#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void dmvm_v1(int n, int m, double *lhs, double *rhs, double *mat) {
    #pragma omp parallel for
    for (int r = 0; r < m; ++r) {
        lhs[r] = 0.0;
        for (int c = 0; c < n; ++c) {
            lhs[r] += mat[r + c*m] * rhs[c];
        }
    }
}

void dmvm_v2(int n, int m, double *lhs, double *rhs, double *mat) {
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic) nowait
        for (int r = 0; r < m; ++r) {
            lhs[r] = 0.0;
            for (int c = 0; c < n; ++c) {
                lhs[r] += mat[r + c*m] * rhs[c];
            }
        }
    }
}

void dmvm_v3(int n, int m, double *lhs, double *rhs, double *mat) {
    #pragma omp parallel
    {
        #pragma omp for schedule(static) nowait
        for (int r = 0; r < m; ++r) {
            lhs[r] = 0.0;
            for (int c = 0; c < n; ++c) {
                lhs[r] += mat[r + c*m] * rhs[c];
            }
        }
    }
}

int main(int argc, char *argv[]) {
    const int n = 40000;
    const int m = 600;
    const long long flops = 2LL * n * m;
    
    double *mat = malloc(n * m * sizeof(double));
    double *rhs = malloc(n * sizeof(double));
    double *lhs = malloc(m * sizeof(double));
    
    for (int c = 0; c < n; ++c) {
        rhs[c] = 1.0;
        for (int r = 0; r < m; ++r)
            mat[r + c*m] = 1.0;
    }
    
    int num_threads = omp_get_max_threads();
    double start, end, time;
    double mflops;
    
    printf("Matrix-Vector Multiplication Benchmark\n");
    printf("Matrix size: %d x %d\n", n, m);
    printf("Number of threads: %d\n", num_threads);
    printf("FLOPS: %lld\n\n", flops);
    
    for (int r = 0; r < m; ++r)
        lhs[r] = 0.0;
    start = omp_get_wtime();
    dmvm_v1(n, m, lhs, rhs, mat);
    end = omp_get_wtime();
    time = end - start;
    mflops = flops / (time * 1e6);
    printf("Version 1 (implicit barrier):\n");
    printf("  Time: %.6f seconds\n", time);
    printf("  MFLOPS: %.2f\n", mflops);
    printf("  Result check: lhs[0] = %.1f (expected 40000.0)\n\n", lhs[0]);
    
    for (int r = 0; r < m; ++r)
        lhs[r] = 0.0;
    start = omp_get_wtime();
    dmvm_v2(n, m, lhs, rhs, mat);
    end = omp_get_wtime();
    time = end - start;
    mflops = flops / (time * 1e6);
    printf("Version 2 (dynamic, nowait):\n");
    printf("  Time: %.6f seconds\n", time);
    printf("  MFLOPS: %.2f\n", mflops);
    printf("  Result check: lhs[0] = %.1f\n\n", lhs[0]);
    
    for (int r = 0; r < m; ++r)
        lhs[r] = 0.0;
    start = omp_get_wtime();
    dmvm_v3(n, m, lhs, rhs, mat);
    end = omp_get_wtime();
    time = end - start;
    mflops = flops / (time * 1e6);
    printf("Version 3 (static, nowait):\n");
    printf("  Time: %.6f seconds\n", time);
    printf("  MFLOPS: %.2f\n", mflops);
    printf("  Result check: lhs[0] = %.1f\n\n", lhs[0]);
    
    free(mat);
    free(rhs);
    free(lhs);
    
    return 0;
}
