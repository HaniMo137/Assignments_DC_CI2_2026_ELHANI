#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int send_data, recv_data;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (size < 2) {
        if (rank == 0) {
            printf("This program requires at least 2 processes\n");
        }
        MPI_Finalize();
        return 0;
    }
    
    if (rank == 0) {
        send_data = 42;
        printf("Process %d sending value %d to process 1\n", rank, send_data);
        MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        
        MPI_Recv(&recv_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received value %d from process 1\n", rank, recv_data);
    }
    else if (rank == 1) {
        MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received value %d from process 0\n", rank, recv_data);
        
        send_data = recv_data * 2;
        printf("Process %d sending value %d to process 0\n", rank, send_data);
        MPI_Send(&send_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
