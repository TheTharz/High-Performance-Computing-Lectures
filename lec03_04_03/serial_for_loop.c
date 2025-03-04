#include <stdio.h>
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

    int sum = 0;
    clock_t start = clock();
    for (int i = 0; i < N; i++)
    {
        sum = sum + (arr1[i] * arr2[i]);
    }
    clock_t end = clock();

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    printf("Sum = %i\n", sum);
    return 0;
}
