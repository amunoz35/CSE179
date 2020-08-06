#include <iostream>
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int nthreads, tid;
	#pragma omp parallel private(nthreads, tid)
	{
		int matA[5][5];
		int matB[5][5];
		int matC[5][5];
		tid = omp_get_thread_num();
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				matC[i][j] = 0;
			}
		}
		for(int i = 0; i < 5; i++){
			for (int j = 0; j < 5; j++){
				matC[i][j]+= matA[i][j] *matB[i][j];
			}
		}
		if(tid == 0){
			nthreads = omp_get_num_threads();
			printf("Number of threads: %d", nthreads);
		}
	}
}
