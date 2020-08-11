#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

void prefix_sum(int *x, int *y, int n){
	y[0] = x[0];
    for (int i = 1; i < n; i++)
        y[i] = y[i - 1] + x[i];
    return;
}

int main(){
	int *x, *y, n;
	double runtime;
	printf("Array size: ");
	scanf("d", &n);
	
	x = (int *)malloc(n * sizeof(int));
    y = (int *)malloc(n * sizeof(int));
	
	//Populate the array with random values
	 for (int i = 0; i < n; i++){
        x[i] = rand() % 100;
	 }
	 runtime = omp_get_wtime();
	 prefix_sum(x, y, n);
	 printf("Runtime: %.9f\n", runtime);
	 
	 return 0;
}