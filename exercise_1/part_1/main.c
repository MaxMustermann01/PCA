/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 1 - main function for test
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      24. OKT 2014
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "matrix_vector_mult.h"
#include "time_measurement.h"
#include <unistd.h>

int main(int argc, char* argv[]){
  int iSeed=0;
  int iSize=0;
  sMatrixInt Mat_Int, Vec_Int, Res_Int;
  sMatrixDouble Mat_Double, Vec_Double, Res_Double;
  sMatrixFloat Mat_Float, Vec_Float, Res_Float;
  double dStartTime=0.0, dElapsedTime=0.0;
  
  /* Open a File for storing time-measurment-values */
  FILE * f = OpenTimeFile();
  
  /* Check integrity of arguments */
  if(argc!=3)
  {
    printf("\nWrong number of arguments. Check usage!"
           " \nmatrix_vector_mult <MATRIX_SIZE> <SEED>\n");
    return EXIT_FAILURE;
  }
  /* Convert C-String to int */
  iSize = atoi(argv[1]);
  iSeed = atoi(argv[2]);
  
  /* Allocate memory for matrizen */
  /* for integer */
  /* TODO: check integrity of memory allocation (it's important) */
  vAllocMatrixInt(&Mat_Int, iSize, iSize);
  vAllocMatrixInt(&Vec_Int, iSize, 1);
  vAllocMatrixInt(&Res_Int, iSize, 1);
  /* for double */
  vAllocMatrixDouble(&Mat_Double, iSize, iSize);
  vAllocMatrixDouble(&Vec_Double, iSize, 1);
  vAllocMatrixDouble(&Res_Double, iSize, 1);
  /* for float */
  vAllocMatrixFloat(&Mat_Float, iSize, iSize);
  vAllocMatrixFloat(&Vec_Float, iSize, 1);
  vAllocMatrixFloat(&Res_Float, iSize, 1);
  
  /* Initialize matrizen with random numbers */
  /* for integer */
  vInitMatrixInt(&Mat_Int, iSeed);
  vInitMatrixInt(&Vec_Int, iSeed);
  /* for double */
  vInitMatrixDouble(&Mat_Double, iSeed);
  vInitMatrixDouble(&Vec_Double, iSeed);
  /* for float */
  vInitMatrixFloat(&Mat_Float, iSeed);
  vInitMatrixFloat(&Vec_Float, iSeed);
  
  /* Start multiplication, measure time and write resulting value in file */
  /* integer */
  dStartTime = dstartMesGTOD();
  vMatrixVecMulInt(&Mat_Int, &Vec_Int, &Res_Int);
  dElapsedTime = dstopMesGTOD(dStartTime);
  writeTimeToFile(f,0,dElapsedTime);
  
  /* double */
  dStartTime = dstartMesGTOD();
  vMatrixVecMulDouble(&Mat_Double, &Vec_Double, &Res_Double);
  dElapsedTime = dstopMesGTOD(dStartTime);
  writeTimeToFile(f,1,dElapsedTime);
  
  /* float */
  dStartTime = dstartMesGTOD();
  vMatrixVecMulFloat(&Mat_Float, &Vec_Float, &Res_Float);
  dElapsedTime = dstopMesGTOD(dStartTime);
  writeTimeToFile(f,1,dElapsedTime);
  
  /* Free Allocated Memory */
  /* integer */
  vFreeMatrixInt(&Mat_Int);
  vFreeMatrixInt(&Vec_Int);
  vFreeMatrixInt(&Res_Int);
  /* double */
  vFreeMatrixDouble(&Mat_Double);
  vFreeMatrixDouble(&Vec_Double);
  vFreeMatrixDouble(&Res_Double);
  /* float */
  vFreeMatrixFloat(&Mat_Float);
  vFreeMatrixFloat(&Vec_Float);
  vFreeMatrixFloat(&Res_Float);
  
  return EXIT_SUCCESS;
}