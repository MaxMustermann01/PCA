/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 8.3 - main function to measure the
 *                                 half-round-trip latency
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      10. Jan 2015
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>

#define MAX_SIZE 1048576    // 2^20
#define ITERATIONS 1000

int main(int argc, char* argv[])
{
  int size, rank, i, j;
  char *message;
  double starttime, endtime, elapsedtime;
  MPI_Status status;
  MPI_Request request;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
 
  if(size < 2)
  {
    printf("A minimum of 2 processes is required to measure the the HRT-Latency!\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  
  for(i = 1; i <= MAX_SIZE ; i*=2)
  {
    message = malloc(i * sizeof(char));
    
    if(rank == 0)
    {
      MPI_Barrier(MPI_COMM_WORLD);
      starttime = MPI_Wtime();
      
      for(j = 0; j < ITERATIONS; j++)
      {
        MPI_Isend(message, i, MPI_CHAR, 1, j, MPI_COMM_WORLD, &request);
	MPI_Wait(&request, &status);
	MPI_Irecv(message, i, MPI_CHAR, 1, j, MPI_COMM_WORLD, &request);
	MPI_Wait(&request, &status);
      }
      
      endtime = MPI_Wtime();
      elapsedtime = (endtime - starttime) / ITERATIONS;
      
      printf("Half-round-trip latency (%d Byte): %lf s \n", i, elapsedtime / 2);
    }
    else
    {
      MPI_Barrier(MPI_COMM_WORLD);
      
      for(j = 0; j < ITERATIONS; j++)
      {
        MPI_Irecv(message, i, MPI_CHAR, 0, j, MPI_COMM_WORLD, &request);
	MPI_Wait(&request, &status);
	MPI_Isend(message, i, MPI_CHAR, 0, j, MPI_COMM_WORLD, &request);
	MPI_Wait(&request, &status);
      }
    }
  }
  MPI_Finalize();
  return 0;
}
