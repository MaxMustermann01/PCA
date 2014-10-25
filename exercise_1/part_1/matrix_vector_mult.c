/*********************************************************************************
 * FILENAME         matrix_vector_mult.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 1 - Implementation for the Matrix-Vector-Multiplication
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

void vMatrixVecMulInt(sMatrixInt *pM, sMatrixInt *pV, sMatrixInt *pVRes)
{
  int i,j;
  
  /* Multiplying matrix by vector (vector=matrix[x][0]) */
  for(i=0; i<pM->iRow; i++)
  {
    pVRes->ppaMat[i][0]=0;
    for(j=0; j<pM->iCol; j++)
      pVRes->ppaMat[i][0] += pM->ppaMat[i][j] * pV->ppaMat[j][0];
  }
}

void vMatrixVecMulDouble(sMatrixDouble *pM, sMatrixDouble *pV, sMatrixDouble *pVRes)
{
  int i,j;
  
  /* Multiplying matrix by vector (vector=matrix[x][0]) */
  for(i=0; i<pM->iRow; i++)
  {
    pVRes->ppaMat[i][0]=0;
    for(j=0; j<pM->iCol; j++)
      pVRes->ppaMat[i][0] += pM->ppaMat[i][j] * pV->ppaMat[j][0];
  }
}

void vMatrixVecMulFloat(sMatrixFloat *pM, sMatrixFloat *pV, sMatrixFloat *pVRes)
{
  int i,j;
  
  /* Multiplying matrix by vector (vector=matrix[x][0]) */
  for(i=0; i<pM->iRow; i++)
  {
    pVRes->ppaMat[i][0]=0;
    for(j=0; j<pM->iCol; j++)
      pVRes->ppaMat[i][0] += pM->ppaMat[i][j] * pV->ppaMat[j][0];
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
      pM->ppaMat[i][j]=rand();
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
