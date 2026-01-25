#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000
#define REPEAT 50

// Function for each unrolling factor U=1,2,4,8,16,32
double test_unroll_1(double *a, volatile double *sink);
double test_unroll_2(double *a, volatile double *sink);
double test_unroll_4(double *a, volatile double *sink);
double test_unroll_8(double *a, volatile double *sink);
double test_unroll_16(double *a, volatile double *sink);
double test_unroll_32(double *a, volatile double *sink);

// U=1: No unrolling
double test_unroll_1(double *a, volatile double *sink) {
    clock_t start = clock();
    double sum = 0.0;
    for (int r = 0; r < REPEAT; r++) {
        for (int i = 0; i < N; i++) {
            sum += a[i];
        }
    }
    *sink = sum;
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// U=2: Unroll by 2
double test_unroll_2(double *a, volatile double *sink) {
    clock_t start = clock();
    double sum = 0.0;
    for (int r = 0; r < REPEAT; r++) {
        int i = 0;
        for (; i + 2 <= N; i += 2) {
            sum += a[i];
            sum += a[i + 1];
        }
        for (; i < N; i++) {
            sum += a[i];
        }
    }
    *sink = sum;
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// U=4: Unroll by 4
double test_unroll_4(double *a, volatile double *sink) {
    clock_t start = clock();
    double sum = 0.0;
    for (int r = 0; r < REPEAT; r++) {
        int i = 0;
        for (; i + 4 <= N; i += 4) {
            sum += a[i];
            sum += a[i + 1];
            sum += a[i + 2];
            sum += a[i + 3];
        }
        for (; i < N; i++) {
            sum += a[i];
        }
    }
    *sink = sum;
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// U=8: Unroll by 8
double test_unroll_8(double *a, volatile double *sink) {
    clock_t start = clock();
    double sum = 0.0;
    for (int r = 0; r < REPEAT; r++) {
        int i = 0;
        for (; i + 8 <= N; i += 8) {
            sum += a[i];
            sum += a[i + 1];
            sum += a[i + 2];
            sum += a[i + 3];
            sum += a[i + 4];
            sum += a[i + 5];
            sum += a[i + 6];
            sum += a[i + 7];
        }
        for (; i < N; i++) {
            sum += a[i];
        }
    }
    *sink = sum;
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// U=16: Unroll by 16
double test_unroll_16(double *a, volatile double *sink) {
    clock_t start = clock();
    double sum = 0.0;
    for (int r = 0; r < REPEAT; r++) {
        int i = 0;
        for (; i + 16 <= N; i += 16) {
            sum += a[i];
            sum += a[i + 1];
            sum += a[i + 2];
            sum += a[i + 3];
            sum += a[i + 4];
            sum += a[i + 5];
            sum += a[i + 6];
            sum += a[i + 7];
            sum += a[i + 8];
            sum += a[i + 9];
            sum += a[i + 10];
            sum += a[i + 11];
            sum += a[i + 12];
            sum += a[i + 13];
            sum += a[i + 14];
            sum += a[i + 15];
        }
        for (; i < N; i++) {
            sum += a[i];
        }
    }
    *sink = sum;
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// U=32: Unroll by 32
double test_unroll_32(double *a, volatile double *sink) {
    clock_t start = clock();
    double sum = 0.0;
    for (int r = 0; r < REPEAT; r++) {
        int i = 0;
        for (; i + 32 <= N; i += 32) {
            sum += a[i];
            sum += a[i + 1];
            sum += a[i + 2];
            sum += a[i + 3];
            sum += a[i + 4];
            sum += a[i + 5];
            sum += a[i + 6];
            sum += a[i + 7];
            sum += a[i + 8];
            sum += a[i + 9];
            sum += a[i + 10];
            sum += a[i + 11];
            sum += a[i + 12];
            sum += a[i + 13];
            sum += a[i + 14];
            sum += a[i + 15];
            sum += a[i + 16];
            sum += a[i + 17];
            sum += a[i + 18];
            sum += a[i + 19];
            sum += a[i + 20];
            sum += a[i + 21];
            sum += a[i + 22];
            sum += a[i + 23];
            sum += a[i + 24];
            sum += a[i + 25];
            sum += a[i + 26];
            sum += a[i + 27];
            sum += a[i + 28];
            sum += a[i + 29];
            sum += a[i + 30];
            sum += a[i + 31];
        }
        for (; i < N; i++) {
            sum += a[i];
        }
    }
    *sink = sum;
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    double *a = malloc(N * sizeof(double));
    volatile double sink = 0.0;
    for (int i = 0; i < N; i++) a[i] = 1.0;
    // Test each unrolling factor
    printf("U=1: %f ms\n", test_unroll_1(a, &sink) * 1000);
    printf("U=2: %f ms\n", test_unroll_2(a, &sink) * 1000);
    printf("U=4: %f ms\n", test_unroll_4(a, &sink) * 1000);
    printf("U=8: %f ms\n", test_unroll_8(a, &sink) * 1000);
    printf("U=16: %f ms\n", test_unroll_16(a, &sink) * 1000);
    printf("U=32: %f ms\n", test_unroll_32(a, &sink) * 1000);
    
    if (sink == 0.0) {
        printf("sink=%f\n", sink);
    }
    free(a);
    return 0;
}