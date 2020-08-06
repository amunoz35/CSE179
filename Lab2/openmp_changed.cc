#include <iostream>
#include "omp.h"

int main(int argc, char *argv[]){
	int nthreads, tid;
	//Refer to Parallel Region Example in: computing.llnl.gov/tutorials/openMP/
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		printf("Hello World in thread: %d\n", tid);

		if(tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Amount of threads: %d\n", nthreads);
		}
	}
	return 0;
}
