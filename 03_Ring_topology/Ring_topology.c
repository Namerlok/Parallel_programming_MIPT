#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // The number of threads must be greater than one for the program to execute.
    if (size == 1) { 
        printf("It is impossible to execute the program on one thread\n");
        exit(0);
    }
    
    // Array to output
    int NP = size;
    int output_arr[NP];
    
    if (rank == 0) {
        // Filled the array with random numbers
        srand(time(NULL));
        for (int i = 0; i < NP; ++i)
            output_arr[i] = rand() % 1000;
        
        // We output an array to check the correctness of the transfer between threads
        printf("output array = ");
        for (int i = 0; i < NP; ++i)
            printf("|%i", output_arr[i]);
        printf("|\n");
        
        printf("[%2i] = %3i\n", rank, output_arr[rank]);
        MPI_Send(output_arr, size, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        MPI_Status status;
        MPI_Recv(output_arr, size, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
    } else {
        MPI_Status status;
        MPI_Recv(output_arr, size, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("[%2i] = %3i\n", rank, output_arr[rank]);
        MPI_Send(output_arr, size, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
