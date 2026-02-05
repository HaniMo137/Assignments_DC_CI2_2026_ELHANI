#include <stdio.h>
#include <omp.h>

int main(void) {
    int num_threads;
    
    #pragma omp parallel
    {
        int rank = omp_get_thread_num();
        
        #pragma omp single
        {
            num_threads = omp_get_num_threads();
        }
        
        printf("Hello from the rank %d thread\n", rank);
        
        #pragma omp barrier
        
        #pragma omp master
        {
            printf("Parallel execution of hello_world with %d threads\n", num_threads);
        }
    }
    
    return 0;
}