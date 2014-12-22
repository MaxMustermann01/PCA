/*********************************************************************************
 * FILENAME         matrix.h
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 7 - Header-File the Matrix-handling
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      22. Dez 2014
 * 
 ********************************************************************************/
#ifndef MATRIX_H
#define MATRIX_H

#define FI 0.24

typedef struct sMatrixDouble
{
  int iRow;       // for rows
  int iCol;       // for columns
  double** ppaMat;   // int[][]
} sMatrixDouble;

/* Global variables */
int iNumThreads, index;;
sMatrixDouble sMgrid[2]; //, sMTmp;

/*
 * DESCRIPTION - does the relaxion, serial
 * PARAMETER   -
 *
 * RETURN      - void 
 */
void vRelaxMatrixSer(void);

/*
 * DESCRIPTION - does the relaxion, parallel
 * PARAMETER   - void
 *
 * RETURN      - void 
 */
void vRelaxMatrixPar(int);

/*
 * DESCRIPTION - Fill up a circle with numbers and with a given diameter.
 * PARAMETER   - sMatrixInt: pointer to a sMatrix type in which the circle should
 *                           be drawn
 *               integer   : size of the diameter
 *               double    : used value to fill the circle
 * RETURN       - void 
 */
void vFillCircleMatrix(sMatrixDouble *, int, double);

/*
 * DESCRIPTION - Allocate memory for the dynamic matrix;
 * PARAMETER   - sMatrixInt: pointer to a sMatrix type for which the memory will be allocated
 *             - Integer: matrix rows
 *             - Integer: matrix columns
 * RETURN       - Integer: 0 if alloc was ok, 1 if alloc failed 
 */
int iAllocMatrixDouble(sMatrixDouble *,int, int);

/*
 * DESCRIPTION - will free the allocated memory;
 * PARAMETER   - pointer to type sMatrix, which should be destroid
 * RETURN      - void
 */
void vFreeMatrixDouble(sMatrixDouble *);
/*
 * DESCRIPTION - prints the matrix-elements;
 * PARAMETER   - pointer to matrix, which should be printed
 * RETURN      - void
 */
void vPrintMatrixDouble(sMatrixDouble *);
/*
 * DESCRIPTION - initialize a matrix with random numbers;
 * PARAMETER   - pointer to matrix...
 *               integer for seed
 * RETRUN      - void
 */
void vInitMatrixDouble(sMatrixDouble *, int);

#endif
