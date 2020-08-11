#include <stdlib.h>
#include <stdio.h>
#include "omp.h"

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

void parallel_task(struct node *p){

// open a parallel channel
#pragma omp parallel
   {
// open a single channel
#pragma omp single
      while (p != NULL)
      {
// open a intialized p task channel
#pragma omp task firstprivate(p)
         processwork(p);
         p = p->next;
      }
   }

   return;
}
//Instead of N size, make some n+1
void parallel_traverse(struct node *p)
{
	struct node *traverse[N+1];
	#pragma omp parallel
	{
		#pragma omp for schedule (static, 1)
		{
			for(int i = 0; i < N + 1; i++)
			{
				traverse[i] = p;
				p = p->next;
			}
			for (int i = 0; i < N + 1; i++)
				processwork(traverse[i]);
		}
	}
	return;
}

void processwork(struct node* p) 
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;
    
    head = malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (i=0; i< N; i++) {
       temp  = malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     
     printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
 
     p = init_list(p);
     head = p;

     start = omp_get_wtime();
	 #pragma omp parallel 
     {
		 #pragma omp single
		 {
			while (p != NULL) {
				processwork(p);
				p = p->next;
			}
		 }
     }
	 parallel_task();
	 parallel_traverse(p);
     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
     }  
	 free (p);

     printf("Compute Time: %f seconds\n", end - start);

     return 0;
}

