/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 7 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      22. Dez 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdint.h>
#include "matrix.h"
#include "time_measurement.h"

#define SIZE 1024
#define DIAMETER 128
#define HEATVAL 66

int main(int argc, char* argv[]){
  int j, iIterations;
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
  index = 0;
  
    /* Allocate memory for grid */
  if(iAllocMatrixDouble(&sMgrid[0], SIZE, SIZE))
  {
    printf("ERROR: Allocation failure!");
    exit(1);
  }
  
  /* Allocate memory for temporary matrix */
  if(iAllocMatrixDouble(&sMgrid[1], SIZE, SIZE))
  {
    printf("ERROR: Allocation failure!");
    exit(1);
  }
  
  /* Initialize Grid */
  vFillCircleMatrix(&sMgrid[index], DIAMETER, HEATVAL);
  
  /* Start time-measurement, parallel multiply*/
  dStartTime = dstartMesGTOD();
  /* Start multiplication */
  for(j = 0; j < iIterations; j++)
  {
    #pragma omp parallel num_threads(iNumThreads)
    vRelaxMatrixPar(omp_get_thread_num());
      
    /* Barrier, to avoid race conditions */
    #pragma omp barrier
    index = 1 - index;
  }
  /* Stop time-measurement, integer */
  dElapsedTimePar = dstopMesGTOD(dStartTime) / iIterations;
  
  /* Write reslulting values in file, integer */
  printf("\n Time for calculation (per Iteration): \n");
  printf("\n Parallel       : %lfs \n", dElapsedTimePar);
  
  /* Initialize Grid */
  vFillCircleMatrix(&sMgrid[index], DIAMETER, HEATVAL);
    
  /* Start time-measurement for serial relaxation */
  dStartTime = dstartMesGTOD();
  for(j = 0; j < iIterations; j++)
  {
    vRelaxMatrixSer();
    index = 1 - index;
  }
  dElapsedTimeSer = dstopMesGTOD(dStartTime) / iIterations;
    
  printf(" Serial         : %lfs \n\n", dElapsedTimeSer);
  printf(" Iteration Rate : %lf per sec\n", 1/dElapsedTimePar);
  printf(" Speed-Up       : %lf \n", dElapsedTimeSer/dElapsedTimePar);
  
  /* Free Allocated Memory */
  vFreeMatrixDouble(&sMgrid[0]);
  vFreeMatrixDouble(&sMgrid[1]);
  return EXIT_SUCCESS;
}