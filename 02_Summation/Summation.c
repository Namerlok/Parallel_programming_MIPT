#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    // Summation range
    int N = 10000;
    int summ = 0 ;
    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // The number of threads must be greater than one for the program to execute.
    if (size == 1) { 
        printf("It is impossible to execute the program on one thread\n");
        exit(0);
    }
    
    // divide the range from 1 to N into rank - 1 parts
    if (rank == 0) {
        for (int i = 1; i < size; ++i) {
            MPI_Status status;
            int part_summ = 0;
            MPI_Recv(&part_summ, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            summ += part_summ;
        }
        printf("Sum of numbers from 1 to %i = %i\n", N, summ);
    } else if (rank ==  size - 1){ // last rank gets the range modulo
        for (int i = (rank - 1) * N / (size - 1) + 1; i <= N; ++i) 
            summ += i;
        MPI_Send(&summ, 1,  MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = (rank - 1) * N / (size - 1) + 1; 
             i <= rank * N / (size - 1); ++i)
            summ += i;
        MPI_Send(&summ, 1,  MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}
