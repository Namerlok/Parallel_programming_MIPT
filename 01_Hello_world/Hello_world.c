#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    
    int size = 0, rank = 0, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &name_len);
    
    printf("Hell, world!\nprocessor %s, rank %d out of %d processors\n", processor_name, rank, size);
    
    MPI_Finalize();
    return 0;
}
