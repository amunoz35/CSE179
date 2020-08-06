#include <iostream>
#include "omp.h"
#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int nthreads, tid;
	#pragma omp parallel for
	void omp_set_dynamic(int dynamic_threads);
		int matA[5][5];
		int matB[5][5];
		int matC[5][5];
		tid = omp_get_thread_num();
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 5; j++){
				result+= matA[i][j] *matB[i][j];
				int omp_get_dynamic(void);
			}
		}

		if(tid == 0){
			nthreads = omp_get_num_threads();
			printf("Number of threads: %d", nthreads);
		}
	}
}
