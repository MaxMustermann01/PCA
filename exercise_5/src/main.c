/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 5 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      29. Nov 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include "matrix.h"
#include "time_measurement.h"

#define SIZE 1024
#define DIAMETER 128
#define HEATVAL 66

int main(int argc, char* argv[]){
  pthread_t * threads;    // pointer to a group of threads
  int i, j, k, iIterations;
  double dStartTime=0.0, dElapsedTimeSer=0.0, dElapsedTimePar=0.0;
  
  /* Check integrity of arguments */
  if(argc!=3)
  {
    printf("\nWrong number of arguments. Check usage!"
           " \nrelaxation <NUM_THREADS> <NUM_ITERATIONS>\n");
    return EXIT_FAILURE;
  }
  /* Convert C-String to integer */
  iNumThreads = atoi(argv[1]);
  iIterations = atoi(argv[2]);
  
    /* Allocate memory for grid */
  if(iAllocMatrixDouble(&sMgrid, SIZE, SIZE))
  {
    printf("ERROR: Allocation failure!");
    exit(1);
  }
  
  /* Allocate memory for temporary matrix */
  if(iAllocMatrixDouble(&sMTmp, SIZE, SIZE))
  {
    printf("ERROR: Allocation failure!");
    exit(1);
  }
  
  /* Allocate memory for the thread-pointer */
  threads = (pthread_t *) malloc(iNumThreads*sizeof(pthread_t));
  
  /* Initialize Grid */
  vFillCircleMatrix(&sMgrid, DIAMETER, HEATVAL);
  
  /* Start time-measurement, parallel multiply*/
  dStartTime = dstartMesGTOD();
  /* Start multiplication */
  for(j = 0; j < iIterations; j++)
  {
    /* Copy each matrix element in the temporary matrix */
    for(i=0; i<sMgrid.iRow; i++)
      for(k=0; k<sMgrid.iCol; k++)
        sMTmp.ppaMat[i][k]=sMgrid.ppaMat[i][k];
    
    for(i = 1; i < iNumThreads; i++)
    {
      if(pthread_create(&threads[i], NULL, (void *)vRelaxMatrixPar, (void *) (intptr_t)i) != 0)
      {
        printf("ERROR: Couldn't create thread\n");
        free(threads);
        exit(-1);
      }
    }
    /* Main thread works on slice 0 */
    vRelaxMatrixPar(0);
    /* Main thread waiting for other threads to complete */
    for(k = 1; k < iNumThreads; k++)
      pthread_join(threads[k], NULL);
  }
  /* Stop time-measurement, integer */
  dElapsedTimePar = dstopMesGTOD(dStartTime) / iIterations;
  
  /* Write reslulting values in file, integer */
  printf("\n Time for calculation (per Iteration): \n");
  printf("\n Parallel       : %lfs \n", dElapsedTimePar);
  
  /* Initialize Grid */
  vFillCircleMatrix(&sMgrid, DIAMETER, HEATVAL);
    
  /* Start time-measurement for serial relaxation */
  dStartTime = dstartMesGTOD();
  for(j = 0; j < iIterations; j++)
    vRelaxMatrixSer();
  dElapsedTimeSer = dstopMesGTOD(dStartTime) / iIterations;
    
  printf(" Serial         : %lfs \n\n", dElapsedTimeSer);
  printf(" Iteration Rate : %lf per sec\n", 1/dElapsedTimePar);
  printf(" Speed-Up       : %lf \n", dElapsedTimeSer/dElapsedTimePar);
  
  /* Free Allocated Memory */
  vFreeMatrixDouble(&sMgrid);
  vFreeMatrixDouble(&sMTmp);
  return EXIT_SUCCESS;
}