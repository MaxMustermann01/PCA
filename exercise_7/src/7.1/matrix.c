/*********************************************************************************
 * FILENAME         matrix.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 7 - Implementation for the Matrix-handling
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
#include <stdint.h>
#include "matrix.h"

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

int iAllocMatrixDouble(sMatrixDouble *pM, int iRow, int iCol)
{ 
  int i=0, iRet=0;
  double * pdtmp;
  /* Init rows and cols in matrix structure */
  pM->iCol=iCol;
  pM->iRow=iRow;
  /* Alloc Mem for Rows-Pointer */
  pM->ppaMat = malloc(iRow * sizeof(double *));
  if(NULL == pM->ppaMat)
    iRet=1;
  pdtmp = (double *)malloc(iRow * iCol *sizeof(double));
  /* Allocate Memory for Rows */
  for(i=0; i < iRow; i++)
  {
    // pM->ppaMat[i] = malloc(iCol * sizeof(double *));
    /* make it contiguous in memory */
    pM->ppaMat[i] = pdtmp + (i*iCol);
    if(NULL == pM->ppaMat[i])
      iRet=1;
  }
  return iRet;
}

void vRelaxMatrixSer()
{
  int i,j;
  
  /* Calculate new grid points */
  for(i=0; i<sMgrid[index].iRow; i++)
    for(j=0; j<sMgrid[index].iCol; j++)
    {
      /* Ignore boundary points */
      if(!(i==0  || i==sMgrid[index].iRow-1 || j==0 || j==sMgrid[index].iCol-1))
      {
        sMgrid[1-index].ppaMat[i][j]=sMgrid[index].ppaMat[i][j];
        sMgrid[1-index].ppaMat[i][j]+=FI*((-4)*sMgrid[index].ppaMat[i][j] \
                           +sMgrid[index].ppaMat[i+1][j]+sMgrid[index].ppaMat[i-1][j] \
                           +sMgrid[index].ppaMat[i][j+1]+sMgrid[index].ppaMat[i][j-1]);
      }
    }
}

void vRelaxMatrixPar(int slice)
{
  int i,j;
  int s = slice;
  int iFrom = (s * sMgrid[index].iRow)/iNumThreads;
  int iTo = ((s+1) * sMgrid[index].iRow)/iNumThreads;

  /* Calculate new grid points */
  for(i = iFrom; i < iTo; i++)
    for(j=0; j<sMgrid[index].iCol; j++)
    {
      /* Ignore boundary points */
      if(!(i==0  || i==sMgrid[index].iRow-1 || j==0 || j==sMgrid[index].iCol-1))
      {
        sMgrid[1-index].ppaMat[i][j]=sMgrid[index].ppaMat[i][j];
        sMgrid[1-index].ppaMat[i][j]+=FI*((-4)*sMgrid[index].ppaMat[i][j] \
                           +sMgrid[index].ppaMat[i+1][j]+sMgrid[index].ppaMat[i-1][j] \
                           +sMgrid[index].ppaMat[i][j+1]+sMgrid[index].ppaMat[i][j-1]);
      }
    }
}


void vFillCircleMatrix(sMatrixDouble *pM, int iDiameter, double dValue)
{
  int i,j,x,y,a,b, iRadius;
  
  x=pM->iCol / 2;
  y=pM->iRow / 2;
  iRadius = iDiameter / 2;
  
  for(i=0; i<pM->iRow; i++)
  {
    for(j=0; j<pM->iCol; j++)
    {
      a = i-x;
      b = j-y;
      /* Set boundary points to 0.0 */
      if(i==0  || i==pM->iRow-1 || j==0 || j==pM->iCol-1)
        pM->ppaMat[i][j]=0.0;
      else if((a*a+b*b)<=(iRadius*iRadius))
	pM->ppaMat[i][j]=dValue;
    }
  }
}

void vFreeMatrixDouble(sMatrixDouble *pM)
{
  free(pM->ppaMat[0]);
  free(pM->ppaMat);
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
      pM->ppaMat[i][j]=(double) (rand()%20);
  }
}

void vPrintMatrixDouble(sMatrixDouble *pM)
{
  int i,j;
  /* matrix[zeile][spalte] */
  for(i=0; i<pM->iRow; i++)
  { 
    printf("\n");
    for(j=0; j<pM->iCol; j++)
      printf("%6.1lf", pM->ppaMat[i][j]);
  }
  printf("\n");
}
