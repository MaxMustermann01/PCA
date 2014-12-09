/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 6 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      09. Dec 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdint.h>
#include "matrix_vector_mult.h"
#include "time_measurement.h"

#define SEED 4

int main(int argc, char* argv[]){
  int iSize=0, iMode=0, j, iIterations;
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
  
    /* Start time-measurement, parallel multiply*/
    dStartTime = omp_get_wtime();
     
    /* Start multiplication */
    for(j = 0; j < iIterations; j++)
    {
      #pragma omp parallel num_threads(iNumThreads) 
      vMatrixVecMulIntPar(omp_get_thread_num());
    }
    
    /* Stop time-measurement, integer */
    dElapsedTimePar = (omp_get_wtime() - dStartTime) / iIterations;
  
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
    
    
  } else if(iMode==2) {
    /* Allocate memory for matrizen */
    vAllocMatrixInt(&Mat_Int, iSize, iSize);
    vAllocMatrixInt(&Vec_Int, iSize, 1);
    vAllocMatrixInt(&Res_Int, iSize, 1);
  
    /* Initialize matrizen with random numbers */
    vInitMatrixInt(&Mat_Int, SEED);
    vInitMatrixInt(&Vec_Int, SEED);
  
    /* Start time-measurement, parallel multiply*/
    dStartTime = omp_get_wtime();
     
    /* Start multiplication */
    for(j = 0; j < iIterations; j++)
    {
      #pragma omp parallel num_threads(iNumThreads) 
      vMatrixVecMulDoublePar(omp_get_thread_num());
    }
    
    /* Stop time-measurement, double */
    dElapsedTimePar = (omp_get_wtime() - dStartTime) / iIterations;
  
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
    
    
  } else if(iMode==3) {
    /* Allocate memory for matrizen */
    vAllocMatrixInt(&Mat_Int, iSize, iSize);
    vAllocMatrixInt(&Vec_Int, iSize, 1);
    vAllocMatrixInt(&Res_Int, iSize, 1);
  
    /* Initialize matrizen with random numbers */
    vInitMatrixInt(&Mat_Int, SEED);
    vInitMatrixInt(&Vec_Int, SEED);
  
    /* Start time-measurement, parallel multiply*/
    dStartTime = omp_get_wtime();
     
    /* Start multiplication */
    for(j = 0; j < iIterations; j++)
    {
      #pragma omp parallel num_threads(iNumThreads) 
      vMatrixVecMulFloatPar(omp_get_thread_num());
    }
    
    /* Stop time-measurement, float */
    dElapsedTimePar = (omp_get_wtime() - dStartTime) / iIterations;
  
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
  
  

  return EXIT_SUCCESS;
}