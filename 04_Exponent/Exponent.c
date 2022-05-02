#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double Fact(int n);

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    double startwime = 0.0, endwtime = 0.0;
    double startwime_rank = 0.0, endwtime_rank = 0.0;
    double drob = 0.0, drobsum = 0.0, result = 0.0;
    int N = atoi(argv[1]);
    
    int rank = 0, size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // number of threads must be greater than one for the program to execute.
    if (size == 1) { 
        printf("It is impossible to execute the program on one thread\n");
        exit(0);
    }
    
    if (rank == 0)
         startwime = MPI_Wtime();
    
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    startwime_rank = MPI_Wtime();

    // count the elements of a series depending on the rank
    for (int i = rank; i <= N; i += size) { 
        drob = 1 / Fact(i);
        drobsum += drob;
    }
    
    endwtime_rank = MPI_Wtime();
    printf("execution time rank %i = %f\n", rank, 
           (endwtime_rank - startwime_rank) * 1000);
    // add sums from different flows to the main
    MPI_Reduce(&drobsum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        printf("exp = %.10f\n", result);
         endwtime = MPI_Wtime();
         printf("total time = %f\n", (endwtime - startwime) * 1000);
    }
    
    MPI_Finalize();
    return 0;
}

// counts factorial
double Fact(int n) {
    if (n == 0)
        return 1;
    else 
        return n * Fact(n - 1);
}
