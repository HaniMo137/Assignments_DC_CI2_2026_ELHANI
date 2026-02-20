#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data;
    int local_sum, global_sum;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
        data = 100;
        printf("Process 0 broadcasting value: %d\n", data);
    }
    
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    printf("Process %d received broadcast value: %d\n", rank, data);
    
    local_sum = rank + 1;
    
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("\nSum of all ranks (1 to %d): %d\n", size, global_sum);
    }
    
    MPI_Finalize();
    return 0;
}
