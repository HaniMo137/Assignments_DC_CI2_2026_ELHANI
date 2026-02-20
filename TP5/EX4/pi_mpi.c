#include <stdio.h>
#include <mpi.h>

static long num_steps = 100000;

int main(int argc, char *argv[]) {
    int rank, size;
    double step, x, pi, sum = 0.0, local_sum = 0.0;
    double start_time, end_time;
    int i;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    step = 1.0 / (double)num_steps;
    
    start_time = MPI_Wtime();
    
    for (i = rank; i < num_steps; i += size) {
        x = (i + 0.5) * step;
        local_sum += 4.0 / (1.0 + x * x);
    }
    
    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    end_time = MPI_Wtime();
    
    if (rank == 0) {
        pi = step * sum;
        printf("PI = %.15f\n", pi);
        printf("Number of processes: %d\n", size);
        printf("CPU time = %.6f seconds\n", end_time - start_time);
    }
    
    MPI_Finalize();
    return 0;
}
