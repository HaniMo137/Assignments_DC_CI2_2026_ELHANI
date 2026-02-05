#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int main() {
    int i;
    double x, pi, sum = 0.0;
    double start_time, end_time;
    
    step = 1.0 / (double)num_steps;
    
    start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        double partial_sum = 0.0;
        
        // Each thread computes its portion of the sum
        for (i = id; i < num_steps; i += num_threads) {
            x = (i + 0.5) * step;
            partial_sum += 4.0 / (1.0 + x * x);
        }
        
        // Critical section to accumulate partial sums
        #pragma omp critical
        {
            sum += partial_sum;
        }
    }
    
    pi = step * sum;
    
    end_time = omp_get_wtime();
    
    printf("PI = %.15f\n", pi);
    printf("CPU time = %.6f seconds\n", end_time - start_time);
    
    return 0;
}