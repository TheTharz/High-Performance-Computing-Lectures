#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 1000

int main(int argc, char* argv[]){
    int partial_Sum, total_Sum;

    int arr1[N], arr2[N];

    for (int i = 0; i < N; i++)
    {
        arr1[i] = i;
        arr2[i] = i;
    }

    clock_t start = clock();
    #pragma omp parallel private(partial_Sum) shared(total_Sum)
    {
        partial_Sum = 0;
        total_Sum = 0;

        #pragma omp for
        for(int i = 1; i < N; i++){
            partial_Sum = partial_Sum + (arr1[i]*arr2[i]);
        }

        //Create thread safe region.
        #pragma omp critical
        {
            //add each threads partial sum to the total sum
            total_Sum += partial_Sum;
        }
    }

    clock_t end = clock();

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);
    printf("Total Sum: %d\n", total_Sum);
    return 0;
}