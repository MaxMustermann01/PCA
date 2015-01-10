/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 8 - main function to test the MPI-Hello-World!
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      10. Jan 2015
 * 
 ********************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
  int size, rank;
  char hostname[50];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  gethostname(hostname, 50);
  printf("Hello World! I'm number %2d of %2d running on host %s\n",rank, size, hostname);
  MPI_Finalize();
  return 0;
}
