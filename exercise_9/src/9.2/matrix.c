/*********************************************************************************
 * FILENAME         matrix.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 9 - functions for the grid handling
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      14. Dez 2015
 * 
 ********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

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

void vRelaxMatrix(sMatrixDouble *pM)
{
  int i,j;
  sMatrixDouble sMTmp;
  /* Allocate memory for temporary matrix */
  if(iAllocMatrixDouble(&sMTmp, pM->iRow, pM->iCol))
  {
    printf("DEBUG: Allocation failure!");
    exit(1);
  }
  /* Copy each matrix element in the temporary matrix */
  for(i=0; i<pM->iRow; i++)
    for(j=0; j<pM->iCol; j++)
      sMTmp.ppaMat[i][j]=pM->ppaMat[i][j];
  /* Calculate new grid points */
  for(i=0; i<pM->iRow; i++)
    for(j=0; j<pM->iCol; j++)
    {
      /* Set boundary points to 0.0 */
      if(i==0  || i==pM->iRow-1 || j==0 || j==pM->iCol-1)
        pM->ppaMat[i][j]=0.0;
      else
      {
	pM->ppaMat[i][j]=sMTmp.ppaMat[i][j];
	pM->ppaMat[i][j]+=FI*((-4)*sMTmp.ppaMat[i][j]+sMTmp.ppaMat[i+1][j]+sMTmp.ppaMat[i-1][j]+sMTmp.ppaMat[i][j+1]+sMTmp.ppaMat[i][j-1]);
      }
    }
  /* Delete temporary matrix again */
  vFreeMatrixDouble(&sMTmp);
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
