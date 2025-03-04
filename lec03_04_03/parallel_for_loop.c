#include <stdio.h>
#include <omp.h> 
#include <time.h>
#define N 1000
int main()
{
    int arr1[N], arr2[N];

    for (int i = 0; i < N; i++)
    {
        arr1[i] = i;
        arr2[i] = i;
    }

    omp_set_num_threads(4);

    int sum = 0;
    // #pragma omp parallel 
    // in above way the parallelness cause race conditions because all threads simulataneously updates the same variable
    // use a critical region to define the block causing the race condition

    // solution
    clock_t start = clock();
    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {

        //thread safe region
        #pragma omp critical
        {
            sum = sum + (arr1[i] * arr2[i]);
        }

    }

    clock_t end = clock();

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    printf("Sum = %i\n", sum);
    return 0;
}
