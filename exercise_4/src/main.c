/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 4 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      25. Nov 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include "matrix_vector_mult.h"
#include "time_measurement.h"

#define SEED 4

int main(int argc, char* argv[]){
  pthread_t * threads;    // pointer to a group of threads
  int iSize=0, iMode=0, i, j, k, iIterations;
  double dStartTime=0.0, dElapsedTimeSer=0.0, dElapsedTimePar=0.0;
  
  /* Check integrity of arguments */
  if(argc!=5)
  {
    printf("\nWrong number of arguments. Check usage!"
           " \nmat_mult <MATRIX_SIZE> <NUM_THREADS> <NUM_ITERATIONS> <MODE>\n");
    return EXIT_FAILURE;
  }
  /* Convert C-String to integer */
  iSize = atoi(argv[1]);
  iNumThreads = atoi(argv[2]);
  iIterations = atoi(argv[3]);
  iMode = atoi(argv[4]);
  
  if(iMode==1)
  {
    /* Allocate memory for matrizen */
    vAllocMatrixInt(&Mat_Int, iSize, iSize);
    vAllocMatrixInt(&Vec_Int, iSize, 1);
    vAllocMatrixInt(&Res_Int, iSize, 1);
  
    /* Initialize matrizen with random numbers */
    vInitMatrixInt(&Mat_Int, SEED);
    vInitMatrixInt(&Vec_Int, SEED);
  
    /* Allocate memory for the thread-pointer */
    threads = (pthread_t *) malloc(iNumThreads*sizeof(pthread_t));
  
    /* Start time-measurement, parallel multiply*/
    dStartTime = dstartMesGTOD();
    /* Start multiplication */
    for(j = 0; j < iIterations; j++)
    {
      for(i = 1; i < iNumThreads; i++)
      {
        if(pthread_create(&threads[i], NULL, (void *)vMatrixVecMulIntPar, (void *) (intptr_t)i) != 0)
        {
          printf("ERROR: Couldn't create thread\n");
          free(threads);
          vFreeMatrixInt(&Mat_Int);
          vFreeMatrixInt(&Vec_Int);
          vFreeMatrixInt(&Res_Int);
          exit(-1);
        }
      }
      /* Main thread works on slice 0 */
      vMatrixVecMulIntPar(0);
      /* Main thread waiting for other threads to complete */
      for(k = 1; k < iNumThreads; k++)
        pthread_join(threads[k], NULL);
    }
    /* Stop time-measurement, integer */
    dElapsedTimePar = dstopMesGTOD(dStartTime) / iIterations;
  
    /* Write reslulting values in file, integer */
    printf("\n Time for calculation (Intger): \n");
    printf("\n Parallel : %lfs \n", dElapsedTimePar);
    
    /* Start time-measurement, parallel multiply*/
    dStartTime = dstartMesGTOD();
    for(j = 0; j < iIterations; j++)
      vMatrixVecMulIntSer();
    dElapsedTimeSer = dstopMesGTOD(dStartTime) / iIterations;
    
    printf(" Seriell  : %lfs \n", dElapsedTimeSer);
    printf(" Speed-Up : %lf \n", dElapsedTimeSer/dElapsedTimePar);
    /* Free Allocated Memory */
    vFreeMatrixInt(&Mat_Int);
    vFreeMatrixInt(&Vec_Int);
    vFreeMatrixInt(&Res_Int);
  }
  else if (iMode == 2)
  {
    /* Allocate memory for matrizen */
    vAllocMatrixDouble(&Mat_Double, iSize, iSize);
    vAllocMatrixDouble(&Vec_Double, iSize, 1);
    vAllocMatrixDouble(&Res_Double, iSize, 1);
  
    /* Initialize matrizen with random numbers */
    vInitMatrixDouble(&Mat_Double, SEED);
    vInitMatrixDouble(&Vec_Double, SEED);
  
    /* Allocate memory for the thread-pointer */
    threads = (pthread_t *) malloc(iNumThreads*sizeof(pthread_t));
  
    /* Start time-measurement, parallel multiply*/
    dStartTime = dstartMesGTOD();
    /* Start multiplication */
    for(j = 0; j < iIterations; j++)
    {
      for(i = 1; i < iNumThreads; i++)
      {
        if(pthread_create(&threads[i], NULL, (void *)vMatrixVecMulDoublePar, (void *) (intptr_t)i) != 0)
        {
          printf("ERROR: Couldn't create thread\n");
          free(threads);
          vFreeMatrixDouble(&Mat_Double);
          vFreeMatrixDouble(&Vec_Double);
          vFreeMatrixDouble(&Res_Double);
          exit(-1);
        }
      }
      /* Main thread works on slice 0 */
      vMatrixVecMulDoublePar(0);
      /* Main thread waiting for other threads to complete */
      for(k = 1; k < iNumThreads; k++)
        pthread_join(threads[k], NULL);
    }
    /* Stop time-measurement */
    dElapsedTimePar = dstopMesGTOD(dStartTime) / iIterations;
  
    /* Write reslulting values in file */
    printf("\n Time for calculation (Double): \n");
    printf("\n Parallel : %lfs \n", dElapsedTimePar);
    
    /* Start time-measurement, parallel multiply*/
    dStartTime = dstartMesGTOD();
    for(j = 0; j < iIterations; j++)
      vMatrixVecMulDoubleSer();
    dElapsedTimeSer = dstopMesGTOD(dStartTime) / iIterations;
    
    printf(" Seriell  : %lfs \n", dElapsedTimeSer);
    printf(" Speed-Up : %lf \n", dElapsedTimeSer/dElapsedTimePar);
    /* Free Allocated Memory */
    vFreeMatrixDouble(&Mat_Double);
    vFreeMatrixDouble(&Vec_Double);
    vFreeMatrixDouble(&Res_Double);
  }
  else if (iMode == 3)
  {
    /* Allocate memory for matrizen */
    vAllocMatrixFloat(&Mat_Float, iSize, iSize);
    vAllocMatrixFloat(&Vec_Float, iSize, 1);
    vAllocMatrixFloat(&Res_Float, iSize, 1);
  
    /* Initialize matrizen with random numbers */
    vInitMatrixFloat(&Mat_Float, SEED);
    vInitMatrixFloat(&Vec_Float, SEED);
  
    /* Allocate memory for the thread-pointer */
    threads = (pthread_t *) malloc(iNumThreads*sizeof(pthread_t));
  
    /* Start time-measurement, parallel multiply*/
    dStartTime = dstartMesGTOD();
    /* Start multiplication */
    for(j = 0; j < iIterations; j++)
    {
      for(i = 1; i < iNumThreads; i++)
      {
        if(pthread_create(&threads[i], NULL, (void *)vMatrixVecMulFloatPar, (void *) (intptr_t)i) != 0)
        {
          printf("ERROR: Couldn't create thread\n");
          free(threads);
          vFreeMatrixFloat(&Mat_Float);
          vFreeMatrixFloat(&Vec_Float);
          vFreeMatrixFloat(&Res_Float);
          exit(-1);
        }
      }
      /* Main thread works on slice 0 */
      vMatrixVecMulFloatPar(0);
      /* Main thread waiting for other threads to complete */
      for(k = 1; k < iNumThreads; k++)
        pthread_join(threads[k], NULL);
    }
    /* Stop time-measurement */
    dElapsedTimePar = dstopMesGTOD(dStartTime) / iIterations;
  
    /* Write reslulting values in file */
    printf("\n Time for calculation (Float): \n");
    printf("\n Parallel : %lfs \n", dElapsedTimePar);
    
    /* Start time-measurement, parallel multiply*/
    dStartTime = dstartMesGTOD();
    for(j = 0; j < iIterations; j++)
      vMatrixVecMulFloatSer();
    dElapsedTimeSer = dstopMesGTOD(dStartTime) / iIterations;
    
    printf(" Seriell  : %lfs \n", dElapsedTimeSer);
    printf(" Speed-Up : %lf \n", dElapsedTimeSer/dElapsedTimePar);
    /* Free Allocated Memory */
    vFreeMatrixFloat(&Mat_Float);
    vFreeMatrixFloat(&Vec_Float);
    vFreeMatrixFloat(&Res_Float);
  }
  else
  {
    printf("ERROR: Wrong option (1) Integer, (2) Double, (3) Float\n");
  }
  return EXIT_SUCCESS;
}