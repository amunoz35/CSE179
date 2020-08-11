//**NOTE: Change the number of MPI processors to 4, 6, and 8 and measure execution time **
#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>
#include <stdlib.h>
//This will attempt to modify a variable after initialized at zero to anything, e.g. the square of said value
int main(int argc, char *argv[]){
	int rank, test_init, test_modified, numprocs;
	double timePast = 0.0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	test_init = rand() % 10;
	if(rank == 0){
		test_init *= test_init;
	}
	printf("[%d]: Initialized value before broadcast: %d\n", rank, test_init);

	MPI_Barrier(MPI_COMM_WORLD);
	timePast -= MPI_Wtime();
	MPI_Bcast(&test_init, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	timePast += MPI_Wtime();

	printf("[%d]: Value after broadcast: %d\n", rank, test_init);

	if(rank > 0){
		MPI_Finalize();
	}
	else
		printf("Runtime: %lf\n", 1e3 * timePast);
	return 0;
}
