#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
  int arr[1000];
  for(int i =0 ;i<1000;i++){
    arr[i] = i;
  }

  int sum = 0;
  for(int i=0;i<1000;i++){
    sum = sum + i;
  }

  printf("Total from serial=%d",sum);

  int total = 0;

  #pragma omp parallel for reduction(+:total)
  for(int i=0;i<1000;i++){
    total = total + i;
  }

  printf("Total from parallel=%d",total);

  int max_val = arr[0];

  #pragma omp parallel for reduction(max:max_val)
  for(int i=0;i<1000;i++){
    if(max_val<arr[i]){
      max_val=arr[i];
    }
  }

  printf("Maximum value of array=%d",max_val);

  int min_val = arr[999];

  #pragma omp parallel for reduction(min:min_val)
  for(int i = 0;i<1000;i++){
    if(min_val>arr[i]){
      min_val = arr[i];
    }
  }

  printf("Minimum value of array=%d",min_val);

}
