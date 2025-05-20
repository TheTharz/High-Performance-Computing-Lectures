#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int loadtiff_(char *fileName, unsigned char *image, int *iw, int *ih);
extern int dumptiff_(char *fileName, unsigned char *image, int *w, int *h);

int
main(int argc, char *argv[])
{
  int width = 256, height = 256;
  int rank, comm_size, sum, my_sum;
  unsigned char pixels[65536];
  unsigned char recvbuf[65536];
  int numpixels, my_count;
  int i, val;
  double rms;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  

  if (rank == 0) {
    /* Load the Image */
    loadtiff_("irish.tif", pixels, &width, &height);
    numpixels = width * height;
 
    /* Calculate the number of pixels in each sub image */
    my_count = numpixels / comm_size;
    
    printf("Image loaded: %d x %d pixels (%d total)\n", width, height, numpixels);
    printf("Each process will handle %d pixels\n", my_count);
  }

  /* Broadcasts my_count to all the processes */
  MPI_Bcast(&my_count, 1, MPI_INT, 0, MPI_COMM_WORLD);

  /* Scatter the image into the recvbuf buffer*/
  MPI_Scatter(pixels, my_count, MPI_UNSIGNED_CHAR, recvbuf, my_count, MPI_UNSIGNED_CHAR,
              0, MPI_COMM_WORLD);

  /* Take the sum of the squares of the partial image */
  for (i = 0, my_sum = 0; i < my_count; i++)
    my_sum += recvbuf[i]*recvbuf[i];

  /* Find the global sum of the squares = sum */
  MPI_Allreduce(&my_sum, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  /* rank 0 calculates the root mean square */
  if (rank == 0) {
    rms = sqrt((double)sum / (double)numpixels);
    printf("RMS = %lf\n", rms);
  }

  /* Rank 0 broadcasts the RMS to the other nodes */
  MPI_Bcast(&rms, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  /* Do the contrast operation */
  for (i = 0; i < my_count; i++) {
    val = 2*recvbuf[i] - rms;
    if (val < 0)
      recvbuf[i] = 0;
    else if (val > 255)
      recvbuf[i] = 255;
    else
      recvbuf[i] = val;
  }

  /* Gather back to root */
  MPI_Gather(recvbuf, my_count, MPI_UNSIGNED_CHAR, pixels, my_count, MPI_UNSIGNED_CHAR,
             0, MPI_COMM_WORLD);

  /* Dump the Image */
  if (rank == 0) {
    dumptiff_("irish_new.tif", pixels, &width, &height);
    printf("Enhanced image saved as irish_new.tif\n");
  }

  MPI_Finalize();
  return 0;
}
