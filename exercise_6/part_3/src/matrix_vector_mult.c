/*********************************************************************************
 * FILENAME         matrix_vector_mult.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 6 - Implementation for the Matrix-Vector-Multiplication
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
#include <stdint.h>
#include "matrix_vector_mult.h"

void vMatrixVecMulIntSer(void)
{
  int i,j;
  for(i=0; i<Mat_Int.iRow; i++)
  {
    Res_Int.ppaMat[i][0]=0;
    for(j=0; j<Mat_Int.iCol; j++)
      Res_Int.ppaMat[i][0] += Mat_Int.ppaMat[i][j] * Vec_Int.ppaMat[j][0];
  }
}

void vMatrixVecMulIntPar(int s)
{
  int i,j;
  int iFrom = (s * Mat_Int.iRow)/iNumThreads;
  int iTo = ((s+1) * Mat_Int.iRow)/iNumThreads;
  
  for(i = iFrom; i < iTo; i++)
  {
    Res_Int.ppaMat[i][0]=0;
    for(j=0; j<Mat_Int.iCol; j++)
      Res_Int.ppaMat[i][0] += Mat_Int.ppaMat[i][j] * Vec_Int.ppaMat[j][0];
  }
}

void vMatrixVecMulDoubleSer(void)
{
  int i,j;
  
  /* Multiplying matrix by vector (vector=matrix[x][0]) */
  for(i=0; i<Mat_Double.iRow; i++)
  {
    Res_Double.ppaMat[i][0]=0;
    for(j=0; j<Mat_Double.iCol; j++)
      Res_Double.ppaMat[i][0] += Mat_Double.ppaMat[i][j] * Vec_Double.ppaMat[j][0];
  }
}

void vMatrixVecMulDoublePar(int s)
{
  int i,j;
  int iFrom = (s * Mat_Double.iRow)/iNumThreads;
  int iTo = ((s+1) * Mat_Double.iRow)/iNumThreads;
  
  /* Multiplying matrix by vector (vector=matrix[x][0]) */
  for(i = iFrom; i < iTo; i++)
  {
    Res_Double.ppaMat[i][0]=0;
    for(j=0; j<Mat_Double.iCol; j++)
      Res_Double.ppaMat[i][0] += Mat_Double.ppaMat[i][j] * Vec_Double.ppaMat[j][0];
  }
}

void vMatrixVecMulFloatSer(void)
{
  int i,j;
  
  /* Multiplying matrix by vector (vector=matrix[x][0]) */
  for(i=0; i<Mat_Float.iRow; i++)
  {
    Res_Float.ppaMat[i][0]=0;
    for(j=0; j<Mat_Float.iCol; j++)
      Res_Float.ppaMat[i][0] += Mat_Float.ppaMat[i][j] * Vec_Float.ppaMat[j][0];
  }
}

void vMatrixVecMulFloatPar(int s)
{
  int i,j;
  int iFrom = (s * Mat_Float.iRow)/iNumThreads;
  int iTo = ((s+1) * Mat_Float.iRow)/iNumThreads;
  
  /* Multiplying matrix by vector (vector=matrix[x][0]) */
  for(i = iFrom; i < iTo; i++)
  {
    Res_Float.ppaMat[i][0]=0;
    for(j=0; j<Mat_Float.iCol; j++)
      Res_Float.ppaMat[i][0] += Mat_Float.ppaMat[i][j] * Vec_Float.ppaMat[j][0];
  }
}

int vAllocMatrixInt(sMatrixInt *pM, int iRow, int iCol)
{ 
  int i=0, iRet=0;
  /* Init rows and cols in matrix structure */
  pM->iCol=iCol;
  pM->iRow=iRow;
  /* Alloc Mem for Rows-Pointer */
  pM->ppaMat = malloc(iRow * sizeof(int *));
  if(NULL == pM->ppaMat)
    iRet=1;
  /* Allocate Memory for Rows */
  for(i=0; i < iRow; i++)
  {
    pM->ppaMat[i] = malloc(iCol * sizeof(int *));
    if(NULL == pM->ppaMat[i])
      iRet=1;
  }
  return iRet;
}

int vAllocMatrixDouble(sMatrixDouble *pM, int iRow, int iCol)
{ 
  int i=0, iRet=0;
  /* Init rows and cols in matrix structure */
  pM->iCol=iCol;
  pM->iRow=iRow;
  /* Alloc Mem for Rows-Pointer */
  pM->ppaMat = malloc(iRow * sizeof(double *));
  if(NULL == pM->ppaMat)
    iRet=1;
  /* Allocate Memory for Rows */
  for(i=0; i < iRow; i++)
  {
    pM->ppaMat[i] = malloc(iCol * sizeof(double *));
    if(NULL == pM->ppaMat[i])
      iRet=1;
  }
  return iRet;
}

int vAllocMatrixFloat(sMatrixFloat *pM, int iRow, int iCol)
{ 
  int i=0, iRet=0;
  /* Init rows and cols in matrix structure */
  pM->iCol=iCol;
  pM->iRow=iRow;
  /* Alloc Mem for Rows-Pointer */
  pM->ppaMat = malloc(iRow * sizeof(float *));
  if(NULL == pM->ppaMat)
    iRet=1;
  /* Allocate Memory for Rows */
  for(i=0; i < iRow; i++)
  {
    pM->ppaMat[i] = malloc(iCol * sizeof(float *));
    if(NULL == pM->ppaMat[i])
      iRet=1;
  }
  return iRet;
}

void vFreeMatrixInt(sMatrixInt *pM)
{
  int i;
  /* free the Rows */
  for(i=0; i<pM->iRow; i++)
    free(pM->ppaMat[i]);
  /* free cols */
  free(pM->ppaMat);
}

void vFreeMatrixDouble(sMatrixDouble *pM)
{
  int i;
  /* free the Rows */
  for(i=0; i<pM->iRow; i++)
    free(pM->ppaMat[i]);
  /* free cols */
  free(pM->ppaMat);
}

void vFreeMatrixFloat(sMatrixFloat *pM)
{
  int i;
  /* free the Rows */
  for(i=0; i<pM->iRow; i++)
    free(pM->ppaMat[i]);
  /* free cols */
  free(pM->ppaMat);
}

void vInitMatrixInt(sMatrixInt *pM, int iSeed)
{
  int i,j;
  /* Initializes random number generator */
  srand((unsigned) iSeed);
  /* Fill the matrix-elements with random numbers */
  /* matrix[zeile][spalte] */
  for(i=0; i<pM->iRow; i++)
  {
    for(j=0; j<pM->iCol; j++)
      /* Generate numbers fronm 0 to 50 */
      pM->ppaMat[i][j]=rand()%20;
  }
}

void vInitMatrixDouble(sMatrixDouble *pM, int iSeed)
{
  int i,j;
  /* Initializes random number generator */
  srand((unsigned) iSeed);
  /* Fill the matrix-elements with random numbers */
  /* matrix[zeile][spalte] */
  for(i=0; i<pM->iRow; i++)
  {
    for(j=0; j<pM->iCol; j++)
      /* Generate numbers fronm 0 to 50 */
      pM->ppaMat[i][j]=(double)rand();
  }
}

void vInitMatrixFloat(sMatrixFloat *pM, int iSeed)
{
  int i,j;
  /* Initializes random number generator */
  srand((unsigned) iSeed);
  /* Fill the matrix-elements with random numbers */
  /* matrix[zeile][spalte] */
  for(i=0; i<pM->iRow; i++)
  {
    for(j=0; j<pM->iCol; j++)
      /* Generate numbers fronm 0 to 50 */
      pM->ppaMat[i][j]=(float)rand();
  }
}

void vPrintMatrixInt(sMatrixInt *pM)
{
  int i,j;
  /* matrix[zeile][spalte] */
  for(i=0; i<pM->iRow; i++)
  { 
    printf("\n");
    for(j=0; j<pM->iCol; j++)
      printf("%5d", pM->ppaMat[i][j]);
  }
  printf("\n");
}
