#include <stdio.h>
#include <math.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

void task_light(int n) {
    double x = 0.0;
    for (int i = 0; i < n; i++) {
        x += sin(i * 0.001);
    }
}

void task_moderate(int n) {
    double x = 0.0;
    for (int i = 0; i < 5*n; i++) {
        x += sqrt(i * 0.5) * cos(i * 0.001);
    }
}

void task_heavy(int n) {
    double x = 0.0;
    for (int i = 0; i < 20*n; i++) {
        x += sqrt(i * 0.5) * cos(i * 0.001) * sin(i * 0.0001);
    }
}

int main() {
    double start, end;
    
    printf("Load Balancing with Parallel Sections\n");
    printf("======================================\n\n");
    
    printf("Sequential execution:\n");
    start = omp_get_wtime();
    task_light(ARRAY_SIZE);
    task_moderate(ARRAY_SIZE);
    task_heavy(ARRAY_SIZE);
    end = omp_get_wtime();
    printf("Time: %.6f seconds\n\n", end - start);
    
    printf("Parallel sections (unbalanced):\n");
    start = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Thread %d executing light task\n", omp_get_thread_num());
            double t1 = omp_get_wtime();
            task_light(ARRAY_SIZE);
            double t2 = omp_get_wtime();
            printf("Thread %d finished light task in %.6f seconds\n", omp_get_thread_num(), t2-t1);
        }
        
        #pragma omp section
        {
            printf("Thread %d executing moderate task\n", omp_get_thread_num());
            double t1 = omp_get_wtime();
            task_moderate(ARRAY_SIZE);
            double t2 = omp_get_wtime();
            printf("Thread %d finished moderate task in %.6f seconds\n", omp_get_thread_num(), t2-t1);
        }
        
        #pragma omp section
        {
            printf("Thread %d executing heavy task\n", omp_get_thread_num());
            double t1 = omp_get_wtime();
            task_heavy(ARRAY_SIZE);
            double t2 = omp_get_wtime();
            printf("Thread %d finished heavy task in %.6f seconds\n", omp_get_thread_num(), t2-t1);
        }
    }
    end = omp_get_wtime();
    printf("Total parallel time: %.6f seconds\n\n", end - start);
    
    printf("Optimized: Split heavy task into multiple sections\n");
    start = omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            task_light(ARRAY_SIZE);
        }
        
        #pragma omp section
        {
            task_moderate(ARRAY_SIZE);
        }
        
        #pragma omp section
        {
            double x = 0.0;
            for (int i = 0; i < 10*ARRAY_SIZE; i++) {
                x += sqrt(i * 0.5) * cos(i * 0.001) * sin(i * 0.0001);
            }
        }
        
        #pragma omp section
        {
            double x = 0.0;
            for (int i = 10*ARRAY_SIZE; i < 20*ARRAY_SIZE; i++) {
                x += sqrt(i * 0.5) * cos(i * 0.001) * sin(i * 0.0001);
            }
        }
    }
    end = omp_get_wtime();
    printf("Optimized parallel time: %.6f seconds\n", end - start);
    
    return 0;
}
