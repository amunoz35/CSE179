#include <stdio.h>
#include <mpi.h>
//Using MPI_simple.c
int main(int argc, char *argv[]){
        int numprocs, rank, namelen;
	int message, tag;
        char processor_name[MPI_MAX_PROCESSOR_NAME];
        MPI_Init(&argc, &argv);
	MPI_Status status;
        MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Get_processor_name(processor_name, &namelen);
	//Check the value of rank and will only output dependant on rank i+1
	message = rank;
	tag = 0;
	MPI_Send(&message, 1, MPI_INT, (rank + 1)%numprocs, tag, MPI_COMM_WORLD);
	if(rank == 0){
        	MPI_Recv(&message, 1, MPI_INT, numprocs - 1, tag, MPI_COMM_WORLD, &status);
		printf("Process %d on %s out of process: %d\n", rank, processor_name, numprocs-1);
	}
	else{
		MPI_Recv(&message, 1, MPI_INT, rank - 1, tag, MPI_COMM_WORLD, &status);
		printf("Process %d on %s out of process: %d\n", rank, processor_name, rank -1);
	}
	MPI_Finalize();
}










