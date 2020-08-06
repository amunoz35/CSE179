#include <iostream>
#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int nthreads, tid;
	#pragma omp parallel for
	default(shared) private(i)  \  
    schedule(static,chunk)      \  
    reduction(+:result) 
		int matA[5][5];
		int matB[5][5];
		int matC[5][5];
		tid = omp_get_thread_num();
		Parallel.For(int i = 0; i < 5; i++){
			Parallel.For(int j = 0; j < 5; j++){
				result+= matA[i][j] *matB[i][j];
			}
		}

		if(tid == 0){
			nthreads = omp_get_num_threads();
			printf("Number of threads: %d", nthreads);
		}
	}
}
