#include <unistd.h> 
#include <stdlib.h> 
#include <omp.h> 
#include <stdio.h> 
#define THREADS 16 
#define N 100000000 
#define CHUNK 100 
int main ( ) { 
int i; 
, we markedly improve 
printf("Running %d iterations on %d threads dynamically.\n", N, 
THREADS); 
#pragma omp parallel for schedule(dynamic, CHUNK) 
num_threads(THREADS) 
for (i = 0; i < N; i++) { 
/* a loop that doesn't take very long */ 
} 
/* all threads done */ 
printf("All done!\n"); 
return 0; 
} 
