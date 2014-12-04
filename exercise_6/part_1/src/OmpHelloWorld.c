/*********************************************************************************
 * FILENAME         OmpHelloWorld.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 6 - Hello World OpenMP
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      04. DEC 2014
 * 
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  // Check Argument count
  if(argc == 2)
  {
    omp_set_num_threads(atoi(argv[1]));
    printf("\nThere are %d Threads active now \n", omp_get_max_threads());
    
    #pragma omp parallel
    {
      printf("Hello World (%d) \n", omp_get_thread_num());
    }

    return EXIT_SUCCESS;
  }
  else
  {
    printf("Wrong number of arguments. Please make sure you typed ./HelloWorld <IntNumberOfThreads>\n");
    return EXIT_FAILURE;
  }
  
  
  
}