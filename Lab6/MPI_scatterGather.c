#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

int main (int argc, char* argv[]){
	int rank, test, tasks, i;
	i = 10;
	int array[i];
	int array2[i];
	double timePast;

	timePast = 0.0;

 	MPI_Init(&argc, &argv);
 	MPI_Comm_size(MPI_COMM_WORLD, &tasks);
 	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	test = i / tasks;
	int *buf = malloc(test * sizeof(int));
	if (rank == 0){
		printf("[%d]: ", rank);
		for(int j = 0; j < i; j++){
			array[j] = j;
			printf("%d:", array[j]);
		}
	}	
	printf("\n");

	timePast -= MPI_Wtime();
	MPI_Scatter(array, test, MPI_INT, buf, test, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	printf("[%d]: ", rank);
	for(int j = 0; j < test; j++){
		printf("%d ", buf[j]);
		buf[j] += rank;
		printf("%d ", buf[j]);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Gather(buf, test, MPI_INT, array2, i, MPI_INT, 0, MPI_COMM_WORLD);
	timePast += MPI_Wtime();
	if(rank == 0){
		printf("[%d]", rank);
		for (int j = 0; j < i; j++){
			printf("%d ", array2[j]);
		}
		printf("Runtime: %lf", 1e3 * timePast);
	}
	MPI_Finalize();
	return 0;
}
