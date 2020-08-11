#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#define NUM_THREADS 32
#define SAMPLE_POINTS_PER_THREAD 10000

void *compute_pi (void *s){
        int seed, i, *hit_pointer;
        double x_coord, y_coord;
        int local_hits;
        hit_pointer = (int *) s;
        seed = *hit_pointer;
        local_hits = 0;
        for(int i = 0; i < SAMPLE_POINTS_PER_THREAD; i++){
                x_coord =(double)(rand_r(&seed))/(RAND_MAX) - 0.5;
                y_coord = (double)(rand_r(&seed))/(RAND_MAX) - 0.5;
                if((x_coord * x_coord + y_coord * y_coord) < 0.25)
                        local_hits++;

        }
        *hit_pointer = local_hits;
        pthread_exit(0);
}

int main(){
        struct timeval start, end;
        int hits[NUM_THREADS];
        int total_hits;
        double pi;
        pthread_t p_threads[NUM_THREADS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        gettimeofday(&start, NULL);
        for (int i = 0; i < NUM_THREADS; i++){
                hits[i] = i;
                pthread_create(&p_threads[i], &attr, compute_pi, (void*) &hits[i]);
        }
        for (int i = 0; i <NUM_THREADS; i++){
                pthread_join(p_threads[i], NULL);
                total_hits += hits[i];
        }
        pi = (double)4 *total_hits/(SAMPLE_POINTS_PER_THREAD * NUM_THREADS);
        gettimeofday(&end, NULL);

        printf("Estimated Pi Value: %f\n", pi);
        printf("Calculated Runtime: %ld\n",(end.tv_usec - start.tv_usec));
}
