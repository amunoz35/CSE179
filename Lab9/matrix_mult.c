#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
//Define size of Matrix n
#define n 4

int mat1[n][n], mat2[n][n], matFinal[n][n];

int main(int argc, char** argv){
	int i, j, k;
	int numprocs, rank;
	double timer;
	struct timeval start, end;
	int tag = 0;
	int posX, posY, block;
	int num;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	num = rank* n/numprocs;
	srand(time(NULL));
	//Populate the matrices with random values within a value of 10
		for(i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				mat1[i][j] = rand()%10;
				mat2[i][j] = rand()%10;
			}
		}
		MPI_Scatter (mat1, n*n/numprocs, MPI_INT, mat1[num], n*n/numprocs, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatter (mat2, n*n/numprocs, MPI_INT, mat2[num], n*n/numprocs, MPI_INT, 0, MPI_COMM_WORLD);
		 for (i=num; i<n; i++) {
    for (j=0; j<n; j++) {
      matFinal[i][j]=0;
      for (k=0; k<n; k++){
        matFinal[i][j] += mat1[i][k]*mat2[k][j];
      }
    }
  }
  MPI_Gather (matFinal[num], n*n/numprocs, MPI_INT, matFinal, n*n/numprocs, MPI_INT, 0, MPI_COMM_WORLD);
  if (rank==0) {
      printf("  Matrix 1 \n");
      printf("________________");
    for (i=0; i<n; i++) {
      printf("\n"); 
      for (j=0; j<n; j++){
        printf("%3d ", mat1[i][j]);
      }
    }
    printf("\n"); 
    printf("\n   Matrix 2 \n");
    printf("___________________");

     for (i=0; i<n; i++) {
      printf("\n"); 
      for (j=0; j<n; j++){
        printf("%3d ", mat2[i][j]);
      }
    }
    printf("\n"); 
    printf("\nResulting Matrix \n");
    printf("____________________");

    for (i=0; i<n; i++) {
      printf("\n"); 
      for (j=0; j<n; j++){
        printf("%3d ", matFinal[i][j]);
      }
    }
    printf("\n"); 
  }
  MPI_Finalize();
  return 0;
}