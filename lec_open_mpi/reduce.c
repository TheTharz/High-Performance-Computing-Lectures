#include "mpi.h"
#include <stdio.h>
#define SIZE 4

int main(int argc, char *argv[])  {
int numtasks, rank, sendcount, recvcount, source;
float sendbuf[SIZE][SIZE] = {
    {1.0, 2.0, 3.0, 4.0},
    {5.0, 6.0, 7.0, 8.0},
    {9.0, 10.0, 11.0, 12.0},
    {13.0, 14.0, 15.0, 16.0}  };
float recvbuf[SIZE];
int recvcounts[SIZE];

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

if (numtasks == SIZE) {
    // Print buffer before reduction
    printf("Rank %d before reduction - sendbuf[%d][0:3]: %f %f %f %f\n", 
           rank, rank, sendbuf[rank][0], sendbuf[rank][1], sendbuf[rank][2], sendbuf[rank][3]);
    
    // Set up recvcounts array - each process gets one element
    for (int i = 0; i < SIZE; i++) {
        recvcounts[i] = 1;
    }
    
    // Perform reduce-scatter operation
    MPI_Reduce_scatter(sendbuf, recvbuf, recvcounts, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);

    // Print buffer after reduction
    printf("Rank %d after reduction - recvbuf[0]: %f\n", rank, recvbuf[0]);
    }
else
    printf("Must specify %d processors. Terminating.\n", SIZE);

MPI_Finalize();
}
