/*********************************************************************************
 * FILENAME         main.c
 * 
 * DESCRIPTION      These functions are part of the submission to exercises of 
 *                  the Parallel Computer Architecture (PCA) lecture of the 
 *                  University of Heidelberg.
 * 
 *                  Exercise 9 - functions for the Heat equation
 * 
 * AUTHORS          Shamna Shyju (shamnashyju@googlemail.com)
 *                  Fabian Finkeldey (Fabian@Finkeldey-hm.de)
 *                  Günther Schindler (G.Schindler@stud.uni-heidelberg.de)
 *
 * LAST CHANGE      14. Dez 2015
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

/*
 * DESCRIPTION - Inject Matrix with elements 
 * PARAMETER   - sMatrixInt: pointer to a sMatrix type in which should be injected
 *               int: diameter
 *               int: heat-Value
 * RETURN      - void 
 */
void vFillCircleMatrix(sMatrixDouble *, int, double);

/*
 * DESCRIPTION - Run the heat relaxation 
 * PARAMETER   - sMatrixInt: pointer to a sMatrix type in which should be injected
 * RETURN      - void 
 */
void vRelaxMatrix(sMatrixDouble *);

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

#endif
